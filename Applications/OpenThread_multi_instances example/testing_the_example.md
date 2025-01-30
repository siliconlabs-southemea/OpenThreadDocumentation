---
sort: 3
---
# Using the example

## 1. Testing the Matter device on first Thread instance

Like any other standart Matter device, you can provision and control the Matter device using the python controller, chip-tool (standalone or pre-built), Android, iOS app or the mattertool utility from the Matter Hub package provided by Silicon Labs. The pre-built chip-tool instance ships with the Matter Hub image. More information on using the Matter Hub can be found in the online Matter documentation here: [Silicon Labs Matter Documentation](https://docs.silabs.com/matter/2.5.0/matter-thread/raspi-img)


More information on using the chip-tool directly can be found here: [CHIPTool](https://github.com/project-chip/connectedhomeip/blob/master/examples/chip-tool/README.md)


Here is an example with the CHIPTool:

```shell
chip-tool pairing ble-thread 1 hex:<operationalDataset> 20202021 3840

chip-tool onoff on 1 1
```

## 2. Testing the COAP communication on second Thread instance

At start-up, the MatterLightOverThread application automatically create a new Thread network if no network exists for the second Thread instance.
Since console is connected to second Thread instance, you can retrieve the dataset by the following command:

````
otcli dataset active -x
````
![1736256558922](image/dataset.png)


Once you have retrieved the proprietary Thread network dataset, you can configure a COAP client to join your Thread network created by the second instance and then receive COAP commands sent by this client.

This is documented in the following [example](../OpenThread_Coap_example/)

