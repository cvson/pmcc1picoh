#!/bin/bash 
source /home/cvson/rootv5r34_setup.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-fixresf-fin3binFAK/bin/simpleTest5nodet.exe"`
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-fixresf-fin3binFAK/outputs/five/fittoy_result_1nodet.root"`
#cd /home/cvson/scraid2/cc1picoh/FIT/version04genieAllParaTSpline/bin
echo ${scriptFile}
echo ${outputFile}
${scriptFile}  -o ${outputFile} -s 87


