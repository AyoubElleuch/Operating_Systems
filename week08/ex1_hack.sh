pid=$(cat /tmp/ex1.pid)

sudo gcore $pid

xxd core.$pid > core_$pid.hex

grep -Po 'pass:........' core_$pid.hex
printf "Memory address:"
grep -bPo 'pass:\K.{8}' core_$pid.hex | awk -F ':' '{print $1}'

kill -9 $pid