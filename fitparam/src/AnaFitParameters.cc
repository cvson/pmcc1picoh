#include "AnaFitParameters.hh"

using namespace std;

// ctor
AnaFitParameters::AnaFitParameters()
{
    m_name    = "none";
    Npar      = 0;
    hasCovMat = false;
    checkDims = false;
    
    covariance  = NULL;
    covarianceI = NULL;
    throwParms  = NULL;
}

// dtor
AnaFitParameters::~AnaFitParameters()
{
    if(covariance != NULL) covariance->Delete();
    if(covarianceI != NULL) covarianceI->Delete();
    if(throwParms != NULL) delete throwParms;
}

// SetCovarianceMatrix
void AnaFitParameters::SetCovarianceMatrix(TMatrixDSym *covmat)
{
    if(covariance != NULL) covariance->Delete();
    if(covarianceI != NULL) covarianceI->Delete();
    
    covariance  = new TMatrixDSym(*covmat);
    covarianceI = new TMatrixDSym(*covmat);
    covarianceI->Invert();
    
    cout<<"Number of parameters in covariance matrix for "<<m_name
    <<" "<<covariance->GetNrows()<<endl;
    
    hasCovMat = true;
}

// GetChi2
double AnaFitParameters::GetChi2(std::vector<double> &params)
{
    //if no covariance matrix ...
    if(!hasCovMat) return 0.0;
    
    if(!checkDims) //check dimensions of various things are ok
    {
        CheckDims(params);
        if(!checkDims) return 0.0;
    }
    //for(size_t i=0;i<params.size();i++)
    //cout<<i<<" "<<params[i]<<" "<<pars_prior[i]<<endl;
    double chi2 = 0;
    for(int i=0; i<covarianceI->GetNrows(); i++)
        for(int j=0; j<covarianceI->GetNrows(); j++)
        {
            chi2+= (params[i]-pars_prior[i])*
            (params[j]-pars_prior[j])*(*covarianceI)(i,j);
        }
    
    return chi2;
}

// CheckDims
void AnaFitParameters::CheckDims(std::vector<double> &params)
{
    checkDims = (params.size() == pars_prior.size());
    if(!checkDims)
        cerr<<"ERROR: dimensions of vectors don't match"<<endl;
    if(hasCovMat) checkDims = checkDims && (covariance->GetNrows() ==
                                            (int)pars_prior.size());
    if(!checkDims)
        cerr<<"ERROR: dimensions of vector and cov mat don't match"<<endl;
}

// InitThrows
void AnaFitParameters::InitThrows()
{
    if(!HasCovMat()) return;
    if(throwParms!=NULL) delete throwParms;
    TVectorD priorVec(covariance->GetNrows());
    for(int i=0; i<covariance->GetNrows(); i++)
        priorVec(i) = pars_prior[i];
    
    throwParms = new ThrowParms(priorVec,(*covariance));
}

// Do throw
void AnaFitParameters::DoThrow(std::vector<double> &pars)
{
    pars.clear();
    if(!hasCovMat)
    {
        pars = pars_prior;
        return;
    }
    
    if(!throwParms)
        InitThrows();
    
    throwParms->ThrowSet(pars_throw);
    
    if(((TString)m_name).Contains("flux_shape")){
        flux_mod->Reset();
        for(int j=0; j<Npar;j++){
            //cout<<"parameter "<<j<<" before "<<pars_throw[j]<<endl;
            flux_mod->SetBinContent(j+1,pars_throw[j]*flux->GetBinContent(j+1));
        }
        flux_mod->Scale(flux->Integral()/flux_mod->Integral());
        for(int j=0; j<Npar;j++){
            //cout<<flux_mod->GetBinContent(j+1)<<" - "<<flux->GetBinContent(j+1)<<
            //" / "<<flux->GetBinContent(j+1)<<endl;
            pars_throw[j]=flux_mod->GetBinContent(j+1)/flux->GetBinContent(j+1);
            //cout<<"parameter "<<j<<" after "<<pars_throw[j]<<endl;
        }
    }
    pars = pars_throw;
}

//should go to the flux class? But then how I can use the fluxhisto here?
void AnaFitParameters::SetFluxHisto(TH1F* h_flux)
{
    flux=h_flux;
    if(h_flux->GetXaxis()->GetNbins() != Npar){
        cout<<"Wrong number of flux shape parameters aborting"<<endl;
        abort();
    }
    flux_mod=(TH1F*)(flux->Clone("fluxMod"));
    flux_mod->Reset();
}

