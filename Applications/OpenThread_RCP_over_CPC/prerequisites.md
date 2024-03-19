---
sort: 1
---
# Prerequisites

## What you need

1. A Linux based machine **that has a functional CPC daemon available**

   In this tutorial we are going to use a Raspberry Pi 4 running **Ubuntu 22.04.3 for Raspberry**

   You can refer to the CPC daemon and runtime libraries section of the OpenThread Border Router CPC article to set this up
2. Enable ssh on your Raspberry Pi (Optional, only if you do not use the RPi's HDMI interface)

   You can find a nice guide on how to achieve this according to your RPi usage on this [PhoenixNAP Knowledge Base Article](https://phoenixnap.com/kb/enable-ssh-raspberry-pi)

   You will also need an SSH client if you are connecting remotely to the Raspberry Pi or Build computer :

   * [PuTTY](https://www.putty.org/)
   * A good old Linux terminal (For Windows users, WSL can achieve this)
3. A Silicon Labs Wireless Starter Kit which can support Thread developement

   Full list is available on this [page](https://www.silabs.com/wireless/thread#software)

   Preferred and most economic option being our [EFR32 MG24 Devkit](https://www.silabs.com/development-tools/wireless/efr32xg24-dev-kit?tab=overview)
4. Simplicity Studio to build an OpenThread RCP image and the Bootloader with firmware upgrade support

   Simplicity Studio can be downloaded [here](https://www.silabs.com/developers/simplicity-studio)
5. A Flash Utility installed on your machine (either via Simplicity Studio or JLink)

   Simplicity comes with Simplicity Commander or Simplicity Studio Flash Programmer

   This guide will use Simplicity Commander

**Note :**

This guide does not cover how to get a Raspberry pi up and running.
For that please refer to [this guide](https://projects.raspberrypi.org/en/projects/raspberry-pi-getting-started)

This guide does not cover how to perform a Linux installation on a computer.
For this please refer to [this guide](https://ubuntu.com/core/docs/getting-started)
