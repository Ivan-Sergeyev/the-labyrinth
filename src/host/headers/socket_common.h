#ifndef SRC_HOST_HEADERS_SOCKET_COMMON_H_
#define SRC_HOST_HEADERS_SOCKET_COMMON_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT "3490"  // the port users will be connecting to


// kill zombie children
void _sigchld_handler(int s);

// get sockaddr, IPv4 or IPv6
void *_get_in_addr(struct sockaddr *sa);

#endif  // SRC_HOST_HEADERS_SOCKET_COMMON_H_
