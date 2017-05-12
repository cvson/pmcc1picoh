#include "cccoh_ana1x.h"

#define NEVT 16

float Draw(TGraphErrors *g){

  g->GetXaxis()->SetTitle("Noise rate [hits/cycle]");
  g->GetYaxis()->SetTitle("Variation of cross setion result [%]");
  g->SetMarkerStyle(8);
  g->SetMarkerSize(1);
  g->Draw("AP");
  //TF1 *f1= new TF1("f1","[0]*(1-[1]*x)");
  TF1 *f1= new TF1("f1","[0]+[1]*x");
  f1->SetParName(0,"#alpha");
  f1->SetParName(1,"#beta");
  f1->SetLineWidth(2);
  f1->SetLineStyle(7);
  f1->SetLineColor(2);
  g->Fit("f1");
  TF1 *func=g->GetFunction("f1");


  TLegend* leg    = new TLegend(0.61-0.45, 0.61, 0.89-0.45, 0.89);
  leg  -> SetFillColor  (0);
  leg  -> SetShadowColor(0);
  leg  -> SetLineWidth  (0);
  leg  -> SetLineColor  (0);
  leg  -> SetTextSize   (0.05);
  leg  -> AddEntry(g,"MC results", "lep");
  leg  -> AddEntry(f1,"Fitting by y = #alpha +#beta x", "l");
  leg  -> Draw();
  float res = func->GetParameter(1);
  return res;
};

void t2kpre_detsyst_noise_draw_cccoh_nom(){

 // gStyle->SetOptTitle(0);
 gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
  float x[NEVT],y[3][NEVT],ex[NEVT],ey[3][NEVT],qe1[NEVT],nqe1[NEVT],qe2[NEVT],nqe2[NEVT];
  float y0;
  int nevt = NEVT;

  char FileName_qe1[200],FileName_nqe1[200],OutFile1[200];
  char FileName_qe2[200],FileName_nqe2[200],OutFile2[200],OutFile_tot[200];

  float ratio[3];

  sprintf(FileName_qe1,"detsyst/noise_nom_nevent_cccoh1_qe.txt");
  sprintf(FileName_nqe1,"detsyst/noise_nom_nevent_cccoh1_nqe.txt");
  sprintf(OutFile1,"detsyst/noise_nom_slope_cccoh1.txt");
  //sprintf(FileName_qe2,"detsyst/noise_nom_nevent_cccoh2_qe.txt");
  //sprintf(FileName_nqe2,"detsyst/noise_nom_nevent_cccoh2_nqe.txt");
  //sprintf(OutFile2,"slope_cccoh2.txt");

  ifstream data_qe1(FileName_qe1);
  ifstream data_nqe1(FileName_nqe1);
  ofstream output1(OutFile1);
  //ifstream data_qe2(FileName_qe2);
  //ifstream data_nqe2(FileName_nqe2);
  //ofstream output2(OutFile2);

  for(int i=0;i<nevt;i++){
    data_qe1>>x[i]>>qe1[i];
    data_nqe1>>x[i]>>nqe1[i];
    //data_qe2>>x[i]>>qe2[i];
    //data_nqe2>>x[i]>>nqe2[i];
  }

  int nomi=11;
  for(int i=0;i<nevt;i++){
    y[0][i]=(qe1[nomi]*result_qe+nqe1[nomi]-nqe1[i])/qe1[i]/result_qe;
    //y[1][i]=(qe2[noomi]*result_qe+nqe2[nomi]-nqe2[i])/qe2[i];

    //x[i]=x[i]*100;
    //ex[i]=1/sqrt(y[i]*1e-15/2);
    //ey[i]=1/sqrt(y[i]*8e-18/3);
    //y[i]=(y[i]-y0)/y0*100;
    //ey[i]=1/sqrt(y[i]*8e-18/3)/7;
    //y[i]=(y[i]-y0)/y0*100/2;
    y[0][i]=(y[0][i]-1)*100/2;
    //y[1][i]=(y[1][i]-1)*100/2;
    ex[i]=0;
    ey[0][i]=0;
    //ey[1][i]=0;
  }

  TGraphErrors *g1 = new TGraphErrors(nevt,x,y[0],ex,ey[0]);
  //TGraphErrors *g2 = new TGraphErrors(nevt,x,y[1],ex,ey[1]);

  TCanvas *c1 = new TCanvas("c1","c1",0,0,1600/2,1200/2);
  //c1->Divide(2,2);

  //c1->cd(1);
  float res1 = Draw(g1);
  titleStyle(g1);
  output1<<res1<<endl;
  c1->Print("detsyst/noise_nom_graph.eps");
  //c1->cd(2);
  //float res2 = Draw(g2);
  //output2<<res2<<endl;
}
