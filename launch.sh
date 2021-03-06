#!/bin/bash -x

dir=`pwd`
testpgm=$dir/lpaggregtest/Release/lpaggregtest
tracepgm=$dir/lpaggregtrace/Release/lpaggregtrace
input=$dir/results/input
output=$dir/results/output
row=100

elements=`seq 10 10 90`
elements1=`seq 100 100 900`
elements2=`seq 1000 1000 9000`
elements3=`seq 10000 2000 18000`
i=0
echo "ID, TRACE_TYPE, PARAM_TYPE, PARAM, TRACE" > $input
for el in $elements $elements1 $elements2 $elements3
do
  for ttype in I A
  do
    for ptype in 0 1 A
    do
      $tracepgm $el $row $ttype $ptype $i input_$i
      cat input_$i >> $input
      rm input_$i
      i=$(($i + 1))
  done
  done
done

taskset 0x00000001 $testpgm $input $output
