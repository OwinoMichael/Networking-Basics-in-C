#include<stdio.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
 * struct addrinfo
 * ---------------
 * Used with getaddrinfo() to prepare socket addresses.
 * You fill "hints", then get a linked list of results.
 * Each node describes one possible way to connect/bind.
 *
 * Key idea:
 * - Abstracts IPv4 vs IPv6 (use AF_UNSPEC to be agnostic)
 * - ai_addr points to the actual address (sockaddr*)
 * - ai_next lets you iterate through multiple results
 */
struct addrinfo {
    int              ai_flags;     // options (e.g., AI_PASSIVE for bind)
    int              ai_family;    // AF_INET (IPv4), AF_INET6, or AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM (TCP), SOCK_DGRAM (UDP)
    int              ai_protocol;  // usually 0 (auto-select)
    size_t           ai_addrlen;   // size of ai_addr
    struct sockaddr *ai_addr;      // generic address (cast later)
    char            *ai_canonname; // canonical hostname (optional)

    struct addrinfo *ai_next;      // next result in linked list
};

/*
 * struct sockaddr (generic address container)
 * -------------------------------------------
 * Base type used by socket APIs (connect, bind, etc).
 * Usually NOT used directly—just cast from sockaddr_in/_in6.
 */
struct sockaddr {
    unsigned short    sa_family;    // AF_INET or AF_INET6
    char              sa_data[14];  // raw address data (avoid using directly)
}; 


// ================= IPv4 =================

/*
 * struct sockaddr_in (IPv4-specific)
 * ----------------------------------
 * Easier way to work with IPv4 addresses.
 * Can be cast to (struct sockaddr *) when calling APIs.
 *
 * Important:
 * - sin_port must be in network byte order (use htons())
 * - sin_zero is padding → set to 0 (memset)
 */
struct sockaddr_in {
    short int          sin_family;  // AF_INET
    unsigned short int sin_port;    // port (network byte order)
    struct in_addr     sin_addr;    // IPv4 address
    unsigned char      sin_zero[8]; // padding (zero it out)
};

/*
 * struct in_addr
 * --------------
 * Holds a 32-bit IPv4 address (e.g., 127.0.0.1)
 */
struct in_addr {
    uint32_t s_addr; // 4-byte IPv4 address
};


// ================= IPv6 =================

/*
 * struct sockaddr_in6 (IPv6-specific)
 * -----------------------------------
 * Same idea as sockaddr_in but for IPv6.
 */
struct sockaddr_in6 {
    u_int16_t       sin6_family;   // AF_INET6
    u_int16_t       sin6_port;     // port (network byte order)
    u_int32_t       sin6_flowinfo; // rarely used
    struct in6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // scope (advanced use)
};

/*
 * struct in6_addr
 * ---------------
 * Holds a 128-bit IPv6 address
 */
struct in6_addr {
    unsigned char   s6_addr[16];   // 16-byte IPv6 address
};


// ================= Generic Storage =================

/*
 * struct sockaddr_storage
 * -----------------------
 * Large enough to hold either IPv4 or IPv6.
 * Use when you don't know the address type in advance.
 *
 * Check ss_family to determine actual type, then cast:
 * - AF_INET  → sockaddr_in
 * - AF_INET6 → sockaddr_in6
 */
struct sockaddr_storage {
    sa_family_t  ss_family;     // AF_INET or AF_INET6

    // padding (ignore, implementation-specific)
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};