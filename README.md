# mini-vpn

## TODO
- [x] read [Tun/Tap interface tutorial](https://backreference.org/2010/03/26/tuntap-interface-tutorial/)
- [ ] create temporary tun interface and see ICMP packet from `ping` on it

### mini TUN interface manager
> This is a suid program.
> `ip` command can do the same things.
- [ ] create a persistent tun device and assign it to the given user
- [ ] list existing tun device
- [ ] remove a persitent tun device

### mini tunnel
- [ ] attach to the tun interface given by argv[1]
- [ ] read/write some data from another VM?
- [ ] detach from the tun interface

### mini VPN
I suppose VPN need to operator on layer-2, so TAP interface?

## Tun/Tap Interface
They operate like physical network wire from the kernel's perspective. If the data is sent or received from a tun/tap interface, the kernel passes the data to the corresponding userspace program as if it is from/to the physical wire.
Tun interface read/write IP packets; Tap interface read/write Ethernet frames.
The [kernel's documentation](https://www.kernel.org/doc/Documentation/networking/tuntap.txt) explains it very-well.

### Create Tun/Tap Interface
1. open `/dev/net/tun` with read and write permission
2. initialize `struct ifreq` with 0
3. set `ifr_flags`
    - `IFF_TUN`, `IFF_TAP`: tun or tap
    - `IFF_NO_PI`: don't send packet info
      > If flag `IFF_NO_PI` is not set, each frame format is:
      >   Flags [2 bytes]
      >   Proto [2 bytes]
      >   Raw protocol(IP, IPv6, etc) frame
    - `IFF_PERSIST`: read-only flag that can only set by the kernel, used to determine [if the interface is in persist mode](https://github.com/torvalds/linux/blob/master/drivers/net/tun.c#L3102)
4. set `ifr_name` (`IFNAMSIZ` bytes at max), or `\x00` to let the kernel pick the inteface name
5. call `ioctl(fd, TUNSETIFF, ifr))` to create the interface
6. (optional) read the interface name set by the kernel from `ifr_name`

## Reference
- [Tun/Tap interface tutorial](https://backreference.org/2010/03/26/tuntap-interface-tutorial/)
- [VTun - tun-1.1 example](https://vtun.sourceforge.net/tun/index.html)
- Linux Kernel
    - [Documentation/networking/tuntap.txt](https://www.kernel.org/doc/Documentation/networking/tuntap.txt)
    - [`struct ifreq`](https://github.com/torvalds/linux/blob/master/include/uapi/linux/if.h#L234)
    - [`TUNSETIFF` ifr flags](https://github.com/torvalds/linux/blob/master/include/uapi/linux/if_tun.h#L65)
    - [drivers/net/tun.c](https://github.com/torvalds/linux/blob/master/drivers/net/tun.c#L3102)
- [WireGuard-go](https://github.com/WireGuard/wireguard-go.git)
