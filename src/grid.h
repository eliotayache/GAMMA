#ifndef FLUID_GRID_H_
#define FLUID_GRID_H_

#include "environment.h"
#include "cell.h"

//////////////////////////////////////////////////////////////////////////////////////////
class Grid{

  public:
  Grid();
  ~Grid();

  // total grid info
  int nsimu;         // number of cells in simu
  int nax[NUM_D];    // number of cells in each direction to be allocated
                        // nax[MV] = n_max (includes ghosts)
  int ncell[NUM_D];  // number of cells in simulation domain
  int ngst;          // number of ghost cells on each side of the grid

  // node-specific info
  int nde_ntot;        // total number of allocated cells on node
  int nde_nax[NUM_D];  // number of cells in each direction (including ghosts)
  int nde_ncell[NUM_D];  // number of cells in each direction
  int origin[NUM_D];    // coordinates of C[0][0] in simulation domain

  #if   NUM_D == 1
    Cell         *C;
    Interface    *I;     // moving interfaces
    int n_act;           // number of active cells in track

  #elif NUM_D == 2
    Cell         **Cinit; // initial simulation domain
    Cell         **C;     // physical grid (without ghost tracks, but ghosts cells in MV)
    Cell         **Ctot;  // grid with ghost tracks
    Interface    **I;     // moving dim interfaces (without ghost to ghost in moving dim)
                            // does include ghost tracks
    Interface    **Itot;  // moving dim interfaces 
    int *nact;
    int jLbnd, jRbnd, *iLbnd, *iRbnd; // tot index of first ghost cell out of active grid

  #elif NUM_D == 3
    Cell         ***C;
    Interface    ***I;
    int **n_act;
    int **iLactive, **iRactive;

  #endif


  // bool initialised;

  // int ncells_active;          // number of active cells at a given moment (ACTIVE)
  // int ncells_total;           // total number of cells (ghost, active)
  // int ncells_max;             // max number of cells (ghost, active, inactive)
  // int iLactive, iRactive;     // indexes of leftmost and rightmost active cells
  // int iLlim, iRlim;           // indexes of left and right evolving region limits
  // Cell        *C;
  // Interface    *I;

  // // METHODS
  void initialise(s_par par);          // allocate memory for maximum number of cells
  int  initialGeometry();
  int  initialValues();
  void destruct();            // free memory
  void print(int var);
  void prepForRun();
  void prepForUpdate();
  void updateGhosts();
  void interfaceGeomFromCellPos();

  template <class T> void apply(void (T::*func)());
                     void apply(void (FluidState::*func)());
                      // overloading for FluidState

  void mpi_exchangeGhostTracks();

  // void loadInitialConfig(s_config_setup config);   // Fill grid with initial conditions
  // void reloadConfig(s_config_setup *pconfig); // Fill grid with result of previous run
  // void updateBoundaries();    // sets up the boundary conditions

  // // in geometry.h (geometry setup and update)
  // void setupGeometry(s_config_setup config);  // compute cell geometrical variables
  // void geomFromInterfacePositions();  // new geom for new interface positions
  //                   // analog to las bit of moveMesh()

  // // in hydro.cpp (hydro evolution)
  // void updateWaveSpeeds();    // Updates the wavespeeds at all interfaces
  // void updateCells(long int it, double t, double dt);// Computes the next state of the grid
  // void updateInterCellFluxes();// Computes the flux accross all interfaces of the grid
  // void reconstructInterfaceStates(double dt); // Runs reconstruction for all interfaces in grid
  // void updateSolver(long int it, double t, double dt); // chooses the solver to be used
  //                            // for each interface
  // void forceSolverToHLLC();   // Forces solver to HLLC on all interfaces. (Useful for
  //               // ALE_TYPE_ == CD_)

  // // in time.cpp (time integration methods)
  // void firstOrderUpdate(long int it, double t, double dt); // updates cells and moves mesh

  // // in hydro_moving_mesh.cpp (moving mesh methods)
  // void updateMeshKinematics(long int it, double t); // updates the Mesh kinematics in accordance
  //                     // with grid states
  // void moveMesh(double t, double dt); // Moves the mesh according to kinematics 
  //                   // specified before
  // void regrid(s_config_setup config, int boolRefine, double t);  // merges cells that are too small.
  //                    // splits cells that are too big.
  // void flagGradients(); // computes second derivative of velocity over all grid.
  // void refine(s_config_setup config, int ix);     // refines for index ix
  // void derefine(s_config_setup config, int ix);   // de-refines for index ix
  // void findMinInactive();   // updates minInactiveC and pFirstInactiveI
  // void correctCellsForMovingMesh(double dt);  // Corrects cell values to account for
  //                       // interfaces position updates.
  // void sort(); // sorts the cells in memory to be ordered again
  // void moveRightBoundary(double dt); // moves the right side boundary when activated

  // #if REFINEMENT_CRITERION_ == USER_REFINEMENT_
  // void userRefine(s_config_setup, int ix);        // custom refinement decision
  // #endif
  // #if DEREFINEMENT_CRITERION_ == USER_DEREFINEMENT_
  // void userDerefine(s_config_setup, int ix);      // custom derefinement decision
  // #endif
  

  // // extending fluid functions to the grid
  // void prim2cons();
  // void prim2aux();
  // void cons2prim();
  // void state2flux();
  // void cons2all(long int it, double t, double dt);


  // // RK3 methods
  // void RK3CopyState0();
  // void RK3ComputeState2(long int it, double t, double dt);
  // void RK3ComputeState3(long int it, double t, double dt);

};

#endif
