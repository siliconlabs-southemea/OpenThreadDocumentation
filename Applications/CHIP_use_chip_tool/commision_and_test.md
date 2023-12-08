---
sort: 3
---

# Common usage of Chip Tool

## Commissioning the node

  1.  First, you need a built and running Border Router from which you recovered the dataset :

      To do so run the following `ot-ctl` commands :
      ```bash
      sudo ot-ctl dataset active -x

      0e080000000000010000000300000f35060004001fffe0020811111111222222220708fd3a0171dcccd9a0051000112233445566778899aabbccddeeff030e4f70656e54687265616444656d6f01021234041061e1206d2c2b46e079eb775f41fc72190c0402a0fff8
      Done
      ```

  2.  Then you need to retrieve **setup-pin-code** and **discriminator** from the Matter device. That information can be obtained with JLink RTT viewer after a reset of the device:

      ```bash
      <info  > [DL] Device Configuration:
      <info  > [DL]   Serial Number: TEST_SN
      <info  > [DL]   Vendor Id: 9050 (0x235A)
      <info  > [DL]   Product Id: 21324 (0x534C)
      <info  > [DL]   Hardware Version: 0
      <info  > [DL]   Setup Pin Code: 73141520
      <info  > [DL]   Setup Discriminator: 3840 (0xF00)
      <info  > [DL]   Manufacturing Date: (not set)
      <info  > [DL]   Device Type: 65535 (0xFFFF)
      ````

  3.  Finally you need to choose a node id that will be used later after commissioning to send ZCL command to the node. As an example `12344321`.

  4.  Once you gathered all of the above information, you can proceed with actual commissioning 

      Start by going into the build folder :

      ```bash
      cd connectedhomeip/out/standalone
      ```

      Then simply run the chip-tool binary as follows :

      ```bash
      ./chip-tool pairing ble-thread [node-id] hex:[operationalDataset] [setup-pin-code] [discriminator]
      ```

      As an example with `node-id`, `dataset`, `pin-code` and `discriminator`set :

      ```bash
      ./chip-tool pairing ble-thread 12344321 hex:0e080000000000010000000300000f35060004001fffe0020811111111222222220708fd3a0171dcccd9a0051000112233445566778899aabbccddeeff030e4f70656e54687265616444656d6f01021234041061e1206d2c2b46e079eb775f41fc72190c0402a0fff8 73141520 3840
      ```
        
      **Note : It is very important NOT TO FORGET the `hex:` in front of the dataset hex string**

      If commissioning is successfull you should see this message at the end of operation:
      ```bash
        [1643224216.709173][2269:2274] CHIP:TOO: Device commissioning completed with success
      ```
      At this point your device should appear on your thread network as a router

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have built Python controller

Still, if you run into some of these issues:
* **If you run into commissioning issues**
  1.  Verify that your dataset is correct
  2.  Try to **factoryreset** both the border router and the controller using `sudo ot-ctl factoryrest` before commissioning
  3.  Try to use a new node id
