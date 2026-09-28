#!/bin/bash

for i in $(cat Files.txt)
do
	echo ${i}
	run-groovy getCurrent.groovy ${i}
done
