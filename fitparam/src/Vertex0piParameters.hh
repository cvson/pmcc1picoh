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

#ifndef __Vertex0piParameters_hh__
#define __Vertex0piParameters_hh__

#include "AnaFitParameters.hh"

struct CC0piBin
{
    double plow, phigh;
    double cthlow, cthhigh;
};

class Vertex0piParameters : public AnaFitParameters
{
public:
    Vertex0piParameters(const char *fname,
                   const char *name = "par_vertex0pi");
    ~Vertex0piParameters();
    
    void InitEventMap(std::vector<AnaSample*> &sample);
    void EventWeights(std::vector<AnaSample*> &sample,
                      std::vector<double> &params);
    void ReWeight(AnaEvent *event, int nsample, int nevent,
                  std::vector<double> &params);
    void SetBinning(const char *fname);
    
private:
    //binnig function
    int GetBinIndex(double p, double cth);
    
    int cc0pi_recode;              //reaction code
    std::vector<CC0piBin> m_bins; //binning
};

#endif
