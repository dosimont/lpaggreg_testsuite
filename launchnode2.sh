#!/bin/bash -x

dir=`pwd`
testpgm=$dir/lpaggregtest/Release/lpaggregtest
tracepgm=$dir/lpaggregtrace/Release/lpaggregtrace
input=/run/media/dosimont/Stock/input_node3
output=$dir/results/output_node3

elements=`seq 1000000 1000000 9000000`
i=0
echo "ID, NODES, TREE, TYPE, PARAM_TYPE, PARAM, TRACE..." > $input
for el in $elements
do
  for tree in 0 2 3 5 10
  do
    for ttype in I A
    do
      for ptype in 0 1 A
      do
        if [ $tree -eq 0 ]
        then
        row=5
        else
        row=5
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
