#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

// The "Blacklisted" IP we want to block
#define BLOCKED_IP "8.8.8.8" 

struct ip_hdr {
    unsigned char  ip_hl:4, ip_v:4;
    unsigned char  ip_tos;
    unsigned short ip_len;
    unsigned short ip_id;
    unsigned short ip_off;
    unsigned char  ip_ttl;
    unsigned char  ip_p;
    unsigned short ip_sum;
    struct in_addr ip_src, ip_dst;
};

int main() {
    int sockfd;
    unsigned char buffer[4096];
    struct ip_hdr *ip;

    // Create raw socket to intercept traffic
    sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sockfd < 0) {
        perror("Error: Run as sudo");
        exit(1);
    }

    printf("--- MINI FIREWALL ACTIVE: BLOCKING %s ---\n", BLOCKED_IP);

    while(1) {
        recv(sockfd, buffer, 4096, 0);
        ip = (struct ip_hdr *) buffer;

        char *src_ip = inet_ntoa(ip->ip_src);

        // Check if the source matches our blacklist
        if (strcmp(src_ip, BLOCKED_IP) == 0) {
            printf("[BLOCK] Dropped packet from: %s | Reason: Blacklisted\n", src_ip);
        } else {
            printf("[ALLOW] Passed packet from:  %s\n", src_ip);
        }
    }
    return 0;
}
