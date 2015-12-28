
#! /bin/bash
> ../graph/friendship
#sed "1,102d" ../graph/friendship_fb > /tmp/friendshipTmp
#sort -n +0 -1 /tmp/friendshipTmp > /tmp/friendship

current=""
friendship=""

echo -e '\E[31m'"\033[1mChecking relationship...\033[0m" 

while read vertice ligado 
do
	if [ "$vertice" != "$current" ] 
	then
		current=$vertice
		if [ "$friendship" != "" ]
		then
			echo $friendship >> ../graph/friendship
		fi
		friendship="Friendship($vertice): $ligado"
		
	else	
		friendship="$friendship $ligado"
	fi

done <  ../graph/friendship_fb

#Prints the last one
echo $friendship >> ../graph/friendship

echo -e '\E[32m'"\033[1mAll relationships mapped!\033[0m"
echo -e '\E[32m'"\033[1mSaved at graphs/friendship\033[0m"
