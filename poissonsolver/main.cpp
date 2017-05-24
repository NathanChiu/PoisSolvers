#include <iostream>
#include "./src/solver.h"

int main() {
/*
    poisson1DJacobi();
    poisson1DGaussSeidel();
    poisson1DSOR();
*/
    //Parameters
    int Nx = 100;
    int Ny = 100;
    int Nz = 100;
    double Lx = 1;
    double Ly = 2;
    double Lz = 3;
    //initialize
    Solver s;
    s.set_val(s.N, Nx, Ny, Nz);
    s.set_val(s.L, Lx, Ly, Lz);
    s.set_val(s.h2, LATTICECONSTANT*LATTICECONSTANT);
//    s.init_val( s.rho, Q_E/EPS0);
    s.init_rho( );
//    s.write(s.rho, FILENAMERHO);
    s.init_eps( ); //will replace with reading from file eventually
    s.init_val( s.V, 0); //Need to initiate V before setting Boundary conds.
    s.set_BCs(0, 0, 0, 0, 0, 0);
    s.set_electrodes();//initialize and set electrodes
/*
    //call for Jacobi
    s.set_val( s.solvemethod, JACOBI);
    s.solve();
    s.write(FILENAMEJAC);
    //reset and call for Gauss-Seidel
    s.init_val( s.V, 0);
    s.set_val( s.solvemethod, GAUSS_SEIDEL);
    s.solve();
    s.write(FILENAMEGAU);
*/
    //reset and call for SOR
    s.init_val( s.V, 0);
    s.set_val( s.solvemethod, SOR_GEN);
    s.solve();
    s.write_2D(s.V, FILENAMESOR_GEN);
    s.write_2D(s.rho, FILENAMERHO);
//    s.write_2D(s.eps, FILENAMEEPS);
//    s.write(s.V, FILENAMESOR);
    return 0;
}
