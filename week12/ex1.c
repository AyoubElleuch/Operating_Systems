#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>

#define MAX_SHORTCUTS 3
#define MAX_SHORTCUT_LENGTH 6

// Define the custom shortcuts
char shortcuts[MAX_SHORTCUTS][MAX_SHORTCUT_LENGTH] = {
    "P+E",
    "C+A+P",
    "A+B"
};

// Define the messages for the custom shortcuts
char shortcut_messages[MAX_SHORTCUTS][50] = {
    "I passed the Exam!",
    "Get some cappuccino!",
    "This is a custom shortcut!"
};

int main() {
    int fd;
    struct input_event ev;
    int shortcut_pressed;
    int keys_pressed[6];
    int keys_repeated[6];
    int num_keys_pressed = 0;
    int num_keys_repeated = 0;
    int i, j;

    // Open the keyboard device file
    fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    if (fd == -1) {
        printf("Error opening the input file");
        exit(1);
    }

    // Open the output file for appending
    FILE *f = fopen("ex1.txt", "a");
    if (f == NULL) {
        printf("Error opening the text file");
        exit(1);
    }

    // Print the available shortcuts
    printf("Available shortcuts:\n");
    for (i = 0; i < MAX_SHORTCUTS; i++) {
        printf("%s -> %s\n", shortcuts[i], shortcut_messages[i]);
    }

    // Read keyboard events and handle shortcuts
    while (1) {
        if (read(fd, &ev, sizeof(ev)) < sizeof(ev)) {
            printf("Error reading the input file");
            exit(1);
        }

        // Handle only PRESSED, REPEATED, and RELEASED events
        if (ev.type == EV_KEY && (ev.value == 0 || ev.value == 1 || ev.value == 2)) {

            // Handle the events
            if (ev.value == 0) {
                for (i = 0; i < num_keys_pressed; i++) {
                    if (keys_pressed[i] == ev.code) {
                        for (j = i; j < num_keys_pressed - 1; j++) {
                            keys_pressed[j] = keys_pressed[j + 1];
                        }
                        num_keys_pressed--;
                        break;
                    }
                }
                for(i = 0; i < num_keys_repeated; i++){
                    if(keys_repeated[i] == ev.code){
                        for(j = i; j<num_keys_repeated-1; j++){
                            keys_repeated[j] = keys_repeated[j+1];
                        }
                        num_keys_repeated--;
                        break;
                    }
                }
                fprintf(f, "RELEASED 0x%04x (%d)\n", ev.code, ev.code);
            } else if (ev.value == 1) {
                keys_pressed[num_keys_pressed++] = ev.code;
                fprintf(f, "PRESSED 0x%04x (%d)\n", ev.code, ev.code);
            } else if(ev.value ==  2){
                int skip = 0;
                for(i=0; i<num_keys_pressed; i++){
                    if(keys_repeated[i] == ev.code){
                        skip = 1;
                        break;
                    }
                }
                if(skip == 0) {
                    fprintf(f, "REPEATED 0x%04x (%d)\n", ev.code, ev.code);
                    keys_repeated[num_keys_repeated] = ev.code;
                    num_keys_repeated++;
                }
            }

            // Handle shortcuts
            if(num_keys_pressed == 2 && keys_pressed[0] == 25 && keys_pressed[1] == 18){
                fprintf(f, "%s\n", shortcut_messages[0]);
            }
            if(num_keys_pressed == 3 && keys_pressed[0] == 46 && keys_pressed[1] == 16 && keys_pressed[2] == 25){
                fprintf(f, "%s\n", shortcut_messages[1]);
            }
            if(num_keys_pressed == 2 && keys_pressed[0] == 16 && keys_pressed[1] == 48){
                fprintf(f, "%s\n", shortcut_messages[2]);
            }


            // Terminate the program on E+X
            if (num_keys_pressed == 2 && keys_pressed[0] == 18 && keys_pressed[1] == 45) {
                fclose(f);
                close(fd);
                exit(0);
            }

            fflush(f);
        }
    }

    return 0;
}