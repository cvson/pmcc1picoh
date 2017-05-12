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

#ifndef __ScaleParameters_hh__
#define __ScaleParameters_hh__

#include "AnaFitParameters.hh"

struct ScaleBin
{
    double plow, phigh;
    double cthlow, cthhigh;
};

class ScaleParameters : public AnaFitParameters
{
public:
    ScaleParameters(const char *fname,
                   const char *name = "par_scale");
    ~ScaleParameters();
    
    void InitEventMap(std::vector<AnaSample*> &sample);
    void EventWeights(std::vector<AnaSample*> &sample,
                      std::vector<double> &params);
    void ReWeight(AnaEvent *event, int nsample, int nevent,
                  std::vector<double> &params);
    void SetBinning(const char *fname);
    
private:
    //binnig function
    int GetBinIndex(double p, double cth);
    
    int scale_recode;              //reaction code
    std::vector<ScaleBin> m_bins; //binning
};

#endif
