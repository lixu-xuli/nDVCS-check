#!/bin/bash

for i in $(cat Files_5nA.txt)
do
	echo ${i}
	run-groovy getCurrent_lowLumi.groovy ${i}
done

for i in $(cat Files_10nA.txt)
do
	echo ${i}
	run-groovy getCurrent_lowLumi.groovy ${i}
done

for i in $(cat Files_20nA.txt)
do
	echo ${i}
	run-groovy getCurrent_lowLumi.groovy ${i}
done

for i in $(cat Files_35nA.txt)
do
	echo ${i}
	run-groovy getCurrent.groovy ${i}
done

for i in $(cat Files_45nA.txt)
do
	echo ${i}
	run-groovy getCurrent.groovy ${i}
done

for i in $(cat Files_50nA.txt)
do
	echo ${i}
	run-groovy getCurrent.groovy ${i}
done
