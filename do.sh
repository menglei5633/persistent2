#bin/bash
paramfile=$1
datafile=$2
resfile=$3
startline=$4
exactfile=$5
m=$6
p=$7
./main.out $paramfile $datafile $resfile $startline $m $p > main.result
./tongji/tongji.sh $exactfile $resfile
