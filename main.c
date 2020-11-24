#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv){
	char path[1000]; 
	int i=0;
	if (argc>1){
		strncpy(path,argv[1],sizeof(path));
	}
	else{
		printf("Input a path to directory: ");
		fgets(path,sizeof(path),stdin);
		while(path[i]){};
		path[i-1]=0;
	}
	printf("%s\n",path);
	DIR *dir=opendir(path);
	if (dir==0){
		printf("error: %d %s\n",errno,strerror(errno));
		return 0;
	}
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
	closedir(dir);
	return 0;
}
	