#!/bin/bash

for i in $(cat Files_5nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData_lowLumi.C\(\"${i}\"\,\"data_5nA\"\)
done

for i in $(cat Files_10nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData_lowLumi.C\(\"${i}\"\,\"data_10nA\"\)
done

for i in $(cat Files_20nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData_lowLumi.C\(\"${i}\"\,\"data_20nA\"\)
done

for i in $(cat Files_35nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData.C\(\"${i}\"\,\"data_35nA\"\)
done

for i in $(cat Files_45nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData.C\(\"${i}\"\,\"data_45nA\"\)
done

for i in $(cat Files_50nA.txt)
do
	echo ${i}
	clas12root -l -b -q processData.C\(\"${i}\"\,\"data_50nA\"\)
done
