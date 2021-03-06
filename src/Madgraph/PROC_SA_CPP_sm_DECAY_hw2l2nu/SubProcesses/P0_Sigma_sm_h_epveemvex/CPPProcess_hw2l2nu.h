//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.2, 2014-11-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef MG5_Sigma_sm_h_epveemvex_H
#define MG5_Sigma_sm_h_epveemvex_H

#include <complex> 
#include <vector> 

#include "../../src/Parameters_sm_hw2l2nu.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: h > w+ e- ve~
// *   Decay: w+ > e+ ve WEIGHTED=2
// Process: h > w+ mu- vm~
// *   Decay: w+ > e+ ve WEIGHTED=2
// Process: h > w+ e- ve~
// *   Decay: w+ > mu+ vm WEIGHTED=2
// Process: h > w+ mu- vm~
// *   Decay: w+ > mu+ vm WEIGHTED=2
//--------------------------------------------------------------------------

class CPPProcess_hw2l2nu
{
  public:

    // Constructor.
    CPPProcess_hw2l2nu() {}

    // Destructor.
    virtual ~CPPProcess_hw2l2nu() {}

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "h > e+ ve e- ve~ (sm)";}

    virtual int code() const {return 0;}

    const vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    vector < double * > getMomenta(){return p;}
    void setMomenta(vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 1; 
    static const int nexternal = 5; 
    static const int nprocesses = 1; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 7; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 1; 
    std::complex<double> amp[namplitudes]; 
    double matrix_h_wpemvex_wp_epve(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_sm_hw2l2nu * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_sm_h_epveemvex_H
