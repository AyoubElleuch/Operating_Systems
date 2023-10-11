gcc -pthread ex3.c -o ex3
for i in 1 2 4 10 100
do
    echo "Time taken for the range [0, 10000000) and $i threads:" >> ex3_res.txt
    /bin/time -p ./ex3 10000000 $i 2 >> ex3_res.txt
    echo "------------------------------------------------------" >> ex3_res.txt
done