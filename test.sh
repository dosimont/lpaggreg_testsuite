#!/bin/bash -x

dir=/home/dosimont/Documents/github/lpaggregt
testpgm=/home/dosimont/Documents/github/lpaggregtest/Release/lpaggregtest
tracepgm=/home/dosimont/Documents/github/lpaggregtrace/Release/lpaggregtrace
row=100

elements=`seq 10 10 90`
elements1=`seq 100 100 900`
elements2=`seq 1000 1000 9000`
echo "Parameter, Trace" > input
for el in $elements $elements1 $elements2
do
  $tracepgm $el $row input_$el
  cat input_$el >> input
  rm input_$el
done

$testpgm input output

