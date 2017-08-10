//////////////////////////////////////////////////////////
//
//  CC1picoh cross-section parameters
//  Scale applied for each bins
//
//
//  Created:
//  Modified:
//
//////////////////////////////////////////////////////////

#ifndef __Vertex1piParameters_hh__
#define __Vertex1piParameters_hh__

#include "AnaFitParameters.hh"

struct CC1piBin
{
    double plow, phigh;
    double cthlow, cthhigh;
};

class Vertex1piParameters : public AnaFitParameters
{
public:
    Vertex1piParameters(const char *fname,
                   const char *name = "par_vertex1pi");
    ~Vertex1piParameters();
    
    void InitEventMap(std::vector<AnaSample*> &sample);
    void EventWeights(std::vector<AnaSample*> &sample,
                      std::vector<double> &params);
    void ReWeight(AnaEvent *event, int nsample, int nevent,
                  std::vector<double> &params);
    void SetBinning(const char *fname);
    
private:
    //binnig function
    int GetBinIndex(double p, double cth);
    
    int cc1pi_recode;              //reaction code
    std::vector<CC1piBin> m_bins; //binning
};

#endif
