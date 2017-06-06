To be used as a collection of numerical solvers of the Poisson's equation
using various implementations.

Dolfin
  Uses the FEniCS library to build a mesh, set up a PDE, and solve the equation.
  Demo code implements a 2D solver, and modifications need to be made to extend
  the demo's functionality to a 3D solver.

multigrid
  Implements a multigrid algorithm to solve the Poisson's equation.

PoisFFT
  Uses the fftw library to implement a Fourier transform based solver. This solution is used to verify the simple case for poissonsolver below.

poissonsolver
  Uses the Successive Over-relaxation method to solve a generalised Poisson's equation. The generalised equation takes into account variable permittivity, and allows for electrodes to be arbitrarily placed within the solving range.
