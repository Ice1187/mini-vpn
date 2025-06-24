#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#define FATAL(...) do { \
    fprintf(stderr, __VA_ARGS__); \
    exit(1); \
} while (0) \

/* TODO:
  - [ ] create temporary tun interface and see ICMP packet from `ping` on it
*/

int main(void) {
    int fd, err;
    struct ifreq ifr;

    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) FATAL("Failed to open tun device: %d\n", errno);


    // TODO: what if we set IFF_PERSIST? Will that work?
    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags |= (IFF_TUN | IFF_NO_PI);

    err = ioctl(fd, TUNSETIFF, &ifr);
    if (err < 0) FATAL("Failed to create the tun device: %d\n", errno);

    printf("tun %s created\n", ifr.ifr_name);

    return 0;
}
