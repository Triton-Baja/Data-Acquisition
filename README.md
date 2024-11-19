# Setup
This readme will guide you through the process of setting up your Raspberry Pi

## What you will need
- MicroSD card
- Computer with microSD reader
- Pi power supply
- Monitor
- Keyboard
- BalenaEtcher

## OS Installation
We will be using the Raspberry Pi OS Lite
1) Download the [system image](https://en.wikipedia.org/wiki/System_image) [here](https://www.raspberrypi.com/software/operating-systems/)
2) After downloading, extract/unzip the file
3) Using BalenaEtcher, burn the image into the microSD card
4) Insert the microSD in the Pi and boot it up
5) Set the username to `triton-baja` followed by the Pi number, e.g., `triton-baja1`

## Pi configuration
We can configure the Pi through the `Raspberry Pi Software Configuration Tool`, which we can access through
```
sudo raspi-config
```
Here we have multiple settings we can play with, but the ones we'll be changing are the following:
- System Options/Wireless LAN &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; → connect to a personal network (home network/hotspot)
- System Options/Boot / Auto Login &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; → console autologin
- Interface Options/ SSH &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; → enable
- Localisation Options &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; → timezone, keyboard, etc


## Updating Packages
First we'll want to update system packages to the latest version. This is a two step process. First we want to update the package index, which basically lets the Pi know what is the latest version of the installed packages.
```
sudo apt update
```
Once the Pi has the updated package index, we can ahead and install their latest version
```
sudo apt full-upgrade
```

## Setup WiFi

Check if dhcpcd is installed
```
which dhcpcd
```

If not installed
```
sudo apt install dhcpcd5
```

Update `dhcpcd.conf` by adding the line `interface wlan0` at the end of the file
```
sudo nano /etc/dhcpcd.conf
```

Enable and start dhcpcd
```
sudo systemctl enable dhcpcd
sudo systemctl start dhcpcd
sudo systemctl status dhcpcd   # should show active and enabled
```

Scan for WiFi networks
```
sudo iwlist wlan0 scan | grep "ESSID"
```

In order to connect the Pi to a WiFi network we need to modify the `wpa_supplicant.conf` file. We can open it on nano using
```
sudo nano /etc/wpa_supplicant/wpa_supplicant.conf
```

Add the network configuration
```
country=US
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

# for personal/home networks
network={
    ssid="Your_SSID"
    psk="Your_Password"
    priority=1
}

# for UCSD network
network={
    ssid="UCSD-PROTECTED"
    key_mgmt=WPA-EAP
    eap=PEAP
    identity="UCSD_Username"
    password="UCSD_Password"
    phase2="auth=MSCHAPV2"
    priority=2
}
```


Stop the network manager since it conflicts with the supplicant file
```
sudo systemctl stop NetworkManager
sudo systemctl disable NetworkManager
```

Enable and start wpa_supplicant
```
sudo systemctl enable wpa_supplicant
sudo systemctl start wpa_supplicant
```

Reboot the Pi
```
reboot
```

Check network status
```
iwconfig wlan0
```

We can further check if the Pi is connected to internet by pinging a website, e.g.,
```
ping www.google.com
```
<br><br>
If you were successful, stop here, else follow these extra steps. Go into the wpa_supplicant service
```
sudo nano /etc/systemd/system/wpa_supplicant@wlan0.service
```

Add the following:
```
[Unit]
Description=WPA supplicant for %i
Requires=sys-subsystem-net-devices-%i.device
After=sys-subsystem-net-devices-%i.device

[Service]
ExecStart=/sbin/wpa_supplicant -c /etc/wpa_supplicant/wpa_supplicant.conf -i %i
Restart=always

[Install]
WantedBy=multi-user.target
```

Enable and start the service
```
sudo systemctl enable wpa_supplicant@wlan0.service
sudo systemctl start wpa_supplicant@wlan0.service
```

Check the process' status
```
sudo systemctl status wpa_supplicant@wlan0.service
```

Check connection

## SSH
The [Secure Shell](https://en.wikipedia.org/wiki/Secure_Shell) protocol allows us to remotely access the Pi through the terminal. This way we can use our laptop to communicate with the Pi without the need for an external screen or keyboard. By default a Pi has a dynamic IP address, that means that the DHCP server assigns a temporary IP to the Pi. In this case the one assigning the IPs could be the router used at home and on campus. Given that we have no control over the dynamic IP, usually you would want something like a static IP, but in this case we will be using [Multicast DNS](en.wikipedia.org/wiki/Multicast_DNS) (mDNS) through Avahi since it is a [zero-configuration](en.wikipedia.org/wiki/Zero-configuration_networking) service.

If we were to use SSH the "standard" way, we would connect by
```
ssh username@PI_IP_ADDRESS
```
e.g.,
```
ssh triton-baja@192.186.85.21
```
However, since the IP is constantly changing, we would have to obtain the Pi's IP every single time. On the other hand, mDNS works by resolving hostnames to IP addresses, so we would connect by
```
ssh username@hostname.local
```
e.g.,
```
ssh triton-baja@raspberrrypi.local
```
Before we begin, we need to make sure that every raspberrypi has its own unique hostname. The default hostname is `raspberrypi`. We need to change this to `raspberrypitb` `n`, where again, `n` is the number of Pi, e.g., `raspberrypitb1`. You can change this through `sudo raspi-config` under System Options/Hostname and rebooting.

Let's install Avahi
```
sudo apt install avahi-daemon
```

Check it is enabled and running
```
sudo systemctl status avahi-daemon
```

Now, on your laptop, try pinging the Pi
```
ping hostname.local
```

Try connecting
```
ssh  username@hostname.local
```

## BCM2835 Library
This will be the C library we will be using to program the Pi. It is the fastest library other than native C. Let's download it
```
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.75.tar.gz
```

Extract the file
```
tar zxvf bcm2835-1.75.tar.gz
```

Install the library
```
cd bcm2835-1.71
./configure
make
sudo make install
```

Delete all the downloaded files and anything that was created as a result of extracting

# Apendix
Other commands

## Miscellaneous
Check the weather just for fun
```
curl wttr.in/location
```
e.g.,
```
curl wttr.in/Paris
```
Check disk usage
```
df -h
```

## Basic Linux Commands

- `sudo command` run `command` with admin priviliges<br>
- `nano file` Open/create `file` in `nano`<br>
- `ls` list the contents of the directory<br>
- `cd directory` navigate to `directory`<br>
- `~` home directory<br>
- `\` root directory<br>
- `mkdir directory` make `directory`<br>
- `rmdir directory` delete empty `directory`<br>
- `rm -r directory` delete non-empty `directory`<br>
- `rm file` delete `file`<br>
- `Ctrl + C` exit pretty much anything<br>

## Other Linux Commands

`sudo systemctl action process` perform `action` (enable, disable, start, stop, etc) on `process`<br>
`ps aux | grep process` dump `process` status/data<br>


## WiFi
Enable WiFi
```
sudo raspi-config nonint do_wifi_country US
```

Check if WiFi is blocked
```
sudo rfkill list
```

Unblock soft blocked WiFi
```
sudo rfkill unblock wifi
```

Update supplicant process without rebooting
```
sudo wpa_cli -i wlan0 reconfigure
```

Manually connect to WiFi
```
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
```

Manually connect to WiFi 2.0
```
sudo wpa_cli -i wlan0 reconfigure
sudo dhclient wlan0
```

Check `wpa_supplicant` logs
```
journalctl -u wpa_supplicant
journalctl -xe | grep wpa
```

Set correct permissions to supplicant file
```
sudo chmod 600 /etc/wpa_supplicant/wpa_supplicant.conf
```

Reset WiFi interface
```
sudo ifconfig wlan0 down
sudo ifconfig wlan0 up
```

## Troubleshooting
P: I connected through `sudo raspi-config` and can't seem to find the network information in the supplicant file.<br>
A: The network was added under `/etc/NetworkManager/system-connections`. Delete the file and add the information in the `wpa_supplicant.conf`
