#include "poissolver.h"

//Set the values in PhysConstants
namespace PhysConstants
{
   const double QE = 1.6021766208e-19; //elementary charge
   const double EPS0 = 8.85418782e-12; //permittivity of free space
   const double WF_GOLD = 5.1; //workfunction for gold in eV
   const double WF_COPPER = 4.7; //workfunction for copper in eV
   const double WF_ZINC = 4.3; //workfunction for zinc in eV
   const double WF_CESIUM = 2.1; //workfunction for cesium in eV
   const double WF_NICKEL = 5.01; //workfunction for nickel in eV
   const double CHI_SI = 4.05; //electron affinity for silicon in eV from http://www.ioffe.ru/SVA/NSM/Semicond/Si/basic.html
   const double EPS_SI = 11.7; //relative permittivity of silicon
};


using namespace phys;


PoisSolver::PoisSolver(const std::string& i_path, const std::string& o_path)
  : PhysicsEngine("PoisSolver", i_path, o_path)
{
  helloWorld();
}


std::vector<Electrodes> PoisSolver::set_buffer(std::vector<Electrodes> elec_vec) {
  //want to scale electrodes down to fit the simulation space.
  //First, find the (min, max) (x, y) values.
  //Then, extend or contract so that 10% of the sim space is left on each edge as buffer space.
  double xmin = 100;
  double ymin = 100;
  double xmax = 0;
  double ymax = 0;
  double xlength;
  double ylength;
  double xscale = 1;
  double yscale = 1;
  for(unsigned int i = 0; i < elec_vec.size(); i++){
    xmin = std::min(xmin, elec_vec[i].x[0]);
    ymin = std::min(ymin, elec_vec[i].y[0]);
    xmax = std::max(xmax, elec_vec[i].x[1]);
    ymax = std::max(ymax, elec_vec[i].y[1]);
  }

  //x-scaling to keep 10% buffer on each horizontal side.
  if(xmin < 0.1*SimParams::Ls[0] || xmax > 0.9*SimParams::Ls[0]){
    xlength = xmax - xmin;
    xscale = 0.8*SimParams::Ls[0]/xlength;
    std::cout << "xlength: " << xlength << std::endl;
  }
  if(ymin < 0.1*SimParams::Ls[1] || ymax > 0.9*SimParams::Ls[1]){
    ylength = ymax - ymin;
    yscale = 0.8*SimParams::Ls[1]/ylength;
    std::cout << "ylength: " << ylength << std::endl;
  }
  //scale all elements by lowest scaling factor.
  SimParams::finalscale = std::min(xscale, yscale);
  for(unsigned int i = 0; i < elec_vec.size(); i++){
    elec_vec[i].x[0] *= SimParams::finalscale;
    elec_vec[i].x[1] *= SimParams::finalscale;
    elec_vec[i].y[0] *= SimParams::finalscale;
    elec_vec[i].y[1] *= SimParams::finalscale;
  }
  //now sample is sure to fit within simulation boundaries, with space for buffer.
  //translate the violating part to the buffer boundary, once for x and once for y.
  xmin = 100;
  ymin = 100;
  xmax = 0;
  ymax = 0;
  //find how far outside the boundary the shapes still sit.
  for(unsigned int i = 0; i < elec_vec.size(); i++){
    xmin = std::min(xmin, elec_vec[i].x[0]);
    ymin = std::min(ymin, elec_vec[i].y[0]);
    xmax = std::max(xmax, elec_vec[i].x[1]);
    ymax = std::max(ymax, elec_vec[i].y[1]);
  }
  if(xmin < 0.1*SimParams::Ls[0]){  //too far to the left, want positive offset to bring it right
    //find the offset
    SimParams::xoffset = 0.1*SimParams::Ls[0] - xmin;
  }else if(xmax > 0.9*SimParams::Ls[0]){ //too far right, want negative offset to bring it left.
    SimParams::xoffset = 0.9*SimParams::Ls[0] - xmax;
  }
  if(ymin < 0.1*SimParams::Ls[1]){ //too far up
    //find the offset in y
    SimParams::yoffset = 0.1*SimParams::Ls[1] - ymin;
  }else if(ymax > 0.9*SimParams::Ls[1]){ //too far down
    SimParams::yoffset = 0.9*SimParams::Ls[1] - ymax;
  }
  //fix the offsets
  for(unsigned int i = 0; i < elec_vec.size(); i++){ //move all points based on offset.
    elec_vec[i].x[0] += SimParams::xoffset;
    elec_vec[i].x[1] += SimParams::xoffset;
    elec_vec[i].y[0] += SimParams::yoffset;
    elec_vec[i].y[1] += SimParams::yoffset;
  }
  return elec_vec;
}


bool PoisSolver::runSim()
{
  std::cout << "PoisSolver::runSim()" << std::endl;
  std::cout << "Grab all electrode locations..." << std::endl;

  //parse electrodes into elec_vec
  for(auto elec : problem) {
    elec_vec.push_back(Electrodes(
      elec->x1*SimParams::Ls[0], elec->x2*SimParams::Ls[0],
      elec->y1*SimParams::Ls[1], elec->y2*SimParams::Ls[1],
      0.3e-6, 0.7e-6, elec->potential, PhysConstants::WF_GOLD)); //elec_vec is part of phys_engine
  }
  //scale and offset electrodes in elec_vec
  elec_vec = set_buffer(elec_vec);
  std::cout << "Beginning solver." << std::endl;
  for(int i = 0; i < 1; i++){
    // All the relevant information is inside SimParams.
    worker(i, elec_vec); //where the magic happens
  }
  return true;
}


void PoisSolver::initVars(void)
{
  std::cout << "PoisSolver::initVars" << std::endl;
  bc = problem.parameterExists("bcs") ?
                  problem.getParameter("bcs") : "Dirichlet";
  resolution = problem.parameterExists("resolution") ?
                  std::stoi(problem.getParameter("resolution")) : 50;
  length = problem.parameterExists("length") ?
                  std::stoi(problem.getParameter("length")) : 1E-6;
  max_error = problem.parameterExists("max_error") ?
                  std::stoi(problem.getParameter("max_error")) : 5E-2;
  std::cout << bc << std::endl;
  std::cout << resolution << std::endl;
  std::cout << length << std::endl;
  std::cout << max_error << std::endl;
}


void PoisSolver::helloWorld(void)
{
  std::cout << "PoisSolver instantiated." << std::endl;
}


void PoisSolver::worker(int step, std::vector<Electrodes> elec_vec)
{
  std::cout << "Modified by Nathan Chiu. Code is offered as is, with no warranty. See LICENCE.GPL for licence info." << std::endl;
  std::cout << "Current step: " << step << std::endl;
  double cycleErr;
  int* indexErr = new int;

  // Calculate and save ds
  for (int i = 0; i<3; i++){
    SimParams::ds[i] = SimParams::Ls[i] / (double)SimParams::ns[i];
  }
  const int nsize = SimParams::ns[0]*SimParams::ns[1]*SimParams::ns[2]; //array size
  double temp[nsize] = {0};
  arr = temp;
  double *eps = new double[nsize]; //RELATIVE permittivity.
  double *chi = new double[nsize]; //electron affinity or WF
  double *RHS = new double[nsize]; // from which you can get a pointer to contiguous buffer, will contain rho.
  double *correction = new double[nsize]; // correction used to update RHS
  std::pair<int,double> *electrodemap = new std::pair<int,double>[nsize]; //stores electrode surface info and potentials.
  int cycleCount = 0;
  const std::clock_t begin_time = std::clock();
  init_eps(eps); // set permittivity
  init_rhs(chi, eps, RHS); // set rho and apply relative permittivity, also save electron affinity for bulk.
  create_electrode(RHS, electrodemap, chi, elec_vec);
  PoisFFT::Solver<3, double> S(SimParams::ns, SimParams::Ls, SimParams::BCs); //   create solver object, 3 dimensions, double precision

  std::cout << "Beginning solver loops." << std::endl;
  do{
    S.execute(arr, RHS); //run the solver, can be run many times for different right-hand side
    cycleErr = check_error(arr, correction, electrodemap, indexErr, eps);
    apply_correction(RHS, correction, electrodemap);
    std::cout << "On cycle " << cycleCount << " with error " << cycleErr << " at index " << *indexErr << ". " << arr[*indexErr] << " " << electrodemap[*indexErr].second << std::endl;
    cycleCount++;
  }while(cycleErr > SimParams::MAX_ERROR && cycleErr != 0);

  calc_charge(RHS, elec_vec);
  std::cout << "Finished on cycle " << cycleCount << " with error " << cycleErr << std::endl;

  std::cout << "Time elapsed: " << float(clock()-begin_time)/CLOCKS_PER_SEC << " seconds" << std::endl;
  std::cout << "Ending, deleting variables" << std::endl;

  delete indexErr;
  delete[] eps;
  delete[] RHS;
  delete[] electrodemap;
  delete[] chi;
  delete[] correction;
}


void PoisSolver::calc_charge(double* RHS , std::vector<Electrodes> elecs)
{
  //Want this to take in electrode location parameters, and spit out the charge on the conductor.
  double xmin, xmax, ymin, ymax, zmin, zmax, sum;
  for(unsigned int currElectrode = 0; currElectrode < elecs.size(); currElectrode++){
    xmin = elecs[currElectrode].x[0];
    xmax = elecs[currElectrode].x[1];
    ymin = elecs[currElectrode].y[0];
    ymax = elecs[currElectrode].y[1];
    zmin = elecs[currElectrode].z[0];
    zmax = elecs[currElectrode].z[1];
    sum = 0;
    for(int i = (int) SimParams::ns[0]*xmin/SimParams::Ls[0]; i <= (int) SimParams::ns[0]*xmax/SimParams::Ls[0]; i++){ //xmin first, then xmax
      for(int j = (int) SimParams::ns[1]*ymin/SimParams::Ls[1]; j <= (int) SimParams::ns[1]*ymax/SimParams::Ls[1]; j++){
        for(int k = (int) SimParams::ns[2]*zmin/SimParams::Ls[2]; k <= (int) SimParams::ns[2]*zmax/SimParams::Ls[2]; k++){
          sum += RHS[SimParams::IND(i,j,k)];
        }
      }
    }
    sum = sum*((xmax-xmin)*(ymax-ymin)*(zmax-zmin));
    std::cout << "Calculated charge on electrode " << currElectrode << " = " << sum << std::endl;
  }
}


void PoisSolver::create_electrode(double* RHS, std::pair<int,double> *electrodemap, double* chi, std::vector<Electrodes> elecs)
{
  for(unsigned int i = 0; i < elecs.size(); i++){
    elecs[i].draw(SimParams::ns, SimParams::Ls, RHS, electrodemap, chi); //separately call draw for each electrode.
  }
}


void PoisSolver::apply_correction(double *RHS, double *correction, std::pair<int,double> *electrodemap)
{
  for(int i = 0; i < SimParams::ns[0]*SimParams::ns[1]*SimParams::ns[2]; i++){
    if(electrodemap[i].first == true){ //only correct error at electrode surfaces.
      RHS[i] -= correction[i];
    }
  }
}


double PoisSolver::check_error(double *arr, double *correction, std::pair<int,double> *electrodemap, int *indexErr, double *eps)
{
  double err = 0;
  double errOld;
  double correctionWeight = 0;
  if(SimParams::BCs[0] == PoisFFT::PERIODIC){
    correctionWeight = 1e-7*SimParams::ns[0]*PhysConstants::EPS0/PhysConstants::QE/SimParams::Ls[0]/SimParams::Ls[0]; //Periodic
  } else if(SimParams::BCs[0] == PoisFFT::DIRICHLET || SimParams::BCs[0] == PoisFFT::NEUMANN){
    correctionWeight = 0.5e-7*SimParams::ns[0]*PhysConstants::EPS0/PhysConstants::QE/SimParams::Ls[0]/SimParams::Ls[0];  //Dirichlet & Neumann
  }
  for(int i = 0; i < SimParams::ns[0]*SimParams::ns[1]*SimParams::ns[2]; i++){
    if(electrodemap[i].first == true){ //only check error at electrodes.
      errOld = err;
      correction[i] = electrodemap[i].second-arr[i]; //intended potential - found potential. Looking at laplacian of potential doesn't allow snapping to electrode potentials.
      correction[i] *= correctionWeight;
      if(electrodemap[i].second != 0){
        err = std::max(err, fabs((arr[i] - electrodemap[i].second)/electrodemap[i].second)); //get largest error value.
      } else {
        err = std::max(err, arr[i]);
      }
      if( errOld != err ){
        *indexErr = i;
      }
    }
  }
  return err;
}


void PoisSolver::init_correction(double* correction)
{
  int i,j,k;
  std::cout << "Initialising correction" << std::endl;
  for (i=0;i<SimParams::ns[0];i++){
    // double x = SimParams::ds[0]*(i+0.5);
    for (j=0;j<SimParams::ns[1];j++){
      double y = SimParams::ds[1]*(j+0.5);
      for (k=0;k<SimParams::ns[2];k++){
        // double z = SimParams::ds[2]*(k+0.5);
        if (y < SimParams::Ls[1]/2){
          // a[IND(i,j,k)] = PhysConstants::EPS_SI; //Si relative permittivity
          correction[SimParams::IND(i,j,k)] = 0;  //Free space
        } else{
          correction[SimParams::IND(i,j,k)] = 0;  //Free space
        }
      }
    }
  }
  std::cout << "Finished eps initialisation" << std::endl;
}

void PoisSolver::init_eps(double* eps)
{
  int i,j,k;
  std::cout << "Initialising eps" << std::endl;
  for (i=0;i<SimParams::ns[0];i++){
    // double x = SimParams::ds[0]*(i+0.5);
    for (j=0;j<SimParams::ns[1];j++){
      double y = SimParams::ds[1]*(j+0.5);
      for (k=0;k<SimParams::ns[2];k++){
        // double z = SimParams::ds[2]*(k+0.5);
        if (y < SimParams::Ls[1]/2){
          // a[IND(i,j,k)] = PhysConstants::EPS_SI; //Si relative permittivity
          eps[SimParams::IND(i,j,k)] = 1;  //Free space
        } else{
          eps[SimParams::IND(i,j,k)] = 1;  //Free space
        }
      }
    }
  }
  std::cout << "Finished eps initialisation" << std::endl;
}


void PoisSolver::init_rhs(double* chi, double* eps, double* rhs)
{
  int i,j,k;
  std::cout << "Initialising RHS" << std::endl;
  for (i=0;i<SimParams::ns[0];i++){
    // double x = SimParams::ds[0]*(i+0.5);
    for (j=0;j<SimParams::ns[1];j++){
      // double y = SimParams::ds[1]*(j+0.5);
      for (k=0;k<SimParams::ns[2];k++){
        // double z = SimParams::ds[2]*(k+0.5);
        // a[IND(i,j,k)] = 1e16*PhysConstants::QE/PhysConstants::EPS0/eps[IND(i,j,k)]; //in m^-3, scale by permittivity
        rhs[SimParams::IND(i,j,k)] = 0*PhysConstants::QE/PhysConstants::EPS0/eps[SimParams::IND(i,j,k)]; //in m^-3, scale by permittivity
        chi[SimParams::IND(i,j,k)] = PhysConstants::CHI_SI;
      }
    }
  }
  std::cout << "Finished RHS initialisation" << std::endl;
}
