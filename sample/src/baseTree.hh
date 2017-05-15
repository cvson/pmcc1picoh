//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 16 13:17:37 2015 by ROOT version 5.34/23
// from TTree tree/tree
// found on file: /home/t2k/cvson/gpfs/ingrid/backup/dataProcess/fix20150420/pm_merged_ccqe_tot_addpidFFnew.root
//////////////////////////////////////////////////////////

#ifndef baseTree_h
#define baseTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <vector>
#include <string>
#include "AnaEvent.hh"
#include "AnaSample.hh"
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class baseTree {
    public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain
    
    // Declaration of leaf types
    Int_t           Ntrack;
    Int_t           Ningtrack;
    Float_t         muang;
    Float_t         pang;
    Float_t         ppe;
    Float_t         mupe;
    Float_t         opening;
    Float_t         coplanarity;
    Float_t         norm;
    Float_t         totcrsne;
    Int_t           inttype;
    Float_t         nuE;
    Int_t           mufc;
    Int_t           pfc;
    Int_t           pingridfc;
    Int_t           mupdg;
    Int_t           ppdg;
    Float_t         veract;
    Float_t         mumucl;
    Float_t         pmucl;
    Float_t         muang_t;
    Float_t         pang_t;
    Float_t         xreco;
    Float_t         yreco;
    Float_t         zreco;
    Float_t         xnu;
    Float_t         ynu;
    Float_t         znu;
    Float_t         exptime;
    Float_t         startxch;
    Float_t         startych;
    Int_t           startxpln;
    Int_t           startypln;
    Float_t         endxch;
    Float_t         endych;
    Int_t           endxpln;
    Int_t           endypln;
    Float_t         pstartxch;
    Float_t         pstartych;
    Int_t           pstartxpln;
    Int_t           pstartypln;
    Float_t         pendxch;
    Float_t         pendych;
    Int_t           pendxpln;
    Int_t           pendypln;
    Float_t         rangetot;
    Float_t         range;
    Float_t         muscirange;
    Float_t         muironrange;
    Int_t           pene;
    Float_t         prangetot;
    Float_t         prange;
    Float_t         pscirange;
    Float_t         pironrange;
    Int_t           ppene;
    Float_t         tmomtrans;
    Int_t           fileIndex;
    Float_t         pid;
    Float_t         pid1pres;
    Float_t         pidccqe;
    Float_t         pidfsi;
    Float_t         pidfsi1pres;
    Float_t         pidfsiccqe;
    //newadd
    Float_t         pidfsi1prescor;
    Float_t         pidfsiccqecor;
    Float_t         pidfsinorange;
    Float_t         pidfsi1prescornorange;
    Float_t         pidfsiccqecornorange;
    //add count
    Int_t         npioncount;
    Int_t         nmuoncount;
    Int_t         nprotoncount;   
     
    // List of branches
    TBranch        *b_Ntrack;   //!
    TBranch        *b_Ningtrack;   //!
    TBranch        *b_muang;   //!
    TBranch        *b_pang;   //!
    TBranch        *b_ppe;   //!
    TBranch        *b_mupe;   //!
    TBranch        *b_opening;   //!
    TBranch        *b_coplanarity;   //!
    TBranch        *b_norm;   //!
    TBranch        *b_totcrsne;   //!
    TBranch        *b_inttype;   //!
    TBranch        *b_nuE;   //!
    TBranch        *b_mufc;   //!
    TBranch        *b_pfc;   //!
    TBranch        *b_pingridfc;   //!
    TBranch        *b_mupdg;   //!
    TBranch        *b_ppdg;   //!
    TBranch        *b_veract;   //!
    TBranch        *b_mumucl;   //!
    TBranch        *b_pmucl;   //!
    TBranch        *b_muang_t;   //!
    TBranch        *b_pang_t;   //!
    TBranch        *b_xreco;   //!
    TBranch        *b_yreco;   //!
    TBranch        *b_zreco;   //!
    TBranch        *b_xnu;   //!
    TBranch        *b_ynu;   //!
    TBranch        *b_znu;   //!
    TBranch        *b_exptime;   //!
    TBranch        *b_startxch;   //!
    TBranch        *b_startych;   //!
    TBranch        *b_startxpln;   //!
    TBranch        *b_startypln;   //!
    TBranch        *b_endxch;   //!
    TBranch        *b_endych;   //!
    TBranch        *b_endxpln;   //!
    TBranch        *b_endypln;   //!
    TBranch        *b_pstartxch;   //!
    TBranch        *b_pstartych;   //!
    TBranch        *b_pstartxpln;   //!
    TBranch        *b_pstartypln;   //!
    TBranch        *b_pendxch;   //!
    TBranch        *b_pendych;   //!
    TBranch        *b_pendxpln;   //!
    TBranch        *b_pendypln;   //!
    TBranch        *b_rangetot;   //!
    TBranch        *b_range;   //!
    TBranch        *b_muscirange;   //!
    TBranch        *b_muironrange;   //!
    TBranch        *b_pene;   //!
    TBranch        *b_prangetot;   //!
    TBranch        *b_prange;   //!
    TBranch        *b_pscirange;   //!
    TBranch        *b_pironrange;   //!
    TBranch        *b_ppene;   //!
    TBranch        *b_tmomtrans;   //!
    TBranch        *b_fileIndex;   //!
    TBranch        *b_pid;   //!
    TBranch        *b_pid1pres;   //!
    TBranch        *b_pidccqe;   //!
    TBranch        *b_pidfsi;   //!
    TBranch        *b_pidfsi1pres;   //!
    TBranch        *b_pidfsiccqe;   //!
    //newadd
    TBranch        *b_pidfsi1prescor;   //!
    TBranch        *b_pidfsiccqecor;   //!
    TBranch        *b_pidfsinorange;   //!
    TBranch        *b_pidfsi1prescornorange;   //!
    TBranch        *b_pidfsiccqecornorange;   //!
    //add count
    TBranch        *b_npioncount;   //!
    TBranch        *b_nmuoncount;   //!
    TBranch        *b_nprotoncount;   //!

    baseTree(TTree *tree=0);
    virtual ~baseTree();
    virtual Int_t    CutPreselection(Long64_t entry);
    virtual Int_t    CutMVA(Long64_t entry,Float_t cutValue);
    virtual Int_t    CutNOM(Long64_t entry);
    virtual Int_t    CutTOPO(Long64_t entry, Int_t topotype);
    virtual Int_t    CutSignalR(Long64_t entry);
    virtual Int_t    CutSignalRHiVeract(Long64_t entry);
    virtual Int_t    CutSignalRNoVeract(Long64_t entry);
    virtual Int_t    CutCR1(Long64_t entry);
    virtual Int_t    CutCR23Comb(Long64_t entry);
    virtual Int_t    CutCR1NonVeract(Long64_t entry);
    virtual Int_t    CutCR23CombNonVeract(Long64_t entry);
    virtual Int_t    CutCR23QEIsolated(Long64_t entry);
    virtual Int_t    CutCR23QEIsolatedLoQsq(Long64_t entry);//lowQsq <0.05
    virtual Int_t    CutCR23QEIsolatedHiQsq(Long64_t entry);//highQsq >0.05
    
    virtual Int_t    CutCR23QEFreed(Long64_t entry);
    virtual Int_t    CutCR23QEFreedLowVeract(Long64_t entry);
    
    virtual Int_t    CutCR23QEFreedHighVeract(Long64_t entry);
    virtual Int_t    CutCR23QEFreedHighVeractHiResPID(Long64_t entry);//pid1pres>0
    virtual Int_t    CutCR23QEFreedHighVeractLoResPID(Long64_t entry);//pid1pres<0
    
    virtual Int_t    CutMore2Track(Long64_t entry);
    virtual Int_t    CutMore2TrackHiResPID(Long64_t entry);//pid>-0.125
    virtual Int_t    CutMore2TrackLoResPID(Long64_t entry);//pid<-0.125 && veract<475
    virtual Int_t    CutMore2TrackAllElse(Long64_t entry);
    virtual Int_t    CutMore2TrackSignal(Long64_t entry);
    
    virtual Int_t    CutCCQE1track(Long64_t entry);
    virtual Int_t    CutCCQE1trackLoQsq(Long64_t entry);//lowQsq <0.05
    virtual Int_t    CutCCQE1trackHiQsq(Long64_t entry);//highQsq >0.05
    
    virtual Int_t    Cut1picohKikawa(Long64_t entry);
    virtual Int_t    Cut1picohKikawaNoVeract(Long64_t entry);
    virtual Int_t    Cut1picohKikawaHiVeract(Long64_t entry);
    virtual Int_t    CutCCQEKikawa2trk(Long64_t entry);
    virtual Int_t    CutCCQEPID2trk(Long64_t entry);
    virtual Int_t    CutSamplebyID(Long64_t entry,Int_t myid);//define consistent with xsecparameter
    
    virtual Int_t    CutTopologybyID(Long64_t entry, Int_t topoID);
    virtual Int_t    CutTopologyFSIbyID(Long64_t entry, Int_t topoID);
    virtual Int_t    CutTopology2OptimizeFSIbyID(Long64_t entry, Int_t topoID);
    virtual Int_t    CutInteractionbyID(Long64_t entry, Int_t interactID);
    virtual Int_t    CutInteractionbyIDGENIE(Long64_t entry, Int_t interactID);
    virtual Int_t    CutInteractionSBbyID(Long64_t entry, Int_t interactID);
    virtual Int_t    CutTrueTrackbyID(Long64_t entry, Int_t trackID);
    
    virtual Int_t    GetEntry(Long64_t entry);
    
    //Cut for Timing syst.
    virtual Int_t    CutTimingbyIndex(Long64_t entry, Int_t index);
    virtual Int_t    CutFVbyIndex(Long64_t entry, Int_t index);
    virtual Int_t    CutVetobyIndex(Long64_t entry, Int_t index);
    
    //this is for AnaEvent
    virtual Int_t    GetEventType(Long64_t entry);
    virtual Int_t    GetSampleType(Long64_t entry);//this can be removed
    virtual Int_t    GetInteractionType(Long64_t entry);
    virtual double   GetPrec(double rangeval);
    virtual double   GetErec(double p, double theta);
    virtual double   GetQsq(double p, double theta);
    virtual double   GetXbjorken(double p, double theta);
    virtual double   GetInelasticity(double p, double theta);
    
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     GenerateDetSyst(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges);
    virtual void     MakeBasicHisto(TString ipFile, TString opFile);
    virtual void     MakeBasicHistoBySample(TString ipFile, TString opFile, Int_t ithtopo);
    virtual void     MakeBasicHistoBySamplev532(TString ipFile, TString opFile, Int_t ithtopo);
    virtual void     MakeBasicHistoBySampleGENIE(TString ipFile, TString opFile, Int_t ithtopo);
    virtual void     CheckVeract(TString ipFile, TString opFile);
    virtual void     CheckFSI(TString ipFile, TString opFile);
    virtual void     OptimizeFSICut(TString ipFile, TString opFile);
    virtual void     GetEvents(std::vector<AnaSample*> ana_samples);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef baseTree_cxx
baseTree::baseTree(TTree *tree) : fChain(0)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../datafsipionFS/datamc_pionFSpm_merged_ccqe_addpidFFnew_addnue.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("../../datafsipionFS/datamc_pionFSpm_merged_ccqe_addpidFFnew_addnue.root");
        }
        f->GetObject("tree",tree);
        
    }
    Init(tree);
}

baseTree::~baseTree()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t baseTree::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t baseTree::LoadTree(Long64_t entry)
{
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void baseTree::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).
    
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);
    
    fChain->SetBranchAddress("Ntrack", &Ntrack, &b_Ntrack);
    fChain->SetBranchAddress("Ningtrack", &Ningtrack, &b_Ningtrack);
    fChain->SetBranchAddress("muang", &muang, &b_muang);
    fChain->SetBranchAddress("pang", &pang, &b_pang);
    fChain->SetBranchAddress("ppe", &ppe, &b_ppe);
    fChain->SetBranchAddress("mupe", &mupe, &b_mupe);
    fChain->SetBranchAddress("opening", &opening, &b_opening);
    fChain->SetBranchAddress("coplanarity", &coplanarity, &b_coplanarity);
    fChain->SetBranchAddress("norm", &norm, &b_norm);
    fChain->SetBranchAddress("totcrsne", &totcrsne, &b_totcrsne);
    fChain->SetBranchAddress("inttype", &inttype, &b_inttype);
    fChain->SetBranchAddress("nuE", &nuE, &b_nuE);
    fChain->SetBranchAddress("mufc", &mufc, &b_mufc);
    fChain->SetBranchAddress("pfc", &pfc, &b_pfc);
    fChain->SetBranchAddress("pingridfc", &pingridfc, &b_pingridfc);
    fChain->SetBranchAddress("mupdg", &mupdg, &b_mupdg);
    fChain->SetBranchAddress("ppdg", &ppdg, &b_ppdg);
    fChain->SetBranchAddress("veract", &veract, &b_veract);
    fChain->SetBranchAddress("mumucl", &mumucl, &b_mumucl);
    fChain->SetBranchAddress("pmucl", &pmucl, &b_pmucl);
    fChain->SetBranchAddress("muang_t", &muang_t, &b_muang_t);
    fChain->SetBranchAddress("pang_t", &pang_t, &b_pang_t);
    fChain->SetBranchAddress("xreco", &xreco, &b_xreco);
    fChain->SetBranchAddress("yreco", &yreco, &b_yreco);
    fChain->SetBranchAddress("zreco", &zreco, &b_zreco);
    fChain->SetBranchAddress("xnu", &xnu, &b_xnu);
    fChain->SetBranchAddress("ynu", &ynu, &b_ynu);
    fChain->SetBranchAddress("znu", &znu, &b_znu);
    fChain->SetBranchAddress("exptime", &exptime, &b_exptime);
    fChain->SetBranchAddress("startxch", &startxch, &b_startxch);
    fChain->SetBranchAddress("startych", &startych, &b_startych);
    fChain->SetBranchAddress("startxpln", &startxpln, &b_startxpln);
    fChain->SetBranchAddress("startypln", &startypln, &b_startypln);
    fChain->SetBranchAddress("endxch", &endxch, &b_endxch);
    fChain->SetBranchAddress("endych", &endych, &b_endych);
    fChain->SetBranchAddress("endxpln", &endxpln, &b_endxpln);
    fChain->SetBranchAddress("endypln", &endypln, &b_endypln);
    fChain->SetBranchAddress("pstartxch", &pstartxch, &b_pstartxch);
    fChain->SetBranchAddress("pstartych", &pstartych, &b_pstartych);
    fChain->SetBranchAddress("pstartxpln", &pstartxpln, &b_pstartxpln);
    fChain->SetBranchAddress("pstartypln", &pstartypln, &b_pstartypln);
    fChain->SetBranchAddress("pendxch", &pendxch, &b_pendxch);
    fChain->SetBranchAddress("pendych", &pendych, &b_pendych);
    fChain->SetBranchAddress("pendxpln", &pendxpln, &b_pendxpln);
    fChain->SetBranchAddress("pendypln", &pendypln, &b_pendypln);
    fChain->SetBranchAddress("rangetot", &rangetot, &b_rangetot);
    fChain->SetBranchAddress("range", &range, &b_range);
    fChain->SetBranchAddress("muscirange", &muscirange, &b_muscirange);
    fChain->SetBranchAddress("muironrange", &muironrange, &b_muironrange);
    fChain->SetBranchAddress("pene", &pene, &b_pene);
    fChain->SetBranchAddress("prangetot", &prangetot, &b_prangetot);
    fChain->SetBranchAddress("prange", &prange, &b_prange);
    fChain->SetBranchAddress("pscirange", &pscirange, &b_pscirange);
    fChain->SetBranchAddress("pironrange", &pironrange, &b_pironrange);
    fChain->SetBranchAddress("ppene", &ppene, &b_ppene);
    fChain->SetBranchAddress("tmomtrans", &tmomtrans, &b_tmomtrans);
    fChain->SetBranchAddress("fileIndex", &fileIndex, &b_fileIndex);
    fChain->SetBranchAddress("pid", &pid, &b_pid);
    fChain->SetBranchAddress("pid1pres", &pid1pres, &b_pid1pres);
    fChain->SetBranchAddress("pidccqe", &pidccqe, &b_pidccqe);
    fChain->SetBranchAddress("pidfsi", &pidfsi, &b_pidfsi);
    fChain->SetBranchAddress("pidfsi1pres", &pidfsi1pres, &b_pidfsi1pres);
    fChain->SetBranchAddress("pidfsiccqe", &pidfsiccqe, &b_pidfsiccqe);
    
    //newadd
    fChain->SetBranchAddress("pidfsi1prescor", &pidfsi1prescor, &b_pidfsi1prescor);
    fChain->SetBranchAddress("pidfsiccqecor", &pidfsiccqecor, &b_pidfsiccqecor);
    fChain->SetBranchAddress("pidfsinorange", &pidfsinorange, &b_pidfsinorange);
    fChain->SetBranchAddress("pidfsi1prescornorange", &pidfsi1prescornorange, &b_pidfsi1prescornorange);
    fChain->SetBranchAddress("pidfsiccqecornorange", &pidfsiccqecornorange, &b_pidfsiccqecornorange);
    
    //add count
    fChain->SetBranchAddress("npioncount", &npioncount, &b_npioncount);
    fChain->SetBranchAddress("nmuoncount", &nmuoncount, &b_nmuoncount);
    fChain->SetBranchAddress("nprotoncount", &nprotoncount, &b_nprotoncount);

    Notify();
}

Bool_t baseTree::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.
    
    return kTRUE;
}

void baseTree::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
//May require contained and penetrated only
Int_t baseTree::CutPreselection(Long64_t entry)
{
    if (Ntrack==2 && pang<90 && !(mufc==0 && pene<9)) return 1;
    //if (Ntrack>1 && pang<90 && !(mufc==0 && pene<9)) return 1;
    else return -1;
}
Int_t baseTree::CutMVA(Long64_t entry, Float_t cutValue)
{
    if (pid>cutValue) return 1;
    else return -1;
}
Int_t baseTree::CutNOM(Long64_t entry)
{
    if (mumucl>0.6 && pmucl>0.25 && pang<90 && muang_t<15 && veract*7.6634e-2<34) {
        return 1;
    }
    else return -1;
}
Int_t baseTree::CutTOPO(Long64_t entry, Int_t topotype){
    if (topotype==0) return 1;
    //stoped
    else if (topotype==1) {
        if (mufc==1) {
            return 1;
        }
        else return -1;
    }
    //penetrated
    else if (topotype==2)   {
        if (mufc==0 && pene==9) {
            return 1;
        }
        else return -1;
    }
    //side exit
    else if (topotype==3)   {
        if (mufc==0 && pene<9) {
            return 1;
        }
        else return -1;
    }
    else return 1;
}
//change to validate MVA
//signal enhanced for Analysis I
Int_t    baseTree::CutSignalR(Long64_t entry){
    if (CutPreselection(entry)>0 && pidfsi>0.05 && veract*7.6634e-2<50 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/) {//opt1, opt2, final
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutSignalRHiVeract(Long64_t entry){
    if (CutPreselection(entry)>0 && pidfsi>0.05 && veract*7.6634e-2>50 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/) {//opt1, opt2, final
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutSignalRNoVeract(Long64_t entry){
    if (CutPreselection(entry)>0 && pidfsi>0.05 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/) {//opt1, opt2, final
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutCR1(Long64_t entry){
    if (CutPreselection(entry)>0 && Ntrack==2 && pidfsi>0.0 && veract*7.6634e-2>50 && veract*7.6634e-2<100 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/) {
    //if (CutPreselection(entry)>0 && pidfsi>0.05 && veract*7.6634e-2>50 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/) {//opt9, final
    
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23Comb(Long64_t entry){
    if (Ntrack>2 && pang<90 && pidfsi>0.0 /*&& pidfsi1prescor>-0.1 && pidfsiccqecor<0.1*/ && !(mufc==0 && pene<9) /*&& GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15*/ && veract*7.6634e-2>50 && veract*7.6634e-2<100) {//final
    
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR1NonVeract(Long64_t entry){

    if (CutPreselection(entry)>0 && veract*7.6634e-2>50 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15 && pidfsi>0.05) {//opt9, final

        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23CombNonVeract(Long64_t entry){
    if (Ntrack>2 && pang<90 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && !(mufc==0 && pene<9) && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15 && pidfsi>0.05  && veract*7.6634e-2>50) {//final

        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutCR23QEIsolated(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid<-0.125 && veract>0 && pidccqe>-0.075 ) {
    if (CutPreselection(entry)>0 && pidfsi<-0.05 && pidfsi1pres<0.04) {//final
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23QEIsolatedLoQsq(Long64_t entry){
    if (CutCR23QEIsolated(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23QEIsolatedHiQsq(Long64_t entry){
    if (CutCR23QEIsolated(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6>0.05) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutCR23QEFreed(Long64_t entry){
    if (CutPreselection(entry)>0 && pidfsi<-0.05 && pidfsi1pres>0.04) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23QEFreedLowVeract(Long64_t entry){
    if (CutCR23QEFreed(entry)>0 && veract*7.6634e-2<50 ) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23QEFreedHighVeract(Long64_t entry){
    if (CutCR23QEFreed(entry)>0 && veract*7.6634e-2>50) {
        return 1;
    }
    else return -1;
}
//NOTHING TO DO WITH THIS
Int_t    baseTree::CutCR23QEFreedHighVeractHiResPID(Long64_t entry){
    if (CutCR23QEFreedHighVeract(entry)>0 && pid1pres>0) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCR23QEFreedHighVeractLoResPID(Long64_t entry){
    if (CutCR23QEFreedHighVeract(entry)>0 && pid1pres<0) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutMore2Track(Long64_t entry){
    if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9)) {
    
        
        return 1;
    }
    else return -1;
}
//Temporary
Int_t    baseTree::CutMore2TrackHiResPID(Long64_t entry){
    //if (CutMore2Track(entry)>0 && pid>-0.125) { //col meeting Oct 2015
    //if (CutMore2Track(entry)>0 && pid>-0.125 && veract>475) {// optimized
    if (CutMore2Track(entry)>0 && pidfsi>-0.05 && veract*7.6634e-2>50 && pidfsi1pres>0.07) {//opt9,final
    
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutMore2TrackLoResPID(Long64_t entry){
    //if (CutMore2Track(entry)>0 && pid<-0.125 && veract<475) {
    if (CutMore2Track(entry)>0  && pidfsi<-0.05 && veract*7.6634e-2<50 && pidfsi1pres>0.07) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutMore2TrackAllElse(Long64_t entry){
    if (CutMore2Track(entry)>0 && pidfsi<-0.05 && veract*7.6634e-2>50 && pidfsi1pres>0.07) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutMore2TrackSignal(Long64_t entry){
    if (CutMore2Track(entry)>0 && pidfsi>-0.05 && veract*7.6634e-2<50) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutCCQE1track(Long64_t entry){
    if (Ntrack==1 && mumucl>0.6 && Ningtrack==1 && !(mufc==0 && pene<9)) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCCQE1trackLoQsq(Long64_t entry){
    if (CutCCQE1track(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCCQE1trackHiQsq(Long64_t entry){
    if (CutCCQE1track(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6>0.05) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::Cut1picohKikawa(Long64_t entry){
    if (Ntrack==2 && mumucl>0.6 && pmucl>0.25 && pang<90 && muang_t<15 && veract*7.6634e-2<34) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::Cut1picohKikawaNoVeract(Long64_t entry){
    if (Ntrack==2 && mumucl>0.6 && pmucl>0.25 && pang<90 && muang_t<15) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::Cut1picohKikawaHiVeract(Long64_t entry){
    if (Ntrack==2 && mumucl>0.6 && pmucl>0.25 && pang<90 && muang_t<15 && veract*7.6634e-2>50) {
        return 1;
    }
    else return -1;
}

Int_t    baseTree::CutCCQEKikawa2trk(Long64_t entry){
    if (Ntrack==2 && pang<90 && Ningtrack==1 && mumucl>0.6 && pmucl<0.6 && opening>60 && coplanarity>150) {
        return 1;
    }
    else return -1;
}
Int_t    baseTree::CutCCQEPID2trk(Long64_t entry){
    if (Ntrack==2 && pang<90 && pidccqe>0.05) {
        return 1;
    }
    else return -1;
}


Int_t baseTree::CutSamplebyID(Long64_t entry, Int_t myid)
{
    
    //signal region
    if (myid==0){
        if (CutPreselection(entry)>0 && pidfsi>0.08 && mumucl>0.6 && pmucl>0.25) return 1;
        else return -1;
    }
    //CR1
    /*else if (myid==1){
        if (CutCR1(entry)>0 || CutCR23Comb(entry)>0) return 1;
        else return -1;
    }*/
    
    //CR1
    else if (myid==1){
        if (CutPreselection(entry)>0 && pidfsi<=0.08 && mumucl>0.6 && pmucl>0.25) return 1;
        else return -1;
    }
    //CR2
    else if (myid==2){
        //if (CutCR23Comb(entry)>0) return 1;
        if (CutPreselection(entry)>0 && pidfsi<=0.08 && mumucl>0.6 && pmucl<=0.25) return 1;
	else return -1;
    }
   
     else if (myid==3){
        //if (CutCR23Comb(entry)>0) return 1;
        if (CutPreselection(entry)>0 && pidfsi<=0.08 && mumucl<=0.6) return 1;
        else return -1;
    } 
    
    
    else return -1;
    
}



//0 all, 1 sig, 2 cr1, 3 cr2a, 4 cr2b, 5 cr2c
// 6 more than 2trk
//7 ccq with one track
Int_t baseTree::CutTopologybyID(Long64_t entry, Int_t topoID)
{
    //all
    if (topoID==0) return 1;//all
    //all w/preselection
    else if (topoID==1) {
        if (CutPreselection(entry)>0) return 1;//with preselection, 2trk
        else return -1;
    }
    //plot for include pid cut only
    else if (topoID==2) {
        if (CutPreselection(entry)>0 && pidfsi>0.05) return 1;//with preselection and pid
        else return -1;
    }
    //SIG
    else if (topoID==3) {
        if (CutSignalR(entry)>0) return 1;//selected
        else return -1;
    }
    //CRI
    else if (topoID==4) {
        if (CutCR1(entry)>0) return 1;//cr1 optimized
        else return -1;
    }
    //CRII
    else if (topoID==5) {
        if (CutCR23Comb(entry)>0) return 1;//cr2-A: CCQ isolated
        else return -1;
    }
    //CRIII
    else if (topoID==6) {
        if (CutCR1(entry)>0 || CutCR23Comb(entry)>0) return 1;//cr2-B: CCQ isolated and low veract
        else return -1;
    }
    /////////////////////Newadd 2016/05/19
    //presel + other pid
    else if (topoID==7) {
        if (CutPreselection(entry)>0 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1) return 1;
        else return -1;
    }
    //presel + other pid+ Qsq
    else if (topoID==8) {
        if (CutPreselection(entry)>0 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15) return 1;
        else return -1;
    }
    //presel + other pid + veract
    else if (topoID==9) {
        if (CutPreselection(entry)>0 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && veract*7.6634e-2<50) return 1;
        else return -1;
    }
    //presel + other pid + Qsq + veract
    else if (topoID==10) {
        if (CutPreselection(entry)>0 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15 && veract*7.6634e-2<50) return 1;
        else return -1;
    }
    //presel + other pid + Qsq + non veract
    else if (topoID==11) {
        if (CutPreselection(entry)>0 && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15 && veract*7.6634e-2>50) return 1;
        else return -1;
    }
    
    //presel + veract
    else if (topoID==12) {
        //if (CutPreselection(entry)>0 && veract*7.6634e-2<50) return 1;
        if (CutPreselection(entry)>0 && pidfsi<0.0) return 1;
        else return -1;
    }
    //presel + Qsq
    else if (topoID==13) {
        if (CutPreselection(entry)>0 && pidfsi<0.05) return 1;
        //if (CutPreselection(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15) return 1;
        else return -1;
    }
    //m2trk presel
    else if (topoID==14) {
        if (CutPreselection(entry)>0 && veract*7.6634e-2>50) return 1;
        //if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && veract*7.6634e-2<50) return 1;
        else return -1;
    }
    
    //m2trk presel + other pid
    else if (topoID==15) {
        //if (Ntrack>2  && pang<90 && !(mufc==0 && pene<9) && veract*7.6634e-2<50 && pidfsi>0.05) return 1;
       if (CutPreselection(entry)>0 && CutSignalRNoVeract(entry)>0 && !(Cut1picohKikawaNoVeract(entry)>0)) return 1;  
       else return -1;
    }
    //m2trk presel + other pid + veract
    else if (topoID==16) {
        //if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && pidfsi>0.05) return 1;
       if (CutPreselection(entry)>0 && !(CutSignalRNoVeract(entry))>0 && (Cut1picohKikawaNoVeract(entry)>0)) return 1;  
       else return -1;
    }
    //m2trk presel + other pid + Qsq
    else if (topoID==17) {
        //if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15) return 1;
      if (CutPreselection(entry)>0 && (CutSignalRNoVeract(entry)>0&&Cut1picohKikawaNoVeract(entry)>0)) return 1;  
      else return -1;
    }
    
    //m2trk presel + other pid + nonveract+ Qsq
    else if (topoID==18) {
        //if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && pidfsi1prescor>-0.1 && pidfsiccqecor<0.1 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.15 && veract*7.6634e-2>50) return 1;
       if (CutPreselection(entry)>0 && (CutSignalRNoVeract(entry)>0||Cut1picohKikawaNoVeract(entry)>0)) return 1; 
       else return -1;
    }
    //cr1 but nonveract
    else if (topoID==19) {
        //if (CutCR1NonVeract(entry)>0) return 1;
        if (CutPreselection(entry)>0 && !(CutSignalRNoVeract(entry)>0||Cut1picohKikawaNoVeract(entry)>0)) return 1;
        //if (CutCR1NonVeract(entry)>0 && pidfsi>0.05 && veract*7.6634e-2<120) return 1;
        //if (CutCR1(entry)>0 && pidfsi<-0.1) return 1;
        else return -1;
    }

    //cr2 but non veract
    else if (topoID==20) {
        //if (CutCR23CombNonVeract(entry)>0 && pidfsi>0.05) return 1;
         //if (CutCR23Comb(entry)>0 && pidfsi<-0.1) return 1;
         if (CutPreselection(entry)>0 && CutSignalRHiVeract(entry)>0) return 1;
         else return -1;
    }
    
    //cr1||cr2 but non veract 
    else if (topoID==21) {
        //if ((CutCR1NonVeract(entry)>0 || CutCR23CombNonVeract(entry)>0)) return 1;
        //if ((CutCR1(entry)>0 || CutCR23Comb(entry)>0) && pidfsi<-0.1) return 1;
        if (CutPreselection(entry)>0 && (CutSignalRHiVeract(entry)>0||Cut1picohKikawaHiVeract(entry)>0)) return 1;
        else return -1;
    }
    //TO STUDY VERTEX ACTivity
    //To study vertex activity CCQE 1trk
    else if (topoID==22) {
        //if (CutCCQE1track(entry)>0 ) return 1;
        if (CutPreselection(entry)>0 && (CutSignalRHiVeract(entry)>0)&& !(Cut1picohKikawaHiVeract(entry)>0)) return 1;
        else return -1;
    }
    
    //CCQE 2trk + kikawa
    else if (topoID==23) {
        //if (CutCCQEKikawa2trk(entry)>0) return 1;
        if (CutPreselection(entry)>0 && !(CutSignalRHiVeract(entry)>0) && Cut1picohKikawaHiVeract(entry)>0) return 1;
        else return -1;
    }
    
    //2trk 1mu + 1proton
    else if (topoID==24) {
        //if (Ntrack==2 && Ningtrack==1 && mumucl>0.6 && pmucl<0.6 ) return 1;
       if (CutPreselection(entry)>0 && (CutSignalRHiVeract(entry)>0&&Cut1picohKikawaHiVeract(entry)>0)) return 1; 
       else return -1;
    }
    //2trk 1mu +1pi
    else if (topoID==25) {
        //if (Ntrack==2 && Ningtrack==1 && mumucl>0.6 && pmucl>0.6 ) return 1;
       if (CutPreselection(entry)>0 && !(CutSignalRHiVeract(entry)>0||Cut1picohKikawaHiVeract(entry)>0)) return 1;
        else return -1;
    }
    //2trk 1mu + 1pi + nonveract
    else if (topoID==26) {
        //if (Ntrack==2 && Ningtrack==1 && mumucl>0.6 && pmucl>0.6 && veract*7.6634e-2>50) return 1;
        if (CutPreselection(entry)>0 && Cut1picohKikawaHiVeract(entry)>0) return 1;
        else return -1;
    }
    
    else if (topoID==27) {
        //if (Ntrack>2 && Ningtrack==1 && mumucl>0.6) return 1;
       if (CutPreselection(entry)>0 && Cut1picohKikawaNoVeract(entry)>0) return 1; 
        else return -1;
    }
    else if (topoID==28) {
        //if (Ntrack==1 && mumucl<0.6) return 1;
        if (Cut1picohKikawa(entry)>0) return 1;
        else return -1;
    }
    else if (topoID==29) {
        //if (Ntrack==2 && mumucl<0.6 && pmucl<0.6) return 1;
        if (CutPreselection(entry)>0 &&(Cut1picohKikawa(entry)>0)) return 1;
        else return -1;
    }
    else if (topoID==30) {
        //if (Ntrack>2 && Ningtrack==1 && mumucl>0.6 && pmucl>0.6) return 1;
        if (CutPreselection(entry)>0 && (CutSignalR(entry)>0) && !(Cut1picohKikawa(entry)>0)) return 1;
        else return -1;
    }
    else if (topoID==31) {
        //if (Ntrack>2 && Ningtrack==1 && mumucl>0.6 && pmucl<0.6) return 1;
        if (CutPreselection(entry)>0 && !(CutSignalR(entry)>0) && (Cut1picohKikawa(entry)>0)) return 1;
        else return -1;
    }
    else if (topoID==32) {
        if (CutPreselection(entry)>0 && (CutSignalR(entry)>0 && Cut1picohKikawa(entry)>0)) return 1;
        //if (Ntrack>2 && mumucl<0.6 && pmucl<0.6) return 1;
        else return -1;
    }
     else if (topoID==33) {
        //if (Ntrack==2 && mumucl<0.6 && pmucl>0.6) return 1;
       if (CutPreselection(entry)>0 && (CutSignalR(entry)>0||Cut1picohKikawa(entry)>0)) return 1; 
       else return -1;
    }
   else if (topoID==34) {
       // if (Ntrack>2 && mumucl<0.6 && pmucl>0.6) return 1;
       if (CutPreselection(entry)>0 && !(CutSignalR(entry)>0||Cut1picohKikawa(entry)>0)) return 1;
        else return -1;
    }
    /////////////////////End Newadd 2016/05/19
	  //check more inclusive channel add 20170304 
   else if (topoID==101) {//1mu + 1pro
        if (CutPreselection(entry)>0 && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==102) {//1mu + 1pion
        if (CutPreselection(entry)>0 && mumucl>0.6 && pmucl>0.25) return 1;
        else return -1;
    }
   
   else if (topoID==103) {//1mu + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==104) {//1mu + 1pion in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl>0.25) return 1;
        else return -1;
    }

   else if (topoID==105) {//1mu stopped + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && mufc==1) return 1;
        else return -1;
    }
   else if (topoID==106) {//1mu penestrated + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && mufc!=1) return 1;
        else return -1;
    }
   else if (topoID==107) {//1mu stopped + 1pro + Qsq<0.13 in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.13) return 1;
        else return -1;
    }
   else if (topoID==108) {//1mu stopped + 1pro + Qsq<0.13 in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6>0.13) return 1;
        else return -1;
    }
   else if (topoID==109) {//1mu + 1pro + proton can be backward
        if (Ntrack==2 && pang>90 && !(mufc==0 && pene<9) && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==110) {//1mu + 1pro + proton can be background
        if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==111) {//1mu + 1pro + proton can be background
        if (Ntrack>2 && pang>90 && !(mufc==0 && pene<9) && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }
   
  else if (topoID==112) {//1mu + 1pro + side escaping 
        if (Ntrack==2 && (mufc==0 && pene<9) && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==113) {//1mu + 1pro + sideescaping + >2trk
        if (Ntrack>2 && (mufc==0 && pene<9) && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }

   else if (topoID==114) {//1mu + 1pro + proton can be backward
        if (Ntrack==2 && pang>90) return 1;
        else return -1;
    }

   else if (topoID==115) {//1mu + 1pro + proton can be background
        if (Ntrack>2 && pang>90) return 1;
        else return -1;
    } 

  else if (topoID==116) {//1mu + 1pro + X antipid
        if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25) return 1;
        else return -1;
    }
   
   else if (topoID==117) {//1mu + 1pion + X antipid
        if (Ntrack>2 && pang<90 && !(mufc==0 && pene<9) && pidfsi<0.0 && mumucl>0.6 && pmucl>0.25) return 1;
        else return -1;
    }
   
   else if (topoID==118) {//1mu + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && mufc==1) return 1;
        else return -1;
    }

   else if (topoID==119) {//1mu + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && mufc!=1) return 1;
        else return -1;
    }

    else if (topoID==120) {//1mu + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && pfc==1) return 1;
        else return -1;
    }

    else if (topoID==121) {//1mu + 1pro in antipid
        if (CutPreselection(entry)>0 && pidfsi<0.0 && mumucl>0.6 && pmucl<0.25 && mufc==1 && pfc==1) return 1;
        else return -1;
    }

    else if (topoID==122) {//1mu + 1pro + proton can be backward
        if (Ntrack==2 && pang>90 && mumucl>0.6 && pmucl>0.6) return 1;
        else return -1;
    }

   else if (topoID==123) {//1mu + 1pro + proton can be background
        if (Ntrack==2 && pang>90 && veract*7.6634e-2<30) return 1;
        else return -1;
    }

   else if (topoID==124) {//1mu + 1pro + proton can be background
        if (Ntrack>2 && pang>90 && veract*7.6634e-2<30) return 1;
        else return -1;
    }

   else if (topoID==125) {
        if (CutCCQE1track(entry)>0 && veract*7.6634e-2<30) return 1;
        else return -1;
    }
    
//End add 20170304 
//add 20170510
   else if (topoID==130) {
        if (Ntrack==1 && mumucl<0.25) return 1;
        else return -1;
    }
    
    else if (topoID==131) {
        if (Ntrack==2 && mumucl<0.25 && pmucl<0.25) return 1;
        else return -1;
    }

    else if (topoID==132) {
        if (Ntrack==1 && mumucl<0.25 && mufc==1) return 1;
        else return -1;
    }
     else if (topoID==133) {
        if (Ntrack==1 && mumucl<0.25 && mufc==0 && pene>=9) return 1;
        else return -1;
    }
     else if (topoID==134) {
        if (Ntrack==1 && mumucl<0.25 && mufc==0 && pene<9) return 1;
        else return -1;
    }

     else if (topoID==135) {
        if (Ntrack==2 && mumucl<0.25 && pmucl<0.25 && mufc==1) return 1;
        else return -1;
    }
     else if (topoID==136) {
        if (Ntrack==2 && mumucl<0.25 && pmucl<0.25 && mufc==0 && pene>=9) return 1;
        else return -1;
    }
     else if (topoID==137) {
        if (Ntrack==2 && mumucl<0.25 && pmucl<0.25 && mufc==0 && pene<9) return 1;
        else return -1;
    }

    else return -1;
    
    
}

Int_t baseTree::CutTopologyFSIbyID(Long64_t entry, Int_t topoID)
{
    //all
    if (topoID==0) {
        if (CutPreselection(entry)>0) return 1;
        //if (CutPreselection(entry)>0 && pidfsi>0.075) return 1;
        else return -1;
    }
    //plot for include pid cut only
    else if (topoID==1) {
        //if (CutPreselection(entry)>0 && pid>-0.0125) return 1;
        if (CutPreselection(entry)>0 && pidfsi>0.05) return 1;//CCQE with one track
        else return -1;
    }
    //SIG
    else if (topoID==2) {
        if (CutSignalR(entry)>0) return 1;
        //if (CutPreselection(entry)>0 && pidfsi>0.05 && veract*7.6634e-2<36) return 1;//selected
        else return -1;
    }
    //CRI
    else if (topoID==3) {
        if (CutCR1(entry)>0 || CutMore2TrackHiResPID(entry)>0) return 1;//cr1
        //if (CutPreselection(entry)>0 && pidfsi>0.075 && veract*7.6634e-2>37 && pidfsi1pres>0.05 && pidfsiccqe<0) return 1;//cr1 optimized
        else return -1;
    }
    //CCRES
    else if (topoID==4) {
        if (CutPreselection(entry)>0 && (abs(inttype)==11 || abs(inttype)==12  || abs(inttype)==13) && (fileIndex==1 || fileIndex==10)) return 1;
        //if (CutCR23Comb(entry)>0) return 1;
        else return -1;
    }
    
    //CCQE
    else if (topoID==5) {
        if (CutPreselection(entry)>0 && abs(inttype)==1 && (fileIndex==1 || fileIndex==10)) return 1;
        //if (CutMore2Track(entry)>0) return 1;
        else return -1;
    }
    
    
    //signal only to check FSI
    else if (topoID==6) {
        if (CutPreselection(entry)>0 && abs(inttype)==16 && (fileIndex==1 || fileIndex==10)) return 1;//CCQE with one track
        else return -1;
    }
    
    
    else return -1;
    
    
}

Int_t baseTree::CutTopology2OptimizeFSIbyID(Long64_t entry, Int_t topoID)
{
    //all
    if (topoID==0) {
        if (CutPreselection(entry)>0) return 1;//preselection
        else return -1;
    }
    if (topoID==1) {
        if (CutPreselection(entry)>0 && pidfsi>0.075 && veract*7.6634e-2<37) return 1;//first cuts
        else return -1;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////
//////////Let breakdown by number of pion
//NEUT
Int_t baseTree::CutInteractionbyID(Long64_t entry, Int_t interactID){
    if (interactID==0 && fileIndex<10 && fileIndex>0) return 1;//all but remove genie
    else if (interactID==1) {
        if (abs(inttype)==16 && fileIndex==1) return 1;//cc1picoh
        else return -1;
    }
    else if (interactID==2) {
       // if (abs(inttype)==1 && fileIndex==1) return 1;//ccqe
      // if (abs(inttype)<10 && fileIndex==1) return 1;//ccqe==1 and MEC=2 
       if (npioncount==0 && abs(inttype)<30 && abs(inttype)!=16  && fileIndex==1) return 1;//CC 0pi
        else return -1;
    }
    else if (interactID==3) {
        //if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==1) return 1;//cc1pi
        if (npioncount==1 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 1;//CC 1pi
        else return -1;
    }
    else if (interactID==4) {
        //if (abs(inttype)>14 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 1;//ccother
        if (npioncount>1 && abs(inttype)<30 && abs(inttype)!=16  && fileIndex==1) return 1;//CC other
        else return -1;
    }
    else if (interactID==5 ) {
        if (abs(inttype)>30 && fileIndex==1) return 1;//nc
        else return -1;
    }
    else if (interactID==6 ) {
        if (fileIndex==2) return 1;//numubar
        else return -1;
    }
    else if (interactID==7 ) {
        if (fileIndex==5) return 1;//nue--> add later
        else return -1;
    }
    else if (interactID==8 ) {
        if (fileIndex==4) return 1;//ingrid bkg
        else return -1;
    }
    else if (interactID==9 ) {
        if (fileIndex==3) return 1;//wall bkg
        else return -1;
    }
    
    else return -1;

}

//GENIE
Int_t baseTree::CutInteractionbyIDGENIE(Long64_t entry, Int_t interactID){
    if (interactID==0 && fileIndex>0) return 1;//all but remove genie
    else if (interactID==1) {
        if (abs(inttype)==16 && fileIndex==10) return 1;//cc1picoh
        else return -1;
    }
    else if (interactID==2) {
        //if (abs(inttype)<10 && fileIndex==10) return 1;//ccqe
       if (npioncount==0 && abs(inttype)<30 && abs(inttype)!=16  && fileIndex==10) return 1;//CC 0pi
        else return -1;
    }
    else if (interactID==3) {
        //if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==10) return 1;//cc1pi
        if (npioncount==1 && abs(inttype)<30  && abs(inttype)!=16 &&fileIndex==10) return 1;//CC 1pi
        else return -1;
    }
    else if (interactID==4) {
        //if (abs(inttype)>14 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==10) return 1;//ccother
        if (npioncount>1 && abs(inttype)<30 && abs(inttype)!=16  && fileIndex==10) return 1;//CC other
        else return -1;
    }
    else if (interactID==5 ) {
        if (abs(inttype)>30 && fileIndex==10) return 1;//nc
        else return -1;
    }
    else if (interactID==6 ) {
        if (fileIndex==2) return 1;//numubar
        else return -1;
    }
    else if (interactID==7 ) {
        if (fileIndex==5) return 1;//nue--> add later
        else return -1;
    }
    else if (interactID==8 ) {
        if (fileIndex==4) return 1;//ingrid bkg
        else return -1;
    }
    else if (interactID==9 ) {
        if (fileIndex==3) return 1;//wall bkg
        else return -1;
    }

    else return -1;

}

/////////////////////////////////////////////////////////////////////////////////////////////
//////////This is breakdown by the interaction id
//fileIndex: 0 data; 1 pm; 2 pmbar; 3 wall; 4 ingrid; 10 genie
//0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
//6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
/*Int_t baseTree::CutInteractionbyID(Long64_t entry, Int_t interactID){
    if (interactID==0 && fileIndex<10 && fileIndex>0) return 1;//all but remove genie
    else if (interactID==1) {
        if (abs(inttype)==16 && fileIndex==1) return 1;//cc1picoh
        else return -1;
    }
    else if (interactID==2) {
        if (abs(inttype)==1 && fileIndex==1) return 1;//ccqe
      // if (abs(inttype)<10 && fileIndex==1) return 1;//ccqe==1 and MEC=2 
       else return -1;
    }
    else if (interactID==3) {
        if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==1) return 1;//cc1pi
        else return -1;
    }
    else if (interactID==4) {
        if (abs(inttype)>14 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 1;//ccother
        else return -1;
    }
    else if (interactID==5 ) {
        if (abs(inttype)>30 && fileIndex==1) return 1;//nc
        else return -1;
    }
    else if (interactID==6 ) {
        if (fileIndex==2) return 1;//numubar
        else return -1;
    }
    else if (interactID==7 ) {
        if (fileIndex==5) return 1;//nue--> add later
        else return -1;
    }
    else if (interactID==8 ) {
        if (fileIndex==4) return 1;//ingrid bkg
        else return -1;
    }
    else if (interactID==9 ) {
        if (fileIndex==3) return 1;//wall bkg
        else return -1;
    }
    
    else return -1;

}*/
 
//GENIE
/*Int_t baseTree::CutInteractionbyID(Long64_t entry, Int_t interactID){
    if (interactID==0 && fileIndex>0) return 1;//all but remove genie
    else if (interactID==1) {
        if (abs(inttype)==16 && fileIndex==10) return 1;//cc1picoh
        else return -1;
    }
    else if (interactID==2) {
        if (abs(inttype)<10 && fileIndex==10) return 1;//ccqe
        else return -1;
    }
    else if (interactID==3) {
        if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==10) return 1;//cc1pi
        else return -1;
    }
    else if (interactID==4) {
        if (abs(inttype)>14 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==10) return 1;//ccother
        else return -1;
    }
    else if (interactID==5 ) {
        if (abs(inttype)>30 && fileIndex==10) return 1;//nc
        else return -1;
    }
    else if (interactID==6 ) {
        if (fileIndex==2) return 1;//numubar
        else return -1;
    }
    else if (interactID==7 ) {
        if (fileIndex==5) return 1;//nue--> add later
        else return -1;
    }
    else if (interactID==8 ) {
        if (fileIndex==4) return 1;//ingrid bkg
        else return -1;
    }
    else if (interactID==9 ) {
        if (fileIndex==3) return 1;//wall bkg
        else return -1;
    }
    
    else return -1;
    
}
*/

Int_t baseTree::CutInteractionSBbyID(Long64_t entry, Int_t interactID){
    if (interactID==0) {
        if (abs(inttype)==16 && fileIndex==1) return 1;//signal
        else return -1;
    }
    else if (interactID==1) {
        if (!(abs(inttype)==16 && fileIndex==1)) return 1;//background
        else return -1;
    }
    else return -1;
}

Int_t    baseTree::CutTrueTrackbyID(Long64_t entry, Int_t trackID){
    if (trackID==0 ) {//muon
        if (abs(mupdg)==13) return 1;
        else return -1;
    }
    else if (trackID==1) {
        if (abs(mupdg)==11) return 1;//electron
        else return -1;
    }
    else if (trackID==2) {
        if (abs(mupdg)==211) return 1;//charged pion
        else return -1;
    }
    else if (trackID==3) {
        if (abs(mupdg)==2212) return 1;//cc1pi
        else return -1;
    }
    else if (trackID==4) {
        if (!(abs(mupdg)==13 || abs(mupdg)==11 || abs(mupdg)==211 || abs(mupdg)==2212)) return 1;//ccother
        else return -1;
    }
    
    else if (trackID==5 ) {//muon
        if (abs(ppdg)==13) return 1;
        else return -1;
    }
    else if (trackID==6) {
        if (abs(ppdg)==11) return 1;//electron
        else return -1;
    }
    else if (trackID==7) {
        if (abs(ppdg)==211) return 1;//charged pion
        else return -1;
    }
    else if (trackID==8) {
        if (abs(ppdg)==2212) return 1;//cc1pi
        else return -1;
    }
    else if (trackID==9) {
        if (!(abs(ppdg)==13 || abs(ppdg)==11 || abs(ppdg)==211 || abs(ppdg)==2212)) return 1;//ccother
        else return -1;
    }
    else if (trackID==10 ) {//muon
        if (abs(mupdg)==13 && abs(ppdg)==211) return 1;
        else return -1;
    }
    else if (trackID==11) {
        if (abs(mupdg)==13 && abs(ppdg)!=211) return 1;//electron
        else return -1;
    }
    else if (trackID==12) {
        if (abs(mupdg)!=13 && abs(ppdg)==211) return 1;//charged pion
        else return -1;
    }
    else if (trackID==13) {
        if (abs(mupdg)!=13 && abs(ppdg)!=211) return 1;//cc1pi
        else return -1;
    }
    
    
    
    else return -1;
    
}


//data 1, 0-mc
Int_t    baseTree::GetEventType(Long64_t entry){
    if (fileIndex==0) return 1;
    else return 0;
    
}
//For detector systematics study
Int_t    baseTree::CutTimingbyIndex(Long64_t entry, Int_t index){
    if (index==0) {
        if (exptime<100&&exptime>-100) {
            return 1;
        }
        else return -1;
    }
    else if (index==1) {
        if (exptime<90&&exptime>-90) {
            return 1;
        }
        else return -1;
    }
    else if (index==2) {
        if (exptime<80&&exptime>-80) {
            return 1;
        }
        else return -1;
    }
    else return -1;
}
Int_t    baseTree::CutFVbyIndex(Long64_t entry, Int_t index){
    if (index==0) {
        if (startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50) {
            return 1;
        }
        else return -1;
    }
    else if (index==1) {
        //if (startxch>=7*50&&startxch<17*50&startych>=7*50&&startych<17*50) {
         if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=3*50&&startxch<5*50&startych>=2*50&&startych<22*50)) {
	   return 1;
        }
        else return -1;
    }
    else if (index==2) {
        //if (startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50&&!(startxch>=7*50&&startxch<17*50&&startych>=7*50&&startych<17*50)) {
        if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=11*50&&startxch<13*50&startych>=2*50&&startych<22*50)) {
	     return 1;
        }
        else return -1;
    }
    else if (index==3) {
       // if (startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50&&!(startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50)) {
       if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=19*50&&startxch<21*50&startych>=2*50&&startych<22*50)) {
	     return 1;
        }
        else return -1;
    }
    else if (index==4) {
       // if (startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50&&!(startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50)) {
       if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=2*50&&startxch<22*50&startych>=3*50&&startych<5*50)) {
             return 1;
        }
        else return -1;
    }
    else if (index==5) {
       // if (startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50&&!(startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50)) {
       if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=2*50&&startxch<22*50&startych>=11*50&&startych<13*50)) {
             return 1;
        }
        else return -1;
    }
    else if (index==6) {
       // if (startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50&&!(startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50)) {
       if ((startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50)&&!(startxch>=2*50&&startxch<22*50&startych>=19*50&&startych<21*50)) {
             return 1;
        }
        else return -1;
    }
    else return -1;
}
Int_t    baseTree::CutVetobyIndex(Long64_t entry, Int_t index){
    if (index==0) {
        if (startxpln>=2&&startypln>=2) {
            return 1;
        }
        else return -1;
    }
    else if (index==1) {
        if (startxpln>=3&&startypln>=3) {
            return 1;
        }
        else return -1;
    }
    else if (index==2) {
        if (startxpln>=4&&startypln>=4) {
            return 1;
        }
        else return -1;
    }
    else return -1;
}
//this can be removed
Int_t    baseTree::GetSampleType(Long64_t entry){
    if (CutSignalR(entry)>0) return 0;

    //else if (CutCR1(entry)>0 || CutCR23Comb(entry)>0) return 1;
    
    else if (CutCR1(entry)>0) return 1;
    //else if (CutCR23Comb(entry)>0) return 2;
    else if (CutPreselection(entry)>0 && pidfsi<0.0 && pidfsi1prescor>0.1) return 2;

    else if (CutPreselection(entry)>0 && pidfsi<0.0 && pidfsiccqecor>0.1) return 3;
    else return -1;
    
}
//NEUT
Int_t    baseTree::GetInteractionType(Long64_t entry){
    if (abs(inttype)==16 && fileIndex==1) return 0;
   // else if (abs(inttype)==1 && fileIndex==1) return 1;
    else if (npioncount==0 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 1;
    //else if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==1) return 2;
    else if (npioncount==1 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 2;
    //else if (abs(inttype)>14 && abs(inttype)<30 && fileIndex==1) return 3;
    else if (npioncount>1 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==1) return 3;
    else if (abs(inttype)>30 && fileIndex==1) return 4;
    else if (fileIndex==2) return 5;
    else if (fileIndex==5) return 6;
    else if (fileIndex==4) return 7;
    else if (fileIndex==3) return 8;
    //else if (fileIndex==10) return 9;//this is genie, should not included in sample
    else return -1;
    
}
//GENIE
/*Int_t    baseTree::GetInteractionType(Long64_t entry){
 if (abs(inttype)==16 && fileIndex==10) return 0;
 //else if (abs(inttype)<10 && fileIndex==10) return 1;//there one events with id=9 in GENIE?
 else if (npioncount==0 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==10) return 1;
 //else if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==10) return 2;
 else if (npioncount==1 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==10) return 2;
 //else if (abs(inttype)>14 && abs(inttype)<30 && fileIndex==10) return 3;
 else if (npioncount>1 && abs(inttype)<30 && abs(inttype)!=16 && fileIndex==10) return 3;
 else if (abs(inttype)>30 && fileIndex==10) return 4;
 else if (fileIndex==2) return 5;
 else if (fileIndex==5) return 6;
 else if (fileIndex==4) return 7;
 else if (fileIndex==3) return 8;
 //else if (fileIndex==10) return 9;//this is genie, should not included in sample
 else return -1;
 
 }
*/
//CHANGE HERE for muon momentum conversion
double baseTree::GetPrec(double rangeval)
{
    double prec = rangeval*0.0114127 + 0.230608;
    return prec;
}

double baseTree::GetErec(double p, double theta)
{
    //Needed quantities
    double Eb=27.;
    double Mn=939.56;
    double Mp=938.272;
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double costh=TMath::Cos(TMath::Pi()/180.*theta);
    
    double CompE=(Mp*Mp-TMath::Power(Mn-Eb,2)-Mmu*Mmu+2.*(Mn-Eb)*Emu)/(2.*(Mn-Eb-Emu+p*costh));
    return(CompE);
}

double baseTree::GetQsq(double p, double theta)
{
    //Needed quantities
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double costh=TMath::Cos(TMath::Pi()/180.*theta);
    
    double Qsq=2*GetErec(p,theta)*(Emu-p*costh)-Mmu*Mmu;
    return(Qsq);
}
double baseTree::GetXbjorken(double p, double theta)
{
    //Needed quantities
    double Mn=939.56;
    double Mp=938.272;
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double Erec = GetErec(p,theta);
    double Qsq = GetQsq(p,theta);
    double xbjorken = Qsq/(2*(Erec-Emu)*(Mn+Mp)/2);
    
    return(xbjorken);
}

double baseTree::GetInelasticity(double p, double theta)
{
    //Needed quantities
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double Erec = GetErec(p,theta);
    double inelastic = (Erec-Emu)/Erec;
    
    return(inelastic);
}

#endif // #ifdef baseTree_cxx
