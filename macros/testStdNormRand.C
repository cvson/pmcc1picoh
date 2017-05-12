{
    const Int_t NTHROW  = 10000;
    TFile *pfile = new TFile("../outputs/testStdNormRand.root","RECREATE");
    Float_t u, v;
    Float_t z1, z2;
    TNtuple *ptuple = new TNtuple("tree","StdNormRand","u:v:z1:z2");
    for (Int_t ithrow=0; ithrow < NTHROW; ++ithrow){
        u = 2.*gRandom->Rndm()-1.;
        v = 2.*gRandom->Rndm()-1.;
        
        Float_t s = u*u+v*v;
        
        while(s==0 || s>=1.){
            u = 2.*gRandom->Rndm()-1.;
            v = 2.*gRandom->Rndm()-1.;
            s = u*u+v*v;
        }//end while s
        
        z1 = u*sqrt(-2.*TMath::Log(s)/s);
        z2 = v*sqrt(-2.*TMath::Log(s)/s);
        ptuple->Fill(u,v,z1,z2);
        
    }//end for ithrow
    ptuple->Print();
    pfile->Write();
    pfile->Close();
}