#!/bin/bash -x

dir=`pwd`
testpgm=$dir/lpaggregtest/Release/lpaggregtest
tracepgm=$dir/lpaggregtrace/Release/lpaggregtrace
input=/run/media/dosimont/Stock/input_nodet
output=$dir/results/output_nodet

elements=100
i=0
echo "ID, NODES, TREE, TYPE, PARAM_TYPE, PARAM, TRACE..." > $input
for el in $elements
do
  for tree in 0
  do
    for ttype in A
    do
      for ptype in A
      do
        if [ $tree -eq 0 ]
        then
        row=10000000
        else
        row=10000000
        fi
        $tracepgm $i $row $el $tree $ttype $ptype input_$i
        cat input_$i >> $input
        rm input_$i
        i=$(($i + 1))
      done
    done
  done
done

taskset 0x00000001 $testpgm $input $output
