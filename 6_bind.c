#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr *my_addr, int addrlen);

/*
    Once you have a socket, 
    you might have to associate that socket with a port on your local machine.

    The port number is used by the kernel to match an incoming packet to a certain process’s socket descriptor.
     If you’re going to only be doing a connect()


    sockfd is the socket file descriptor returned by socket(). 
    my_addr is a pointer to a struct sockaddr that contains information about your address,
     namely, port and IP address. addrlen is the length in bytes of that address.
*/


struct addrinfo hints, *res;
int sockfd;

// first, load up address structs with getaddrinfo():

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

getaddrinfo(NULL, "3490", &hints, &res);

// make a socket:

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

// bind it to the port we passed in to getaddrinfo():

bind(sockfd, res->ai_addr, res->ai_addrlen);

/*
    By using the AI_PASSIVE flag, I’m telling the program to bind to the IP of the host it’s running on.
    If you want to bind to a specific local IP address, drop the AI_PASSIVE and 
    put an IP address in for the first argument to getaddrinfo().

*/