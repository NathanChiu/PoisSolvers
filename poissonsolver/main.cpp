 #include <iostream>
#include "./src/solver.h"
#include "./src/electrodes.h"

int main() {
//Parameters
    int Nx = 100;
    int Ny = 100;
    int Nz = 100;
    double Lx = 1.0;
    double Ly = 1.0;
    double Lz = 1.0;
    int numelectrodes = 4;
    Solver sol;
    Solver * s = &sol;
    std::vector<Electrodes> elec(numelectrodes);
    s->set_val(Nx, Ny, Nz, s->N);
    s->set_val(Lx, Ly, Lz, s->L);
//can allocate space for rho, eps, and V now that spacing is known.
    s->rho = s->init_val( 0, s->rho);
    s->V = s->init_val( 0, s->V );
    s->eps = s->init_val( 0, s->eps );
//REQUIRE CONSISTENT L/N IN ALL X, Y, Z
    s->h2 = Lx*Lx/Nx/Nx;
    s->h = Lx/Nx;
    s->boundarytype = DIRICHLET;

//initialize electrodes
    for( int index = 0; index < numelectrodes; index++){
      elec[index].init_elec(); //init all electrodes
    }
//4 total electrodes, arranged in a square
    elec[0].centre = {Nx/4, Ny/4, Nz/2};
    elec[0].dims = {Nx/8, Ny/8, Nz/8};
    elec[0].potential = 1e-3;
    elec[0].workfunction = WF_COPPER;
    elec[1].centre = {3*Nx/4, 3*Ny/4, Nz/2};
    elec[1].dims = {Nx/8, Ny/8, Nz/8};
    elec[1].potential = 1e-3;
    elec[1].workfunction = WF_COPPER;
    elec[2].centre = {3*Nx/4, Ny/4, Nz/2};
    elec[2].dims = {Nx/8, Ny/8, Nz/8};
    elec[2].potential = 0;
    elec[2].workfunction = WF_GOLD;
    elec[3].centre = {Nx/4, 3*Ny/4, Nz/2};
    elec[3].dims = {Nx/8, Ny/8, Nz/8};
    elec[3].potential = 0;
    elec[3].workfunction = WF_GOLD;

    s->electrodemap = s->init_val( 0, s-> electrodemap );
    for( int index = 0; index < numelectrodes; index++){
      elec[index].convert(); //convert vectors into pointers
      //elec[index].draw(s); //draw all electrodes into electrodemap
    }
//eps and rho are already pointers. To use existing rho and eps, initialize and set with:
//s->rho = pointer to array for rho
    s->init_rho( );
    s->init_eps( );
    s->set_BCs(0, 0, 0, 0, 0, 0); //boundary conditions
//reset solution vector and call for SOR_GEN
    s->solvemethod = SOR_GEN;
    s->solve();
    s->write_2D(s->V, FILENAMESOR_GEN);
    s->write_2D(s->rho, FILENAMERHO);
//destructors take care of deleting.
    return 0;
}
