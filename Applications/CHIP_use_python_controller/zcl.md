---
sort: 4
---

# Sending ZCL commands to the node :

## Resolve the address to the node 

The node ID needs to be resolved to an IP address that can be used to communicate with the device. 

To resolve an address, Matter also needs a fabric ID

Such fabric creation is managed by Python Controller

The fabric ID of the network needs to be found using `get-fabricid` in the python controller:

```bash
chip-device-ctrl > get-fabricid

Get fabric ID complete
Raw Fabric ID: 0x0000000000000000 (0)
Compressed Fabric ID: 0x8c1e507bd83c001b (10096595907450241051)
```

To resolve the address use `resolve <fabric compressed id decimal> <node id>` passing the **fabric ID in decimal** as well as previously defined node ID (12344321) 

```bash
resolve 10096595907450241051 12344321
```

## Lighting App Example :
If you are working on a Light example, you can now toggle the led of the example with the following command:

```
> chip-device-ctrl > zcl OnOff Toggle <NodeId> <EndpointId> <GroupId>
```

In our example:

```
> chip-device-ctrl > zcl OnOff Toggle 12121212 1 0
```
 
## Window Covering Example :
If you are working on a Window covering example, you can now close the window covering with the following command:

```
> chip-device-ctrl > zcl WindowCovering WindowCoveringDownClose <NodeId> <EndpointId> <GroupId>
```

In our example:

```
> chip-device-ctrl > zcl WindowCovering WindowCoveringDownClose 12121212 1 0
```

## Troubleshoot
If you precisely follow all of the previous sections (including git checkouts and prerequisites), you should have successfully paired, and used your lighting example

Still, if you run into some of these issues:

* **Address Resolution fails or crashes the controller** 
  1.  Check that your Thread Device is on the network (i.e. using the topology feature of the Border Router)
  1.  Make sure you used the **DECIMAL COMPRESSED** fabric ID