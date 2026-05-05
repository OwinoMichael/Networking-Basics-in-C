#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, struct sockaddr *serv_addr, int addrlen); 

// how to connect to a remote host

/*
    sockfd is our friendly neighborhood socket file descriptor, as returned by the socket() call,
    serv_addr is a struct sockaddr containing the destination port and IP address, 
    and addrlen is the length in bytes of the server address structure.

    All of this information can be gleaned from the results of the getaddrinfo() call, 
    which rocks.

*/

//make a socket connection to “www.example.com”, port 3490:

struct addrinfo hints, *res;
int sockfd;

// first, load up address structs with getaddrinfo():

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

getaddrinfo("www.example.com", "3490", &hints, &res);

// make a socket:

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

// connect!

connect(sockfd, res->ai_addr, res->ai_addrlen);