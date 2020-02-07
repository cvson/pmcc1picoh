#!/bin/bash 
source /home/cvson/rootv5r34_raw.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532/bin/simpleTest1FluxOnly_deco.exe"`
let "shift=$1 +1"
let "seed=${shift} *87"
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532/outputs/FluxOnly/one_deco/fittoy_result_${shift}.root"`
echo ${scriptFile}
echo ${outputFile}
echo ${seed}
${scriptFile}  -o ${outputFile} -s ${seed}
