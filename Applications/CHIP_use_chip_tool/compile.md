---
sort: 2
---

# Building the Matter Chip Tool

`chip-tool` standalone script can be used as a controller for sending commands to a Matter device as well as commission it. It can be built from the connectedHomeip repo from a simple script

If you followed our prerequisites, you should be in a directory within `~/matter_dev/connectedhomeip` 

**This connectedhomeip folder should be a Matter git repository, bootstraped at least** 

If you did activate the environement, that will not be a problem

However, if you did not have an such folder please go back to prerequisites and perform all steps again

## Building

Go to your connectedhomeip repository and launch the following script:

```bash
cd ~/matter_dev/connectedhomeip
```
Start the build procedure

```bash
./scripts/examples/gn_build_example.sh examples/chip-tool out/standalone
```

This will create a **chip-tool** executable in **connectedhomeip/out/standalone** folder

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have built Python controller

Still, if you run into some of these issues:

* **Build fails** 
  Make sure you installed dependencies as mentioned in Matter Dev Environment support
