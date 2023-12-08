---
sort: 2
---

# Install Matter SDK Development Environment:

If you followed our prerequisites, you should be in a directory within `~/matter_dev`

1.  Start by cloning Matter and its submodules there :
    ```bash
    git clone https://github.com/project-chip/connectedhomeip
    cd connectedhomeip
    ```

    **In order to successfully build this repo, the hash b0af6ba42b6ce494748f18ecf3e054a400b8f45b needs to be used to build a Matter device**
    ```bash
    git checkout b0af6ba42b6ce494748f18ecf3e054a400b8f45b
    ```

    Now you can clone the repositories submodules
    ```bash
    git submodule update --init
    ```

    On raspberry Pis this can take a while, make sure to not forget the `git checkout` before submodule updates (otherwise you will spend some time either debugging or simply doing it again)

**IMPORTANT NOTE:** On raspberry Pis it is hghly likely that this first bootstrap fails with python related errors. 
    
If you face that issue please look for the troubleshoot section below

2.  Start the build environment deployment by bootstraping using `source scripts/bootstrap.sh` 
    ```bash
    source scripts/bootstrap.sh

    WELCOME TO...

      ▄███▒  ░▓█  ░▓█ ░▓█▓ ▒█████▄
    ██▒ ▀█▒  ▒█   ▒█  ░█▒  ▒█░  █░
    █▓░      ▒██████  ░█▒  ▒█▄▄▄█░
    ▓█   █▒  ▒█   ▒█  ░█░  ▒█▀
    ░▓███▀  ░▓███░▓█▒ ░█░  ▒█

      BOOTSTRAP! Bootstrap may take a few minutes; please be patient.

    Downloading and installing packages into local source directory:

      Setting up CIPD package manager...done (27.7s)
      Setting up Python environment.....done (2m19.1s)
      Setting up Host tools.............done (0.1s)

    Activating environment (setting environment variables):

      Setting environment variables for CIPD package manager...done
      Setting environment variables for Python environment.....done
      Setting environment variables for Host tools.............done

    Checking the environment:

    20211130 22:46:59 INF Environment passes all checks!

    Environment looks good, you are ready to go!

    To activate this environment in the future, run this in your
    terminal:

      source ./activate.sh
    ```

    **Note:** On raspberry Pis this can take a while (about 10mins on Rpi4 Model B), make sure to not forget to install dependencies from prerequisites

    **IMPORTANT NOTE:** On raspberry Pis it is hghly likely that this first activate fails with python related errors. 
    
    If you face that issue please look for the troubleshoot section below

    If successful as above, call `source scripts/activate.sh`
    ```bash
    source scripts/activate.sh

      WELCOME TO...

      ▄███▒  ░▓█  ░▓█ ░▓█▓ ▒█████▄
    ██▒ ▀█▒  ▒█   ▒█  ░█▒  ▒█░  █░
    █▓░      ▒██████  ░█▒  ▒█▄▄▄█░
    ▓█   █▒  ▒█   ▒█  ░█░  ▒█▀
    ░▓███▀  ░▓███░▓█▒ ░█░  ▒█

      ACTIVATOR! This sets your shell environment variables.

    Activating environment (setting environment variables):

      Setting environment variables for CIPD package manager...done
      Setting environment variables for Python environment.....done
      Setting environment variables for Host tools.............done

    Checking the environment:

    20211130 22:49:49 INF Environment passes all checks!

    Environment looks good, you are ready to go!

    ```
You can now look into Matter application examples or Python Controller tutorials

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have a perfectly working Matter Development Environment

If somehow you still have issues, we identified a few scenarios where you might verifiy you did not miss any step :

* **Bootstrap fails**
  
  1.  Make sure you installed all dependencies as in **prerequisites**. This involves a reboot

      **No other dependency is needed, especially for gn errors (DO NOT install generate-ninja from apt)**

      Once done, re clone and re checkout the Matter repository before bootsraping again

  2.  Be sure that you have the right Raspberry OS

      **It is actually MANDATORY to use Ubuntu Server 64bits 20.04 LTS3 (arm64) if developping for Matter** 

      If you run into the missing gn mentionned above, be sure you are running on top of Ubuntu and not Debian

  3.  **Python 3 Related errors occur**

      The raspberry environment is known to be unstable when bootstraping due to the alpha state of the framework.

      If you face such issues follow the below instructions :

      1.  Reboot the Raspberry Pi

          ```bash
          sudo reboot
          ```

      2.  Go back to `~/matter_dev/connectedhomeip`

          ```bash
          cd ~/matter_dev/connectedhomeip
          ```

      3.  Run bootstrap script again

          ```bash
          source scripts/bootstrap.sh
          ```

      4.  Run activate script again

          ```bash
          source scripts/activate.sh
          ```

          At this point it will either work or throw you an error about pw (PigWeed)

          If so, then go to next error

    4.  **pw : command not found** error

        1.  Get to your matter_dev directory :

            ```bash
            cd ~/matter_dev
            ```

        2.  Delete the entire Matter repository (Sorry for this but we did not found any other option :/)
            
            ```bash
            rm -rf connectedhomeip
            ```

        3.  Reboot the Raspberry Pi

            ```bash
            sudo reboot
            ```

        4.  Perform all of the steps of that page again (clone, checkout, bootstrap, and activate)
