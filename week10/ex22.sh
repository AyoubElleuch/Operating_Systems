ls -i ex1
stat ex1
cp ex1 ex2
stat -c "%h" ex2
inode_ex1=$(stat -c "%i" ex1)
inode_ex2=$(stat -c "%i" ex2)
if [ $inode_ex1 -eq $inode_ex2 ]; then
    echo "ex1 and ex2 have the same i-node numbers."
else
    echo "ex1 and ex2 do not have the same i-node numbers."
fi
stat -c "%h - %n" /etc/* | grep ^3
# The number of links represents the link count of the file, it indicates the number of hard links to the file.
