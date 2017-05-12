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
#ifndef __AnaSample_hh__
#define __AnaSample_hh__

#include <string>
#include <vector>

#include <TH2D.h>
#include <TDirectory.h>
#include <TRandom3.h>

#include "AnaEvent.hh"

///////////////////////////////////////
// Class definition
///////////////////////////////////////
class AnaSample
{
public:
    AnaSample();
    ~AnaSample();
    
    void ClearEvents();
    int GetN();
    int GetSampleType(){ return m_sampleid; }
    AnaEvent* GetEvent(int evnum);
    void AddEvent(AnaEvent &event);
    void ResetWeights();
    void PrintStats();
    void SetNorm(double val){ m_norm = val; }
    double GetNorm(){ return m_norm; }
    
    //virtual functions
    virtual void SetData(TObject *data) = 0;
    virtual void FillEventHisto(int datatype) = 0;
    virtual double CalcChi2() = 0;
    virtual void Write(TDirectory *dirout, const char *bsname, int fititer) = 0;
    
protected:
    int m_sampleid;
    std::string m_name;
    std::vector<AnaEvent> m_events;
    double m_norm;
};

#endif
