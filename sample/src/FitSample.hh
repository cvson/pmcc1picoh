//////////////////////////////////////////////////////////
//
//  A class for event samples for for CCQE analysis
//
//
//
//  Created: Thu Jun  6 12:01:10 CEST 2013
//  Modified:
//
//////////////////////////////////////////////////////////
#ifndef __FitSample_hh__
#define __FitSample_hh__

#include <string>
#include <vector>

#include <TH2D.h>
#include <TDirectory.h>
#include <TRandom3.h>
#include <TTree.h>

#include "AnaEvent.hh"
#include "AnaSample.hh"

///////////////////////////////////////
// Class definition
///////////////////////////////////////
class FitSample : public AnaSample
{
public:
    FitSample(int sample_id, std::string name,
               std::vector<std::pair <double,double> > v_pedges,
               std::vector<std::pair <double,double> > v_cthedges, TTree *data);
    ~FitSample();
    
    //binning for various histograms
    void SetPmuBinning(int nbins, double *bins);
    void SetCThmuBinning(int nbins, double *bins);
    void SetEnuBinning(int nbins, double *bins);
    void MakeHistos(); //must be called after binning is changed
    
    //histogram for event distributions
    void SetData(TObject *hdata);
    void FillEventHisto(int datatype);
    double CalcChi2();
    
    TH1D* GetPredHisto(){ return m_hpred; }
    TH1D* GetDataHisto(){ return m_hdata; }
    //TH1D* GetMCFakeHisto(){ return m_hmcfake; }//newadd
    
    void GetSampleBreakdown(TDirectory *dirout, std::string tag);
    void Write(TDirectory *dirout, const char *bsname, int fititer);
    int GetSampleId(){ return sample_id; }
    
private:
    int sample_id;
    TH1D *m_hmc;
    TH1D *m_hpred; //n(pRec_mu, thetaRec_mu)
    TH1D *m_hdata;
    //TH1D *m_hmcfake;//newadd to scale MC
    TTree * m_data_tree;
    int nbins_pmu, nbins_cthmu, nbins_enu, nccqebins;
    double *bins_pmu, *bins_cthmu, *bins_enu, *bins_ccqe;
    std::vector<std::pair<double, double> > m_pedges;
    std::vector<std::pair<double, double> > m_cthedges;
};

#endif
