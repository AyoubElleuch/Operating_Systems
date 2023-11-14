rm -rf ./tmp
ln -s ./tmp tmp1
ls -li
mkdir ./tmp
ls -li
#The difference is the presence of the ./tmp directory in the output
#of the second ls -li command. This is because the first ls -li command was
#executed before the creation of the ./tmp directory, and the second ls -li
#command was executed after the creation of the ./tmp directory.
bash gen.sh 10 ex1.txt
mv ex1.txt ./tmp
ls ./tmp
ln -s $(realpath ./tmp) tmp1/tmp2
bash gen.sh 10 ex1.txt
mv ex1.txt ./tmp1/tmp2
ls ./tmp1/tmp2
ls ./tmp1/tmp2/tmp2
#I noticed that accessing the sub-folders results in an error because the
#symbolic link tmp1/tmp2 points to the ./tmp directory, and creating a file ex1.txt
#inside ./tmp1/tmp2 creates a loop where tmp2 points to tmp2, causing an infinite
#loop of symbolic links.
rm -rf ./tmp
ls -li
rm tmp1
rm tmp1/tmp2
