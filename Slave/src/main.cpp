#include <Arduino.h>
#include <console.hpp>
#include <ir.hpp>
#include <MemoryFree.h>

Console serial(false);
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

void handleCommand(const String &s) {
  if (s == "learn") {
    learning = true;
    return;
  }

  if (s == "send") {
    learning = false;
    return;
  }

  if (s == "mem") {
    mem();
    return;
  }

  if (!learning) {
    ir.sendCode(IRCommand(s));
  }
}

void loop() {
  if (serial.ready()) {
    String input = receive();
    input.trim();
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
