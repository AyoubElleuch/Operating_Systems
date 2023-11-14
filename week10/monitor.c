#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

const char *path;

void print_stat_info(const char *path){
    struct stat file_stat;
    if(stat(path, &file_stat) == 0){
        printf("Stat info for %s\n", path);
        printf("File size: %ld\n", file_stat.st_size);
        printf("Owner UID: %d\n", file_stat.st_uid);
        printf("Last access time: %s", ctime(&file_stat.st_atime));
        printf("Last modification time: %s\n", ctime(&file_stat.st_mtime));
    }
    else{
        printf("Error getting stat info");
        exit(1);
    }
}


void print_stat_info_for_all_entries(const char *path){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if(dir == NULL){
        printf("Error openning the file\n");
        exit(1);
    }

    while((entry = readdir(dir)) != NULL){
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        print_stat_info(full_path);
    }
    closedir(dir);
}

void signalHandler(int signal){
    if(signal == SIGINT){
        printf("\nReceived SIGINT. Printing stat info\n");
        print_stat_info_for_all_entries(path);
        exit(0);
    }
}

int main(int argc, char *argv[]){

    path = malloc(50*sizeof(char));

    if(argc != 2){
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    path = argv[1];

    print_stat_info_for_all_entries(path);

    int inotify_fd = inotify_init();
    if(inotify_fd == -1){
        printf("Error initializing inotify\n");
        exit(1);
    }

    int wd = inotify_add_watch(inotify_fd, path, IN_ALL_EVENTS);
    if(wd == -1){
        printf("Error in inotify_add_watch");
        exit(1);
    }

    signal(SIGINT, signalHandler);

    char buf[BUF_LEN];
    ssize_t num_read;
    struct inotify_event *event;

    while(1){
        num_read = read(inotify_fd, buf, BUF_LEN);
        if(num_read == 0 ){
            fprintf(stderr, "Reading from inotify_fd returned 0");
            exit(1);
        }
        if(num_read == -1){
            printf("Error");
            exit(1);
        }

        for(char *p = buf; p < buf + num_read;){
            event = (struct inotify_event *)p;
            if(event->len > 0){
                if(event->mask & IN_MODIFY){
                    printf("%s is modified\n", event->name);
                    print_stat_info(event->name);
                }
                else if(event->mask & IN_CREATE){
                    printf("%s is created\n", event->name);
                    print_stat_info(event->name);
                }else if(event->mask & IN_DELETE){
                    printf("%s is deleted\n", event->name);
                }else if(event->mask & IN_ACCESS){
                    printf("%s is accessed\n", event->name);
                    print_stat_info(event->name);
                }else if(event->mask & IN_OPEN){
                    printf("%s is opened\n", event->name);
                    print_stat_info(event->name);
                }else if(event->mask & IN_ATTRIB){
                    printf("%s metadata changed\n", event->name);
                    print_stat_info(event->name);
                }
            }
            p += sizeof(struct inotify_event) + event->len;
        }
    }

    return 0;
}