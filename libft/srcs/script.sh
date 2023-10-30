#!/bin/bash
for file in *.c
do
	echo "Traitement de $file"
	sed -i -e 's/..\/lib/..\/incs\/lib/g' "$file"
done
