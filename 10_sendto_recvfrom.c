// Since datagram sockets aren’t connected to a remote host, guess which piece of information we need to give before we send a packet? 
// That’s right! The destination address! Here’s the scoop:

int sendto(int sockfd, const void *msg, int len, unsigned int flags,
           const struct sockaddr *to, socklen_t tolen); 


/*
    this call is basically the same as the call to send() with the addition of two other pieces of information. 
    to is a pointer to a struct sockaddr 
    (which will probably be another struct sockaddr_in or struct sockaddr_in6 or struct sockaddr_storage that you cast at the last minute) 
    which contains the destination IP address and port. tolen, an int deep-down, can simply be set to sizeof *to or sizeof(struct sockaddr_storage).

    To get your hands on the destination address structure, 
    you’ll probably either get it from getaddrinfo(), 
    or from recvfrom(), below, or you’ll fill it out by hand.

    Just like with send(), 
    sendto() returns the number of bytes actually sent 
    (which, again, might be less than the number of bytes you told it to send!), 
    or -1 on error.
*/

// Equally similar are recv() and recvfrom(). The synopsis of recvfrom() is:

int recvfrom(int sockfd, void *buf, int len, unsigned int flags,
             struct sockaddr *from, int *fromlen); 



/*
    recv() with the addition of a couple fields. 
    from is a pointer to a local struct sockaddr_storage that will be filled with the IP address and port of the originating machine. 
    fromlen is a pointer to a local int that should be initialized to sizeof *from or sizeof(struct sockaddr_storage). 
    When the function returns, fromlen will contain the length of the address actually stored in from.

    recvfrom() returns the number of bytes received, or -1 on error (with errno set accordingly).
*/

/*
    Remember, if you connect() a datagram socket, you can then simply use send() and recv() for all your transactions. 
    The socket itself is still a datagram socket and the packets still use UDP, 
    but the socket interface will automatically add the destination and source information for you.
*/