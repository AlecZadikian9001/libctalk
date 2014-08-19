//
//  ctalk.h
//  libctalk
//
//  Created by Alec Zadikian on 8/12/14.
//  Copyright (c) 2014 AlecZ. All rights reserved.
//

#ifndef libctalk_ctalk_h
#define libctalk_ctalk_h

/*
These functions send and receive individual "messages" (arrays of bytes of any value) preceded by headers containing variable length quantities used to share the length in bytes of each message. Messages are guaranteed to be received separately and in completeness by individual calls to cTalkRecv on the receiving end. Messages sent by cTalkSend MUST be received by cTalkRecv in order to be properly interpreted, and cTalkRecv will only properly receive data sent by cTalkSend. They return the number of bytes sent or received, or 0 if there is an error (see below).
*/
//======

// Sends the data in message over file descriptor fd with a header indicating the size, messageLen. Returns 0 (error) if the system cannot send the data.
//
size_t cTalkSend(int fd, unsigned char* message, size_t messageLen);

// Receives data on file descriptor fd without header and puts it in buffer. For the purpose of security and/or stability, a maximum buffer size bufferLen must be specified. Returns 0 (error) if the received data header indicates a size greater than bufferLen or if data with an invalid header is received. In either case, the system read buffer for fd is NOT flushed.
//
size_t cTalkRecv(int fd, unsigned char* buffer, size_t bufferLen);

//======

#endif
