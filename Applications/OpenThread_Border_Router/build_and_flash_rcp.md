---
sort: 2
---

# RCP firmware
When using Silicon Labs hardware, developers have 2 options to build the RCP firmware
  1.  Either from the OpenThread repository
  2.  Directly within [Simplicity Studio](https://www.silabs.com/developers/simplicity-studio)

      **This second method will not be covered in this guide**

**Important Note:**

For developpers wishing to evaluate **Matter ecosystem** implementations at the time of writing **(November 29th 2021)**

Since Matter is still in its alpha stage, **we recommend to use the 1st option with a checkout to a specific commit hash (mentioned below)**

We will do our best keeping this page up to date 

## Downloading and flashing a Bootloader to the MCU

In order to get our RCP firmware to boot, we will need to flash a bootloader on it

Such bootloader can be built using Simplicity Studio : see [UG266](https://www.silabs.com/documents/public/user-guides/ug266-gecko-bootloader-user-guide.pdf)

For convenience, we hosted a pre built Internal Storage Bootloader for BRD4166 (Built using GSDK 3.2.4)

1.  Download the Thunderboard Sense 2 bootloader 
    ```bash
    wget https://www.dropbox.com/s/qqh45vmflw3w8le/bootloader-storage-internal-single-combined-BRD4166A.s37
    ```

2.  Flash the Bootloader image 
    If you installed JLink utilities in our prerequisites then you already know how to launch the `JLinkExe` tool :
    ```bash
    JLinkExe -device EFR32MG12P432F1024GL125 -speed 4000 -if SWD -autoconnect 1
    ```
    
    **Note:** If you have several kits connected to your Rpi or computer you will need to pass its JLink serial no otherwise **this will fail**

    Flash the RCP using `loadfile ./bootloader-storage-internal-single-combined-BRD4166A.s37` in the newly opened prompt:
    ```bash
    J-Link>loadfile ./bootloader-storage-internal-single-combined-BRD4166A.s37
    Downloading file [./bootloader-storage-internal-single-combined-BRD4166A.s37]...
    Unable to load library icui18n "Cannot load library icui18n: (icui18n: cannot open shared object file: No such file or directory)"
    JLinkGUIServerExe: cannot connect to X server
    J-Link: Flash download: Bank 3 @ 0x0FE10000: 1 range affected (14336 bytes)
    J-Link: Flash download: Total: 0.523s (Prepare: 0.190s, Compare: 0.005s, Erase: 0.000s, Program & Verify: 0.270s, Restore: 0.055s)
    J-Link: Flash download: Program & Verify speed: 52 KB/s
    O.K.
    J-Link>
    ```
    
    Then reset the device and quit 
    ```bash
    J-Link>r
    Reset delay: 0 ms
    Reset type NORMAL: Resets core & peripherals via SYSRESETREQ & VECTRESET bit.
    Reset: Halt core after reset via DEMCR.VC_CORERESET.
    Reset: Reset device via AIRCR.SYSRESETREQ.
    J-Link>q
    ```

## Building the RCP dongle firmware from github

If you followed the instructions from the home page of this guide, your shell should be in /home/pi/border_router_dev, and have git installed

1.  First we need to clone the Openthread repository for EFR32
    ```bash
    git clone https://github.com/openthread/ot-efr32.git
    ```

2. Browse into it 
```bash
cd ot-efr32/
```
At this point you should be in /home/pi/border_router_dev/ot-efr32

3.  Init submodules and run the bootstrap so all needed tools and dependencies for build are installed on your dev environment

    **As of November 10th, this commit needs to be used to build an OpenThread RCP compliant with Matter**

    ```bash
    git checkout ec69725
    ```

    Start by cloning all submodules (this will download the actual Openthread repository) :
    ```bash
    git submodule update --init
    ```

    And run the bootstrap script 
    ```bash
    sudo ./script/bootstrap
    ```
    Please be patient, both last steps can take some (a lot of) time

4.  Now we will build the OpenThread RCP firmware for the Thunderboard Sense 2 
    
    If you would like to use another platform, please follow [these steps](https://github.com/openthread/ot-efr32/blob/main/src/README.md#building-examples)

    Start the build process for Thunderboard Sense 2
    ```bash
    ./script/build efr32mg12 -DBOARD=brd4166a
    ```

    A this stage, the build should be successful

5.  Verify that you have all binaries built in `ot-efr32/build/efr32mg12/bin` using `ls`
    ```bash
    $ ls build/efr32mg12/bin
    ot-cli-ftd      ot-cli-mtd      ot-ncp-ftd      ot-ncp-mtd      ot-rcp      sleepy-demo-ftd      sleepy-demo-mtd
    ot-cli-ftd.s37  ot-cli-mtd.s37  ot-ncp-ftd.s37  ot-ncp-mtd.s37  ot-rcp.s37  sleepy-demo-ftd.s37  sleepy-demo-mtd.s37
    ```

## Flashing the RCP dongle firmware on our Thunderboard Sense 2
If you installed JLink utilities in our prerequisites then you already know how to launch the `JLinkExe` tool :
```bash
JLinkExe -device EFR32MG12P432F1024GL125 -speed 4000 -if SWD -autoconnect 1
```

**Note 1:** If you have several kits connected to your Rpi or computer you will need to pass its JLink serial no

**Note 2:** Do not erase memory before flash, doing so will erase the bootloader section. Redo bootloader flash if necessary (cf above)

This time we will flash the RCP using `loadfile ./build/efr32mg12/bin/ot-rcp.s37` in the newly opened prompt:
```bash
J-Link>loadfile ./build/efr32mg12/bin/ot-rcp.s37
Downloading file [./build/efr32mg12/bin/ot-rcp.s37]...
Unable to load library icui18n "Cannot load library icui18n: (icui18n: cannot open shared object file: No such file or directory)"
JLinkGUIServerExe: cannot connect to X server
J-Link: Flash download: Bank 0 @ 0x00000000: 1 range affected (88064 bytes)
J-Link: Flash download: Total: 1.821s (Prepare: 0.242s, Compare: 0.017s, Erase: 0.000s, Program & Verify: 1.455s, Restore: 0.104s)
J-Link: Flash download: Program & Verify speed: 59 KB/s
O.K.
J-Link>
```

Now just reset the device and quit the `JLinkExe` prompt by using `r` then `q`:
```bash
J-Link>r
Reset delay: 0 ms
Reset type NORMAL: Resets core & peripherals via SYSRESETREQ & VECTRESET bit.
Reset: Halt core after reset via DEMCR.VC_CORERESET.
Reset: Reset device via AIRCR.SYSRESETREQ.
J-Link>q
```

You can now proceed to the Border Router Core Installation

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have built and flashed the RCP firmware as well as a bootloader onto the Thunderboard

Still, if you run into some of these issues:

* **Bootstrap** fails because of permissions
  Make sure you ran the script as sudo

* **Build fails** because of permissions
  Make sure you ran the script as sudo

* **Build fails** because of unidentified BOARD_ID of device family :
  Make sure to run the build script specifying it:
  `./script/build efr32mg12 -DBOARD=brd4166a`

  You can list available boards and fanilies using the shell commands below :
  ```bash
  source ./script/efr32-definitions
  efr32_get_platforms
  efr32mg1 efr32mg12 efr32mg13 efr32mg21
  
  efr32_get_boards efr32mg12
  brd4161a
  brd4166a
  brd4170a
  brd4304a
  ```

* **JLinkExe throws errors** :
  
  If the errors are :
  ```bash 
  Unable to load library icui18n "Cannot load library icui18n: (icui18n: cannot open shared object file: No such file or directory)"
  JLinkGUIServerExe: cannot connect to X server
  ```
  **-> You do not need to worry about it**

  However if you face any other error related to device connection :
  1. Be sure that you have connected your Thunderboard to your Raspberry Pi
  2. Check that you have **one and only one** Thunderboard connected to your Raspberry Pi
