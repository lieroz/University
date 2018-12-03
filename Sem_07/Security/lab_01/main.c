#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

static const unsigned char key[] = {64, 73, 15, 167, 193, 83};

static const char hack_success[] = 
    " ____________________________\n" \
    "( Good, you are 1337 hacker! )\n" \
    " ----------------------------\n" \
    "        o   ^__^\n" \
    "         o  (oo)\\_______\n" \
    "            (__)\\       )\\/\\\n" \
    "                ||----w |\n" \
    "                ||     ||\n";

static const char hack_denied[] = 
    " ________________________________________\n" \
    "( C'mon man! You're not 1337 hacker yet. )\n" \
    " ----------------------------------------\n" \
    "        o   ^__^\n" \
    "         o  (oo)\\_______\n" \
    "            (__)\\       )\\/\\\n" \
    "                ||----w |\n" \
    "                ||     ||\n";

int get_device_mac_addr(unsigned char mac_address[6])
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

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end, !success; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {

            if (!(ifr.ifr_flags & IFF_LOOPBACK)) {
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
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

int main()
{
    int code = 0;
    unsigned char mac_address[6];

    if ((code = get_device_mac_addr(mac_address))) {
        goto exit;
    }

    if (memcmp(key, mac_address, 6) == 0) {
        printf("%s\n", hack_success);
    } else {
        printf("%s\n", hack_denied);
    }

exit:
    return code;
}
