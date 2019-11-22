#!/bin/bash

find ../test -type f -name "*.s" > files.tmp

m=-1
while read -r x ;
do
   if [ ${#x} -gt $m ]
   then
      m=${#x}
   fi
done < files.tmp

while read -r line;
do ./asm $line | grep "Writing output program" > asm.tmp ; ../asm $line 2> _asm.err.tmp 1> /dev/null
	if [ -s asm.tmp ] 
		then printf "%-$(echo -n $m)s \033[38:5:154masm\033[0m   " $line
	else 
		printf "%-$(echo -n $m)s \033[38:5:208masm\033[0m   " $line
	fi
	if [ "$(cat _asm.err.tmp)" = "" ]
		then printf "\033[38:5:154m_asm\033[0m\n"
	else
		printf "\033[38:5:208m_asm\033[0m\n%s\n" "$(cat _asm.err.tmp)"
	fi
done < files.tmp

rm files.tmp
rm asm.tmp _asm.err.tmp
