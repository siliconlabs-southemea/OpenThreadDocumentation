---
sort: 2
---

# Building the Matter Python Controller

`chip-device-ctrl` can be used as a controller for sending commands to a Matter device as well as commission it. It is part of the Python controller tools and can be built from the connectedHomeip repo from a script

If you followed our prerequisites, you should be in a directory within `~/matter_dev/connectedhomeip` 

**This connectedhomeip folder should be a Matter git repository, bootstraped at least** 

If you did activate the environement, that will not be a problem

However, if you did not have an such folder please go back to prerequisites and perform all steps again

## Bulding

Go to your connectedhomeip repository and launch the following script:

```bash
cd ~/matter_dev/connectedhomeip
```
Start the build procedure

```bash
scripts/build_python.sh -m platform -d true
```

Note that the `-d true` switch **enables debug mode which can be verbose and fill the screen with text**. 

You can type commands over the text directly, it will be taken into account

The build should end with :
```bash 
Compilation completed and WHL package installed in:
  ./out/python_env

To use please run:
  source ./out/python_env/bin/activate
```
As mentioned by the build script, in order to use the tools run :
```bash
source out/python_env/bin/activate
```

This script runs the activation script that is needed before building any of the projects in the connectedhomeip repo so there is no need to do that separately. 

Note that you will now be in a python virtual environment :
```bash
(python_env) ubuntu@ubuntu:~/matter_dev/connectedhomeip
```

In order to leave it, just use `deactivate` within the terminal :
```bash
(python_env) ubuntu@ubuntu:~/matter_dev/connectedhomeip$ deactivate
ubuntu@ubuntu:~/matter_dev/connectedhomeip$
```

To get more details about available build configurations, run the command `scripts/build_python.sh --help`

You will obtain a `chip-device-ctrl` binary located in `out/python_env/bin/` directory


## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have built Python controller

Still, if you run into some of these issues:

* **Build fails** 
  Make sure you installed dependencies as mentioned in Matter Dev Environment support








 
