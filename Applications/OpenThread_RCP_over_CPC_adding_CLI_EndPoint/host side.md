---
sort: 4
---
# Host side CpC configuration

CPC tunneling of the RAILTEST interface requires that CPC Daemon is deplyed on the Host machine connected to the EFR32 being tested

Also, Silicon Labs provides examples of CPC Bridging to Telnet only in Rust and Python. If this service must be ran natively as a C/C++ one, an entirely new must be rebuilt against the CPC libraries.

In this case we will use the Python provided script

All of the ressources used are provided in this [github repository](https://github.com/SiliconLabs/cpc-daemon)

## CPC Daemon and libraries build and installation

This part is already described in our Concurrent Multi Protocol guide located in the [OpenThread CPC Border](../../../../OpenThread/Applications/OpenThread_Border_Router_CPC/build_and_install_cpc.md)

## CPC IOStrem Bridge build and usage

Deployment instruction of the Python Library bindings are available [here](https://github.com/SiliconLabs/cpc-daemon/tree/main/lib/bindings/python)

Two possible solutions are provided :

1. Setting PYTHONPATH

2. Create a python package to be installed using PIP

The first option may not work from scratch, we will therefore cover the second installation option (Reused documentation from Silicon Labs)

### Create a package with pip

These bindings are still in development and they rely on libcpc.so which is not
part of this package. For that reason, bindings are not published in PyPi
repositories. Fortunately, it's quite easy to build the package.

First, make sure you have the dependencies installed:

    python3 -m pip install --upgrade build

Then, in this directory, next to the pyproject.toml, run:

    python3 -m build

You should see the following in the `dist` folder:

    dist/
    ├── libcpc-0.0.1-py3-none-any.whl
    └── libcpc-0.0.1.tar.gz

Finally, install the package by running pip install on the wheel file:

    python3 -m pip install libcpc-0.0.1-py3-none-any.whl

### Running the Python Bridge script

Silicon Labs provides a dedicated python script located in `cpc-daemon/script`

Its usage is documented in [this page](https://github.com/SiliconLabs/cpc-daemon/blob/main/doc/iostream_bridge.md)

    1. If CPCd was previously built, installed and configured properly, run it in a dedicated terminal or ssh session :
        ```bash
        cpcd
        ```

    2. If Python Bindings were successfully built and CPC Library installed, run the python bridge script in a dedicated terminal as follows :
        ```bash
        python script/cpc_iostream_bridge.py -n cpcd_0 -l build/libcpc.so -p 8080 -v
        ```

### Cennecting to the bridge over telnet

You can then test the bridge by opening a telnet connection:

```bash
telnet <host_ip> <host_port>
```
