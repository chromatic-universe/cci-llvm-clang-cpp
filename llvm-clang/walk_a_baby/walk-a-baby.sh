#!/bin/bash
set -e
if [ $1 == "make" ]
 then
   set -x
fi

parentdir=$(dirname `pwd`)
echo $parentdir

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
echo "${red}walk-a-baby ${green}william k. johnson 2015${reset}"

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/dev_tools $parentdir

if [ $# -eq 0 ]
  then
    echo "no arguments supplied"
    exit 1
fi


if [ $1 == "make" ] || [ $1 == "make-no-echo" ]
 then	
	make VERBOSE=1	
fi




