#!/bin/sh

declare -i MAX=$RANDOM*10001/32768
declare -i L=$RANDOM
declare -i W=$RANDOM
i=1

echo $MAX
while [ "$i" -le $MAX ]
do
    declare -i j=$RANDOM
    echo $j
    #declare -i k=$RANDOM
    #echo $j $k
    let "i=i+1"
done

echo 0
