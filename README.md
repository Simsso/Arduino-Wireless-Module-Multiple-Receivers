# Arduino-Wireless-Module-Multiple-Receivers
Send different data from one transmitter to multiple receivers using an Arduino.

Video tutorial and demo: https://youtu.be/h3OevEdl674

## System setup
![System setup](https://github.com/Simsso/Arduino-Wireless-Module-Multiple-Receivers/blob/master/Images/setup.png)

## Protocol
To identify the packet destination the first byte contains the receiver ID. Packets have a fixed size (`MESSAGE_LENGTH`)
![Protcol](https://github.com/Simsso/Arduino-Wireless-Module-Multiple-Receivers/blob/master/Images/protocol.png)

## Timing
After transmitting a packet the sender has to wait for a short period of time (`MILLIS_IDLE_BETWEEN_TRANSMISSION`) until transmitting the next packet.
![Timing](https://github.com/Simsso/Arduino-Wireless-Module-Multiple-Receivers/blob/master/Images/timing.png)
