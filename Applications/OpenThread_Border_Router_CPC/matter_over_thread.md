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

```

Once checked out run the bootstrap script at least one (this requires at least 32GB available on your SD Card) :

```
source ./scripts/bootstrap.sh
```

This command can take a while depending on your internet connection

From this point, steps from the regular OTBR guide can be followed :

Matter Chip-Tool Build and Common usage
