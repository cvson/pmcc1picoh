#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>

#include "DetParameters.hh"

using namespace std;

//ctor
DetParameters::DetParameters(std::vector<AnaSample*> &sample, const char *fname, const char *name)
{
    m_name    = name;
    
    //get the binning from a file
    SetBinning(fname,sample);
    
    //parameter names & prior values
    cout<<"Det weight starting values "<<endl;
    for(size_t i=0;i<Npar;i++)
    {
        pars_name.push_back(Form("%s%d", m_name.c_str(), (int)i));
        double parprior = 0;//changefrom  1
        cout<<i<<" "<<parprior<<endl;
        pars_prior.push_back(parprior);
        pars_step.push_back(0.05);
        pars_limlow.push_back(-1.0);
        pars_limhigh.push_back(1.0);
    }
}

//dtor
DetParameters::~DetParameters()
{;}

void DetParameters::SetBinning(const char *fname, std::vector<AnaSample*> &sample )
{
    string line;
    DetBin bin;
    //loop over the 6 samples
    for(int i=0; i<sample.size(); i++){
        bin.sample=i;
        ifstream fin(fname);
        assert(fin.is_open());
        while (getline(fin, line))
        {
            stringstream ss(line);
            double p1, p2, cth1, cth2;
            if(!(ss>>cth1>>cth2>>p1>>p2))
            {
                cerr<<"Bad line format: "<<endl
                <<"     "<<line<<endl;
                continue;
            }
            bin.plow    = p1;
            bin.phigh   = p2;
            bin.cthlow  = cth1;
            bin.cthhigh = cth2;
            m_bins.push_back(bin);
        }
        fin.close();
    }
    //Npar is equal to bin number X sample number
    Npar = m_bins.size();
    
    cout<<endl<<"Det Syst binning:"<<endl;
    for(size_t i = 0;i<m_bins.size();i++)
    {
        cout<<setw(3)<<i
        <<setw(5)<<m_bins[i].sample
        <<setw(5)<<m_bins[i].cthlow
        <<setw(5)<<m_bins[i].cthhigh
        <<setw(5)<<m_bins[i].plow
        <<setw(5)<<m_bins[i].phigh<<endl;
    }
    cout<<endl<<"Det Syst # parameters: "<<Npar<<endl;
    cout<<endl;
}

// --
int DetParameters::GetBinIndex(double p, double cth, int sample_id)
{
    int binn = BADBIN;
    for(size_t i=0;i<m_bins.size();i++)
    {
        if(sample_id != m_bins[i].sample)
            continue;
        if(p>=m_bins[i].plow && p<m_bins[i].phigh &&
           cth>=m_bins[i].cthlow && cth<m_bins[i].cthhigh)
            binn = (int)i;
    }
    
    return binn;
}

// initEventMap
void DetParameters::InitEventMap(std::vector<AnaSample*> &sample)
{
    m_evmap.clear();
    
    //loop over events to build index map
    for(size_t s=0;s<sample.size();s++)
    {
        vector<int> row;
        for(int i=0;i<sample[s]->GetN();i++)
        {
            AnaEvent *ev = sample[s]->GetEvent(i);
            //get event true p and cth
            double p   = ev->GetRecPtrk();
            double cth = ev->GetRecCThtrk();
            int reaction = ev->GetReaction();
            //if(reaction==0)  //detector systematics apply only to signal
            //GetSampleType --> return the ID
            //int binn   = GetBinIndex(p, cth,sample[s]->GetSampleType());
            //using Index instead
            int binn   = GetBinIndex(p, cth, s);
            //else
            //binn == PASSEVENT;
            if(binn == BADBIN)
            {
                cout<<"WARNING: "<<m_name<<" p = "<<p<<" cth = "
                <<cth<<" fall outside bin ranges"<<endl;
                cout<<"        This event will be ignored in analysis."
                <<endl;
            }
            row.push_back(binn);
        }
        m_evmap.push_back(row);
    }
}

// EventWeghts
void DetParameters::EventWeights(std::vector<AnaSample*> &sample,
                                 std::vector<double> &params)
{
    if(m_evmap.empty()) //build an event map
    {
        cout<<"Need to build event map index for "<<m_name<<endl;
        InitEventMap(sample);
    }
    
    for(size_t s=0;s<sample.size();s++)
    {
        for(int i=0;i<sample[s]->GetN();i++)
        {
            AnaEvent *ev = sample[s]->GetEvent(i);
            //if(ev->GetReaction()==0) //detector systematics apply only to signal
            ReWeight(ev, s, i, params);
        }
    }
}

// ReWeight
void DetParameters::ReWeight(AnaEvent *event, int nsample, int nevent,
                             std::vector<double> &params)
{
    if(m_evmap.empty()) //need to build an event map first
    {
        cout<<"Need to build event map index for "<<m_name<<endl;
        return;
    }
    
    int binn = m_evmap[nsample][nevent];
    
    if(binn == PASSEVENT) return;
    if(binn == BADBIN)
        event->AddEvWght(0.0); //skip!!!!
    else
    {
        if(binn>(int)params.size())
        {
            cerr<<"ERROR: number of bins "<<binn<<" for "<<m_name
            <<" does not match num of param"<<endl;
            event->AddEvWght(0.0);
        }
        //event->AddEvWght(params[binn]);
        event->AddEvWght(1+params[binn]);
    }
}


