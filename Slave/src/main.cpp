#include <Arduino.h>
#include <console.hpp>
#include <ir.hpp>
#include <MemoryFree.h>

Console serial(true);
IR ir(2);

String receive() {
  String input = serial.get();
  input.trim();
  return input;
}

void setup() {
  serial.begin();
  Serial.println(F("ready"));
  delay(500);
}

bool learning = false;

void handleCommand(String s) {
  if (s == F("learn")) {
    learning = true;
    return;
  }

  if (s == F("send")) {
    learning = false;
    return;
  }

  if (s == F("mem")) {
    Serial.println(freeMemory());
    return;
  }

  if (s == F("")) {
    ir.sendCode(IRCommand(F("{\"protocol\":2,\"value\":3216,\"bits\":12}")));
  }
}

void loop() {
  if (serial.ready()) {
    String input = receive();
    handleCommand(input);
  }

  if (learning) {
    if (ir.received()) {
      IRCommand cmd = ir.receiveCode();

      if (cmd.protocol == UNKNOWN) {
        return;
      }

      cmd.sendJSON();
    }
  }

  delay(20);
}
