#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct File;

struct Directory{
	char name[100];
	struct File* files[100];
	struct Directory* directories[100];
	unsigned char nf;
	unsigned char nd;
	char path[2048];
};

struct File{
        int id;
        char name[63];
        int size;
        char data[10240];
        struct Directory *directory;

};

void add_file(struct File* file, struct Directory* dir){
	dir->files[dir->nf] = file;
	dir->nf++;
	file->directory = dir;

};

void overwrite_to_file(struct File* file, const char* str){
	strcpy(file->data, str);
	file->size = strlen(str);
};

void append_to_file(struct File* file, const char* str){
	strcat(file->data, str);
	file->size += strlen(str);
};

void printp_file(struct File* file){
	struct Directory* currentDirectory = file->directory;
	printf("%s\\%s\\", currentDirectory->path, currentDirectory->name);
	printf("%s\n", file->name);
}


int main(){
	struct Directory* root = (struct Directory*)malloc(sizeof(struct Directory));
	struct Directory* home = (struct Directory*)malloc(sizeof(struct Directory));
	struct Directory* bin = (struct Directory*)malloc(sizeof(struct Directory));
	struct File* bash = (struct File*)malloc(sizeof(struct File));
	struct File* ex3_1 = (struct File*)malloc(sizeof(struct File));
	struct File* ex3_2 = (struct File*)malloc(sizeof(struct File));

	strcpy(root->name, "root");
	strcpy(root->path, "\\");

	// Initialize of counters of directories to 0
	root->nf = 0;
	root->nd = 0;

	home->nf = 0;
	home->nd = 0;

	bin->nf = 0;
	bin->nd = 0;

	// Append directories
	strcpy(home->name, "home");
	(root->directories)[root->nd] = home;
	root->nd++;
	strcpy(bin->name, "bin");
	(root->directories)[root->nd] = bin;
	root->nd++;
	
	// Work with files
	add_file(bash, bin);
	strcpy(bash->name, "bash");
	strcpy(ex3_1->name, "ex3_1.c");
	strcpy(ex3_2->name, "ex3_2.c");
	overwrite_to_file(ex3_1, "int printf(const char* format, ...);");
	overwrite_to_file(ex3_2, "\\\\This is a comment in C language");
	add_file(ex3_1, home);
	add_file(ex3_2, home);
	append_to_file(bash, "Bourne Again Shell!");
	append_to_file(ex3_1,"int main(){printf(\"Hello World!\")}");

	printp_file(bash);
	printp_file(ex3_1);
	printp_file(ex3_2);

	return 0;
}
