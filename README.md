📌 Project Overview

Developed as part of a deep dive into Network Security and Low-level C Programming, this project implements a stateless packet filter using Raw Sockets. Inspired by the methodology in Hacking: The Art of Exploitation, this tool bypasses the standard OS network stack to intercept, parse, and filter IPv4 traffic at Layer 3 of the OSI Model.
🛠 Features

    Raw Socket Integration: Uses AF_INET and SOCK_RAW to capture TCP/IP traffic directly from the kernel.

    Custom Header Parsing: Implements a custom ip_hdr struct to map and decode binary packet data into human-readable IP addresses.

    Stateless Filtering: Applies a real-time "Blacklist" logic to identify and drop traffic from unauthorized sources.

    Live Monitoring: Provides a verbose console output for [ALLOW] and [BLOCK] actions, suitable for network auditing.

🚀 Technical Implementation

The core of this firewall lies in the Memory Mapping of the IP Header. By casting the raw buffer to a structured pointer, the application identifies the protocol type and source IP without the overhead of heavy libraries like libpcap.
Prerequisites

    Linux Environment (Tested on Kali Linux)

    GCC Compiler

    Root/Sudo Privileges (Required for Raw Socket access)

Installation & Usage

    Clone the repository:
    Bash

git clone https://github.com/lewiskagunya/mini-firewall.git
cd mini-firewall

Compile the source:
Bash

gcc mini_firewall.c -o mini_firewall

Execute with Root Privileges:
Bash

sudo ./mini_firewall
