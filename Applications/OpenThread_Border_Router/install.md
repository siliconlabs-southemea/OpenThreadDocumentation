---
sort: 3
---

# Border Router Install

**Important Note :** Before starting from this point, make sure you have followed all steps from *Prerequisites* and *OpenThread Border Router setup on a Raspberry Pi 4 - RCP firmware*

## Build and Install the Open Thread Border Router core:
Browse back tou your development directory :
```bash
cd ~/border_router_dev
```

Then clone the OpenThread Border Router repository
```bash
git clone https://github.com/openthread/ot-br-posix
```

Browse into the cloned directory:
```bash
cd ot-br-posix
```

**As of November 10th, this commit needs to be used to build an OpenThread RCP compliant with Matter**
```bash
git checkout 72bb3d456
```

Run the bootstrap script to install build dependencies
```bash
sudo ./script/bootstrap
```

And finally launch the build procedure
```bash
sudo BACKBONE_ROUTER=1 INFRA_IF_NAME=eth0 ./script/setup
```
These two last steps can take a while

Update OTBR-Agent by replacing **OTBR_AGENT_OPTS** with below line

This will tell the otbr-agent that we are a Backbone Router on eth0 `-B eth0`, the tty interface we want to use `/dev/ttyACM0` and the spinel baudrate `uart-baudrate=460800` for the created `wpan0` interface
```bash
sudo nano /etc/default/otbr-agent

OTBR_AGENT_OPTS="-I wpan0 -B eth0 spinel+hdlc+uart:///dev/ttyACM0?uart-baudrate=460800 trel://eth0"
```

Once the build and install procedure is over, simply reboot your Raspberry Pi:
```bash
sudo reboot now
```

## Verify that the Border Router is up and running

Once the reboot is complete, and you have logged into the RPi again, check that otbr services are running fine:

```bash
sudo systemctl status | grep otbr

             ├─otbr-web.service
             │ └─448 /usr/sbin/otbr-web
             ├─otbr-agent.service
             │ └─441 /usr/sbin/otbr-agent -I wpan0 -B eth0 spinel+hdlc+uart:///dev/ttyACM0?uart-baudrate=460800 trel://eth0
```

As well as for the avahi service 
```bash
sudo systemctl status | grep avahi

             ├─avahi-daemon.service
             │ ├─422 avahi-daemon: running [raspberrypi.local]
             │ └─426 avahi-daemon: chroot helper
```

At this point, the OpenThread Border Router should provide access to the `ot-ctl` tool from the shell
```bash
sudo ot-ctl state

disabled
Done
```

At this stage you can proceed creating your Thread Network on next page 

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have a perfectly running OpenThread Border Router

If somehow you still have issues, we identified a few scenarios where you might verifiy you did not miss any step :

* **sudo: unable to resolve host ubuntu: Name or service not known**

This can happen when otbr installation messes up with `/etc/hosts`

To fix it, edit your file using `sudo nano /etc/hosts` so it looks as below :
```bash
127.0.0.1 localhost ubuntu

# The following lines are desirable for IPv6 capable hosts
::1 ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
ff02::3 ip6-allhosts
```

Note the added `ubuntu` at the end of first line

* **GCC seems to stall during build**:

If you have an RPI 4 with less than 8GB RAM memory then you may need to setup swap memory before attempting to build any of the projects:

```bash
free -mh
sudo dd if=/dev/zero of=/home/swap bs=1024 count=640000
sudo mkswap /home/swap
sudo swapon /home/swap
```

* **Bootstrap fails** because of permissions
  
  Make sure you ran the script as sudo

* **Build fails** because of permissions
  
  Make sure you ran the script as sudo

* **ot-ctl connect session failed**
  
  It is usually due to an issue with otbr-agent unable to communicate with the RCP 

  `cat` syslog to identify the possible issue:
  ```bash
  cat /var/log/syslog | grep otbr
  ```

  If the issue is: **RadioSpinelNoResponse**
  1.  The obvious one, make sure you plugged the Thunderboard USB cable on the Raspberry Pi, and not on some other device

  2.  Make sure you edited the `/etc/default/otbr-agent` correctly

      As stated above, agent options should be :
      ```bash
      OTBR_AGENT_OPTS="-I wpan0 -B eth0 spinel+hdlc+uart:///dev/ttyACM0?uart-baudrate=460800 trel://eth0"
      ```

  3.  Make sure that you did flash the correct binary : `ot-rcp.s37`
      
      It is a common mistake to flash ot-ftd, ot-mtd or ot-ncp variants

  4.  Make sure that you flashed a bootloader to your Thunderboard Sense 2
      
      See first section of this article. Without it the RCP firmware will not run, MCU ends in DefaultHanlder

  5.  Make sure that you have updated your Thunderboard Sense 2 Kit to a version > 1v3p0
      
      See the prerequisites section. This prevents the kit to disable flow control, hence blocking the UART communications

  6.  Finally if all of the above did not help make sure flow control is not forced enabled on your Thunderboard.

      To do so, you need to connect to the "ADMIN" console via Simplicity Studio
      
      A detailed Knowledge Base can be found [here](https://community.silabs.com/s/article/wstk-virtual-com-port-baudrate-setting?language=en_US)

* **Still not working ?**

If none of the above worked, you can download a **binary built** during the writing of this guide [here](https://www.dropbox.com/s/d9aay5yjq3bcdld/ot-rcp-brd4166.s37)

**DO NOT FORGET** to flash a bootloader alongside it. Bootloader is provided [here](https://www.dropbox.com/s/qqh45vmflw3w8le/bootloader-storage-internal-single-combined-BRD4166A.s37)

If by using these 2 binaries you can get further, make sure that you ran through `Building the RCP dongle firmware from github` following all steps, especially git checkout to a known working version

If your Border Router Still does not run, make sure that you ran through `Building the RCP dongle firmware from github` following all steps, especially git checkout to a known working version

If not there at this stage you might request for help on building a border router on Silicon Labs Community 

There is a dedicated [Thread](https://community.silabs.com/s/topic/0TO1M000000qHbcWAE/thread?language=en_US) section in which you can ask community users for help
