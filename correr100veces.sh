#!/bin/bash

for i in $(seq 1 70);
do
    ./main2 1000 1000 >> ./resultados2.txt
done
