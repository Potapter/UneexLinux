#!/bin/bash

DELAY=0
if [[ $# != 0 ]]
then
    DELAY=$1
fi

row=0
col=0
letter_coords=()

while IFS= read -r line
do
    for ((col=0; col<${#line}; ++col))
    do
        letter=${line:${col}:1}
        if [[ $letter != " " ]]
        then
            letter_coords+="$letter $row $col\n"
        fi
    done
    row=$((row+1))
done

letter_coords=$(printf "$letter_coords" | shuf)
tput clear

echo -e "$letter_coords" | while read letter row col
do
        tput cup $row $col
        echo -e $letter
        sleep $DELAY
done

tput cup $rows 0
