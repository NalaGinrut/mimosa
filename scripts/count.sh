#  Copyright (C) 2010-2011  
#       "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
