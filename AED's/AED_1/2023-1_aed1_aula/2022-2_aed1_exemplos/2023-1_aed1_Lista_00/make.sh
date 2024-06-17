#!/bin/bash
#
clear
if [ -f "$1" ];         then 
   rm -f $1                  
fi
if [ -f "output.txt" ]; then
   rm -f output.txt          
fi
if [ -f "$1.c" ];       then 
   gcc -g -o $1 $1.c         
fi 
if [ -f "$1" ];         then 
   $1 <input.txt >output.txt 
fi
if [ -f "output.txt" ]; then 
   cat output.txt            
fi
