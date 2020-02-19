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
	int status;
	DIR* dir;
	struct dirent* dp;
	char* subPath;

	/*if(access(inputPath, R_OK) < 0) {
		printf("\nCan't read %s\n", inputPath);
		return 0;  //... user can't read this file ...
	} */
	

	/*
	dir == Null
	errno == ENOTDIR
	s = lstat(inPath, &buffer)
	s >= 0 check reg, check access, else return -errno
	*/

	dir = opendir(inputPath);
	while((dp = readdir(dir)) > 0) {
		subPath = dp->d_name; //check files in ~/.
		status = lstat(inputPath, s); //check stats of the inputPath 
		if(status < 0) {		//if lstat returns < 0 there is an error
			perror("Error");
			continue;		//want to skip this file
		}

		if(dir == NULL) {
			if(errno == ENOTDIR) {
				if(access(inputPath, R_OK) < 0) {
					perror("Error");
					return -errno; //no permission
				}
				if(S_ISREG(s->st_mode)) 
					closedir(dir);
					return ++count;
				/*else {
					printf("does this ever trigger?\n");
					return (errno);  //file DNE || no permission
				}*/
			} else {
				perror("Error");
	    		return -errno;
	    	}
		} else if(S_ISDIR(s->st_mode)) {
			count += recurseDir(subPath);
			chdir("..");
		}
	}

	closedir(dir);
	return count;
}

	

	/*while((dp = readdir(dir)) > 0) {
		subPath = dp->d_name; //check files in ~/.
		chdir(subPath);
		if(dp == NULL) {
			printf("not a directory\n"); //not directory
			count += readable(subPath);
			break;
		}

		//strcat(subPath, "/");		//need to malloc space for this
		//strcat(subPath, dp->d_name);
		//printf("%s\n", subPath);
		
		if((strcmp(subPath, ".") == 0) || (strcmp(subPath, "..") == 0)) continue;

		//strcat(inputPath, "/");
		//printf("currently in: %s\n", inputPath);
		//chdir(subPath);
		//subPath = malloc((strlen(inputPath) + strlen(subPath) + 2));
		count += readable(subPath);
		chdir("..");

		

		//printf("subPath = %s\n", subPath);
		//count += readable(subPath);
		//free(subPath);
	}

	closedir(dir);
	return count;*/





int recurseDir(char* dirPath) {
	struct stat area, *s = &area;
	unsigned int count = 0;
	DIR* dir;
	struct dirent* dp;
	char* subPath;

	chdir(dirPath); 
	dir = opendir("."); // Open the current working directory.

	while((dp = readdir(dir)) > 0) {
		subPath = dp->d_name; //check files in ~/.
		if(dp == NULL) {
			if((dp->d_type == DT_REG) && (access(subPath, R_OK) == 0)) 
				++count;
			printf("not a directory\n"); //not directory
			//count += readable(dirPath);
			break;
		}

		//strcat(subPath, "/");		//need to malloc space for this
		//strcat(subPath, dp->d_name);
		//printf("%s\n", subPath);
		
		if((strcmp(subPath, ".") == 0) || (strcmp(subPath, "..") == 0)) continue;

		//strcat(inputPath, "/");
		//printf("currently in: %s\n", inputPath);
		//chdir(subPath);
		//subPath = malloc((strlen(inputPath) + strlen(subPath) + 2));
		count += readable(subPath);
		chdir("..");

		

		//printf("subPath = %s\n", subPath);
		//count += readable(subPath);
		//free(subPath);
	}

	closedir(dir);
	return count;


}



/****The struct stat definition and stat bit settings below****

struct stat { 
	ino_t		st_ino;		// inode
    nlink_t		st_nlink;	 // link count 
    uid_t		st_uid;		// uid
    gid_t		st_gid;		// gid
    mode_t		st_mode;	// mode bits
    time_t		st_atime;	// last access
    time_t		st_ctime;	// creation
    time_t		st_mtime;	// last mod
    off_t		st_size;	// size
    off_t		st_blksize;
    dev_t		st_dev;
    dev_t		st_rdev;
};

#define S_IRUSR 	00400
#define S_IWUSR		00200
#define S_IXUSR		00100

#define S_IRGRP		00040
#define S_IWGRP		00020
#define S_IXGRP		00010

#define S_IROTH		00004
#define S_IWOTH		00002
#define S_IXOTH		00001

#define S_ISREG(m) 	(((m) & 0xf000) == 0x0000) 
#define S_ISDIR(m)	(((m) & 0xf000) == 0x3000)

***************************************************************/