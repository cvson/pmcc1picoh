# /bin/sh -f
for i in {1..200}
do
bsub -q l -o outfile /home/t2k/cvson/gpfs/ingrid/cc1picoh/FIT/version03genieallxsec/jobs/one/run$i.sh
done
