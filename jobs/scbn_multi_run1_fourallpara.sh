#!/bin/bash 
source /home/cvson/rootv5r34_setup.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/versionfsicombstat/bin/simpleTest4allpara.exe"`
let "shift=$1 +1"
let "seed=${shift} *87"
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/versionfsicombstat/outputs/fourallpara/fittoy_result_${shift}.root
ot"`
echo ${scriptFile}
echo ${outputFile}
echo ${seed}
${scriptFile}  -o ${outputFile} -s ${seed}

