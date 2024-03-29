/**********************************************************************
name: Spencer Ross
	readable -- recursively count readable files.
description:	
	See CS 360 Files and Directories lecture for details.
***********************************************************************/

// Includes and definitions

/**********************************************************************
Take as input some path. Recursively count the files that are readable.
If a file is not readable, do not count it. Return the negative value
of an error codes you may get. However, consider what errors you want
to respond to.
**********************************************************************/
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

//DEBUG INCLUDES
#include <stdio.h>
#include <stdlib.h>

int readable(char* inputPath) {
	struct stat area, *s = &area;
	unsigned int count = 0;
	DIR* dir;
	struct dirent* dp;
	char *subPath, *nextPath;

	//printf("inP=%s\n", inputPath);

	if (inputPath == NULL) inputPath = ".";

	if(access(inputPath, R_OK) < 0) {
		//perror("Error");
		return -errno;
	}

	int status = lstat(inputPath, s);
	
	if(status < 0) return -errno;

	//open a DIR, return 1 if file 0 if unsuccessful
   	if((dir = opendir(inputPath)) == NULL ) {
   		//closedir(dir);
   		if(S_ISREG(s->st_mode) && (access(inputPath, R_OK) == 0))
   			return 1;
   		return 0;
   	}
    
    //read each file within a DIR
    while((dp = readdir(dir))) {
    	subPath = dp->d_name;	//path of current file in ~/.
    	printf("currentSub=%s : ", subPath);

    	//making new string for next pathname
    	//smashing '/' between current dir and file name
    	nextPath = malloc(strlen(inputPath) + strlen(subPath) + 2);
        nextPath[0] = '\0';
        strcat(nextPath, inputPath);
        strcat(nextPath, "/");
        strcat(nextPath, subPath);

    	//if lstat fails or if don't have permission, pass over
    	if((lstat(nextPath, s) < 0) || (access(nextPath, R_OK) < 0)) {
			perror("Error");
			printf("count=%d\n", count);
			continue;
		}

    	if ((strcmp(subPath, ".") == 0) || (strcmp(subPath, "..") == 0)) 
        	continue;
        
        if(dp->d_type == DT_REG) {
        	++count;
        	//printf("count=%d\n", count);
        } else if(dp->d_type == DT_DIR) {
        	count += readable(nextPath);
        	//printf("count=%d\n", count);
        	free(nextPath);
        }
    }

    closedir(dir);
    return count;
}
