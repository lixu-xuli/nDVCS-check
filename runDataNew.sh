#!/bin/bash

for i in $(cat Files_50nA_new.txt)
do
	echo ${i}
	clas12root -l -b -q processData.C\(\"${i}\"\,\"data_50nA\"\)
done
