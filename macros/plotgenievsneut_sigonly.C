{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfilegenie = new TFile("../outputs/neutvsgenie_sample_newbin2.root");
    //copy from version02/outputs
    TFile *pfileneut = new TFile("../outputs/genievsneut_sample_newbin2.root");
    string tag = "nominal";
    string samplestr = "SIG";
    string reactionstr = "sig";
    TH1D *hgenie;
    TH1D *hneut;
    
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut->GetYaxis()->SetTitle("Number of Events");
    hneut->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
    plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC","genievsneut_sigonly",0.4,0.65);
    
    
     samplestr = "SIG";
     reactionstr = "ccqe";
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
     plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",Form("genievsneut_ccqe_%s",samplestr.c_str()),0.4,0.65);
    
    
    
    samplestr = "CRIIALoQsq";
    reactionstr = "ccqe";
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",Form("genievsneut_ccqe_%s",samplestr.c_str()),0.4,0.65);
    
    
    samplestr = "CRIIAHiQsq";
    reactionstr = "ccqe";
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",Form("genievsneut_ccqe_%s",samplestr.c_str()),0.4,0.65);
    
    samplestr = "ONETRKLoQsq";
    reactionstr = "ccqe";
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",Form("genievsneut_ccqe_%s",samplestr.c_str()),0.4,0.65);
    
    samplestr = "ONETRKHiQsq";
    reactionstr = "ccqe";
    hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),reactionstr.c_str(),tag.c_str()));
    plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",Form("genievsneut_ccqe_%s",samplestr.c_str()),0.4,0.65);
    
   
    
}