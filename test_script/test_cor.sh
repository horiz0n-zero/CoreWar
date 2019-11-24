#!/bin/bash

find ../test -type f -name "*.cor" > files.tmp

m=-1
while read -r x ;
do
   if [ ${#x} -gt $m ]
   then
      m=${#x}
   fi
done < files.tmp

while read -r line;
do ../asm --hexcolors $line 1> ori.tmp ; ../asm `echo $line | sed "s/cor/s/g"` 1>/dev/null 2>err.tmp ;
	if [ -s err.tmp ]
		then printf "%-$(echo -n $m)s \033[38:5:208mcannot compile source\033[0m   \n" $line
	elif [ "$(diff <(xxd $line) <(xxd a.cor))" != "" ] 
		then printf "%-$(echo -n $m)s \033[38:5:208mfailure\033[0m   \n" $line
	else 
		printf "%-$(echo -n $m)s \033[38:5:154msuccess\033[0m   \n" $line
	fi
done < files.tmp

rm -rf files.tmp ori.tmp me.tmp err.tmp a.cor
