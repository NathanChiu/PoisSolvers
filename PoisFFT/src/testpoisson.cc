/*
MODIFICATIONS (as required by GPL)
2017 May 11
  -Changes to init_rhs to create non-sinusoidal RHS
  -Added #define FILENAME to define
  -removed call to check_solution from main(). Need exact solution to use check_solution (Need to modify for every test)
  -Added file output to main()
  -Added std::cout statements to check program flow.
  -Added notice to GNU GPL file, as required in section 2c.
  -Added Electrode class and drawing functionality
To build, after installing dependencies (fftw, pfft), go to /src/ and do: sudo scons test
The executable will appear as ../bin/gcc/cc_testpoisson
https://arxiv.org/pdf/1208.0901.pdf
*/

#include <cmath>
#include <iostream>
#include "poisfft.h"
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <utility>
#include <algorithm>
#include <gperftools/profiler.h>
#include <ctime>

const double pi = 3.14159265358979323846;

#define EPS0 8.85418782e-12
#define Q_E 1.6e-19
#define MAXERROR 1e-3
#define IND(i,j,k) (i)*(ns[1]*ns[2])+(j)*(ns[2])+k
#define FILENAME ((char*)"outfile.txt")
#define RHOFILE ((char*) "outrho.txt")
#define CORRECTIONFILE ((char*) "outcorr.txt")

class Electrodes{
  public:
    Electrodes(); //default constructor
    Electrodes(double, double, double, double, double, double, double); //parametrized constructor
    ~Electrodes(); //destructor
    double x[2]; //xmin (x[0]) and xmax (x[1])
    double y[2]; //ymin and ymax
    double z[2]; //zmin and zmax
    double potential;   //pointer after conversion of vector
    void draw(const int[3], const double[3], const double[3], double*, std::pair<int,double>*);
};

Electrodes::Electrodes( void ){}
Electrodes::Electrodes( double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, double pot){
  x[0] = xmin;
  x[1] = xmax;
  y[0] = ymin;
  y[1] = ymax;
  z[0] = zmin;
  z[1] = zmax;
  potential = pot;
}

Electrodes::~Electrodes( void ){}

void Electrodes::draw(const int ns[3], const double ds[3], const double Ls[3], double* RHS, std::pair<int,double> *electrodemap){
  int i, j, k; //draw the electrode into an electrode map
  for(int i = (int) ns[0]*x[0]/Ls[0]; i < (int) ns[0]*x[1]/Ls[0]; i++){ //set RHS 0 inside electrodes
    for(int j = (int) ns[1]*y[0]/Ls[1]; j < (int) ns[1]*y[1]/Ls[1]; j++){
      for(int k = (int) ns[2]*z[0]/Ls[2]; k < (int) ns[2]*z[1]/Ls[2]; k++){
        RHS[i*ns[1]*ns[2] + j*ns[2] + k] = 0;
      }
    }
  }
  for( int iter = 0; iter < 2; iter++){
    i = (int) ns[0]*x[iter]/Ls[0]; //xmin first, then xmax
    for(int j = (int) ns[1]*y[0]/Ls[1]; j <= (int) ns[1]*y[1]/Ls[1]; j++){
      for(int k = (int) ns[2]*z[0]/Ls[2]; k <= (int) ns[2]*z[1]/Ls[2]; k++){
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].first = true; //set true for electrode surface.
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].second = potential; //set electrode potential
      }
    }
  }
  for( int iter = 0; iter < 2; iter++){
    j = (int) ns[1]*y[iter]/Ls[1]; //ymin first, then ymax
    for(int i = (int) ns[0]*x[0]/Ls[0]; i <= (int) ns[0]*x[1]/Ls[0]; i++){
      for(int k = (int) ns[2]*z[0]/Ls[2]; k <= (int) ns[2]*z[1]/Ls[2]; k++){
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].first = true; //set true for electrode surface.
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].second = potential; //set electrode potential
      }
    }
  }
  for( int iter = 0; iter < 2; iter++){
    k = (int) ns[2]*z[iter]/Ls[2]; //zmin
    for(int i = (int) ns[0]*x[0]/Ls[0]; i <= (int) ns[0]*x[1]/Ls[0]; i++){
      for(int j = (int) ns[1]*y[0]/Ls[1]; j <= (int) ns[1]*y[1]/Ls[1]; j++){
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].first = true; //set true for electrode surface.
        electrodemap[i*ns[1]*ns[2] + j*ns[2] + k].second = potential; //set electrode potential
      }
    }
  }
}

void save_file2D(const int[], const double[], const double[], double*, char[]);
void check_solution(const int[], const double[], const double[], double*);
void init_rhs(const int[], const double[], const double[], double*);
double check_error(const int[], const double[], double*, double*, std::pair<int,double>*);
void apply_correction(const int[], const double[], double*, double*, std::pair<int,double>*);

int main(void){
  std::cout << "Modified by Nathan Chiu. Code is offered as is, with no warranty. See LICENCE.GPL for licence info." << std::endl;
  const double Ls[3] = {1.0, 1.0, 1.0}; //x, y, z domain dimensions
  const int ns[3] = {100, 100, 100}; //x, y, z gridpoint numbers
  double ds[3];  // distances between gridpoints
  double cycleErr;
  const int BCs[6] = {PoisFFT::PERIODIC, PoisFFT::PERIODIC,  //boundary conditions
                      PoisFFT::PERIODIC, PoisFFT::PERIODIC,
                      PoisFFT::PERIODIC, PoisFFT::PERIODIC};
  int i;
  for (i = 0; i<3; i++){ // set the grid, depends on the boundary conditions
    ds[i] = Ls[i] / ns[i];
  }
  double *arr = new double[ns[0]*ns[1]*ns[2]]; // allocate the arrays contiguously, you can use any other class
  double *RHS = new double[ns[0]*ns[1]*ns[2]]; // from which you can get a pointer to contiguous buffer
  double *correction = new double[ns[0]*ns[1]*ns[2]]; // correction used to update RHS
  std::pair<int,double> *electrodemap = new std::pair<int,double>[ns[0]*ns[1]*ns[2]]; //stores electrode surface info and potentials.
  int cycleCount = 0;
  // ProfilerStart("./profileresult.out"); //using google performance tools
  const std::clock_t begin_time = std::clock();
  init_rhs(ns, ds, Ls, RHS); // set the right-hand side
  Electrodes elec1(0.2, 0.4, 0.2, 0.4, 0.3, 0.6, 5);
  Electrodes elec2(0.2, 0.4, 0.6, 0.8, 0.3, 0.6, 10);
  Electrodes elec3(0.6, 0.8, 0.2, 0.4, 0.3, 0.6, 15);
  Electrodes elec4(0.6, 0.8, 0.6, 0.8, 0.3, 0.6, 20);
  elec1.draw(ns, ds, Ls, RHS, electrodemap);
  elec2.draw(ns, ds, Ls, RHS, electrodemap);
  elec3.draw(ns, ds, Ls, RHS, electrodemap);
  elec4.draw(ns, ds, Ls, RHS, electrodemap); //separately call draw for each electrode.
  PoisFFT::Solver<3, double> S(ns, Ls, BCs); // create solver object, 3 dimensions, double precision
  std::cout << "Beginning solver" << std::endl;
  save_file2D(ns, ds, Ls, RHS, RHOFILE);
  do{
    S.execute(arr, RHS); //run the solver, can be run many times for different right-hand side
    cycleErr = check_error(ns, ds, arr, correction, electrodemap);
    apply_correction(ns, ds, RHS, correction, electrodemap);
    if(cycleCount%10==0){
      std::cout << "On cycle " << cycleCount << " with error " << cycleErr << "." << std::endl;
    }
    cycleCount++;
  }while(cycleErr > MAXERROR);
  std::cout << "Finished on cycle " << cycleCount << " with error " << cycleErr << std::endl;
  save_file2D(ns, ds, Ls, RHS, RHOFILE);
  save_file2D(ns, ds, Ls, arr, CORRECTIONFILE);
  save_file2D(ns, ds, Ls, arr, FILENAME); //solution is in arr
  // ProfilerStop();
  std::cout << "Time elapsed: " << float(clock()-begin_time)/CLOCKS_PER_SEC << " seconds" << std::endl;
  std::cout << "Ending, deleting variables" << std::endl;
  delete[] RHS;
  delete[] arr;
  delete[] electrodemap;
  delete[] correction;
}

void apply_correction(const int ns[3], const double ds[3], double *RHS, double *correction, std::pair<int,double> *electrodemap){
  for(int i = 0; i < ns[0]*ns[1]*ns[2]; i++){
    if(electrodemap[i].first == true){ //only correct error at electrode surfaces.
      RHS[i] -= correction[i];
    }
  }
}

double check_error(const int ns[3], const double ds[3], double *arr, double *correction, std::pair<int,double> *electrodemap){
  double err = 0;
  for(int i = 0; i < ns[0]*ns[1]*ns[2]; i++){
    if(electrodemap[i].first == true){ //only check error at electrodes.
      correction[i] = electrodemap[i].second-arr[i]; //intended potential - found potential.
      correction[i] = 1000*correction[i];
      err = std::max(err, fabs((electrodemap[i].second-arr[i])/electrodemap[i].second)); //get largest error value.
    }
  }
  return err;
}

void save_file2D(const int ns[3], const double ds[3], const double Ls[3], double* arr, char fname[]){
  std::ofstream outfile;
  outfile.open(fname, std::ios_base::out | std::ios_base::trunc );
  std::cout << "Dumping to " << fname << std::endl;
  const int k = ns[2]/2;
  for (int i = 0; i < ns[0]; i++){
    for (int j = 0; j < ns[1]; j++){
        outfile << std::setprecision(5) << std::scientific << i*ds[0] <<
        " " << j*ds[1] << " " << arr[i*ns[1]*ns[2]+j*ns[2]+k] << std::endl;
    }
    outfile << std::endl;
  }
}

void init_rhs(const int ns[3], const double ds[3], const double Ls[3], double* a){
  int i,j,k;
  std::cout << "Initialising RHS" << std::endl;
  for (i=0;i<ns[0];i++){
    double x = ds[0]*(i+0.5);
    for (j=0;j<ns[1];j++){
      double y = ds[1]*(j+0.5);
      for (k=0;k<ns[2];k++){
        double z = ds[2]*(k+0.5);
        // a[IND(i,j,k)] = -1.5e10*Q_E/EPS0; //Set default set to bulk volume charge density.
        // a[IND(i,j,k)] = -1.5*Q_E/EPS0; //Set default set to bulk volume charge density.
        a[IND(i,j,k)] = -1.5*Q_E/EPS0; //Set default set to bulk volume charge density.
      }
    }
  }
  std::cout << "Finished initialisation" << std::endl;
}
