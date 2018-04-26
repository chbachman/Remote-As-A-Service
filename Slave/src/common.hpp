#include <Arduino.h>
#include <MemoryFree.h>

#ifndef COMMON_H
#define COMMON_H

void mem() {
	Serial.print(F("mem: "));
	Serial.println(freeMemory());
}

class Timer {
public:
	unsigned long time;

	Timer(unsigned long time): time(time) {
		startTime = millis();
	}

	bool ready() {
		unsigned long current = millis();

		if (current - startTime > time) {
			startTime = current;
			return true;
		}

		return false;
	}

private:
	unsigned long startTime;
};

class Button {
public:
	bool prev = false;
	bool curr = false;
	const int port;
	Button(const int p): port(p) {
		pinMode(p, INPUT);
	}

	void update() {
		prev = curr;
		curr = digitalRead(port) == HIGH;
	}

	bool pressed() {
		return prev == false && curr == true;
	}

	bool depressed() {
		return prev == true && curr == false;
	}
};

#endif /* COMMON_H */
