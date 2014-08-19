//
//  main.c
//  libctalk
//
//  Created by Alec Zadikian on 8/12/14.
//  Copyright (c) 2014 AlecZ. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "ctalk.h"

#define LEN 129000

int main(int argc, const char * argv[]){
    int fd[2];
    pid_t   childpid;
    pipe(fd);
    char* test = malloc(LEN);
    if((childpid = fork()) == -1){
        perror("fork");
        return 1;
    }
    if(childpid == 0){
        /* Child process closes up input side of pipe */
        close(fd[0]);
        cTalkSend(fd[1], test, LEN);
    }
    else{
        close(fd[1]);
        unsigned char* buffer = malloc(LEN);
        cTalkRecv(fd[0], buffer, LEN);
        if (memcmp(buffer, test, LEN)==0) printf("It worked.\n");
        else printf("Failed.\n");
    }
}

