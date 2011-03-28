# This program is written by NalaGinrut

#! /bin/bash

count_lines()
{
	find . -type f | sed "/^\.\/\.git/d" | xargs wc -l | tail -n1;
}


count_bytes()
{
	sizes=`find . -ls | awk '{print $7;}'`;
	sum=0;

	for size in $sizes;do
	sum=`expr $sum + $size`;
	done

	sum=`expr $sum - 4096`;
	echo "$sum bytes";
}


case "$1" in
	bytes ) count_bytes ;;
	lines )	count_lines ;;
esac
