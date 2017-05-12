//////////////////////////////////////////////////////////
//
//  Det parameters
//
//
//
//  Created: Oct 2013
//  Modified:
//
//////////////////////////////////////////////////////////

#ifndef __DetParameters_hh__
#define __DetParameters_hh__

#include <TAxis.h>
#include "AnaFitParameters.hh"

struct DetBin
{
    double plow, phigh;
    double cthlow, cthhigh;
    int sample; //from 0 to 5 for the 6 regions
};

class DetParameters : public AnaFitParameters
{
public:
    DetParameters(std::vector<AnaSample*> &sample, const char *fname, const char *name = "par_det");
    ~DetParameters();
    
    void InitEventMap(std::vector<AnaSample*> &sample);
    void EventWeights(std::vector<AnaSample*> &sample,
                      std::vector<double> &params);
    void ReWeight(AnaEvent *event, int nsample, int nevent,
                  std::vector<double> &params);
    void SetBinning(const char *fname, std::vector<AnaSample*> &sample);
    
private:
    int GetBinIndex(double p, double cth, int sample_id); //binning function
    std::vector<DetBin> m_bins;
};

#endif
