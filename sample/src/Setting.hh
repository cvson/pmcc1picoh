#define NMOD 14
#define NBIN 200
#define NMIN 0
#define NMAX 10

const float NPOT = 6.04193507503274721e20;
//oldNEUT
const int   NMCFILE  = 3950;
const int   NBARFILE  = 986;
const int   NWALLFILE  = 55546;//(31085+24461);
const int   NINGRIDFILE  = 7882;//(3941+3941);
const int   NNUEFILE = 985;
//newNEUT
/*const int   NMCFILE  = 3974;
const int   NBARFILE  = 3973;
const int   NWALLFILE  = 55546;//(31085+24461);
const int   NINGRIDFILE  = 7951;//(3941+3941);
const int   NNUEFILE = 3973;
*/

static const float SCALEBAR = NMCFILE/float(NBARFILE);
static const float SCALEWALL = NMCFILE/float(NWALLFILE);
static const float SCALEINGRID = NMCFILE/float(NINGRIDFILE);
static const float SCALENUE = NMCFILE/float(NNUEFILE);

const bool isEnergyReweightInclude = true;
