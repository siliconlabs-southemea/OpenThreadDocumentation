---
sort: 5
---
# Configure and Run Host Services

## Configuring and Running CPCd

CPC configuration is located in `/usr/local/etc/cpcd.conf`. It is overwritten everytime `make intall` is called by a developper.

By default cpcd.conf is set as :

```text
instance_name: cpcd_0
bus_type: UART
uart_device_file: /dev/ttyACM0
uart_device_baud: 115200
uart_hardflow: true
```

CPC daemon is meant to be ran as a service. Also, once installed, it is available from the shell

Steps to run it are :

1. Open a dedicated terminal or ssh session
2. Call `cpcd` from it

At this point, if `/etc/cpcd.conf` was set correctly, communication with the devkit should happen correctly and output shoud resemble :

```bash
[2024-02-13T18:12:21.237132Z] Info : [CPCd v4.4.0.0] [Library API v3] [RCP Protocol v5]
[2024-02-13T18:12:21.237248Z] Info : Git commit: 1fcaa81347466165f81e4533ee4471e9c3b6db0a / branch: refs/heads/main
[2024-02-13T18:12:21.237251Z] Info : Sources hash: 003cfa4e86453f13819ca87500baeb5594e4a7017574604a28a30257bb1c1429
[2024-02-13T18:12:21.237256Z] WARNING : In function 'main' in file /home/ubuntu/border_router_dev/cpc-daemon/main.c at line #187 : Running CPCd as 'root' is not recommended. Proceed at your own risk.
[2024-02-13T18:12:21.237300Z] Info : Reading cli arguments
[2024-02-13T18:12:21.237306Z] Info : cpcd
[2024-02-13T18:12:21.238373Z] Info : Reading configuration
[2024-02-13T18:12:21.238385Z] Info :   file_path = /usr/local/etc/cpcd.conf
[2024-02-13T18:12:21.238387Z] Info :   instance_name = cpcd_0
[2024-02-13T18:12:21.238389Z] Info :   socket_folder = /dev/shm
[2024-02-13T18:12:21.238392Z] Info :   operation_mode = MODE_NORMAL
[2024-02-13T18:12:21.238394Z] Info :   use_encryption = false
[2024-02-13T18:12:21.238396Z] Info :   binding_key_file = /root/.cpcd/binding.key
[2024-02-13T18:12:21.238397Z] Info :   stdout_tracing = false
[2024-02-13T18:12:21.238399Z] Info :   file_tracing = false
[2024-02-13T18:12:21.238401Z] Info :   lttng_tracing = false
[2024-02-13T18:12:21.238403Z] Info :   enable_frame_trace = false
[2024-02-13T18:12:21.238405Z] Info :   traces_folder = /dev/shm/cpcd-traces
[2024-02-13T18:12:21.238407Z] Info :   bus = UART
[2024-02-13T18:12:21.238409Z] Info :   uart_baudrate = 115200
[2024-02-13T18:12:21.238411Z] Info :   uart_hardflow = true
[2024-02-13T18:12:21.238413Z] Info :   uart_file = /dev/ttyACM0
[2024-02-13T18:12:21.238416Z] Info :   fu_recovery_pins_enabled = false
[2024-02-13T18:12:21.238418Z] Info :   fu_connect_to_bootloader = false
[2024-02-13T18:12:21.238420Z] Info :   fu_enter_bootloader = false
[2024-02-13T18:12:21.238422Z] Info :   restart_cpcd = false
[2024-02-13T18:12:21.238423Z] Info :   application_version_validation = false
[2024-02-13T18:12:21.238425Z] Info :   print_secondary_versions_and_exit = false
[2024-02-13T18:12:21.238427Z] Info :   use_noop_keep_alive = false
[2024-02-13T18:12:21.238429Z] Info :   reset_sequence = true
[2024-02-13T18:12:21.238431Z] Info :   stats_interval = 0
[2024-02-13T18:12:21.238433Z] Info :   rlimit_nofile = 2000
[2024-02-13T18:12:21.238435Z] Info : ENCRYPTION IS DISABLED
[2024-02-13T18:12:21.249805Z] Info : Starting daemon in normal mode
[2024-02-13T18:12:21.262826Z] Info : Connecting to Secondary...
[2024-02-13T18:12:21.608953Z] Info : RX capability is 256 bytes
[2024-02-13T18:12:21.608987Z] Info : Connected to Secondary
[2024-02-13T18:12:21.618841Z] Info : Secondary Protocol v5
[2024-02-13T18:12:21.643841Z] Info : Secondary CPC v4.4.0
[2024-02-13T18:12:21.668852Z] Info : Secondary bus bitrate is 115200
[2024-02-13T18:12:21.694266Z] Info : Secondary APP vUNDEFINED
[2024-02-13T18:12:21.694725Z] Info : Daemon startup was successful. Waiting for client connections
```

## Configuring and Running Zigbee Host

No configuration is required as only cpcd instance id is required for establishing communication.

This is passed as an argument to Z3GatewayCpc and defaults to cpcd_0

Therefore to run the Zigbee host :

1. Open a dedicated terminal or ssh session
2. cd in `~/border_router_dev/Z3GatewayCpc`
3. Call `./build/debug/Z3GatewayCpc` from it

At this point, if all was set correctly, communication with the cpcd instance happen correctly and output shoud resemble :

```bash
Reset info: 11 (SOFTWARE)

Connected to CPC daemon, endpoint 5: OK
ezsp ver 0x0D stack type 0x02 stack ver. [7.4.0 GA build 0]

Ezsp Config: set address table size to 0x0002:Success: set

Ezsp Config: set TC addr cache to 0x0002:Success: set

Ezsp Config: set MAC indirect TX timeout to 0x1E00:Success: set

Ezsp Config: set max hops to 0x001E:Success: set

Ezsp Config: set tx power mode to 0x8000:Success: set

Ezsp Config: set supported networks to 0x0001:Success: set

Ezsp Config: set stack profile to 0x0002:Success: set

Ezsp Config: set security level to 0x0005:Success: set

Ezsp Value : set end device keep alive support mode to 0x00000003:Success: set

Ezsp Policy: set binding modify to "allow for valid endpoints & clusters only":Success: set

Ezsp Policy: set message content in msgSent to "return":Success: set

Ezsp Value : set maximum incoming transfer size to 0x00000052:Success: set

Ezsp Value : set maximum outgoing transfer size to 0x00000052:Success: set

Ezsp Value : set default timeout for transient device table to 0x00002710:Success: set

Ezsp Config: set binding table size to 0x0002:Success: set

Ezsp Config: set key table size to 0x0004:Success: set

Ezsp Config: set max end device children to 0x0006:Success: set

Ezsp Config: set aps unicast message count to 0x000A:Success: set

Ezsp Config: set broadcast table size to 0x000F:Success: set

Ezsp Config: set neighbor table size to 0x0010:Success: set

Ezsp Config: set end device poll timeout to 0x0008:Success: set

Ezsp Config: set zll group addresses to 0x0000:Success: set

Ezsp Config: set zll rssi threshold to 0xFFD8:Success: set

Ezsp Config: set transient key timeout to 0x012C:Success: set

Ezsp Config: set retry size to 0x0010:Success: set

Ezsp Endpoint 1 added, profile 0x0104, in clusters: 8, out clusters 17

Ezsp Endpoint 242 added, profile 0xA1E0, in clusters: 0, out clusters 1

Starting identifying on endpoint 0x01, identify time is 0 sec

Stopping identifying on endpoint 0x01

No endpoints identifying; stopping identification feedback.

Found 0 files

Z3GatewayCpc>
```

## Configuring and Running OTBR Agent

Contrary to the other services, `otbr-agent` requires a change in itas default configuration to run with CPC

Change needs to be done in `/etc/default/otbr-agent` so it looks like :

```text
# Default settings for otbr-agent. This file is sourced by systemd

# Options to pass to otbr-agent
#OTBR_AGENT_OPTS="-I wpan0 -B eth0 spinel+hdlc+uart:///dev/ttyACM0 trel://eth0"
OTBR_AGENT_OPTS="-I wpan0 -B eth0 spinel+cpc://cpcd_0?iid=2&iid-list=0 trel://eth0"
OTBR_NO_AUTO_ATTACH=1
```

```
ubuntu@ubuntu-desktop:~$ sudo service otbr-agent status
● otbr-agent.service - OpenThread Border Router Agent
     Loaded: loaded (/lib/systemd/system/otbr-agent.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2024-02-13 19:24:06 CET; 32s ago
    Process: 23428 ExecStartPre=/usr/sbin/service mdns start (code=exited, status=0/SUCCESS)
   Main PID: 23434 (otbr-agent)
      Tasks: 2 (limit: 4127)
     Memory: 1000.0K
        CPU: 130ms
     CGroup: /system.slice/otbr-agent.service
             └─23434 /usr/sbin/otbr-agent -I wpan0 -B eth0 "spinel+cpc://cpcd_0?iid=2&iid-list=0" trel://eth0

févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.182 [I] Platform------: MulticastRoutingManager: Disable: OK
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: [INFO]-BA------: Publish meshcop service OpenThread BorderRouter #063>
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.182 [I] RouterTable---: Route table
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.182 [I] TrelInterface-: Registering DNS-SD service: port:489>
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.195 [I] Platform------: [netif] Host netif is down
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.197 [I] Platform------: [netif] Succeeded to process request>
févr. 13 19:24:08 ubuntu-desktop otbr-agent[23434]: 00:00:00.197 [W] Platform------: [netif] Failed to process request#2:>
févr. 13 19:24:09 ubuntu-desktop otbr-agent[23434]: [INFO]-MDNS----: Successfully registered service OpenThread BorderRou>
févr. 13 19:24:09 ubuntu-desktop otbr-agent[23434]: [INFO]-BA------: Result of publish meshcop service OpenThread BorderR>
févr. 13 19:24:09 ubuntu-desktop otbr-agent[23434]: [INFO]-BA------: Result of publish meshcop service OpenThread BorderR
```

## Turn CPCd into a service

To turn CPCd into a service, we will take advantage of the fact that we are running in a distribution that has systemd

Thus, simply create file `/etc/systemd/system/cpcd.service` with contents as below :

```text
[Unit]
Description=CPC Daemon Service
ConditionPathExists=/dev/ttyACM0

[Service]
ExecStart=/usr/local/bin/cpcd
KillMode=mixed
Restart=on-failure
RestartSec=5
RestartPreventExitStatus=SIGKILL

[Install]
WantedBy=multi-user.target
Alias=cpcd.service

```

And then enable and start it :

```bash
sudo systemctl enable cpcd.service
sudo systemctl start cpcd.service
sudo systemctl status cpcd.service
```

## Troubleshoot

Running CPCd if you get permission error `Permission denied`

Simply add the current user to the dialout group by calling

```bash
sudo usermod -a -G dialout $USER
```

And reboot.
