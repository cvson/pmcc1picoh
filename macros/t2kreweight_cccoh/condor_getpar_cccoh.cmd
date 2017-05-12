Universe        = vanilla
Executable      = /cern/root/root.v5.20.00/bin/root
#Executable      = /home/cvson/utils/root/bin/root
Rank            = kflops
Requirements    = CpuIsBusy == FALSE && \
                  (machine != "scbn00" && \
                   machine != "scbn01.hepnet.scphys.kyoto-u.ac.jp" )

Getenv          = True
Output           = /dev/null
#Output           = ./log$(Process).txt
Error           = /dev/null
#Error           = ./err$(Process).txt
Notification  = Never

Arguments = -l -x ../T2KReWeightGetCCcohRev.C($(Process)) -q
Queue 176
