mkdir -p var/run
gnome-terminal -- bash -c "gcc agent.c -o agent; ./agent; exec bash"
gnome-terminal -- bash -c "gcc controller.c -o controller; ./controller; exec bash"