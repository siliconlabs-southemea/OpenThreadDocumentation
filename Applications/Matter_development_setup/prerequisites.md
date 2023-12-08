---
sort: 1
---

# Initial steps

If you are not already running Ubuntu natively on your computer, you will need an alternative to develop Matter devices

## What you need

  1. A Linux Environment
  
  2. `git` installed on your build machine

     For above mentionned systems a simple package manager installation should work 
     ```c
     sudo apt install git
     ```

  3. Matter Dependencies installed

  3.  A Jlink compatible Flash Utility installed on your machine 

  4.  A Silicon Labs Wireless Starter Kit which can support Matter developments

      Full list is available on this [page](https://www.silabs.com/wireless/matter)

      **Important Note:** Due to RAM limitations, Matter support on EFR32MG21 platform is now deprecated 
     
      Preferred and most economic option being our [Thunderboard Sense 2](https://www.silabs.com/development-tools/thunderboard/thunderboard-sense-two-kit)

## Choosing a Linux environment

Matter needs to be built within a unix environment

There are several options listed below :

  * Using a bare metal environment by installing a distro directly on a computer **(Ubuntu 20.04, Mac)** - **RECOMMENDED**
  
  * Using a bare metal environment by installing a distro directly on a Raspberry Pi **(Ubuntu Server 20.04 64bits LTS3)**

  * Installing Virtualbox and creating a Virtual Machine - **RECOMMENDED**:
  
    For this, download [VirtualBox](https://www.virtualbox.org/)

    Once VirtualBox is installed, create a new virtual machine as a Linux Ubuntu 64 bit. 

    Then either install Linux from an iso available [here](https://ubuntu.com/download/desktop) or a virtual disk already prepared [here](https://www.osboxes.org/ubuntu/).

    In case you're installing from the iso, size the VM disk to at least 20GB to have room for the install and Matter SDK.

      * Configuring the Virtual Machine:

        Before running the VM, we need to configure networking setting and change network adapter to Bridge mode.

        - Open the VirtualBox and click on ‘Settings’ of your Linux VM.
        - Click on ‘Network’ and Select the ‘Adapter 1’ tab.
        - Make sure ‘Bridge Adapter’ is selected in the ‘Attached to:’ box.
        - Click OK.

  * Using Ubuntu on Windows using WSL 

    WSL is a feature disabled by default on Windows

    You can follow this Microsoft [Getting Started with WSL](https://docs.microsoft.com/en-us/learn/modules/get-started-with-windows-subsystem-for-linux/) to install it

    **Important Note:** When chosing your Linux distribution, make sure you select Ubuntu


## Getting Started

  1.  cd to your home directory if not already there :
      ```bash
      cd ~/
      ```

  3.  Create a dedicated folder within your `~/matter_dev` directory for this development purpose
      ```bash
      mkdir ~/matter_dev
      cd ~/matter_dev
      ```

  4.  Check that you have git installed
      ```bash
      sudo apt update
      sudo apt install git
      sudo apt update
      ```
      
      If some packages can be upgraded feel free to do so, **but ensure to run an apt update as last command**

  5.  Install Dependencies

      **Below dependencies are tied to the Matter github commit hash checked out on the next section (test_event_6 branch)**
      ```bash
      sudo apt-get install git gcc g++ python pkg-config libssl-dev libdbus-1-dev libglib2.0-dev libavahi-client-dev ninja-build python3-venv python3-dev python3-pip unzip libgirepository1.0-dev libcairo2-dev
      ```

      Now just reboot once
      ```bash
      sudo reboot
      ```

      Reconnect to your build machine
      Go back to your `~/matter_dev` directory
      ```bash
      cd ~/matter_dev
      ```

  6.  Make sure you have a JLink Flasing Utility installed

      There are two options to flash your devices with the freshly built binaries 

      **Important Note** WSL does not support flash operations

      It might then not be possible for you to use command line utilities to flash your plugged starter kit

      To Flash your device build your binaries on WSL but `cp` them in the Windows File System `/mnt/c/<location>`

      * **Adding Simplicity Commander (optionnal but recommended, only for VM and Bare Metal users)** 

        Simplicity Commander can be used to flash your Starter Kit with the binaries that you will build

        Note that commander **CANNOT be run on Raspberry Pi**, only on Windows, Mac and Linux x86_64 platforms

        If you build your binaries on WSL but locate them in the Windows File System, you can also use Commander from Windows

        Start by downloading the utility for your computer:
        [Installer for Linux](https://www.silabs.com/documents/public/software/SimplicityCommander-Linux.zip)
        [Installer for Windows](https://www.silabs.com/documents/public/software/SimplicityCommander-Windows.zip)
        [Installer for Mac](https://www.silabs.com/documents/public/software/SimplicityCommander-Mac.zip)

        Note that Commander is installed by Simplicity Studio in `<StudioInstallDir>\SimplicityStudio\v5\developer\adapter_packs\commander`

        Or install each package and dependencies according to their README

        **Note : Add Commander to your shell search path if you want to use Matter's flash helper scripts**
        
        If not done, you will have to perform a 2 extra steps provided in the sample applications' guides

        **Note : As mentioned above, this does not apply to Raspberry Pi OS and WSL**

      * **Using JLinkExe utility (required only for VM, Bare Metal and Raspberry OS users)**

        You can install JLink on your system to flash your built binaries

        Go to [JLink Download Page](https://www.segger.com/downloads/jlink/)
        Look for the package that suits your platform and Download it 
        
        For ease of use in a command line environment, we hosted a few packages on a Dropbox:
        * [JLink Linux amd64](https://www.dropbox.com/s/leolh6222ms31r0/JLink_Linux_V758c_x86_64.deb)

        Download as follows for a Native Linux environment or WSL:
      
        ```bash
        wget https://www.dropbox.com/s/leolh6222ms31r0/JLink_Linux_V758c_x86_64.deb
        ```

        Then install using :
        ```bash
        sudo apt update
        sudo dpkg -i JLink_Linux_V758c_x86_64.deb
        sudo apt update
        ```

  7.  Plug in your Thunderboard Sense 2 to your Raspberry Pi and check it is enumerated
    
      ```bash
      ls -ail /dev/ttyACM* 
      450 crw-rw-rw- 1 root dialout 166, 0 Nov 29 19:14 /dev/ttyACM0
      ```
