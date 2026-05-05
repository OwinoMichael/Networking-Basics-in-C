#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int getaddrinfo(const char *node,   // e.g. "www.example.com" or IP
                const char *service,  // e.g. "http" or port number
                const struct addrinfo *hints,
                struct addrinfo **res);

/*
    You give this function three input parameters, and it gives you a pointer to a linked-list, res, of results.

    The node parameter is the host name to connect to, or an IP address.

    Next is the parameter service, which can be a port number, like “80”, or the name of a particular service (found in The IANA Port List21 or the /etc/services file on your Unix machine) like “http” or “ftp” or “telnet” or “smtp” or whatever.

    Finally, the hints parameter points to a struct addrinfo that you’ve already filled out with relevant information.

*/

int main(){

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me

    if(getaddrinfo(NULL, "3080", &hints, &servinfo) != 0){
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }

    // servinfo now points to a linked list of 1 or more
    // struct addrinfos

    // ... do everything until you don't need servinfo anymore ....

    freeaddrinfo(servinfo); // free the linked-list

    return 0;
}

