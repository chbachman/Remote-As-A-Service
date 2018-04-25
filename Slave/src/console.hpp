#include <Arduino.h>

class Console {
public:
	Console(bool printBack = false, char delimiter = '\n'):
	printBack(printBack), delimiter(delimiter) {}

	void begin() {
		Serial.begin(9600);
	  while (!Serial) { /* NOOP */
	  }
	}

	bool ready() {
	  if (Serial.available() > 0) {
	    char incomingByte = Serial.read();

	    if (incomingByte == '\0') {
	      return false;
	    }

	    if (incomingByte == delimiter) {
	      buffer[size] = '\0';
	      size = 0;

				if (printBack) {
					Serial.println();
				}

	      return true;
	    }

	    buffer[size++] = incomingByte;

	    if (printBack) {
	      Serial.print(incomingByte);
	    }
	  }

	  return false;
	}

	String get() {
		String s(buffer);
    s.trim();

		return s;
	}

private:
	char buffer[500];
	int size = 0;

	bool printBack;
	char delimiter;
};
