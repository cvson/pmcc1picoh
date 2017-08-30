{
    /*
     to add
     */
    //need to check how they depends on number of interactions with neutron
    //probably not so strong sensitivity
    //compare CC0pi and CC1pi
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    const Int_t NSAMPLE2CHECK = 9;
    //235 is CCQE 2trk, 244-246 is 235 devided in Q2, 224 is antipid, 223 is antipid CC1pi, 192 is more than 2trk
    Int_t indexNSAM[] = {250,171,235,244,245,246,224,223,192};
    const char *colorcode[] = {
"#000000",
"#0072B2",
"#D55E00",
"#CC79A7",
"#E69F00",
"#009E73",
"#56B4E9",
"#F0E442",
"#000000"
    };
    Int_t ci;
    
    Bool_t isNewVersion=false;//lazy to reproduce all sample with pang vs. muang
    Bool_t isPion=false;
    
    TString subname = "veract";
    TFile *pfile[NSAMPLE2CHECK];
    TFile *pfilegenie[NSAMPLE2CHECK];
    TFile *pfilev532[NSAMPLE2CHECK];
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        pfile[isample] = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170529_sam%d.root",indexNSAM[isample]));//neut532.
        pfilegenie[isample] = new TFile(Form("../outputs/basicHisto_genie_20170529_sam%d.root",indexNSAM[isample]));//genie.
        pfilev532[isample] = new TFile(Form("../outputs/basicHisto_neut5d1d4d2_20170529_sam%d.root",indexNSAM[isample]));//neut5.14.2.
    }
   
    const Int_t NINTERACTION = 10;
    
    //TH1 to scale event;
    TH1F* hdt[NSAMPLE2CHECK];
    TH1F* hmc[NSAMPLE2CHECK];
    TH1F* hmc[NSAMPLE2CHECK];
    TH1F* hmcntype[NSAMPLE2CHECK];//0 to 60 bins
    
    //MC vs daat TH2D
    TH2F* hdtveractvsmuang[NSAMPLE2CHECK];
    TH2F* hmcveractvsmuang[NSAMPLE2CHECK][NINTERACTION];
    TH2F* hdtveractvspang[NSAMPLE2CHECK];
    TH2F* hmcveractvspang[NSAMPLE2CHECK][NINTERACTION];
    TH2F* hdtpangvsmuang[NSAMPLE2CHECK];
    TH2F* hmcpangvsmuang[NSAMPLE2CHECK][NINTERACTION];
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        hdt[isample] = (TH1F*)pfile[isample]->Get(Form("hdata_topo%d_var%d",indexNSAM[isample],2));
        hmc[isample] = (TH1F*)pfile[isample]->Get(Form("hmc_topo%d_var%d_int%d",indexNSAM[isample],2,0));
        hmcntype[isample] = (TH1F*)pfile[isample]->Get(Form("hmc_topo%d_var%d_int%d",indexNSAM[isample],10,0));
        
        if(isNewVersion){hdtpangvsmuang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtpangvsmuang_topo%d",indexNSAM[isample]));}
        hdtveractvsmuang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtveractvsmuang_topo%d",indexNSAM[isample]));
        hdtveractvspang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtveractvspang_topo%d",indexNSAM[isample]));
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            if(isNewVersion)hmcpangvsmuang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcpangvsmuang_topo%d_int%d",indexNSAM[isample],iint));
            hmcveractvsmuang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcveractvsmuang_topo%d_int%d",indexNSAM[isample],iint));
            hmcveractvspang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcveractvspang_topo%d_int%d",indexNSAM[isample],iint));
        }
    }
   //fraction of interaction on neutron
    double fracneutron[NSAMPLE2CHECK];
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        double totalint = hmcntype[isample]->Integral(0,hmcntype[isample]->GetNbinsX()+1);
        double neutronint = hmcntype[isample]->GetBinContent(12)+hmcntype[isample]->GetBinContent(17);
        cout<<"sample "<<indexNSAM[isample]<<" total "<<totalint<<" neutron "<<neutronint<<" percentage "<< (totalint-neutronint)*100.0/totalint<<endl;
        fracneutron[isample] = (totalint-neutronint)/totalint;
    }
    //profile and projection
    TProfile* hprofdtveractvspang[NSAMPLE2CHECK];
    TProfile* hprofmcveractvspang[NSAMPLE2CHECK];
    
    TH1D* hprofdiffveractvspang[NSAMPLE2CHECK];
    TH1D* hprofdiffveractvspangdiv50[NSAMPLE2CHECK];
    
    TH1D* hprojdtveractvspang[NSAMPLE2CHECK];
    TH1D* hprojmcveractvspang[NSAMPLE2CHECK];
    float npot = 6.04193507503274721e20;
    int   nmc  = 3974;
    //int   nmc  = 3974;//for newneut
    float mcpotreweight = npot/(nmc*1e21);
    double data2mc[NSAMPLE2CHECK];
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        hmc[isample]->Scale(mcpotreweight);
        cout<<"sample "<<isample<<" data "<<hdt[isample]->Integral(0,hdt[isample]->GetNbinsX()+1)<<" mc "<<hmc[isample]->Integral(0,hmc[isample]->GetNbinsX()+1)<<endl;
         data2mc[isample] = hdt[isample]->Integral(0,hdt[isample]->GetNbinsX()+1)/(hmc[isample]->Integral(0,hmc[isample]->GetNbinsX()+1));
    }
    const Int_t NREBIN = 9;
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        hprofdtveractvspang[isample] = hdtveractvspang[isample]->ProfileX();
        hprofdtveractvspang[isample]->Rebin(NREBIN);
        hprofmcveractvspang[isample] = hmcveractvspang[isample][0]->ProfileX();
        hprofmcveractvspang[isample]->Rebin(NREBIN);
       
        
        //make projection
        hprojdtveractvspang[isample] = hdtveractvspang[isample]->ProjectionX();
        hprojmcveractvspang[isample] = hmcveractvspang[isample][0]->ProjectionX();
        
        
        for (int ibin=1; ibin<=hprojdtveractvspang[isample]->GetNbinsX(); ++ibin) {
            double yintegraldt = 0;
            double yintegralmc = 0;
            for (int ibiny=1; ibiny<=hdtveractvspang[isample]->GetNbinsY(); ++ibiny) {
             yintegraldt += hdtveractvspang[isample][0]->GetBinContent(ibin,ibiny)*hdtveractvspang[isample][0]->GetYaxis()->GetBinCenter(ibiny);
             yintegralmc += hmcveractvspang[isample][0]->GetBinContent(ibin,ibiny)*hmcveractvspang[isample][0]->GetYaxis()->GetBinCenter(ibiny);
            }
            hprojdtveractvspang[isample]->SetBinContent(ibin,yintegraldt);
            hprojmcveractvspang[isample]->SetBinContent(ibin,yintegralmc);
        }
        hprojmcveractvspang[isample]->Scale(mcpotreweight);
        //additional scale by No. of data events
        hprojmcveractvspang[isample]->Scale(data2mc[isample]);
        hprojdtveractvspang[isample]->Rebin(NREBIN);
        hprojmcveractvspang[isample]->Rebin(NREBIN);
        
        
    }
    double ymax = TMath::Max(hprojmcveractvspang[0]->GetMaximum(),hprojmcveractvspang[1]->GetMaximum());
    ymax = TMath::Max(ymax,hprojmcveractvspang[2]->GetMaximum());
    //plot
    new TCanvas;
    Double_t meanprofdt[NSAMPLE2CHECK];
    Double_t meanprofmc[NSAMPLE2CHECK];
    Double_t meanprofdiff[NSAMPLE2CHECK];
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        meanprofdt[isample]=0;
        meanprofmc[isample]=0;
        for (int ibin=0; ibin<hprofdtveractvspang[isample]->GetNbinsX(); ++ibin) {
            //cout<<"sample "<<isample<<" bin "<<ibin<<" val "<<hprofdtveractvspang[isample]->GetBinContent(ibin)<<endl;
            meanprofdt[isample] += hprofdtveractvspang[isample]->GetBinContent(ibin);
            meanprofmc[isample] += hprofmcveractvspang[isample]->GetBinContent(ibin);
            
        }
        meanprofdiff[isample] = (meanprofdt[isample]-meanprofmc[isample])/hprofdtveractvspang[isample]->GetNbinsX();
        cout<<"sample "<<isample<<" effectively add (MeV) "<<meanprofdiff[isample] <<endl;
        ci = TColor::GetColor(colorcode[isample]);
        hprofdtveractvspang[isample]->SetLineColor(ci);
        hprofdtveractvspang[isample]->SetMarkerColor(ci);
        
        hprofmcveractvspang[isample]->SetLineColor(ci);
        hprofmcveractvspang[isample]->SetMarkerColor(ci);
        if(isample==0){
            hprofdtveractvspang[isample]->SetMinimum(0);
            hprofdtveractvspang[isample]->SetMaximum(120);
            hprofdtveractvspang[isample]->Draw("ep");
            hprofmcveractvspang[isample]->Draw("hist same");
        }
        else {
            hprofdtveractvspang[isample]->Draw("ep same");
            hprofmcveractvspang[isample]->Draw("hist same");
        }
    }
    
    gPad->Print("plots/"+subname+"_prof.eps");
    
    //subtract data-mc/50MeV
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
 
        //data-mc/ 50MeV; mean of protons
        hprofdiffveractvspang[isample] = (TH1D*)hprofdtveractvspang[isample]->ProjectionX(Form("hprofdiff%d",isample),"e");
        hprofdiffveractvspang[isample] ->Sumw2();
        hprofdiffveractvspang[isample] ->Add(hprofmcveractvspang[isample]->ProjectionX(Form("hprofmc%d",isample),"e"),-1);
        hprofdiffveractvspang[isample] ->GetXaxis()->SetTitle("p-like track angle");
        if(indexNSAM[isample]==223 || indexNSAM[isample]==192) hprofdiffveractvspang[isample] ->GetXaxis()->SetTitle("#pi-like track angle");
        if(indexNSAM[isample]==250)hprofdiffveractvspang[isample] ->GetXaxis()->SetTitle("#mu-like track angle");//1track
        hprofdiffveractvspang[isample] ->GetYaxis()->SetTitle("Additional Energy deposit at vertex (MeV)");
        titleStyle(hprofdiffveractvspang[isample]);
        new TCanvas;
        hprofdiffveractvspang[isample]->GetYaxis()->SetRangeUser(-10,40);//mev
        hprofdiffveractvspang[isample]->Draw("ep");
        if(indexNSAM[isample]!=250)hprofdiffveractvspang[isample]->Fit("pol0","","",10,80);
        else hprofdiffveractvspang[isample]->Fit("pol0","","",0,50);
        
        TF1 *g = hprofdiffveractvspang[isample]->GetFunction("pol0");
        Int_t ci = TColor::GetColor("#B45F04");
        g->SetLineColor(ci);
        g->SetLineWidth(3);
        g->Draw("same");
        
        gPad->Print("plots/"+subname+Form("_prof_sam%d.eps",indexNSAM[isample]));
        
        //divide to percentage of neutron target interaction and average of 50MeV
        
        hprofdiffveractvspangdiv50[isample] = (TH1D*)hprofdiffveractvspang[isample]->Clone(Form("hprofdiffdiv50%d",isample));
        hprofdiffveractvspangdiv50[isample] ->Sumw2();
        hprofdiffveractvspangdiv50[isample] ->Scale(100.0/(fracneutron[isample]*50));
        new TCanvas;
        hprofdiffveractvspangdiv50[isample]->GetYaxis()->SetTitle("Probability to add protons (%)");
        hprofdiffveractvspangdiv50[isample]->GetYaxis()->SetRangeUser(-10,60);//mev
        hprofdiffveractvspangdiv50[isample]->Draw("ep");
        if(indexNSAM[isample]!=250)hprofdiffveractvspangdiv50[isample]->Fit("pol0","","",10,80);
        else hprofdiffveractvspangdiv50[isample]->Fit("pol0","","",0,50);
        TF1 *gdiv50 = hprofdiffveractvspangdiv50[isample]->GetFunction("pol0");
        gdiv50->SetLineColor(ci);
        gdiv50->SetLineWidth(3);
        gdiv50->Draw("same");
        
        gPad->Print("plots/"+subname+Form("_prof_sam%d_div50.eps",indexNSAM[isample]));
    }

    

    
   /* new TCanvas;
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        ci = TColor::GetColor(colorcode[isample]);
        hprojdtveractvspang[isample]->SetLineColor(ci);
        hprojdtveractvspang[isample]->SetMarkerColor(ci);
        
        hprojmcveractvspang[isample]->SetLineColor(ci);
        hprojmcveractvspang[isample]->SetMarkerColor(ci);
        if(isample==0){
            hprojdtveractvspang[isample]->SetMinimum(0);
            //hprojdtveractvspang[isample]->SetMaximum(800);
            hprojdtveractvspang[isample]->GetYaxis()->SetRangeUser(0,ymax*1.2);
            hprojdtveractvspang[isample]->Draw("ep");
            hprojmcveractvspang[isample]->Draw("hist same");
        }
        else {
            hprojdtveractvspang[isample]->Draw("ep same");
            hprojmcveractvspang[isample]->Draw("hist same");
        }
    }
    gPad->Print("plots/"+subname+"_proj.eps");*/
   
}
