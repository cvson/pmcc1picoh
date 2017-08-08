//////////////////////////////////////////////////////////
//
//  Xsec modeling parameters
//
//
//
//  Created: Oct 2013
//  Modified:
//
//////////////////////////////////////////////////////////

#ifndef __XsecParameters_hh__
#define __XsecParameters_hh__

#include "AnaFitParameters.hh"
#include <TFile.h>
#include <TGraph.h>

// Sample types
// 0 --> SIG
// 1 --> CR1
// 2 --> CR2A
// 3 --> CR2B
// 4 --> CR2C
// 5 --> More2trk
// 6 --> Onetrack
enum SampleTypes { s_SIG = 0,
    s_CRI = 1,
    s_CRII = 2,
    s_CRIII = 3,
    s_CRIV = 4,
    s_CRV = 5	};

// Reaction and backgrounds
// the indices should match with ntuples
// 0 - CC1picoh
// 1 - CCQE
// 2 - CC1pion
// 3 - CC OTHER
// 4 - NC & Anti-nu background
// 5 - Wall & INGRID
/*enum ReactionTypes { ReCC1picoh = 0,
    ReCCQE = 1,
    ReCC1pi = 2,
    ReCCDIS = 3,
    ReNCAntiNu = 4,
    OutFGD = 5 };*/
//matching with baseTreeWeight:CutInteractionbyIDnew
enum ReactionTypes { ReCCQE = 0,
    ReCC1pi = 1,
    ReCCDIS = 2,
    ReNCAntiNu = 3,
    OutFGD = 4 };


struct XsecBin
{
    double recoPlow, recoPhigh;
    //double truePlow, truePhigh;
    double recoCTHlow, recoCTHhigh;
    //double trueCTHlow, trueCTHhigh;
    SampleTypes topology;
    ReactionTypes reaction;
    std::vector<TGraph*> respfuncs;
};

class XsecParameters : public AnaFitParameters
{
public:
    XsecParameters(const char *name = "par_xsec");
    ~XsecParameters();
    
    void StoreResponseFunctions(std::vector<TFile*> respfuncs,
                                std::vector<std::pair <double,double> > v_pedges,
                                std::vector<std::pair <double,double> > v_cthedges);
    void InitEventMap(std::vector<AnaSample*> &sample);
    void EventWeights(std::vector<AnaSample*> &sample,
                      std::vector<double> &params);
    void ReWeight(AnaEvent *event, int nsample, int nevent,
                  std::vector<double> &params);
private:
    /*int GetBinIndex(SampleTypes sampletype, ReactionTypes reactype,
                    double recoP, double trueP, double recoCTH, double trueCTH);*/
    int GetBinIndex(SampleTypes sampletype, ReactionTypes reactype,
                    double recoP, double recoCTH);
    std::vector<XsecBin> m_bins;
};

#endif
