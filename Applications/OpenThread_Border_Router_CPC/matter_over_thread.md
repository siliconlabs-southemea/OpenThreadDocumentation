---
sort: 7
---
# Matter over Thread support

Since the OpenThread network is now up and running and Bluetooth remains available, Matter software can be built

Just go back to the working directory and clone the Matter repository from CSA. Then just checkout to the version we retrieved in section `Building Host Programs`

In our case we matched it to commit `d140d5c8775`

```
cd ~/border_router_dev
git clone https://github.com/project-chip/connectedhomeip.git
cd connectedhomeip
git checkout d140d5c8775
```

Some APT packages are required as well :

```
sudo apt-get install pkg-config libssl-dev libdbus-1-dev libglib2.0-dev libavahi-client-dev ninja-build python3.10-venv python3-dev python3-pip unzip libgirepository1.0-dev libcairo2-dev
```

And finally, because of `d140d5c8775`, a change is require in `scripts/setup/constraints.txt` :

```txt
prompt-toolkit==3.0.43
```

Once checked out run the bootstrap script at least one (this requires at least 32GB available on your SD Card) :

```bash
git submodule update --init third_party/libwebsockets
git submodule update --init third_party/perfetto
```

```bash
./scripts/checkout_submodules.py --shallow --recursive --platform efr32
. scripts/bootstrap.sh
mkdir out
./scripts/examples/gn_build_example.sh examples/chip-tool out/standalone
```

This command can take a while depending on your internet connection

In case your building on a Raspberry Pi, build may end up failing due to limited resources.

In this case two extra steps may be required :

1. Increase SWAP partition to at least 4GB
    ```bash
    TODO
    ```
2. Reduce the number of cores used for building the tool
    Go edit `scripts/examples/gn_build_example.sh` and add the following ninja argument :
    ```text
    NINJA_ARGS=(-j 1)
    ```

From this point, steps from the regular OTBR guide can be followed :

Matter Chip-Tool Build and Common usage at section usage
https://siliconlabs-southemea.github.io/OpenThread/Applications/CHIP_use_chip_tool/commision_and_test.html

## Troubleshoot

If the chip tool build freezes, on a RPi, you are likely running out of RAM . Increase the SWAP to 8GB

```
sudo swapoff -a
sudo fallocate -l 8G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
```
