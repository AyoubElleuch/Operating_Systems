#include <stdio.h>
#include <dirent.h>

int main(){
    DIR *dir;
    struct dirent *dirent;

    if((dir = opendir("/")) != NULL){
        while((dirent = readdir(dir)) != NULL){
            printf("%s\n", dirent->d_name);
        }
        closedir(dir);
    }else{
        printf("Error opening the directory");
        return 1;
    }

    return 0;
}