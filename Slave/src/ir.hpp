#include <Arduino.h>
#include <IRLibAll.h>
#include <IRLibRecv.h>
#include <ArduinoJson.h>

struct IRCommand {
public:
  unsigned char protocol;
  unsigned int value;
  unsigned char bits;

  IRCommand(unsigned char protocol, unsigned int value, unsigned char bits): protocol(protocol), value(value), bits(bits) {}
  IRCommand(IRdecode decoder): protocol(decoder.protocolNum), value(decoder.value), bits(decoder.bits) {}

  IRCommand(String s) {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(s);
    protocol = root[F("protocol")];
    value = root[F("value")];
    bits = root[F("bits")];
  }

  void sendJSON() {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root[F("protocol")] = protocol;
    root[F("value")] = value;
    root[F("bits")] = bits;
    root.printTo(Serial);
    Serial.println();
  }
};

class IR {
private:
  IRdecode decoder;
  IRsend sender;
  IRrecv reciever;

public:
  IR(int pin = 2): reciever(pin) {
    enable();
  }

  void enable() {
    reciever.enableIRIn();
  }

  bool received() {
    return reciever.getResults();
  }

  IRCommand receiveCode() {
    decoder.decode();
    IRCommand output(decoder);
    enable();
    return output;
  }

  void sendCode(IRCommand ir) {
    // Probably will need to change this.
    if (ir.protocol == UNKNOWN) {
      return;
    }

    sender.send(ir.protocol, ir.value, ir.bits);
  }
};

// void sendCode() {
//   if (!gotNew) { // We've already sent this so handle toggle bits
//     if (codeProtocol == RC5) {
//       codeValue ^= 0x0800;
//     } else if (codeProtocol == RC6) {
//       switch (codeBits) {
//       case 20:
//         codeValue ^= 0x10000;
//         break;
//       case 24:
//         codeValue ^= 0x100000;
//         break;
//       case 28:
//         codeValue ^= 0x1000000;
//         break;
//       case 32:
//         codeValue ^= 0x8000;
//         break;
//       }
//     }
//   }
//   gotNew = false;
//   if (codeProtocol == UNKNOWN) {
//     // The raw time values start in decodeBuffer[1] because
//     // the [0] entry is the gap between frames. The address
//     // is passed to the raw send routine.
//     codeValue = (uint32_t) & (recvGlobal.decodeBuffer[1]);
//     // This isn't really number of bits. It's the number of entries
//     // in the buffer.
//     codeBits = recvGlobal.decodeLength - 1;
//     Serial.println(F("Sent raw"));
//   }
//   mySender.send(codeProtocol, codeValue, codeBits);
//   if (codeProtocol == UNKNOWN)
//     return;
//   Serial.print(F("Sent "));
//   Serial.print(Pnames(codeProtocol));
//   Serial.print(F(" Value:0x"));
//   Serial.println(codeValue, HEX);
// }
