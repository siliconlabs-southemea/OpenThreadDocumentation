---
sort: 3
---

# Magic Packet sender

Use the `rail_soc_simple_trx_std` example to send magic packet. By default example sends/receives 802.15.4 frame, so you don't need to modify frame format.

<img src="./images/simple_trx.png" alt="startup" width="600" class="center">


The addresses (Src and Dst) and the PAN ID can be customized via CLI commands. If you want a complete
list of the available commands issue the help command.

<img src="./images/cli.png" alt="startup" width="600" class="center">

Once your packet has been customized, use the `send` command to send the packet and wake-up the RCP.

# Testing the magic packet detection

Follow this sequence (tested on BRD4166A) to validate the behavior: 

1.  Start the OTBR and create a Thread network. To do so, follow [this guide](https://siliconlabs-southemea.github.io/OpenThread/Applications/OpenThread_Border_Router/create_network.html)
2.  Retrieve PanId of the created Thread network.

    ```bash
    user@ubuntu:~$ sudo ot-ctl dataset active
    Active Timestamp: 1
    Channel: 15
    Channel Mask: 0x07fff800
    Ext PAN ID: 1111111122222222
    Mesh Local Prefix: fd47:8922:96ec:b4d0::/64
    Network Key: 00112233445566778899aabbccddeeff
    Network Name: OpenThreadDemo
    PAN ID: 0xcafe
    PSKc: 445f2b5ca6f2a93a55ce570a70efeecb
    Security Policy: 672 onrc 0
    Done
    ```

3.  Press Button 0 on BRD4166. After, pressing button, RCP will be sensitive to the wake-up frame if it matches magic packet filter.
4.  You can now disconnect UART RX/TX from Host side. BRD4166 needs to stay powered. (You can use Mini Simplicity connector to maintain powering)
5.  On rail_soc_simple_trx_std side, use CLI to set SrcAddr = 0xFFFF, DstAddr = 0xFFFF, and PanId to the PanId retrieved above using CLI
6.  Finally send a packet with the rail_soc_simple_trx_std. Red led of BRD4166 should switch on.


