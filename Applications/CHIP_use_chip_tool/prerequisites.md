---
sort: 1
---

## What you need

  1.  A prepared **Matter Developement Environement**

      This will bring all necessary build and flash tools as well as Matter SDK

## Getting Started

  1.  Install Raspberry Pi Bluetooth dependency and reboot **(For Raspberry pi Users only)**
      ```bash
      sudo apt install pi-bluetooth
      sudo reboot
      ```

  1.  cd to your home directory if not already there :
      ```bash
      cd ~/
      ```

  2.  Create a dedicated folder within your `/home/<user>/matter_dev` directory for this development purpose
      ```bash
      mkdir ~/matter_dev
      cd ~/matter_dev
      ```

  3.  If not done, prepare a **Matter development environment** following [this guide]({{ site.github.url }}/OpenThread/Applications/Matter_development_setup/deploy_matter_env.html)

      This is the base of any Matter, tools and implementation, developments

  
      
Once you have done all of the above, you are ready to start