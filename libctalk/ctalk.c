//
//  ctalk.c
//  libctalk
//
//  Created by Alec Zadikian on 8/12/14.
//  Copyright (c) 2014 AlecZ. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "ctalk.h"

size_t cTalkSend(int fd, unsigned char* message, size_t messageLen){
    int headerLen = (int)(log10(messageLen)/log10(128)) + 1;
    uint8_t header[headerLen];
    size_t tempLen = messageLen;
    for (int i = 0; tempLen>0; i++){
        header[i] = tempLen%128;
        tempLen /= 128;
        if (tempLen>0) header[i] &= (1 << 7);
    }
    struct iovec iov[2];
    iov[0].iov_base = header;
    iov[0].iov_len = headerLen;
    iov[1].iov_base = message;
    iov[1].iov_len = messageLen;
    size_t bytesRemaining = headerLen + messageLen;
    size_t send;
    while (bytesRemaining > 0){
        send = writev(fd, iov, 2);
        if (send==-1) return 0;
        bytesRemaining -= send;
    }
    return messageLen;
}

size_t cTalkRecv(int fd, unsigned char* buffer, size_t bufferLen){
    long recvLength = 0;
    size_t length = 0;
    bool end = false;
    int i = 0;
    while (!end){
        recvLength = read(fd, buffer, sizeof(unsigned char));
        if (recvLength<=0) return 0;
        end = ((buffer[0] >> 7) == 0);
        if (!end) buffer[0] &= ~(1 << 7);
        length+=buffer[0]*powl(128, i);
        if (length>bufferLen) return 0;
        i++;
    }
    size_t bytesRead = 0;
    while (bytesRead < length){
        recvLength = read(fd, buffer + bytesRead, length-bytesRead);
        if (recvLength<=0) return 0;
        bytesRead+=recvLength;
    }
    return bytesRead;
}