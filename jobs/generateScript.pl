#!/usr/bin/perl

### set env
$pkg_dir = "/home/t2k/cvson/gpfs/ingrid/cc1picoh/FIT/version03genieallxsec";

system("mkdir -p $pkg_dir/jobs/one");
system("mkdir -p $pkg_dir/jobs/one/outfile");

### start loop

for($fN = 1; $fN < 201; $fN++){
    
    $file_num = $fN;
    $seed = $fN*87;
    
    open(OUT,">$pkg_dir/jobs/one/run$file_num.sh");
    print(OUT "\# /bin/sh -f\n");
    print(OUT "source /home/t2k/cvson/rootr5v34.sh\n");
    print(OUT "cd $pkg_dir/bin\n");
    print(OUT "./simpleTest.exe -o ../outputs/one/fittoy_result_$file_num.root -s $seed\n");
    close(OUT);
    system("chmod +x $pkg_dir/jobs/one/run$file_num.sh");
    
}


print "total # of files : $fN\n";

open(OUT,">$pkg_dir/jobs/one/submitall.sh");
print(OUT "\# /bin/sh -f\n");
print(OUT "for i in {1..200}\n");
print(OUT "do\n");
print(OUT "bsub -q l -o outfile $pkg_dir/jobs/one/run\$i.sh\n");
print(OUT "done\n");
close(OUT);
system("chmod +x $pkg_dir/jobs/one/submitall.sh");
