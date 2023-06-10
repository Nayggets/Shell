#!/bin/bash
#

command='';
command+="cat Makefile | grep e | grep rm\nexit\n"
printf "$command" 
command2='./shell.elf'
echo $command2
finalCommand=`printf "$command" | $command2`
echo `$finalCommand`
