//////////////////////////////////////////////////////////
//
//  A container with subset of necessary event
//  information for CCQE analysis
//  Copyright Sara Bolognesi
//
//  Created: Thu Jun  6 11:28:13 CEST 2013
//  Modified:
//
//////////////////////////////////////////////////////////
#ifndef __AnaEvent_hh__
#define __AnaEvent_hh__

#include <iostream>

#include <TMath.h>

class AnaEvent
{
public:
    AnaEvent(Long64_t evid) //unique event id
    {
        m_evid       = evid;
        m_evtype     = 0;
        m_reaction   = -1;
        m_sample     = -1;
        m_trueEnu    = -999.0;
        m_recEnu     = -999.0;
        m_truePtrk   = -999.0;
        m_trueThtrk  = -999.0;
        m_trueCThtrk = -999.0;
        m_recPtrk    = -999.0;
        m_recThtrk   = -999.0;
        m_recCThtrk  = -999.0;
        m_wght       = 1.0;
        m_wghtMC       = 1.0;
	m_veract = -999.0;

	//add20170511
        m_recang1trk = -999.0;
        m_recang2trk = -999.0;
        m_recangopening = -999.0;
        m_recangcoplanarity = -999.0;
        m_recqsq = -999.0;
    }
    ~AnaEvent(){;}
    
    //Set/Get methods
    void SetEvType(int val){ m_evtype = val; }
    int GetEvType(){ return m_evtype; }
    
    void SetReaction(int val){ m_reaction = val; }
    int GetReaction(){ return m_reaction; }
    
    void SetSampleType(int val){ m_sample = val; }
    int GetSampleType(){ return m_sample; }
    
    Long64_t GetEvId(){ return m_evid; }
    
    void SetTrueEnu(double val) {m_trueEnu = val;}
    double GetTrueEnu(){ return m_trueEnu; }
    
    void SetRecEnu(double val){ m_recEnu = val; }
    double GetRecEnu(){ return m_recEnu; }
    
    void SetTruePtrk(double val){ m_truePtrk = val; }
    double GetTruePtrk(){ return m_truePtrk; }
    
    void SetRecPtrk(double val){ m_recPtrk = val; }
    double GetRecPtrk(){ return m_recPtrk; }
    
    void SetTrueThtrk(double val)
    {
        m_trueThtrk  = val;
        m_trueCThtrk = TMath::Cos(m_trueThtrk);
    }
    void SetTrueCThtrk(double val)
    {
        m_trueCThtrk = val;
        m_trueThtrk  = TMath::ACos(m_trueCThtrk);
    }
    double GetTrueThtrk(){ return m_trueThtrk; }
    double GetTrueCThtrk(){ return m_trueCThtrk; }
    
    void SetRecThtrk(double val)
    {
        m_recThtrk  = val;
        m_recCThtrk = TMath::Cos(m_recThtrk);
    }
    void SetRecCThtrk(double val)
    {
        m_recCThtrk = val;
        m_recThtrk  = TMath::ACos(m_recCThtrk);
    }
    double GetRecThtrk(){ return m_recThtrk; }
    double GetRecCThtrk(){ return m_recCThtrk; }
    
    void SetEvWght(double val){ m_wght  = val; }
    void SetEvWghtMC(double val){ m_wghtMC  = val; }
    void AddEvWght(double val){ m_wght *= val; }
    double GetEvWght(){ return m_wght; }
    double GetEvWghtMC(){ return m_wghtMC; }

    void SetVeract(double val){ m_veract = val; }
    double GetVeract(){ return m_veract; }

	//add20170511
    void SetRecAng1trk(double val){ m_recang1trk = val; }
    double GetRecAng1trk(){ return m_recang1trk; }

    void SetRecAng2trk(double val){ m_recang2trk = val; }
    double GetRecAng2trk(){ return m_recang2trk;}

    void SetRecAngOpenging(double val){ m_recangopening = val; }
    double GetRecAngOpening(){ return m_recangopening;}

    void SetRecAngCoplanarity(double val){ m_recangcoplanarity = val; }
    double GetRecAngCoplanarity(){ return m_recangcoplanarity;}

    void SetRecQsq(double val){ m_recqsq = val; }
    double GetRecQsq(){ return m_recqsq;}

    void Print()
    {
        std::cout<<"Event ID "<<m_evid<<std::endl
        <<"  Reaction        "<<GetReaction()<<std::endl
        <<"  Sample          "<<GetSampleType()<<std::endl
        <<"  True energy     "<<GetTrueEnu()<<std::endl
        <<"  Recon energy    "<<GetRecEnu()<<std::endl
        <<"  True track mom  "<<GetTruePtrk()<<std::endl
        <<"  Recon track mom "<<GetRecPtrk()<<std::endl
        <<"  True track cth  "<<GetTrueCThtrk()<<std::endl
        <<"  Recon track cth "<<GetRecCThtrk()<<std::endl
        <<"  True track th   "<<GetTrueThtrk()<<std::endl
        <<"  Recon track th  "<<GetRecThtrk()<<std::endl
        <<"  Event weight    "<<GetEvWght()<<std::endl
        <<"  Event weight MC   "<<GetEvWghtMC()<<std::endl;
    }
    
private:
    Long64_t m_evid;     //unique event id
    int m_evtype;        //0 - MC, 1 - Data event
    int m_reaction;      //reaction type
    int m_sample;        //sample type (aka topology)
    double m_trueEnu;    //true nu energy
    double m_recEnu;     //recon nu energy
    double m_truePtrk;   //true track momentum
    double m_trueThtrk;  //true track angle
    double m_trueCThtrk; //true cos track angle
    double m_recPtrk;    //recon track momentum
    double m_recThtrk;   //recon track angle
    double m_recCThtrk;  //recon cos track angle
    double m_wght;       //event weight
    double m_wghtMC;       //event weight from original MC

    double m_veract; 
	
	 //add20170511
    double m_recang1trk;    // recon 1trk angle
    double m_recang2trk;    // recon 2trk angle
    double m_recangopening; // opening angle
    double m_recangcoplanarity;    // coplanairity
    double m_recqsq;    //qsquare
};

#endif
