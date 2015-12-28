#! /bin/bash

turn=1;

while read trash friendship
do
	degree=0;
	for id in $friendship
	do
		degree=$((degree+1))
	done
	
	echo $turn $degree
	turn=$((turn+1))

done < ../graph/friendship_right
