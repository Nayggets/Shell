#!/bin/bash
#

command=`cat Makefile`
str='cat Makefile\nexit\n'
command2=`echo "${str@E}" | ./shell.elf`


if [[ "$command2" == *"$command"* ]]; then
    echo "pass"
fi

