#!/bin/bash -x

dir=`pwd`
testpgm=$dir/lpaggregtest/Release/lpaggregtest
tracepgm=$dir/lpaggregtrace/Release/lpaggregtrace
input=/run/media/dosimont/Stock/input_node
output=$dir/results/output_node

elements=`seq 10 10 90`
elements1=`seq 100 100 900`
elements2=`seq 1000 1000 9000`
elements3=`seq 10000 10000 100000`
i=0
echo "ID, NODES, TREE, TYPE, PARAM_TYPE, PARAM, TRACE..." > $input
for el in $elements $elements1 $elements2 $elements3
do
  for tree in 0 1 2 3 5 10
  do
    for ttype in I A
    do
      for ptype in 0 1 A
      do
        if [ $tree -eq 0 ]
        then
        row=100
        else
        row=10
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
