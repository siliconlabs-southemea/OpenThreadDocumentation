---
sort: 2
---
# CPC daemon and runtime libraries

When targetting Concurrent Multi Protocol (CMP) gateways, users must make use of Silicon Labs' CPC software. This is provided as a separate package available on one of the manufacturer's github repositories

CPC comes as an intermediate service that routes packets according to their original 802.15.4 network (PAN ID based routing if both networks use RCP communication)

## Required packages

Building CPC requires [the following packages](https://github.com/SiliconLabs/cpc-daemon?tab=readme-ov-file#cpcd-dependencies) to be installed :

```bash
sudo apt install libmbedtls-dev cmake
```

## Downloading the CPC sources

Sources are available on [this repository](https://github.com/SiliconLabs/cpc-daemon)

While you are still in your worlink directory :

```bash
git clone https://github.com/SiliconLabs/cpc-daemon.git
```

## Building CPC daemon and installing it

### Build

Go to the cloned repo :

```bash
cd cpc-daemon
```

From there, you can simply follow these [build instructions](https://github.com/SiliconLabs/cpc-daemon?tab=readme-ov-file#compiling-cpcd) provided by Silicon Labs :

```bash
mkdir build
cd build
cmake ../
```

If everything goes fine you should get below output :

```bash
-- The C compiler identification is GNU 12.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test _Wall
-- Performing Test _Wall - Success
-- Performing Test _Wextra
-- Performing Test _Wextra - Success
-- Performing Test _Wconversion
-- Performing Test _Wconversion - Success
-- Performing Test _Wmissing_declarations
-- Performing Test _Wmissing_declarations - Success
-- Performing Test _Wsign_conversion
-- Performing Test _Wsign_conversion - Success
-- Performing Test _Wswitch_default
-- Performing Test _Wswitch_default - Success
-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Looking for backtrace
-- Looking for backtrace - found
-- backtrace facility detected in default set of libraries
-- Found Backtrace: /usr/include
-- Found MbedTLS: v2.28.0
-- CPCD_CONFIG_FILE_PATH=/usr/local/etc/cpcd.conf
-- CPCD_REBOOT_TIME_MS=2000
-- CPC_SOCKET_DIR=/dev/shm
-- DEFAULT_INSTANCE_NAME=cpcd_0
-- Building CPCd with encryption enabled
-- Building CPC Daemon
-- Sources hash: 003cfa4e86453f13819ca87500baeb5594e4a7017574604a28a30257bb1c1429
-- Building release version
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/border_router_dev/cpc-daemon/build
```

**Note : If your purpose is to evaluate the setup, you can disable CPC link encryption by setting `disable_encryption: true` in `cpcd.conf`. This requires you to also disable this in the EFR32 firmware CPC configuration**

### Using Raspberry UART from 40 Pin header and keep BT for Matter

It is possible to optimize even more hardware and connect EFR32 directly using 40 pin header od the RPi and the EXP header of the SIlicon Labs devkit

This requires a modification in `/boot/firmware/config.txt` . Simply add the two lines below at the end of the file :

```plaintext
dtoverlay=miniuart-bt
enable_uart=1
```

### Install

Installation is simply performed by calling `sudo make install` once build is successfully over from the same build directory

Privileges are required to push files in /etc and /usr

You can verify that cpcd is available by calling `cpcd -v` :

```bash
4.4.0.0
GIT commit: 1fcaa81347466165f81e4533ee4471e9c3b6db0a
GIT branch: refs/heads/main
Sources hash: 003cfa4e86453f13819ca87500baeb5594e4a7017574604a28a30257bb1c1429
```
