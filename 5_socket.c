#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol); 

/*
    allow you to say what kind of socket you want (IPv4 or IPv6, stream or datagram, 
    and TCP or UDP).

*/

int s;
struct addrinfo hints, *res;

// do the lookup
// [pretend we already filled out the "hints" struct]
getaddrinfo("www.example.com", "http", &hints, &res);

// again, you should do error-checking on getaddrinfo(), and walk
// the "res" linked list looking for valid entries instead of just
// assuming the first one is good (like many of these examples do).
// See the section on client/server for real examples.

s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

/*
    but what good is this socket? The answer is that it’s really no good by itself, 
    and you need to read on and make more system calls for it to make any sense.
*/