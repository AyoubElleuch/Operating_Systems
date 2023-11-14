file /dev/*
file /etc/*
ls -l /etc | grep ^d | wc -l
gcc ex1.c -o ex1
file ex1
./ex1

: <<'COMMENT'
The difference in the file command output before and after changing the program
to print "Привет, мир!" instead of "Hello world!" is that the file command will
still identify the file as an executable, but the content type might change.
The file command examines the file and tries to determine its type and content.
When the content of the file changes to non-English words, the file command might
recognize the file as containing UTF-8 text instead of ASCII text, depending on
the system's configuration. This change in content type will be reflected in the
output of the file command.
COMMENT
