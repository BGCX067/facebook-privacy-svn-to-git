#! /bin/bash

n=20
> result 

while( [ $n -gt 0 ] )
do

	./simulation ../graph/facebook 5 >> result ;
	sleep 1;
	
	n=$((n -1))
done
