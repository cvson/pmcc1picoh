#!/bin/bash 
source /home/cvson/rootv5r34_raw.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/bin/simpleTest2AllSyst.exe"`
let "shift=$1 +1"
let "seed=${shift} *87"
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/outputs/AllSystStatFluc/twopiless02cor/fittoy_result_${shift}.root"`
#outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/outputs/AllSyst/twopiless02cor/fittoy_result_${shift}.root"`
#outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/outputs/AllSystStatFluc/two/fittoy_result_${shift}.root"`
echo ${scriptFile}
echo ${outputFile}
echo ${seed}
${scriptFile}  -o ${outputFile} -s ${seed}

