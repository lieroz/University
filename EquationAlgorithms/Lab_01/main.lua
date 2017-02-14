--
-- Created by IntelliJ IDEA.
-- User: lieroz
-- Date: 14.02.17
-- Time: 18:56
-- To change this template use File | Settings | File Templates.
--

--[[
--F(x, y) = e^(x^3 - y) + x^6 + 2*(x^3)*y + 2*x^3 - y^2 - 2*y - 2
--]]

local foo = function(x, y)
    return math.exp(x^3 - y) - x^6 + 2*(x^3)*y + 2*x^3 - y^2 - 2*y - 2
end

local calc_tangents = function(func, a, b, eps)
    local dx = b - a
    local df = function(x) return (func(x + dx) - func(x)) / dx end
    local x1 = a - func(a) / df(a)
    local x0 = a

    while math.abs(x0 - x1) > eps do
        x0 = x1
        x1 = x1 - func(x1) / df(x1)
    end

    if math.abs(func(x1)) < math.abs(func(x0)) then return x1 else return x0 end
end

local calc_simpson = function(func, left, right, interval)
    local n = (right - left) / interval
    n = n + (n % 2)

    local h = (right - left) / n
    local s = func(left) * func(right)
    local double_h = 2 * h

    for i = left + h, right, double_h do
        s = s + 4 * func(i)
    end

    for i = left + double_h, right, double_h do
        s = s + 2 * func(i)
    end

    return s * h / 3
end

local calc_integral = function(func, integral_func, equation_func, left, right, eps)
    local Y = function(x)
        local section = function(y) return func(x, y) end
        return equation_func(section, left, left + eps, eps)
    end

    return integral_func(Y, left, right, eps)
end

print(calc_integral(foo, calc_simpson, calc_tangents, 0, 2, 1e-6))