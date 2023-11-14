bash gen.sh 10 ex1.txt
ln ex1.txt ex11.txt
ln ex1.txt ex12.txt
diff ex1.txt ex11.txt
diff ex1.txt ex12.txt
#These files are hard links to the same inode, therefore there are no differences in the content.
ls -i ex1.txt ex11.txt ex12.txt > output.txt
#ex1.txt, ex11.txt, and ex12.txt are hard links to the same file, therefore the i-node numbers are the same.
du ex1.txt
ln ex1.txt ex13.txt
mv ex13.txt /tmp
find . -inum <ex1.txt_inode_number>
find / -inum <ex1.txt_inode_number>
#The difference between searching in the current path and the root path is that the first command
#will search only in the current directory and its subdirectories, while the second command will
#search the entire filesystem starting from the root directory.
ls -l ex1.txt
find . -inum <ex1.txt_inode_number> -exec rm {} \;
