---
sort: 1
---
# OpenThread Border Router Certification Guide

## Introduction

This guide provides a step-by-step process for customers to follow for OpenThread Border Router Certification and Matter Certification for a Border Router.

It includes test setup instructions and pre-work required to fill in the certification forms.

This doecument does not provide a guarantee that CID will be obtained. I shall be used as a reference only. For confirmation contact Silicon Labs support on coommunity.sila

## Test Setup Information

**Date:** 25 Juillet 2025
**Software Stack:** GSDK 4.4.x
**Architecture followed:** AN1333 / standard OTBR over CPC
**Hardware:** EFR32MG2x

## Certification Process

This covers the steps to request a CID for Thread Border Router certification.
This document does

## CID Request Form Questions and Answers based

1. **Does the Candidate prioritize Thread control messages over other messages?**
   Yes. Following standard configuration for Thread.
2. **Does the Candidate store and communicate an Active Commissioning Dataset encoding size of up to 254 bytes?**
   Yes. `OT_OPERATIONAL_DATASET_MAX_LENGTH` in `include/openthread/dataset.h` represents both active and pending Dataset.
3. **Does the Candidate store and communicate a Pending Commissioning Dataset encoding size of up to 254 bytes?**
   Yes. `OT_OPERATIONAL_DATASET_MAX_LENGTH` in `include/openthread/dataset.h` represents both active and pending Dataset.
4. **Does the Candidate support storage and communication of a Thread Network Data encoding size up to 254 bytes?**
   Yes. `OT_OPERATIONAL_DATASET_MAX_LENGTH` in `include/openthread/dataset.h`.
5. **Enter the total # of Children (MED+SED/SSED+FED) supported by the Candidate in Router mode**
   `OPENTHREAD_CONFIG_MLE_MAX_CHILDREN` is 10 in `/src/core/config/mle.h`.
6. **Enter the total # of SED/SSED Children supported by the Candidate in Router mode**
   `OPENTHREAD_CONFIG_MLE_MAX_CHILDREN` is 10 in `/src/core/config/mle.h`.
7. **Enter the # of IPv6 addresses supported by the Candidate in a MTD Child Address Set** `OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD` is 4 in `/src/core/config/mle.h`.
8. **Enter the # of 1280-octet IPv6 datagrams that can be buffered by the Candidate for an attached SED/SSED=**`OPENTHREAD_CONFIG_DEFAULT_SED_BUFFER_SIZE` is 1280 in `/src/core/config/misc.h`.
9. **Enter the # of 106-octet IPv6 datagrams that can be buffered by the Candidate for each attached SED/SSED** `OPENTHREAD_CONFIG_DEFAULT_SED_DATAGRAM_COUNT` is 1 in `/src/core/config/misc.h`.
10. **If the answer to (8) or (9) is greater than one (1): Does the Candidate in Router mode advertise its expanded SED/SSED buffer capacity in a MLE Parent Response message?**
    N/A : Question 8 refers to 1 1280-octet buffer.
11. **Does the Candidate ensure that any buffers guaranteed for a given SED/SSED are solely used for IPv6 datagrams that have an IPv6 Destination Address matching the SED/SSED’s RLOC, its Link Local Address, one of the unicast or multicast addresses explicitly registered by the SED/SSED?**
    Yes.
12. **Enter the # of 6LoWPAN frames that can be buffered by the Candidate for forwarding to neighbors other than SED/SSEDs (i.e., other Routers, REEDs and MTDs)**
    The number of buffers is defined by `OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS`.
    Look through the information in `include/openthread/message.h` for `otBufferInfo`.
13. **Must the Candidate reassemble IPv6 datagrams before forwarding to an MTD?**
    An FTD, acting as a border router, is responsible for reassembling fragmented IPv6 datagrams before forwarding them to MTDs.
14. **If YES, enter the # of 1280-octet IPv6 datagrams that can be buffered** `OPENTHREAD_CONFIG_DEFAULT_SED_BUFFER_SIZE` is 1280 which sets this to 1.
15. **Does the Candidate implement a First In-First Out (FIFO) queue policy when forwarding to a SED/SSED?**
    Yes.
16. **Does the Candidate’s FIFO queue policy prioritize Thread control messages?**
    Yes, `OT_MESSAGE_PRIORITY_HIGH +1` found in stack, with network control messages having the highest priority. Information can be found in `src/core/common/message.hpp`.
17. **Does the Candidate support being the Probing Subject of at least one active Link Metrics series (including Enhanced ACK and Forward Series) per attached SED?**
    Yes.
18. **Are ALL of the above Router mode resource requirements able to be supported by the Candidate simultaneously?**
    Yes.
19. **Does the Candidate support inclusion of at least three (3) IPv6 prefixes, in addition to the Mesh-Local Prefix, in its own Server Data?**
    Yes, see `OPENTHREAD_CONFIG_NETDATA_PUBLISHER_MAX_PREFIX_ENTRIES` in `/src/core/config/dhcp6_server.h`.
20. **Does the Candidate support the storage of a Multicast Listeners Table of at least seventy-five (75) entries in memory?**
    Yes, see `include/openthread/thread.h`.

## Previously known test Case Failure and Resolution

### 2023.12 - Test Case Failure C5.9.9

The product was dropping a packet because the origin was untrusted

**Test Harness script version 59.4 fixed since then.**

## Certification by Inheritance

For certification by inheritance, Silicon Labs should certify this setup with the Thread Group.

Silicon Labs **does not** offer certification for the OTBR.

Therfore no inheritance is possible on OTBR products

### Silicon Labs Internal testing and Certification

- Tests are run against the OTBR using the Silicon Labs config on a Raspberry Pi to ensure that certification can be done.
- Consult the KBA for more info on Thread Certification: Thread Certification Overview.

### Test Suite used

- Silicon Labs cannot ru a ‘full’ suite of tests as there may be more or fewer tests to run based on the exact OTBR configs.
- Tests cover all mandatory, certifiable cases but do not include optional tests.
- If using Silicon Labs config (as defined in `openthread-core-silabs-posix-config.h`) with the GSDK to build the OTBR and paired with the correct RCP version with no further changes, the OTBR should be easily certifiable (not guaranteed).

## **Thread Certification Process with Silicon Labs**

Silicon Labs provides certified stack libraries for Thread certification through inheritance, which are included in SDK releases.
**This only covers SoC architectures, not OTBR**

**Proprietary / OpenThread Field**
One should specify:

- Use of Silicon Labs' OpenThread implementation.
- The version string of the OpenThread library (from certification tables).
- The relevant library CID number for your device configuration.

**Certification by Inheritance Requirements**
To qualify for certification by inheritance, ensure that you:

- Use a Thread Certified chip (EFR32).
- Utilize the certified libraries provided by Silicon Labs.
- Follow the application process for certification by inheritance.

These libraries can be found under `<gecko_sdk>\protocol\openthread\libs`, and can be install as the "OpenThread Certification Libraries" component in your project.

**Thread 1.4 Certification Status**

As of release 2.5.0.0, the SDK defaults to Thread 1.3, while Thread 1.4 features are under development and not yet certified.
The certification table shows Thread 1.4 certification is available in the 2025.6.0 release for EFR32MG24 and EFR32MG26 devices.

To achieve "Built on Thread Border Router" certification, you need to undergo ATL testing, as inheritance is not available for border router devices.

Please see the Knowledge Base Article (KBA) provided below:
[https://community.silabs.com/s/article/Thread-Certification-Overview?language=en_US](https://community.silabs.com/s/article/Thread-Certification-Overview?language=en_US)
