---
sort: 4
---
# OpenThread Border Router CPC setup for Matter and Zigbee CMP Development

## Summary

{% include list.liquid all=true %}

**Written on February 13th 2024**
**Built on Ubuntu Desktop for Raspberry 22.04.3 LTS**

## Purpose of this guide

This guide aims to help devloppers get started with Matter Gateway developement, but with support for Zigbee in a concurrent Multi Protocol architecture

It provides guidance on how to build and run an OpenThread Border Router from scratch on a Raspberry Pi 4 that supports Matter operations

As well as running a Zigbee Host that communicates over CPC (CoProcessor Communication) 

This particular guide covers the build and use of CPC for OTBR Host to RCP communication; and Zigbee Host to NCP communication

CPC allows for multi protocol operation on the Co Processor side, enabling Zigbee and Thread Networking using only one device

This guide is based out of [AN1333](https://www.silabs.com/documents/public/application-notes/an1333-concurrent-protocols-with-802-15-4-rcp.pdf)

## Need Help ?

The only one place to request for help on building a border router will be [**Silicon Labs Community**](https://community.silabs.com/)

There is a dedicated section for [Thread](https://community.silabs.com/s/topic/0TO1M000000qHbcWAE/thread?language=en_US) in which you can ask community users for help

You can also find a non technical Matter Introduction and FAQ on [this Community article](https://community.silabs.com/s/question/0D58Y00008AV6hSSAT/what-is-matter-smart-home-standard-answers-to-10-frequently-asked-questions?language=en_US)

Find a dedicated project page for Matter evaluation on [Community Projects](https://community.silabs.com/s/projects?language=en_US)

## Contributing to this documentation

If you would like to report and or contribute to keeping this repository up to date, simply fill an issue, create a Pull Request and submit

## Documentation

Official Silicon Labs documentation can be found in [Developer Documentation](https://docs.silabs.com/openthread/latest/) page.

**Matter** official github is located [here](https://github.com/project-chip/connectedhomeip)

**OpenThread** open source main documentation page is available [here](https://openthread.io/).

**Specific OTBR** pages are [here](https://openthread.io/guides/border-router).

## Disclaimer

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.
