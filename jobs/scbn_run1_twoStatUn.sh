#!/bin/bash 
source /home/cvson/rootv5r34_raw.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/bin/simpleTest2StatUn.exe"`
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_git_neut532-5bin/outputs/StatUn/fittoy_result_1.root"`
#cd /home/cvson/scraid2/cc1picoh/FIT/version04genieAllParaTSpline/bin
echo ${scriptFile}
echo ${outputFile}
${scriptFile}  -o ${outputFile} -s 87


