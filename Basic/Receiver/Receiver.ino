#include <VirtualWire.h>

#define BPS 8000 // transmission rate (bits per second)
#define RECEIVER_ID 1 // ID of this receiver
#define MESSAGE_LENGTH 3 // number of bytes a data packet contains
#define MILLIS_IDLE_BETWEEN_TRANSMISSION 9 // min. time the transmitter waits before sending the next message

#define RX_PIN 12 // wireless module receiver data pin

uint8_t inputBuffer[MESSAGE_LENGTH]; // full data packet

byte rawData[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming data (can contain parts of a data packet)
byte dataLength = VW_MAX_MESSAGE_LEN; // the size of the data

unsigned long lastDataReceived = 0; // time (millis) of last data reception
byte bytesReceived = 0; // number of bytes of current packet already received

void setup() {
  Serial.begin(9600);

  vw_set_rx_pin(RX_PIN); // pin
  vw_setup(BPS); // transmission rate
  vw_rx_start(); // start receiver
}

void loop() {
  if (vw_get_message(rawData, &dataLength)) { // data incoming
    lastDataReceived = millis();

    // valid number of bytes received
    if (bytesReceived + dataLength > MESSAGE_LENGTH) {
      flushInputBuffer();
    }
    else {
      // append new raw data to input buffer
      for (int i = 0; i < dataLength; i++) {
        inputBuffer[bytesReceived + i] = rawData[i];
      }
      
      bytesReceived += dataLength;
      
      // check whether a full packet has been received already
      if (bytesReceived == MESSAGE_LENGTH) {
        // read recipient information (first byte)
        if (inputBuffer[0] == RECEIVER_ID) {
          // packet is for this receiver
          
          // read packet content
          int val;
          byte* valPtr = (byte*)&val;
          *(valPtr++) = inputBuffer[1];
          *(valPtr++) = inputBuffer[2];
          
          Serial.println(val);
        }

        flushInputBuffer(); // clear input buffer
      }
    }
  }

  if (bytesReceived && lastDataReceived + MILLIS_IDLE_BETWEEN_TRANSMISSION / 2 < millis()) {
    // a broken packet has been received 
    flushInputBuffer();
  }
}

void flushInputBuffer() {
  for (byte i = 0; i < MESSAGE_LENGTH; i++) {
    inputBuffer[i] = 0;  
  }
  bytesReceived = 0;
}
