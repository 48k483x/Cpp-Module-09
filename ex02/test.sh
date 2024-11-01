#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
BOLD='\033[0;1m'
END='\033[0m'

make

# Loop n times
for i in {1..1000}
do
	# Random array size
	size=$((1 + RANDOM % 10000))

	numbers=$(shuf -i 1-10000000 -n $size | tr "\n" " ")

	./PmergeMe $numbers > /dev/null
	if [ $? -ne 0 ]; then
		echo -e "$RED$numbers$END"
	fi
done
