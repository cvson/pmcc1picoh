#!/bin/bash 
source /home/cvson/rootv5r34_setup.sh
scriptFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_base4copy/bin/simpleTest5allpara.exe"`
outputFile=`printf "/home/cvson/scraid2/cc1picoh/FIT/pmcc1picoh_base4copy/outputs/five/fittoy_result_1allpara.root"`
#cd /home/cvson/scraid2/cc1picoh/FIT/version04genieAllParaTSpline/bin
echo ${scriptFile}
echo ${outputFile}
${scriptFile}  -o ${outputFile} -s 87


