#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(){
	struct stat s;
	int fd = stat("stat.c", &s);
	if (fd < 0){
		printf("error number %d: %s\n",errno,strerror(errno));
		return 0;
	}
	printf("File size:%ld\n",s.st_size);
	printf("File mode:%d\n",s.st_mode);
	printf("Last time this file was accessed: %s\n",ctime(&s.st_atime));

	//print bytes
	printf("Size in bytes: ");
	int size = s.st_size;
	if (size > 1000000000){
		 printf("%d gigabytes ", size / 1000000000);
		 size = size % 1000000000;
	}
	if (size > 1000000){
		 printf("%d megabytes ", size / 1000000);
		 size = size % 1000000;
	} 
	if (size > 1000){
		 printf("%d megabytes ", size / 1000);
		 size = size % 1000;
	}
	printf("%d bytes ", size);
	
	//print permissions
	char permission[10];
	permission[9] = '\0';
	int octal = 0;
	int decimal = s.st_mode;
	int multiplier = 1;
	for (int multiplier = 1; multiplier < 10000; multiplier *= 10){
		octal += decimal % 8 * multiplier;
		decimal /= 8;
	}
	int index = 8;
	for(int i = 10; i< 10000; i*=10){
		int perm = octal % i / (i/10);
		if (perm >= 4){
			permission[index - 2] = 'r';
			perm -= 4;	
		}
		else permission[index - 2] = '-';
		if (perm >= 2){
			permission[index - 1] = 'w';
			perm -= 2;
		}
		else permission[index - 1] = '-';
		if (perm >= 1){
			permission[index] = 'x';
			perm -= 1;
		}
		else permission[index] = '-';
		index -= 3;
	}
	printf("\n\nPermission: %s\n", permission);
	return 0;
}
