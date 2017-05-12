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
    
    baseTree(TTree *tree=0);
    virtual ~baseTree();
    virtual Int_t    CutPreselection(Long64_t entry);
    virtual Int_t    CutMVA(Long64_t entry,Float_t cutValue);
    virtual Int_t    CutNOM(Long64_t entry);
    virtual Int_t    CutTopologybyID(Long64_t entry, Int_t topoID);
    virtual Int_t    CutInteractionbyID(Long64_t entry, Int_t interactID);
    virtual Int_t    GetEntry(Long64_t entry);
    //this is for AnaEvent
    virtual Int_t    GetEventType(Long64_t entry);
    virtual Int_t    GetSampleType(Long64_t entry);
    virtual Int_t    GetInteractionType(Long64_t entry);
    virtual double   GetPrec(double rangeval);
    virtual double   GetErec(double p, double theta);
    virtual double   GetQsq(double p, double theta);
    virtual double   GetXbjorken(double p, double theta);
    virtual double   GetInelasticity(double p, double theta);
    
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     MakeBasicHisto(TString ipFile, TString opFile);
    virtual void     MakeDataPlot(TString ipFile, TString opFile);
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
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/t2k/cvson/gpfs/ingrid/backup/dataProcess/fix20150420/pm_merged_ccqe_tot_addpidFFnew.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("/home/t2k/cvson/gpfs/ingrid/backup/dataProcess/fix20150420/pm_merged_ccqe_tot_addpidFFnew.root");
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
    //REMOVING side-exiting sample
    if (Ntrack==2 && pang<90 && !(mufc==0 && pene<9)) return 1;
    return -1;
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

//0 all, 1 sig, 2 cr1, 3 cr2a, 4 cr2b, 5 cr2c
// 6 more than 2trk
//7 ccq with one track
Int_t baseTree::CutTopologybyID(Long64_t entry, Int_t topoID)
{
    if (topoID==0) return 1;//all
    else if (topoID==1) {
        if (CutPreselection(entry)>0 && pid>-0.125 && veract<475) return 1;//selected
        else return -1;
    }
    else if (topoID==2) {
        if (CutPreselection(entry)>0 && pid>-0.125 && veract>890) return 1;//cr1 optimized
        else return -1;
    }
    else if (topoID==3) {
        if (CutPreselection(entry)>0 && pid<-0.125 && pidccqe>-0.075) return 1;//cr2-A: CCQ isolated
        else return -1;
    }
    else if (topoID==4) {
        if (CutPreselection(entry)>0 && pid<-0.125 && pidccqe<-0.075 && veract>475) return 1;//cr2-B: CCQ isolated and high veract
        else return -1;
    }
    else if (topoID==5) {
        if (CutPreselection(entry)>0 && pid<-0.225 && pidccqe<-0.075 && veract<475) return 1;//cr2-C: CCQ isolated and low veract
        else return -1;
    }
    else if (topoID==6) {
        if (Ntrack>2) return 1;//more than 2trk
        else return -1;
    }
    else if (topoID==7) {
        if (Ntrack==1 && Ningtrack==1 && mumucl>0.6) return 1;//CCQE with one track
        else return -1;
    }
    else return -1;
    
    
}
//fileIndex: 0 data; 1 pm; 2 pmbar; 3 wall; 4 ingrid; 10 genie
//0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
//6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
Int_t baseTree::CutInteractionbyID(Long64_t entry, Int_t interactID){
    if (interactID==0 && fileIndex<10) return 1;//all but remove genie
    else if (interactID==1) {
        if (abs(inttype)==16 && fileIndex==1) return 1;//cc1picoh
        else return -1;
    }
    else if (interactID==2) {
        if (abs(inttype)==1 && fileIndex==1) return 1;//ccqe
        else return -1;
    }
    else if (interactID==3) {
        if (abs(inttype)>10 && abs(inttype)<14 && fileIndex==1) return 1;//cc1pi
        else return -1;
    }
    else if (interactID==4) {
        if (abs(inttype)>14 && abs(inttype)<30 && fileIndex==1) return 1;//ccother
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
    /*else if (interactID==10 ) {
        if (fileIndex==10) return 1;//genie
        else return -1;
    }*/
    else return -1;
}
//data 1, 0-mc
Int_t baseTree::GetEventType(Long64_t entry){
    if (fileIndex==0) return 1;
    else return 0;
    
}
Int_t  baseTree::GetSampleType(Long64_t entry){
    if (CutPreselection(entry)>0 && pid>-0.125 && veract<475) return 0;
    else if (CutPreselection(entry)>0 && pid>-0.125 && veract>890) return 1;
    else if (CutPreselection(entry)>0 && pid<-0.125 && pidccqe>-0.075) return 2;
    else if (CutPreselection(entry)>0 && pid<-0.125 && pidccqe<-0.075 && veract>475) return 3;
    else if (CutPreselection(entry)>0 && pid<-0.225 && pidccqe<-0.075 && veract<475) return 4;
    else if (Ntrack>2) return 5;
    else if (Ntrack==1 && Ningtrack==1 && mumucl>0.6) return 6;
    else return -1;
    
}
Int_t  baseTree::GetInteractionType(Long64_t entry){
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
