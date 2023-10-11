gcc publisher.c -o publisher
gcc subscriber.c -o subscriber
gnome-terminal --title="Publisher" -- ./publisher "$1"
for ((i=1;i <= $1;i++))
do
	gnome-terminal --title="Subscriber $i" -- ./subscriber "$i"
done
