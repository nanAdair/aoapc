#!/bin/bash

i=1
j=1
num=1

while [ "$i" == "$j" ]
do
    sh temp.sh > input
    i=`cat input | ./test1`
    j=`cat input | ./test2`
    echo $num
    let "num=num+1"
done

echo $i
echo $j
