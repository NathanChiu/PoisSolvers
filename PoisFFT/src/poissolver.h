#ifndef POISSOLVER_H
#define POISSOLVER_H



#include "phys_connector.h"
#include "poisfft.h" // all the Fortran stuff
#include "electrodes.h" // Electrodes
#include <cmath> // fabs()
#include <iostream> // cout
#include <utility> // pair
#include <algorithm> // min(), max()
#include <ctime> // clock()
#include <boost/property_tree/ptree.hpp> // XML stuff
#include <boost/property_tree/xml_parser.hpp> // XML stuff
#include <vector> // vector
#include <string> // string
#include <fstream>

// Physical constants used for calculation
namespace PhysConstants
{
   extern const double QE; //elementary charge
   extern const double EPS0; //permittivity of free space
   extern const double WF_GOLD; //workfunction for gold in eV
   extern const double WF_COPPER; //workfunction for copper in eV
   extern const double WF_ZINC; //workfunction for zinc in eV
   extern const double WF_CESIUM; //workfunction for cesium in eV
   extern const double WF_NICKEL; //workfunction for nickel in eV
   extern const double CHI_SI; //electron affinity for silicon in eV from http://www.ioffe.ru/SVA/NSM/Semicond/Si/basic.html
   extern const double EPS_SI; //relative permittivity of silicon
};

// Simulation parameters used for simulation control
namespace SimParams
{
  // scaling and offset values
  extern double finalscale, xoffset, yoffset, zoffset;
  extern std::string resultpath;

  //stuff used during simulation
  extern double Ls[3]; // simulation length in x, y, z
  extern int ns[3]; // resolution in x, y, z
  extern double ds[3]; // simulation length per resolution step, CALCULATED
  extern int BCs[6]; // boundary conditions for left, right, top, bottom, front, back.
  extern double MAX_ERROR;
  extern int IND(int i, int j, int k);

  //stuff used post-simulation
  extern char* OUTFILE;
  extern char* RHOFILE;
  extern char* EPSFILE;
  extern char* CORRFILE;
  extern char* RESXML;
};


namespace phys{
  class PoisSolver
  {
    public:
        PoisSolver(const std::string& i_path, const std::string& o_path);
        ~PoisSolver(){} //destructor1
        void initSolver(void);
        void worker(int step, std::vector<Electrodes> elec_vec);
        void initEPS(double* eps);
        void initRHS(double* chi, double* eps, double* rhs);
        double checkError(double *arr, double *correction, std::pair<int,double> *electrodemap, int *indexErr, double *eps);
        void applyCorrection(double *RHS, double *correction, std::pair<int,double> *electrodemap);
        void createElectrode(double* RHS, std::pair<int,double> *electrodemap, double* chi, std::vector<Electrodes> elecs);
        void calcCharge(double* RHS , std::vector<Electrodes> elecs);
        bool runSim();
        void initCorrection(double* correction);
        std::vector<Electrodes> setBuffer(std::vector<Electrodes> elec_vec);
        void initVars(void);
        void exportData(void);        
        
        std::vector<std::vector<std::vector<std::string>>> db_potential_accu;
        std::vector<std::vector<std::string>> db_potential_data;
        std::vector<std::pair<double, double>> db_locs; // location of elecs in x, y
        std::vector<Electrodes> elec_vec; // location of elecs
        std::vector<double> clock_potentials; //vector of potentials used for electrodes when clocking
        double *arr; //will contain the potential
        std::string bc;
        int resolution;
        double length;
        double max_error;
        double z_offset;
        double z_thickness;
        std::string mode;
        double high_pot;
        double low_pot;
        int steps;
        PhysicsConnector* phys_con;
  };
}

double interpolate(double q11, double q12, double q21,  double q22, double x1, double x2, double y1, double y2, double x, double y);

#endif //POISSOLVER_H
