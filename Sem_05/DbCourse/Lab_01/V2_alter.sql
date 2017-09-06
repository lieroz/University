ALTER TABLE Travels.dbo.users
  ADD PRIMARY KEY (id);

ALTER TABLE Travels.dbo.users
  ADD UNIQUE (email);

ALTER TABLE Travels.dbo.locations
  ADD PRIMARY KEY (id);

ALTER TABLE Travels.dbo.locations
  ADD UNIQUE (country, place);

ALTER TABLE Travels.dbo.visits
  ADD PRIMARY KEY (id);

ALTER TABLE Travels.dbo.ulv
  ADD FOREIGN KEY (u_id) REFERENCES users (id);

ALTER TABLE Travels.dbo.ulv
  ADD FOREIGN KEY (l_id) REFERENCES locations (id);

ALTER TABLE Travels.dbo.ulv
  ADD FOREIGN KEY (v_id) REFERENCES visits (id);