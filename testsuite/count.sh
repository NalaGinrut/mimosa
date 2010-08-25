# This programe is written by NalaGinrut

#! /bin/bash

sizes=`find -ls | awk '{print $7;}'`;
sum=0;

for size in $sizes;do
sum=`expr $sum + $size`;
done

sum=`expr $sum - 4096`;
echo $sum;
