#ifndef __XsecFitter_hh__
#define __XsecFitter_hh__

#include <string>
#include <TVirtualFitter.h>
#include <TObject.h>
#include <TMath.h>
#include <TRandom3.h>

#include "AnaSample.hh"
#include "FitSample.hh"
#include "AnaFitParameters.hh"

class XsecFitter : public TObject
{
public:
    XsecFitter(int seed = 1019);
    ~XsecFitter();
    void SetSeed(int seed);
    void fcn(Int_t &npar, Double_t *gin, Double_t &f,
             Double_t *par, Int_t iflag);
    void InitFitter(std::vector<AnaFitParameters*> &fitpara);
    void FixParameter(std::string par_name, double value);
    void Fit(std::vector<AnaSample*> &samples, int datatype);
    void SetSaveMode(TDirectory *dirout, int freq)
    { m_dir = dirout; m_freq = freq; }
    
    ClassDef(XsecFitter, 0);
    
private:
    void GenerateToyData(int toyindx = 0);
    double FillSamples(std::vector< std::vector<double> > new_pars,
                       int datatype = 0);
    void DoSaveParams(std::vector< std::vector<double> > new_pars);
    void DoSaveEvents(int fititer);
    void DoSaveChi2();
    void DoSaveResults(std::vector< std::vector<double> > parresults,
                       std::vector< std::vector<double> > parerrors, double chi2);
    
    TRandom3 *rand;
    TDirectory *m_dir;
    std::vector<AnaFitParameters*> m_fitpara;
    std::vector<int> m_nparclass;
    std::vector<AnaSample*> m_samples;
    int m_npar, m_calls, m_freq;
    std::vector<std::string> par_names;
    std::vector<double> par_prefit;
    std::vector<double> par_postfit;
    std::vector<double> par_errfit;
    std::vector<double> par_toydata;
    std::vector<double> vec_chi2_stat;
    std::vector<double> vec_chi2_sys;
};
#endif
