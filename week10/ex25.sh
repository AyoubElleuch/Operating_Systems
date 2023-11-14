touch ex5.txt
chmod a-w ex5.txt
chmod u=rw, o=rw ex5.txt
chmod g=u ex5.txt
#660: the owner and the group have read and write permissions, the others don't.
#775: the owner and the group have read, write, and execute permissions, the others don't.
#777: everyone (owner, group, and others) have read, write, and execute permissions.
