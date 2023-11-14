#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

const char *path;


void find_all_hlinks(const char* source){
    struct stat file_stat;
    ino_t inode = file_stat.st_ino;
    dev_t device = file_stat.st_dev;

    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    
    while((entry = readdir(dir)) != NULL){
        if(lstat(entry->d_name, &file_stat) == -1){
            printf("Error in lstat\n");
            continue;
        }
        if(file_stat.st_ino == inode && file_stat.st_dev == device){
            char resolved_path[PATH_MAX];
            if(realpath(entry->d_name, resolved_path) == NULL){
                printf("Error in realpath\n");
                continue;
            }
            printf("inode: %lu, path: %s\n", file_stat.st_ino, resolved_path);
        }
    }

    closedir(dir);
}

void unlink_all(const char* source){
    struct stat file_stat;

    ino_t inode = file_stat.st_ino;
    dev_t device = file_stat.st_dev;

    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");

    char last_link_path[PATH_MAX];
    while((entry = readdir(dir)) != NULL){
        if(lstat(entry->d_name, &file_stat) == -1){
            printf("Error in lstat\n");
            continue;
        }
        if(file_stat.st_ino == inode && file_stat.st_dev == device){
            if(unlink(entry->d_name) == -1){
                printf("Unlink\n");
                continue;
            }
            strcpy(last_link_path, entry->d_name);
        }
    }
    printf("Last hard link path: %s\n", last_link_path);
    closedir(dir);
}

void create_sym_link(const char* source, const char* link){
    printf("Symbolic link created: %s -> %s\n", link, source);
}

int main(int argc, char *argv[]){
    path = malloc(100 * sizeof(char));
    path = argv[1];

    FILE *file = fopen("myfile1.txt", "w");
    if(file != NULL){
        fputs("Hello world.", file);
        fclose(file);
    }else{
        printf("Error opening the file");
        return 1;
    }


    link("myfile1.txt", "myfile11.txt");
    link("myfile1.txt", "myfile12.txt");
    rename("myfile1.txt", "test_dir/myfile1.txt");

    find_all_hlinks("test_dir/myfile1.txt");

    rename("test_dir/myfile1.txt", "/tmp/myfile1.txt");

    FILE *file11 = fopen("test_dir/myfile11.txt", "a");
    
    create_sym_link("/tmp/myfile1.txt", "test_dir/myfile13.txt");

    FILE *tmpFile = fopen("/tmp/myfile1.txt", "a");

    unlink_all("test_dir/myfile11.txt");
    struct stat file_stat;
    if(lstat("test_dir/myfile11.txt", &file_stat) == 0){
        printf("inode: %lu, number of hard links: %lu\n", file_stat.st_ino, file_stat.st_nlink);   
    }else{
        printf("Error in lstat\n");
        return 1;
    }

    return 0;
}