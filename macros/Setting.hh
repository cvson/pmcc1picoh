#define NMOD 14
#define NBIN 200
#define NMIN 0
#define NMAX 10

const float NPOT = 6.04193507503274721e20;
const int   NMCFILE  = 3950;
const int   NBARFILE  = 986;
const int   NWALLFILE  = 55546;//(31085+24461);
const int   NINGRIDFILE  = 7882;//(3941+3941);
const int   NNUEFILE = 985;

float SCALEBAR = NMCFILE/float(NBARFILE);
float SCALEWALL = NMCFILE/float(NWALLFILE);
float SCALEINGRID = NMCFILE/float(NINGRIDFILE);
float SCALENUE = NMCFILE/float(NNUEFILE);

bool isEnergyReweightInclude = true;

