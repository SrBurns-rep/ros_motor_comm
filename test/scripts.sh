#!/bin/bash

exec roscore
exec rosserial_python serial_node.py /dev/ttyUSB0

# Publish to subscriber
rostopic pub <name of the node> std_msgms/UInt32
