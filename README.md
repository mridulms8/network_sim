# network_sim
# Network Simulator using CPP

This project is a network simulator implemented in C++. It provides a simulation of various layers of a computer network, including the Physical Layer, Data Link Layer, Network Layer, and DNS Protocol. The simulator allows users to create end devices, hubs, bridges, switches, and routers, and simulate the communication and functionality of these network components.
The program is interactive and easy to use.

## Features

The network simulator includes the following features:

1. **Physical Layer:**
   - Creation of end devices and hubs.
   - Establishment of connections between devices using star topology.
   - Sending and receiving data between devices.

2. **Data Link Layer:**
   - Addition of bridges and switches to the network.
   - Address learning in the case of switches.
   - Implementation of an access control protocol (token passing).
   - Implementation of two flow control protocols for noisy channels (stop and wait ARQ, selective repeat ARQ).

3. **Network Layer:**
   - Introduction of routers to the network.
   - Assignment of well-formatted classless IPv4 addresses to devices.
   - Utilization of ARP (Address Resolution Protocol) to find the MAC address of a host within a network.
   - Implementation of static routing.
   - Implementation of the OSPF (Open Shortest Path First) protocol for dynamic routing.

4. **DNS Protocol:**
   - Integration of the DNS (Domain Name System) protocol into the network simulation.

**Note :** The C++ libraries used to add DNS protocol may not work on Windows, Mac OS is preferred.
