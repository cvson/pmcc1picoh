//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 17 13:11:17 2015 by ROOT version 5.34/09
// from TTree tree/tree
// found on file: /home/cvson/cc1picoh/dataProcess/fix20150420/merged_ccqe_forResponseFunction.root
//////////////////////////////////////////////////////////

#ifndef baseTreeWeight_h
#define baseTreeWeight_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class baseTreeWeight {
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
    Int_t           mupdg;
    Int_t           ppdg;
    Float_t         veract;
    Float_t         mumucl;
    Float_t         pmucl;
    Float_t         muang_t;
    Float_t         pang_t;
    Float_t         xnu;
    Float_t         ynu;
    Float_t         znu;
    Float_t         exptime;
    Float_t         startxch;
    Float_t         startych;
    Int_t           startxpln;
    Int_t           startypln;
    Float_t         range;
    Int_t           pene;
    Float_t         prange;
    Int_t           ppene;
    Float_t         reweight[175];
    Int_t           fileIndex;
    Float_t         pidccqe;
    Float_t         pid1pres;
    Float_t         pid;
    Float_t         pidfsi;
    Float_t         pidfsi1pres;
    Float_t         pidfsiccqe;
    //newadd
    Float_t         pidfsi1prescor;
    Float_t         pidfsiccqecor;
    Float_t         pidfsinorange;
    Float_t         pidfsi1prescornorange;
    Float_t         pidfsiccqecornorange;
    
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
    TBranch        *b_mupdg;   //!
    TBranch        *b_ppdg;   //!
    TBranch        *b_veract;   //!
    TBranch        *b_mumucl;   //!
    TBranch        *b_pmucl;   //!
    TBranch        *b_muang_t;   //!
    TBranch        *b_pang_t;   //!
    TBranch        *b_xnu;   //!
    TBranch        *b_ynu;   //!
    TBranch        *b_znu;   //!
    TBranch        *b_exptime;   //!
    TBranch        *b_startxch;   //!
    TBranch        *b_startych;   //!
    TBranch        *b_startxpln;   //!
    TBranch        *b_startypln;   //!
    TBranch        *b_range;   //!
    TBranch        *b_pene;   //!
    TBranch        *b_prange;   //!
    TBranch        *b_ppene;   //!
    TBranch        *b_reweight;   //!
    TBranch        *b_fileIndex;   //!
    TBranch        *b_pidccqe;   //!
    TBranch        *b_pid1pres;   //!
    TBranch        *b_pid;   //!
    TBranch        *b_pidfsi;   //!
    TBranch        *b_pidfsi1pres;   //!
    TBranch        *b_pidfsiccqe;   //!
    //newadd
    TBranch        *b_pidfsi1prescor;   //!
    TBranch        *b_pidfsiccqecor;   //!
    TBranch        *b_pidfsinorange;   //!
    TBranch        *b_pidfsi1prescornorange;   //!
    TBranch        *b_pidfsiccqecornorange;   //!
    
    baseTreeWeight(TTree *tree=0);
    virtual ~baseTreeWeight();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    CutTOPO(Long64_t entry, Int_t topotype);
    virtual Int_t    CutPreselection(Long64_t entry);
    virtual Int_t    CutSignalR(Long64_t entry);
    virtual Int_t    CutCR1(Long64_t entry);
    virtual Int_t    CutCR23Comb(Long64_t entry);
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
    
    virtual Int_t    CutCCQE1track(Long64_t entry);
    virtual Int_t    CutCCQE1trackLoQsq(Long64_t entry);//lowQsq <0.05
    virtual Int_t    CutCCQE1trackHiQsq(Long64_t entry);//highQsq >0.05
    
    virtual Int_t    Cut1picohKikawa(Long64_t entry);
    virtual Int_t    CutCCQEKikawa2trk(Long64_t entry);
    virtual Int_t    CutCCQEPID2trk(Long64_t entry);
    virtual Int_t    CutSamplebyID(Long64_t entry,Int_t myid);//define consistent with xsecparameter
    virtual Int_t    CutbyID(Long64_t entry,Int_t myid);
    virtual Int_t    CutInteractionbyID(Long64_t entry,Int_t myid);
    virtual Int_t    CutInteractionbyIDnew(Long64_t entry,Int_t myid);
    
    //this is for AnaEvent
    virtual Int_t    GetEventType(Long64_t entry);
    virtual Int_t    GetSampleType(Long64_t entry);
    virtual Int_t    GetInteractionType(Long64_t entry);
    virtual double   GetPrec(double rangeval);
    virtual double   GetErec(double p, double theta);
    virtual double   GetQsq(double p, double theta);
    virtual double   GetXbjorken(double p, double theta);
    virtual double   GetInelasticity(double p, double theta);
    
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(TString ipFile, char* treeName, TString opFile, Int_t iSample);
    virtual void     Loop(TString ipFile, char* treeName, TString opFile);
    virtual void     MakeResponseFunction(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges, int ithParameter);
    virtual void     MakeResponseFunctionAllElse(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef baseTreeWeight_cxx
baseTreeWeight::baseTreeWeight(TTree *tree) : fChain(0)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        /*TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../datafsi/merged_ccqe_forResponseFunction.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("../../datafsi/merged_ccqe_forResponseFunction.root");
        }*/
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../datafsicornorange/merged_ccqe_forResponseFunction.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("../../datafsicornorange/merged_ccqe_forResponseFunction.root");
        }
        f->GetObject("tree",tree);
        
    }
    Init(tree);
}

baseTreeWeight::~baseTreeWeight()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t baseTreeWeight::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t baseTreeWeight::LoadTree(Long64_t entry)
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

void baseTreeWeight::Init(TTree *tree)
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
    fChain->SetBranchAddress("mupdg", &mupdg, &b_mupdg);
    fChain->SetBranchAddress("ppdg", &ppdg, &b_ppdg);
    fChain->SetBranchAddress("veract", &veract, &b_veract);
    fChain->SetBranchAddress("mumucl", &mumucl, &b_mumucl);
    fChain->SetBranchAddress("pmucl", &pmucl, &b_pmucl);
    fChain->SetBranchAddress("muang_t", &muang_t, &b_muang_t);
    fChain->SetBranchAddress("pang_t", &pang_t, &b_pang_t);
    fChain->SetBranchAddress("xnu", &xnu, &b_xnu);
    fChain->SetBranchAddress("ynu", &ynu, &b_ynu);
    fChain->SetBranchAddress("znu", &znu, &b_znu);
    fChain->SetBranchAddress("exptime", &exptime, &b_exptime);
    fChain->SetBranchAddress("startxch", &startxch, &b_startxch);
    fChain->SetBranchAddress("startych", &startych, &b_startych);
    fChain->SetBranchAddress("startxpln", &startxpln, &b_startxpln);
    fChain->SetBranchAddress("startypln", &startypln, &b_startypln);
    fChain->SetBranchAddress("range", &range, &b_range);
    fChain->SetBranchAddress("pene", &pene, &b_pene);
    fChain->SetBranchAddress("prange", &prange, &b_prange);
    fChain->SetBranchAddress("ppene", &ppene, &b_ppene);
    fChain->SetBranchAddress("reweight", reweight, &b_reweight);
    fChain->SetBranchAddress("fileIndex", &fileIndex, &b_fileIndex);
    fChain->SetBranchAddress("pidccqe", &pidccqe, &b_pidccqe);
    fChain->SetBranchAddress("pid1pres", &pid1pres, &b_pid1pres);
    fChain->SetBranchAddress("pid", &pid, &b_pid);
    fChain->SetBranchAddress("pidfsi", &pidfsi, &b_pidfsi);
    fChain->SetBranchAddress("pidfsi1pres", &pidfsi1pres, &b_pidfsi1pres);
    fChain->SetBranchAddress("pidfsiccqe", &pidfsiccqe, &b_pidfsiccqe);
    
    //newadd
    fChain->SetBranchAddress("pidfsi1prescor", &pidfsi1prescor, &b_pidfsi1prescor);
    fChain->SetBranchAddress("pidfsiccqecor", &pidfsiccqecor, &b_pidfsiccqecor);
    fChain->SetBranchAddress("pidfsinorange", &pidfsinorange, &b_pidfsinorange);
    fChain->SetBranchAddress("pidfsi1prescornorange", &pidfsi1prescornorange, &b_pidfsi1prescornorange);
    fChain->SetBranchAddress("pidfsiccqecornorange", &pidfsiccqecornorange, &b_pidfsiccqecornorange);
    

    Notify();
}

Bool_t baseTreeWeight::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.
    
    return kTRUE;
}

void baseTreeWeight::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
Int_t baseTreeWeight::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  1 if entry is accepted.
    // returns -1 otherwise.
    return 1;
}
Int_t baseTreeWeight::CutTOPO(Long64_t entry, Int_t topotype){
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
Int_t baseTreeWeight::CutPreselection(Long64_t entry)
{
    //REMOVING side-exiting sample
    if (Ntrack==2 && pang<90 && !(mufc==0 && pene<9)) return 1;
    else return -1;
}

Int_t    baseTreeWeight::CutSignalR(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid>-0.125 && veract<475 && pidccqe<-0.1 ) {
    //if (CutPreselection(entry)>0 && pid>-0.125 && veract<475) {
    if (CutPreselection(entry)>0 && pidfsi>0.08 && veract*7.6634e-2<36) {//opt1, opt2, final
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR1(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid>-0.125 && veract>890 && pidccqe<-0.1) {
    //if (CutPreselection(entry)>0 && pid>-0.125 && veract>890) {
    if (CutPreselection(entry)>0 && pidfsi>-0.05 && veract*7.6634e-2>60 &&  (pidfsi1pres>0.02)) {//opt9, final
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23Comb(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid<-0.125 && veract>0 ) {
    if (CutPreselection(entry)>0 && pidfsi<-0.05) {//final
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEIsolated(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid<-0.125 && veract>0 && pidccqe>-0.075 ) {
    if (CutPreselection(entry)>0 && pidfsi<-0.05 && pidfsi1pres<0.04) {//final
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEIsolatedLoQsq(Long64_t entry){
    if (CutCR23QEIsolated(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEIsolatedHiQsq(Long64_t entry){
    if (CutCR23QEIsolated(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6>0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEFreed(Long64_t entry){
    //if (CutPreselection(entry)>0 && pid<-0.125 && veract>0 && pidccqe<-0.075 ) {
    if (CutPreselection(entry)>0 && pidfsi<-0.05 && pidfsi1pres>0.04) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEFreedLowVeract(Long64_t entry){
    //if (CutCR23QEFreed(entry)>0 && veract<475 && pid<-0.255) {
    if (CutCR23QEFreed(entry)>0 && veract*7.6634e-2<60 ) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEFreedHighVeract(Long64_t entry){
    //if (CutCR23QEFreed(entry)>0 && veract>475) {
    if (CutCR23QEFreed(entry)>0 && veract*7.6634e-2>60) {
        return 1;
    }
    else return -1;
}
//NOTHING TO DO WITH THIS
Int_t    baseTreeWeight::CutCR23QEFreedHighVeractHiResPID(Long64_t entry){
    if (CutCR23QEFreedHighVeract(entry)>0 && pid1pres>0) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCR23QEFreedHighVeractLoResPID(Long64_t entry){
    if (CutCR23QEFreedHighVeract(entry)>0 && pid1pres<0) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutMore2Track(Long64_t entry){
    //if (Ntrack>2 && !(mufc==0 && pene<9) && pidccqe<-0.1) {//?
    if (Ntrack>2 && !(mufc==0 && pene<9) && pang<90) {//?
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutMore2TrackHiResPID(Long64_t entry){
    //if (CutMore2Track(entry)>0 && pid>-0.125 && veract>475) {
    if (CutMore2Track(entry)>0 && pidfsi>-0.05 && veract*7.6634e-2>60 && pidfsi1pres>0.07) {//opt9,final
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutMore2TrackLoResPID(Long64_t entry){
    //if (CutMore2Track(entry)>0 && pid<-0.125 && veract<475) {
    if (CutMore2Track(entry)>0  && pidfsi<-0.05 && veract*7.6634e-2<60 && pidfsi1pres>0.07) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutMore2TrackAllElse(Long64_t entry){
    //if (CutMore2Track(entry)>0 && pid<-0.125 && veract>475) {
    if (CutMore2Track(entry)>0 && pidfsi<-0.05 && veract*7.6634e-2>60 && pidfsi1pres>0.07) {
        return 1;
    }
    else return -1;
}

Int_t    baseTreeWeight::CutCCQE1track(Long64_t entry){
    if (Ntrack==1 && mumucl>0.6 && Ningtrack==1 && !(mufc==0 && pene<9)) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCCQE1trackLoQsq(Long64_t entry){
    if (CutCCQE1track(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6<0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCCQE1trackHiQsq(Long64_t entry){
    if (CutCCQE1track(entry)>0 && GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6>0.05) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::Cut1picohKikawa(Long64_t entry){
    if (Ntrack==2 && mumucl>0.6 && pmucl>0.25 && pang<90 && muang_t<15 && veract*7.66339869e-2<34) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCCQEKikawa2trk(Long64_t entry){
    if (Ntrack==2 && pang<90 && Ningtrack==1 && mumucl>0.6 && pmucl<0.6 && opening>60 && coplanarity>150) {
        return 1;
    }
    else return -1;
}
Int_t    baseTreeWeight::CutCCQEPID2trk(Long64_t entry){
    if (Ntrack==2 && pang<90 && pidccqe>0.05) {
        return 1;
    }
    else return -1;
}

Int_t baseTreeWeight::CutbyID(Long64_t entry, Int_t myid)
{
    //all
    if (myid==0) return 1;
    
    //signal region
    else if (myid==1){
        if (CutSignalR(entry)>0) return 1;
        else return -1;
    }
    //CR1
    else if (myid==2){
        if (CutCR1(entry)>0) return 1;
        else return -1;
    }
    //CR23 comb
    else if (myid==3){
        if (CutCR23Comb(entry)>0) return 1;
        else return -1;
    }
    //CR23 CCQE isolated
    else if (myid==4){
        if (CutCR23QEIsolated(entry)>0) return 1;
        else return -1;
    }
    //CR23 freed CCQE
    else if (myid==5){
        if (CutCR23QEFreed(entry)>0) return 1;
        else return -1;
    }
    //CR23 freed-CCQE low veract
    else if (myid==6){
        if (CutCR23QEFreedLowVeract(entry)>0) return 1;
        else return -1;
    }
    //CR23 freed-CCQE high veract
    else if (myid==7){
        if (CutCR23QEFreedHighVeract(entry)>0) return 1;
        else return -1;
    }
    //1track QE
    else if (myid==8){
        if (CutCCQE1track(entry)>0) return 1;
        else return -1;
    }
    //more than 2track
    else if (myid==9){
        if (CutMore2Track(entry)>0) return 1;
        else return -1;
    }
    //signal region by Kikawa
    else if (myid==10){
        if (Cut1picohKikawa(entry)>0) return 1;
        else return -1;
    }
    //CCQE
    //CCQE  kikawa
    else if (myid==11){
        if (CutCCQEKikawa2trk(entry)>0) return 1;
        else return -1;
    }
    //CCQE son
    else if (myid==12){
        if (CutCCQEPID2trk(entry)>0) return 1;
        else return -1;
    }
    
    else return -1;
    
}
Int_t baseTreeWeight::CutSamplebyID(Long64_t entry, Int_t myid)
{
    
    //signal region
    if (myid==0){
        if (CutSignalR(entry)>0) return 1;
        else return -1;
    }
    //CR1
    else if (myid==1){
        if (CutCR1(entry)>0 || CutMore2TrackHiResPID(entry)>0) return 1;
        else return -1;
    }
    
    //CR2
    else if (myid==2){
        if (CutCR23QEFreedLowVeract(entry)>0 || CutMore2TrackLoResPID(entry)>0) return 1;
        else return -1;
    }
    //CR3
    else if (myid==3){
        if (CutCR23QEFreedHighVeract(entry)>0 || CutMore2TrackAllElse(entry)>0) return 1;
        else return -1;
    }
    
    
    
    else return -1;
    
}

Int_t baseTreeWeight::CutInteractionbyID(Long64_t entry, Int_t myid)
{
    //all
    if (myid==0) return 1;
    
    //CC1pioncoh
    else if (myid==1){
        if (abs(inttype)==16) return 1;
        else return -1;
    }
    //CCQE
    else if (myid==2){
        if (abs(inttype)==1) return 1;
        else return -1;
    }
    //CC1pion
    else if (myid==3){
        if (abs(inttype)==11 || abs(inttype)==12 || abs(inttype)==13) return 1;
        else return -1;
    }
    //CCother
    else if (myid==4){
        if (abs(inttype)>16 && abs(inttype)<30) return 1;
        else return -1;
    }
    //NC
    else if (myid==5){
        if (abs(inttype)>30) return 1;
        else return -1;
    }
    else return -1;

}

Int_t baseTreeWeight::CutInteractionbyIDnew(Long64_t entry, Int_t myid)
{
    
    //CC1pioncoh
    if (myid==0){
        if (abs(inttype)==16) return 1;
        else return -1;
    }
    //CCQE
    else if (myid==1){
        if (abs(inttype)==1) return 1;
        else return -1;
    }
    //CC1pion
    else if (myid==2){
        if (abs(inttype)==11 || abs(inttype)==12 || abs(inttype)==13) return 1;
        else return -1;
    }
    //CCother
    else if (myid==3){
        if (abs(inttype)>16 && abs(inttype)<30) return 1;
        else return -1;
    }
    //NC
    else if (myid==4){
        if (abs(inttype)>30) return 1;
        else return -1;
    }
    else return -1;
    
}
//data 1, 0-mc
Int_t    baseTreeWeight::GetEventType(Long64_t entry){
    if (fileIndex==0) return 1;
    else return 0;
    
}
Int_t    baseTreeWeight::GetSampleType(Long64_t entry){
    if (CutSignalR(entry)>0) return 0;
    
    else if (CutCR1(entry)>0 || CutMore2TrackHiResPID(entry)>0) return 1;
    
    else if (CutCR23QEFreedLowVeract(entry)>0 || CutMore2TrackLoResPID(entry)>0) return 2;
    else if (CutCR23QEFreedHighVeract(entry)>0 || CutMore2TrackAllElse(entry)>0) return 3;
    
    else return -1;
    
}
Int_t    baseTreeWeight::GetInteractionType(Long64_t entry){
    if (abs(inttype)==16 && fileIndex==1) return 0;
    else if (abs(inttype)==1 && fileIndex==1) return 1;
    else if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==1) return 2;
    else if (abs(inttype)>14 && abs(inttype)<30 && fileIndex==1) return 3;
    else if (abs(inttype)>30 && fileIndex==1) return 4;
    else if (fileIndex==2) return 5;
    else if (fileIndex==5) return 6;
    else if (fileIndex==4) return 7;
    else if (fileIndex==3) return 8;
    //else if (fileIndex==10) return 9;//this is genie, should not included in sample
    else return -1;
    
}
/*Int_t    baseTreeWeight::GetInteractionType(Long64_t entry){
 if (abs(inttype)==16 && fileIndex==10) return 0;
 else if (abs(inttype)<10 && fileIndex==10) return 1;//there one events with id=9 in GENIE?
 else if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==10) return 2;
 else if (abs(inttype)>14 && abs(inttype)<30 && fileIndex==10) return 3;
 else if (abs(inttype)>30 && fileIndex==10) return 4;
 else if (fileIndex==2) return 5;
 else if (fileIndex==5) return 6;
 else if (fileIndex==4) return 7;
 else if (fileIndex==3) return 8;
 //else if (fileIndex==10) return 9;//this is genie, should not included in sample
 else return -1;
 
 }*/
double baseTreeWeight::GetPrec(double rangeval)
{
    double prec = rangeval*0.0114127 + 0.230608;
    return prec;
}

double baseTreeWeight::GetErec(double p, double theta)
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

double baseTreeWeight::GetQsq(double p, double theta)
{
    //Needed quantities
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double costh=TMath::Cos(TMath::Pi()/180.*theta);
    
    double Qsq=2*GetErec(p,theta)*(Emu-p*costh)-Mmu*Mmu;
    return(Qsq);
}
double baseTreeWeight::GetXbjorken(double p, double theta)
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

double baseTreeWeight::GetInelasticity(double p, double theta)
{
    //Needed quantities
    double Mmu=105.658;
    double Emu=TMath::Sqrt(p*p+Mmu*Mmu);
    double Erec = GetErec(p,theta);
    double inelastic = (Erec-Emu)/Erec;
    
    return(inelastic);
}

#endif // #ifdef baseTreeWeight_cxx
