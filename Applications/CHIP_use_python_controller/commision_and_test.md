---
sort: 3
---

# Common usage of Python controller

## Running Python Controller

1.  First, you need a built and running Border Router from which you recovered the dataset and extended pan id :

    To do so run the following `ot-ctl` commands :
    ```bash
    sudo ot-ctl dataset active -x

    0e080000000000010000000300000f35060004001fffe0020811111111222222220708fd3a0171dcccd9a0051000112233445566778899aabbccddeeff030e4f70656e54687265616444656d6f01021234041061e1206d2c2b46e079eb775f41fc72190c0402a0fff8
    Done
    ```

    For Extended pan id
    ```bash
    sudo ot-ctl extpanid

    1111111122222222
    Done
    ```

2.  You will also need to follow the prerequisites so you can have a built Python controller

    If you did not build the python controller, please go back to prerequisites

    To enable the Python controller virtual environment and launch it, follow these steps :
      1.  Activate the python virtual environment 
          ```bash
          source out/python_env/bin/activate

          (python_env) ubuntu@ubuntu:~/matter_dev/connectedhomeip$
          ```

      2.  Launch the utility as `sudo`
          ```bash
          sudo out/python_env/bin/chip-device-ctrl
          ```

    **You are now ready to pair your Matter device **


## Commissioning the node using Python Controller

`chip-device-ctrl` can then be run as follows:

```bash
sudo out/python_env/bin/chip-device-ctrl

[1638398220.195698][2196:2196] CHIP:CTL: SyncSetKeyValue on ExampleOpCredsCAKey
[1638398220.196167][2196:2196] CHIP:CTL: SyncSetKeyValue on ExampleOpCredsICAKey
[1638398220.196552][2196:2196] CHIP:CTL: Generating NOC
[1638398220.197018][2196:2196] CHIP:CTL: Generating ICAC
[1638398220.197403][2196:2196] CHIP:CTL: Generating RCAC
[1638398220.197784][2196:2196] CHIP:CTL: SyncSetKeyValue on ExampleCARootCert0
[1638398220.202949][2196:2196] CHIP:DL: writing settings to file (/tmp/chip_factory.ini-j3myvg)
[1638398220.203159][2196:2196] CHIP:DL: renamed tmp file to file (/tmp/chip_factory.ini)
[1638398220.203384][2196:2196] CHIP:DL: writing settings to file (/tmp/chip_config.ini-d8UXZd)
[1638398220.203517][2196:2196] CHIP:DL: renamed tmp file to file (/tmp/chip_config.ini)
[1638398220.203703][2196:2196] CHIP:DL: writing settings to file (/tmp/chip_counters.ini-U9M3wh)
[1638398220.203832][2196:2196] CHIP:DL: renamed tmp file to file (/tmp/chip_counters.ini)
[1638398220.204339][2196:2196] CHIP:IN: UDP::Init bind&listen port=0
[1638398220.204481][2196:2196] CHIP:IN: UDP::Init bound to port=51534
[1638398220.204517][2196:2196] CHIP:IN: UDP::Init bind&listen port=0
[1638398220.204628][2196:2196] CHIP:IN: UDP::Init bound to port=47609
[1638398220.204659][2196:2196] CHIP:IN: TransportMgr initialized
[1638398220.204684][2196:2196] CHIP:DIS: Init fabric pairing table with server storage
[1638398220.209302][2196:2196] CHIP:DL: Avahi client registered
[1638398220.210438][2196:2196] CHIP:ZCL: Using ZAP configuration...
[1638398220.210561][2196:2196] CHIP:ZCL: deactivate report event
[1638398220.211302][2196:2196] CHIP:DIS: Verifying the received credentials
[1638398220.213436][2196:2196] CHIP:DIS: Added new fabric at index: 1, Initialized: 1
[1638398220.213472][2196:2196] CHIP:DIS: Assigned compressed fabric ID: 0x2E844DFA0BA1AE9E, node ID: 0x000000000001B669
[1638398220.213496][2196:2196] CHIP:CTL: Joined the fabric at index 1. Compressed fabric ID is: 0x2E844DFA0BA1AE9E
[1638398220.227535][2196:2204] CHIP:DL: Platform main loop started.
Chip Device Controller Shell

chip-device-ctrl >
```

## Another usage by selecting the BLE interface that should be used

```bash
sudo out/python_env/bin/chip-device-ctrl --bluetooth-adapter=hci2
```

## Pairing the Matter lighting device 

  * Issue a `ble-scan` command to discover your Matter device
    ```bash
    chip-device-ctrl > ble-scan
    2021-12-01 23:33:00,666 ChipBLEMgr   INFO     scanning started
    2021-12-01 23:33:00,908 ChipBLEMgr   INFO     Name            = EFR32_LIGHT
    2021-12-01 23:33:00,909 ChipBLEMgr   INFO     ID              = d558231f-fb05-389c-bae2-6b797b364d28
    2021-12-01 23:33:00,910 ChipBLEMgr   INFO     RSSI            = -24
    2021-12-01 23:33:00,911 ChipBLEMgr   INFO     Address         = 04:CD:15:72:FC:D5
    2021-12-01 23:33:00,915 ChipBLEMgr   INFO     Pairing State   = 0
    2021-12-01 23:33:00,916 ChipBLEMgr   INFO     Discriminator   = 3840
    2021-12-01 23:33:00,916 ChipBLEMgr   INFO     Vendor Id       = 9050
    2021-12-01 23:33:00,916 ChipBLEMgr   INFO     Product Id      = 21324
    2021-12-01 23:33:00,919 ChipBLEMgr   INFO     Adv UUID        = 0000fff6-0000-1000-8000-00805f9b34fb
    2021-12-01 23:33:00,920 ChipBLEMgr   INFO     Adv Data        = 00000f5a234c53
    2021-12-01 23:33:00,921 ChipBLEMgr   INFO
    2021-12-01 23:33:10,849 ChipBLEMgr   INFO     scanning stopped
    ```

  * Connect to the advertising device using the discriminator, pin code and provide an option node ID. 
  
    **At the moment values are fixed ones due to alpha stage of the development**
    If the node ID is not provided here it will be assigned after connecting

    To do that call `connect -ble 3840 73141520 [nodeid]` :

    ```bash
    connect -ble 3840 73141520 12344321
    ```

    Here node ID is: 12344321

  * Provision the device with the Thread Network dataset you recovered from your Border Router in step 1:
    
    `zcl NetworkCommissioning AddThreadNetwork [nodeid] 0 0 operationalDataset=hex:[operationalkey] breadcrumb=0 timeoutMs=1000`

    ```bash
    zcl NetworkCommissioning AddThreadNetwork 12344321 0 0 operationalDataset=hex:0e080000000000010000000300000f35060004001fffe0020811111111222222220708fd4666991b8aa4f2051000112233445566778899aabbccddeeff030e4f70656e54687265616444656d6f01021234041061e1206d2c2b46e079eb775f41fc72190c0402a0fff8 breadcrumb=0 timeoutMs=1000
    ```

  * Enable provisoned Thread Network using extpanid you recovered from your Border Router in step 1:

    `zcl NetworkCommissioning EnableNetwork [nodeid] 0 0 networkID=hex:[extpanid] breadcrumb=0 timeoutMs=1000`

    ```bash
    zcl NetworkCommissioning EnableNetwork 12344321 0 0 networkID=hex:1111111122222222 breadcrumb=0 timeoutMs=1000
    ```

  * Close the BLE connection
    
    ```bash
    close-ble
    ```

  At this point your device should appear on your thread network aws a router

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should run the Python controller without issues

Still, if you run into some of these issues:

* **Runtime** fails because of `AttributeError: 'BluezManager' object has no attribute 'disconnect'`
  1.  Make sure you run the activate script as in previous section
  2.  Make sure you installed the raspberry bluetooth package **(For Raspberry users only)**
  3.  Make sure you run this utility on a device that has a Bluetooth Low Energy Interface
  
      Find your BLE controller of your machine with the hciconfig command:

      ```bash
      $ hciconfig

      hci0: 	Type: Primary  Bus: USB
        BD Address: A0:A8:CD:10:EA:27  ACL MTU: 1021:5  SCO MTU: 96:5
        UP RUNNING PSCAN ISCAN
        RX bytes:1437 acl:0 sco:0 events:170 errors:0
        TX bytes:28144 acl:0 sco:0 commands:169 errors:0
      ```


