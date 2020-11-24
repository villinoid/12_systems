#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(){
	DIR *dir=opendir(".");
	printf("Statistics for directory:\n");
	int size=0;
	struct dirent *entry;
	struct stat *file_info=malloc(sizeof(struct stat));
	entry=readdir(dir);
	while (entry) {
		stat(entry->d_name,file_info);
		size+=file_info->st_size;
		entry=readdir(dir);
	}
	printf("Total Diectory Size: %d bytes\n",size);
	free(file_info);
	rewinddir(dir);
	printf("Directories: \n");
	entry=readdir(dir);
	while(entry){
		if(entry->d_type==DT_DIR){
			printf("\t%s\n",entry->d_name);
		}
		entry=readdir(dir);
	}
	rewinddir(dir);
	printf("Regular files:\n");
	entry=readdir(dir);
	while(entry){
		if(entry->d_type==DT_REG){
			printf("\t%s\n",entry->d_name);
		}
		entry=readdir(dir);
	}
	return 0;
}
	