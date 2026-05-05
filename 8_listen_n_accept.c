// want to wait for incoming connections and handle them in some way. 
//The process is two step: first you listen(), then you accept()

int listen(int sockfd, int backlog); 

/*
    sockfd is the usual socket file descriptor from the socket() system call. 
    backlog is the number of connections allowed on the incoming queue. 
    What does that mean? 

    Well, incoming connections are going to wait in this queue until you accept() 
    them (see below) and this is the limit on how many can queue up. 

    Most systems silently limit this number to about 20; 
    you can probably get away with setting it to 5 or 10.

*/

//we need to call bind() before we call listen() so that the server is running on a specific port.

getaddrinfo();
socket();
bind();
listen();
/* accept() goes here */ 

/*
    Get ready—the accept() call is kinda weird! 
    What’s going to happen is this: someone far far away will try 
    to connect() to your machine on a port that you are listen()ing on. 
    Their connection will be queued up waiting to be accept()ed. 
    You call accept() and you tell it to get the pending connection. 
    It’ll return to you a brand new socket file descriptor to use for this single connection! That’s right, suddenly you have two socket file descriptors for the price of one! The original one is still listening for more new connections, and the newly created one is finally ready to send() and recv(). We’re there!


*/

#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); 


/*
    sockfd is the listen()ing socket descriptor. 
    Easy enough. addr will usually be a pointer to a local struct sockaddr_storage. 
    This is where the information about the incoming connection will go 
    (and with it you can determine which host is calling you from which port).
    addrlen is a local integer variable that should be set to sizeof(struct sockaddr_storage) before its address is passed to accept(). 
    accept() will not put more than that many bytes into addr. 
    If it puts fewer in, it’ll change the value of addrlen to reflect that.
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MYPORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue holds

int main(void)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;

    // !! don't forget your error checking for these calls !!

    // first, load up address structs with getaddrinfo():

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo(NULL, MYPORT, &hints, &res);

    // make a socket, bind it, and listen on it:

    sockfd = socket(res->ai_family, res->ai_socktype,
                                                 res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);

    // now accept an incoming connection:

    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
                                                       &addr_size);

    // ready to communicate on socket descriptor new_fd!
    .
    .
    .