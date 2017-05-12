#!/bin/bash 
source /home/cvson/rootv5r34_raw.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_base4copy/bin/simpleTest1DetOnly.exe"`
let "shift=$1 +1"
let "seed=${shift} *87"
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_base4copy/outputs/DetOnly/one/fittoy_result_${shift}.root
ot"`
echo ${scriptFile}
echo ${outputFile}
echo ${seed}
${scriptFile}  -o ${outputFile} -s ${seed}

