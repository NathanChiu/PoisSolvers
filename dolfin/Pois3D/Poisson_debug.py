#!/usr/bin/env python
from ufl import *
set_level(DEBUG)
# Copyright (C) 2005-2009 Anders Logg
#
# This file is part of DOLFIN.
#
# DOLFIN is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# DOLFIN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
#
# First added:  2005
# Last changed: 2011-03-08
#
# The bilinear form a(u, v) and linear form L(v) for
# Poisson's equation.
#
# Compile this form with FFC: ffc -l dolfin Poisson.ufl.


V = FiniteElement("Lagrange", tetrahedron, 1)
R = FiniteElement("R", tetrahedron, 0)
element = V * R
#element = FiniteElement("Lagrange", triangle, 1)
#V = element
#R = element


(u, c) = TrialFunctions(element)
(v, d) = TestFunctions(element)
f = Coefficient(element)
g = Coefficient(element)

a = (inner(grad(u), grad(v)) + c*v + u*d )*dx
L = f*v*dx + g*v*ds
