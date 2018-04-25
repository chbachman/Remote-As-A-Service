#include "Arduino.h"

#ifndef COMMON_H
#define COMMON_H

int GREEN = LED_BUILTIN;
int RED = 12;
int BLUE = 11;
int MODE_BUTTON = 2;

void redLED(int value) { digitalWrite(RED, value); }

void blueLED(int value) { digitalWrite(BLUE, value); }

void greenLED(int value) { digitalWrite(GREEN, value); }

void allLED(int value) {
	digitalWrite(RED, value);
	digitalWrite(BLUE, value);
	digitalWrite(GREEN, value);
}

void displayNumber(int num) {
	allLED(LOW);

	greenLED((num >> 2 & 1) ? HIGH : LOW);
	redLED((num >> 1 & 1) ? HIGH : LOW);
	blueLED((num & 1) ? HIGH : LOW);
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
