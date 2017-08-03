#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/io.h>
#define ERROR -1
#define OK 0
#define SLASH '/'
#define MODE (S_IRWXU | S_IRWXG | S_IRWXO)

// judge if thedirectory exists or not
int is_valid_dir(const char *dir_name) {
    return access(dir_name, F_OK);
}

int mkdirs(const char *dir_name) {
    // if the directory exisrts
    if (is_valid_dir(dir_name) != ERROR) {
        printf("The directory exists, mkdir fail.\n");
        return ERROR;
    }
    char *slash_pos = NULL;
    int bias = 0;
    while((slash_pos = strchr(dir_name + bias, SLASH)) != NULL) {
        bias = slash_pos - dir_name + 1;
        char mk_dir_name[30] = {0};
        strncpy(mk_dir_name, dir_name, slash_pos - dir_name);
        // if the directory does not exist, create it
        if (is_valid_dir(mk_dir_name) == ERROR) {
            if (mkdir(mk_dir_name, MODE) == ERROR) {
                printf("mkdir fail\n");
                return ERROR;
            }
        }
    }
    // if dose not create any directory, bias = 0
    if (bias == 0 && mkdir(dir_name, MODE) == ERROR) {
        printf("mkdir fail\n");
        return ERROR;
    }
    return OK;
}


int main() {
    printf("Please input your path name:\n");
    char path_name[30] = {0};
    fscanf(stdin, "%s", path_name);
    strncpy(path_name, path_name, strlen(path_name)-1);
    if (mkdirs(path_name) == OK) {
        printf("mkdir successfully\n");
    }
}
