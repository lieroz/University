#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 6 

static const char success[] = 
    " ____________________________\n" \
    "( Good, you are 1337 hacker! )\n" \
    " ----------------------------\n" \
    "        o   ^__^\n" \
    "         o  (oo)\\_______\n" \
    "            (__)\\       )\\/\\\n" \
    "                ||----w |\n" \
    "                ||     ||\n";

static const char denied[] = 
    " ________________________________________\n" \
    "( C'mon man! You're not 1337 hacker yet. )\n" \
    " ----------------------------------------\n" \
    "        o   ^__^\n" \
    "         o  (oo)\\_______\n" \
    "            (__)\\       )\\/\\\n" \
    "                ||----w |\n" \
    "                ||     ||\n";

int get_device_mac_addr(unsigned char mac_address[])
{
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    int success = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) return -1;

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) return -1;

    struct ifreq *it = ifc.ifc_req;
    const struct ifreq *end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end, !success; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {

            if (!(ifr.ifr_flags & IFF_LOOPBACK)) {
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    memcpy(mac_address, ifr.ifr_hwaddr.sa_data, SIZE);
                }
            }
        }

        else {
            return -1;
        }
    }
    
    close(sock);
    return success ? 0 : -1;
}

void mac_to_str(unsigned char mac_address[], char buf[])
{
    unsigned char *it = mac_address;
    const unsigned char *end = mac_address + SIZE;

    for (int i = 0; it != end; ++it, ++i) {
        snprintf(buf + i, 2, "%c", *it);
    }
}

int main()
{
    int fd, code = 0;
    char buf[SIZE], check_buf[SIZE];
    unsigned char mac_address[SIZE];

    if ((code = get_device_mac_addr(mac_address))) {
        goto exit;
    }

    if ((fd = open("license.key", O_CREAT | O_RDWR, 0644)) != -1) {
        if (!read(fd, buf, SIZE)) {
            mac_to_str(mac_address, buf);
            write(fd, buf, SIZE);
            goto exit;
        }
    } else 
        goto exit;

    mac_to_str(mac_address, check_buf);

    if (strcmp(buf, check_buf) == 0) {
        printf("%s\n", success);
    } else {
        printf("%s\n", denied);
    }

exit:
    close(fd);
    return code;
}
