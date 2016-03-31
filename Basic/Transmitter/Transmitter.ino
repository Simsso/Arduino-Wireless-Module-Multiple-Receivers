#include <VirtualWire.h>

#define BPS 8000 // transmission rate (bits per second)

// IDs of the receiver modules [1;255]
#define RECEIVER1_ID 1
#define RECEIVER2_ID 2

#define MESSAGE_LENGTH 3 // packet size in bytes

#define MILLIS_IDLE_BETWEEN_TRANSMISSION 9 // recommended approx. MESSAGE_LENGTH * 8 / BPS * 1,000 * 3


uint8_t outputBuffer[MESSAGE_LENGTH]; // output buffer

void setup() {
  vw_set_tx_pin(12); // transmitter module data pin
  vw_setup(BPS); // transmission rate
}

void loop() {
  sendValue(RECEIVER1_ID, 2309); // send data to receiver 1
  sendValue(RECEIVER2_ID, 63); // send data to receiver 2
}

void sendValue(int receiverId, int value) {
  byte* valPtr = (byte*)&value;
  
  // fill output buffer with data
  outputBuffer[0] = (uint8_t)receiverId;
  outputBuffer[1] = (uint8_t) *(valPtr++);
  outputBuffer[2] = (uint8_t) *(valPtr++);
  
  // transmitt data
  vw_send(outputBuffer, MESSAGE_LENGTH);
  vw_wait_tx(); // wait until the whole message is gone
  delay(MILLIS_IDLE_BETWEEN_TRANSMISSION); // wait some more time
}

