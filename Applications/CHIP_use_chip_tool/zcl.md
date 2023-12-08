---
sort: 4
---

# Sending ZCL commands to the node

Contrary to python controller, the chipt-tool is able to talk directly with devices without prior operations.

To do so, use the following shell command to send a ZCL message to the matter device:

```bash
./chip-tool cluster_name command_name [param1 param2 ...]
```

## Lighting App Example
If you are working on a Light example, you can now toggle the led of the example with the following command:

```
./chip-tool onoff command_name <NodeId> <EndpointId> <GroupId>
```

In our example this gives:

```
./chip-tool onoff toggle 12344321 1
```
