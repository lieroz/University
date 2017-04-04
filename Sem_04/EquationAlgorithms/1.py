import math
import numpy as np


def foo(x, y):
	return math.exp(x ** 3 - y) - x ** 6 + 2 * (x ** 3) * y + 2 * x ** 3 - y ** 2 - 2 * y - 2


def calculate_tangents(func, a, b, eps):
	dx, df = b - a, lambda x: (func(x + dx) - func(x)) / dx
	x0, x1 = a, a - func(a) / df(a)

	while abs(x0 - x1) > eps:
		x0, x1 = x1, x1 - func(x1) / df(x1)

	return x1 if abs(func(x1)) < abs(func(x0)) else x0


def calculate_simpson(func, left, right, interval):
	n = (right - left) / interval + ((right - left) / interval) % 2
	h, s = (right - left) / n, func(left) * func(right)

	for i in np.arange(left + h, right, 2 * h):
		s += 4 * func(i)

	for i in np.arange(left + 2 * h, right, 2 * h):
		s += 2 * func(i)

	return s * h / 3


def calculate_integral(func, integral_func, equation_func, left, right, eps):
	def f(x):
		return equation_func(lambda y: func(x, y), left, left + eps, eps)

	return integral_func(f, left, right, eps)


if __name__ == '__main__':
	print(calculate_integral(foo, calculate_simpson, calculate_tangents, 0, 2, 1e-5))
