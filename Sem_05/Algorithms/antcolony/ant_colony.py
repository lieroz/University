from threading import Thread


class AntColony:
    """Class describing ant colony."""

    class Ant(Thread):
        """Class describing single ant object. Derives from Thread."""

        def __init__(self, init_location, possible_locations, pheromone_map,
                     distance_callback, alpha, beta, first_pass=False):
            """Constructor."""
            Thread.__init__(self)

            self.init_location = init_location
            self.possible_locations = possible_locations
            self.route = []
            self.distance_traveled = 0.0
            self.location = init_location
            self.pheromone_map = pheromone_map
            self.distance_callback = distance_callback
            self.alpha = alpha
            self.beta = beta
            self.first_pass = first_pass

            self._update_route(init_location)

            self.tour_complete = False

        def run(self):
            """"Overrided method for Thread class to start."""
            while self.possible_locations:
                next = self._pick_path()
                self._traverse(self.location, next)

            self.tour_complete = True

        def _pick_path(self):
            if self.first_pass:
                import random
                return random.choice(self.possible_locations)

            attractiveness = dict()
            sum_total = 0.0
            for possible_next_location in self.possible_locations:
                pheromone_amount = float(self.pheromone_map[self.location][
                                         possible_next_location])
                distance = float(self.distance_callback(
                    self.location, possible_next_location))

                attractiveness[possible_next_location] = pow(
                    pheromone_amount, self.alpha) * pow(1 / distance, self.beta)
                sum_total += attractiveness[possible_next_location]

            if sum_total == 0.0:
                def next_up(x):
                    import math
                    import struct

                    if math.isnan(x) or (math.isinf(x) and x > 0):
                        return x

                    if x == 0.0:
                        x = 0.0

                    n = struct.unpack('<q', struct.pack('<d', x))[0]

                    if n >= 0:
                        n += 1
                    else:
                        n -= 1
                    return struct.unpack('<d', struct.pack('<q', n))[0]

                for key in attractiveness:
                    attractiveness[key] = next_up(attractiveness[key])
                sum_total = next_up(sum_total)

            import random
            toss = random.random()

            cummulative = 0
            for possible_next_location in attractiveness:
                weight = (attractiveness[possible_next_location] / sum_total)
                if toss <= weight + cummulative:
                    return possible_next_location
                cummulative += weight

        def _traverse(self, start, end):
            self._update_route(end)
            self._update_distance_traveled(start, end)
            self.location = end

        def _update_route(self, new):
            self.route.append(new)
            self.possible_locations.remove(new)

        def _update_distance_traveled(self, start, end):
            self.distance_traveled += float(self.distance_callback(start, end))

        def get_route(self):
            """Return complete route."""
            if self.tour_complete:
                return self.route
            return None

        def get_distance_traveled(self):
            """Return traveled distance."""
            if self.tour_complete:
                return self.distance_traveled
            return None

    def __init__(self, nodes, distance_callback, start=None, ant_count=50,
                 alpha=.5, beta=1.2, pheromone_evaporation_coefficient=.40,
                 pheromone_constant=1000.0, iterations=80):
        """Constructor."""
        if type(nodes) is not dict:
            raise TypeError("nodes must be dict")

        if len(nodes) < 1:
            raise ValueError("there must be at least one node in dict nodes")

        self.id_to_key, self.nodes = self._init_nodes(nodes)
        self.distance_matrix = self._init_matrix(len(nodes))
        self.pheromone_map = self._init_matrix(len(nodes))
        self.ant_updated_pheromone_map = self._init_matrix(len(nodes))

        if not callable(distance_callback):
            raise TypeError(
                "distance_callback is not callable, should be method")

        self.distance_callback = distance_callback

        if start is None:
            self.start = 0
        else:
            self.start = None
            for key, value in self.id_to_key.items():
                if value == start:
                    self.start = key

            if self.start is None:
                raise KeyError("Key: " + str(start) +
                               " not found in the nodes dict passed.")

        if type(ant_count) is not int:
            raise TypeError("ant_count must be int")

        if ant_count < 1:
            raise ValueError("ant_count must be >= 1")

        self.ant_count = ant_count

        if (type(alpha) is not int) and type(alpha) is not float:
            raise TypeError("alpha must be int or float")

        if alpha < 0:
            raise ValueError("alpha must be >= 0")

        self.alpha = float(alpha)

        if (type(beta) is not int) and type(beta) is not float:
            raise TypeError("beta must be int or float")

        if beta < 1:
            raise ValueError("beta must be >= 1")

        self.beta = float(beta)

        if (type(pheromone_evaporation_coefficient) is not int) and (
                type(pheromone_evaporation_coefficient) is not float):
            raise TypeError(
                "pheromone_evaporation_coefficient must be int or float")

        self.pheromone_evaporation_coefficient = float(
            pheromone_evaporation_coefficient)

        if (type(pheromone_constant) is not int) and (
                type(pheromone_constant) is not float):
            raise TypeError("pheromone_constant must be int or float")

        self.pheromone_constant = float(pheromone_constant)

        if (type(iterations) is not int):
            raise TypeError("iterations must be int")

        if iterations < 0:
            raise ValueError("iterations must be >= 0")

        self.iterations = iterations

        self.first_pass = True
        self.ants = self._init_ants(self.start)
        self.shortest_distance = None
        self.shortest_path_seen = None

    def _get_distance(self, start, end):
        if not self.distance_matrix[start][end]:
            distance = self.distance_callback(
                self.nodes[start], self.nodes[end])

            if (type(distance) is not int) and (type(distance) is not float):
                raise TypeError(
                    "distance_callback should return either int or float, saw: {}"
                    .format(distance))

            self.distance_matrix[start][end] = float(distance)
            return distance
        return self.distance_matrix[start][end]

    def _init_nodes(self, nodes):
        id_to_key = dict()
        id_to_values = dict()

        id = 0
        for key in sorted(nodes.keys()):
            id_to_key[id] = key
            id_to_values[id] = nodes[key]
            id += 1

        return id_to_key, id_to_values

    def _init_matrix(self, size, value=0.0):
        ret = []
        for row in range(size):
            ret.append([float(value) for x in range(size)])
        return ret

    def _init_ants(self, start):
        if self.first_pass:
            return [self.Ant(start, self.nodes.keys(), self.pheromone_map,
                             self._get_distance, self.alpha, self.beta,
                             first_pass=True) for x in range(self.ant_count)]
        for ant in self.ants:
            ant.__init__(start, self.nodes.keys(), self.pheromone_map,
                         self._get_distance, self.alpha, self.beta)

    def _update_pheromone_map(self):
        for start in range(len(self.pheromone_map)):
            for end in range(len(self.pheromone_map)):
                self.pheromone_map[start][end] = (
                    1 - self.pheromone_evaporation_coefficient) * (
                    self.pheromone_map[start][end])

                self.pheromone_map[start][
                    end] += self.ant_updated_pheromone_map[start][end]

    def _populate_ant_updated_pheromone_map(self, ant):
        route = ant.get_route()
        for i in range(len(route) - 1):
            current_pheromone_value = float(
                self.ant_updated_pheromone_map[route[i]][route[i + 1]])

            new_pheromone_value = (
                self.pheromone_constant / ant.get_distance_traveled())

            self.ant_updated_pheromone_map[route[i]][
                route[i + 1]] = current_pheromone_value + new_pheromone_value
            self.ant_updated_pheromone_map[
                route[i + 1]][route[i]] = (
                    current_pheromone_value + new_pheromone_value)

    def mainloop(self):
        """Define algorithm mainloop."""
        for _ in range(self.iterations):
            for ant in self.ants:
                ant.start()

            for ant in self.ants:
                ant.join()

            for ant in self.ants:
                self._populate_ant_updated_pheromone_map(ant)

                if not self.shortest_distance:
                    self.shortest_distance = ant.get_distance_traveled()

                if not self.shortest_path_seen:
                    self.shortest_path_seen = ant.get_route()

                if ant.get_distance_traveled() < self.shortest_distance:
                    self.shortest_distance = ant.get_distance_traveled()
                    self.shortest_path_seen = ant.get_route()

            self._update_pheromone_map()

            if self.first_pass:
                self.first_pass = False

            self._init_ants(self.start)

            self.ant_updated_pheromone_map = self._init_matrix(
                len(self.nodes), value=0)

        ret = []
        for id in self.shortest_path_seen:
            ret.append(self.id_to_key[id])

        return ret
