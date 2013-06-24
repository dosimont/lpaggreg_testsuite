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
echo "Parameter, Trace" > $input
for el in $elements $elements1 $elements2
do
  $tracepgm $el $row input_$el
  cat input_$el >> $input
  rm input_$el
done

$testpgm $input $output
