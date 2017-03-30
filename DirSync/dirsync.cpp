#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/time.h"
#include "dirent.h"
#include "sys/stat.h"
#include "limits.h"
#include "string.h"
#include "time.h"
#include "utime.h"
#include "unistd.h"
using namespace std;

// Directory Check Values
#define PATH_NOT_DIRECTORY 1
#define DIR_EXIST 2
#define DIR_DOES_NOT_EXIST 3
#define CHUNK_SIZE 1048576	// Reading file using 1 mb chunk size.

// Get the directory name without the preceeding path.
char * getDirName(char * path);
// Check if data/folder "query" exists in folder "path".
int doesExist(char * path, char * query);
// Get version of source directory in the backup.
int getVersion(char * sourceDirectory, char * destinationDirectory);
// Main function. Recursively copy whole data/or make links.
bool copyDirectory(char * sourceDirectory, char * destinationDirectory, int version, char * previousVersion);	
// Set attributes of a new file.
void setAttributes(char * sourceFile, char * targetFile);
// Check for equality of files..
bool filesEqual(char * file1, char * file2);


int main(int argc, char * argv[]){

	// Workspace variables.
	char workingDirectory[PATH_MAX+1];

	// Set the source and destination directories.
	char sourceDirectory[PATH_MAX+1];
	char destinationDirectory[PATH_MAX+1];
	char previousVersion[PATH_MAX+1];
	strcpy(previousVersion,"");
	strcpy(sourceDirectory, argv[1]);
	strcpy(destinationDirectory, argv[2]);
	int length = strlen(sourceDirectory);

	// Remove the last char if it is '/'. 
	if (sourceDirectory[length-1] == '/')
		sourceDirectory[length-1] = NULL;

	length = strlen(destinationDirectory);
	if (destinationDirectory[length-1] == '/')
		destinationDirectory[length-1] = NULL;
	
	// Let's first create the directory if it does not exist.
	// Get directory name.
	char * name = getDirName(sourceDirectory);
//	if (doesExist(destinationDirectory, name) == DIR_DOES_NOT_EXIST){
	// Get backup version. version is -1 if this is the first time this folder will be backed up.
	// otherwise, it takes a value between 0-n, and each time dirsync is called, backup is incremented by 1.
	int version = getVersion(sourceDirectory, destinationDirectory);
	// Now, let us recursively copy the files here.
	copyDirectory(sourceDirectory, destinationDirectory, version, previousVersion);	
//	}
	return 0;
}

char * getDirName(char * path){
	char * name = (char *) malloc(sizeof(char)*(PATH_MAX+1));
	char * pos = strrchr(path, '/');
	strcpy(name, pos+1);
	return name;
}

// The checker function that looks for a file or folder under a given path.
int doesExist(char * path, char * query){
	DIR * pathDir = opendir(path);
	if (pathDir==NULL)
	{
		// path does not refer to a directory, return false.
		return PATH_NOT_DIRECTORY;
	}
	else{
		struct dirent * dirP;
		while((dirP = readdir(pathDir)) != NULL)
		{
			if (!strcmp(dirP->d_name, query) && dirP->d_type==DT_DIR)
				return DIR_EXIST;	
		}
		return DIR_DOES_NOT_EXIST;
	}	
	closedir(pathDir);
}


// Get backup version. Does not return current version, it returns an incremented value.
int getVersion(char * sourceDirectory, char * destinationDirectory){
	char versionedSourceDir[PATH_MAX+1];
	int version = 0;
	char versionString[PATH_MAX+1];
	char * name = getDirName(sourceDirectory);
	switch(doesExist(destinationDirectory, name)){
		case DIR_DOES_NOT_EXIST:
			return -1;
		break;
		case DIR_EXIST:
			while(1){
				strcpy(versionedSourceDir, name);
				strcat(versionedSourceDir, ".");
				sprintf(versionString, "%d", version);	
				strcat(versionedSourceDir, versionString);
				if (doesExist(destinationDirectory, versionedSourceDir) != DIR_EXIST)
					return version;
				version++;
			}
		break;
		default:
		printf("Source Directory is not a real directory\n");

	}
	free(name);
}

bool copyDirectory(char * sourceDirectory, char * destinationDirectory, int version, char * previousVersion){
	cout<<"Directory to be Copied:"<<sourceDirectory<<endl<<"Directory for Backup:"<<destinationDirectory<<endl<<"Version:"<<version<<endl;
	DIR * pathDir = opendir(sourceDirectory);	
	struct dirent * dp;
	char * name = getDirName(sourceDirectory);
	char sourceFile[PATH_MAX+1];
	char targetFile[PATH_MAX+1];
	char previousFile[PATH_MAX+1];
	char versionString[PATH_MAX+1];
	char previousVersionString[PATH_MAX+1];
	FILE * fp, *tfp;
	int fileSize;
	int chunkItr, successfulWriteCount, numberOfItr;
	char buffer[CHUNK_SIZE];

	char pointedFile[PATH_MAX+1];
	int numberOfChars;

	strcpy(targetFile, destinationDirectory);
	strcat(targetFile, "/");
	strcat(targetFile, name);
	// If we have a previous version, we need its path too. Let's geth both current directory to be written, and where its previous version resides.
	// Changed only on first call.
	if (version>-1){
		sprintf(versionString, "%d", version);	
		strcat(targetFile, ".");
		strcat(targetFile, versionString);
		// Now get the previous version.
		strcpy(previousVersion,destinationDirectory);
		strcat(previousVersion, "/");
		strcat(previousVersion, name);
		// The previous version of version "0" is named as the folder itself. 
		if (version){
			sprintf(previousVersionString, "%d", version-1);	
			strcat(previousVersion, ".");
			strcat(previousVersion, previousVersionString);
		}
	}
	
	// Create destination directory, return false if we could not create it.
	if (mkdir(targetFile, S_IRWXU))
		return false;	
	
	while((dp = readdir(pathDir)) != NULL){
		cout<<"CURRENT:"<<dp->d_name<<endl;
		// Lets see what we have as a file.
		strcpy(sourceFile, sourceDirectory);
		strcat(sourceFile, "/");
		// Following eight lines are a repetition on the first call. Not necessary.
		strcpy(targetFile, destinationDirectory);
		strcat(targetFile, "/");
		strcat(targetFile, name);
		if (version>-1){
			sprintf(versionString, "%d", version);	
			strcat(targetFile, ".");
			strcat(targetFile, versionString);
		}
		// Copy the file or directory.
		cout<<"Copied Under"<<targetFile<<endl;
		switch(dp->d_type){
			case DT_DIR:
			// Copying a directory.
			// we should not copy "." and ".."
			if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
				strcat(sourceFile, dp->d_name);
				cout<<"DIRECTORY:"<<sourceFile<<" "<<targetFile<<endl;			
				
				// backup the directory on the target directory. Which means copying it.	
				if (copyDirectory(sourceFile, targetFile, -1, previousVersion) == false)
				return false;
			}
			break;	
		
			case DT_REG:
				// Get source and target file strings ready.
				strcat(sourceFile, dp->d_name);
				strcat(targetFile, "/");
				strcat(targetFile, dp->d_name);

				// Here, we need to check if a previous version of this file exists.
				// FILE EQUALITY CHECK.
				// Using a heuristic here. If the file lengths are same, and their modification times are the same, 
				// we'll assume that the files are the same.

				if (strcmp(previousVersion,"")){
					strcpy(previousFile,previousVersion);
					strcat(previousFile, "/");
					strcat(previousFile, dp->d_name);
				}
				// If current version of the file is the same as we backed up in previous version, we'll hard link the new file to prev. 
				// version.
				if (strcmp(previousVersion, "") && filesEqual(previousFile, sourceFile)){
					cout<<"HARD LINKING "<<previousFile<<" AND "<<targetFile<<endl; 
					// Hard-linking the new file to previous version.
					link(previousFile, targetFile);

				}	
				else{
					//Copy a regular file.
					// Read file in chunks and write it.
					// Get file size first.
					cout<<"FILE:"<<sourceFile<<" "<<targetFile<<endl;			


					fp = fopen(sourceFile,"rb");
					tfp = fopen(targetFile, "wb");
  					fseek (fp , 0 , SEEK_END);
  					fileSize = ftell (fp);
  					rewind(fp);

					numberOfItr = fileSize/CHUNK_SIZE + 1;
				
					for(chunkItr = 0;chunkItr<numberOfItr;chunkItr++){
						successfulWriteCount = fread(buffer, 1, CHUNK_SIZE, fp);
						cout<<fileSize<<" "<<successfulWriteCount<<endl;
						// TODO: Check for successful writes here.
						fwrite(buffer, 1, successfulWriteCount, tfp);
					}
					fclose(fp);
					fclose(tfp);		

					// Set access modes and time attributes.
					setAttributes(sourceFile, targetFile);
				}
			break;
			
			case DT_FIFO:
			break;
			case DT_CHR:
			break;
			case DT_BLK:
			break;
			case DT_SOCK:
			break;
			case DT_LNK:
				// The File is a symbolic link.
				strcat(sourceFile, dp->d_name);
				strcat(targetFile, "/");
				strcat(targetFile, dp->d_name);
				numberOfChars = readlink(sourceFile, pointedFile, PATH_MAX);
				pointedFile[numberOfChars] = NULL;
				symlink(pointedFile, targetFile);
				setAttributes(sourceFile, targetFile);
			break;
			default:
			// This is the unknown case. Apply regular file copy.
			;
		}
	}
	return true;
}

bool filesEqual(char * file1, char * file2){
	// File sizes are equal, now check last modification times.
	struct stat file1Buffer;
	struct stat file2Buffer;
	stat(file1, &file1Buffer);
	stat(file2, &file2Buffer);
	
	if (file1Buffer.st_mtime != file2Buffer.st_mtime || file1Buffer.st_size != file2Buffer.st_size)
		return false;
	// All correct, we'll assume that they are equal files.
	return true;
}

// Set attributes of new file.
void setAttributes(char * sourceFile, char * targetFile){

	struct stat fileAttr;
	struct utimbuf timestamps;
	
	// Set access modes and time attributes.
	lstat(sourceFile, &fileAttr);	
	// Change file access mode.
	chmod(targetFile, fileAttr.st_mode);
	timestamps.actime=fileAttr.st_atime;
	timestamps.modtime=fileAttr.st_mtime;
	utime(targetFile, &timestamps);
}


