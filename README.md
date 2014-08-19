cTalk - C library for sending and receiving individual messages over sockets, pipes, etc.

A common problem programmers face when creating sending and receiving ends (for example, a TCP/IP-networked server and client) is that data sent over file/socket descriptors is sent and received as a continuous stream, not separated as messages. There is no built-in way to know what data is meant to be received together. To send and receive separated data, the programmer has to wrap the data before it is sent and unwrap it after it is received, requiring additional programming on the sending and receiving end. cTalk provides functions for sending and receiving individual messages over file descriptors. It simply prepends a header indicating the size of each message when sending data so the receiving end can separate out the messages. The sender AND receiver MUST use cTalk functions (or functions that behave in the same way) for messages to be received in the intended way.

Consider this example:

Sending end:
write(s, "test", strlen("test")+1);
write(s, "test2", strlen("test2")+1);

Receiving end:
read(s, buf, buflen);
printf("%s", buf);

What does the receving end print? It could either print "t" or "te" or "tes" or "test" or ... or "testtest" or "testtest2". The read function will put whatever available bytes there are into the buffer at the time it is called. Relying on it putting "test" into the buffer is relying on a race condition.
