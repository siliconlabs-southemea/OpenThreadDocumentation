---
sort: 1
---

## What you need

  1.  A prepared **Matter Developement Environement**

      This will bring all necessary build and flash tools as well as Matter SDK
  
  2. A built and functionnal **Matter python controller**

  3. A built and running **OpenThread Border Router**

  4.  A Silicon Labs Wireless Starter Kit which can support Matter developments

      Full list is available on this [page](https://www.silabs.com/wireless/matter)

      **Important Note:** Due to RAM limitations, Matter support on EFR32MG21 platform is now deprecated 
     
      Preferred and most economic option being our [Thunderboard Sense 2](https://www.silabs.com/development-tools/thunderboard/thunderboard-sense-two-kit)


## Getting Started

  1.  cd to your home directory if not already there :
      ```bash
      cd ~/
      ```

  2.  Create a dedicated folder within your `~/matter_dev` directory for this development purpose
      ```bash
      mkdir ~/matter_dev
      cd ~/matter_dev
      ```

  3.  If not done, prepare a **Matter development environment** following [this guide]({{ site.github.url }}/OpenThread/Applications/Matter_development_setup/)

      This is the base of any Matter, tools and implementation, developments

  4.  Also, build a **Matter python controller** following this [guide]({{ site.github.url }}/OpenThread/Applications/CHIP_use_python_controller/)
      
      This will allow us to commission our Matter device on the Border Router Thread network
  
  5.  If not already done either, build an **OpenThread Border Router compatible with Matter** following this [guide]({{ site.github.url }}OpenThread/Applications/OpenThread_Border_Router/)

      This will need an extra Starter kit as well as a dedicated running Linux based environment

      The referenced guide uses a dedicated Raspberry Pi 4 in addition to one Thunderboard Sense 2
      

Once you have done all of the above, you are ready to start