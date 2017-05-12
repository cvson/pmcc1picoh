#!/bin/bash
source /home/t2k/cvson/rootr5v34.sh
cd /home/t2k/cvson/gpfs/ingrid/cc1picoh/FIT/version03pullscale/bin/
for i in {1..2}
do
echo "TOY $i / 100"
let seed=$i*87
echo "with $seed "
./simpleTest.exe -o ../outputs/one/toyfit_$i.root -s $seed
done


