#include<stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    // ================= IPv4 =================
    char ipv4_str[] = "192.168.1.1";
    struct in_addr ipv4_bin;
    char ipv4_out[INET_ADDRSTRLEN];

    // Convert string -> binary
    if (inet_pton(AF_INET, ipv4_str, &ipv4_bin) != 1){
        printf("IPv4 inet_pton failed\n");
        return 1;
    }

    // Convert binary -> string
    if (inet_ntop(AF_INET, &ipv4_bin, ipv4_out, INET_ADDRSTRLEN) == NULL){
        printf("IPv4 inet_ntop failed\n");
        return 1;
    }

    printf("IPv4 original: %s\n", ipv4_str);
    printf("IPv4 roundtrip: %s\n\n", ipv4_out);

    

    // ================= IPv6 =================
    char ipv6_str[] = "2001:db8::1";
    struct in6_addr ipv6_bin;
    char ipv6_out[INET6_ADDRSTRLEN];

    // Convert string → binary
    if (inet_pton(AF_INET6, ipv6_str, &ipv6_bin) != 1) {
        printf("IPv6 inet_pton failed\n");
        return 1;
    }

    // Convert binary → string
    if (inet_ntop(AF_INET6, &ipv6_bin, ipv6_out, INET6_ADDRSTRLEN) == NULL) {
        printf("IPv6 inet_ntop failed\n");
        return 1;
    }

    printf("IPv6 original: %s\n", ipv6_str);
    printf("IPv6 roundtrip: %s\n", ipv6_out);


    return 0;
}