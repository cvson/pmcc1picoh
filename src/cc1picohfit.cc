#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
using namespace std;

int main(int argc, char *argv[])
{
    string fmc = "../inputs/mc.root";
    string fdata = "../inputs/data.root";
    string ffluxcov = "../inputs/flux_covariance.root";
    string fdetcov = "../inputs/det_covariance.root";
    string fbinning = "../inputs/binning_scheme.txt";
    string foutput = "../outputs/fitresults";
    
    double potD     = 57.34;   //in units of 10^19
    double potMC    = 57.34; //in units 10^19
    int seed        = 1019;
    
    //get command line options
    char cc;
    /*-h can use with no argument*/
    while((cc = getopt(argc, argv, "hi:e:b:o:n:N:s:f:")) != -1)
    {
        switch(cc)
        {
            case 'i': //selected events
                fmc = optarg;
                break;
            case 'e': //flux covariance matrix
                ffluxcov = optarg;
                break;
            case 'd': //det covariance matrix
                fdetcov = optarg;
                break;
            case 'b': //binning for xsec weights
                fbinning = optarg;
                break;
            case 'o': //output file
                foutput = optarg;
                break;
            case 'n': //data POT
                potD = atof(optarg);
                break;
            case 'N': //MC POT
                potMC = atof(optarg);
                break;
            case 's': //random seed
                seed = atoi(optarg);
                break;
            case 'f': //fake data file
                fdata = optarg;
                break;
            case 'h': //help
                std::cout << "USAGE: "
                << argv[0] << " OPTIONS:" << std::endl
                << "-i : \tset event selection" << std::endl
                << "-e : \tset prefit covariances" << std::endl
                << "-d : \tset detector covariances" << std::endl
                << "-b : \tset ccqe xsec bin definitions" << std::endl
                << "-o : \tset name of output file" << std::endl
                << "-n : \tset POT for data in units 10**19" << std::endl
                << "-N : \tset POT for MC in units 10**19" << std::endl
                << "-s : \tset random seed" << std::endl;
                return 0;
                break;
            default:
                return 1;
        }//end switch
    }//end while
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
