#include <Arduino.h>
#include <LiquidCrystal.h>
#include "common.hpp"

class LCD {
public:
	LiquidCrystal screen;
	const int fps = 3;

	LCD(int rs, int enable, int d4, int d5, int d6, int d7):
		screen(rs, enable, d4, d5, d6, d7), timer(1000 / fps) {}

	LCD(int rs, int rw, int enable, int d4, int d5, int d6, int d7):
		screen(rs, rw, enable, d4, d5, d6, d7), timer(1000 / fps) {}

	LCD(int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7):
		screen(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7), timer(1000 / fps) {}

	LCD(int rs, int rw, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7):
	 	screen(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7), timer(1000 / fps) {}

	void begin(int width) {
			screen.begin(width, 2);
			topWidth = width;
			bottomWidth = width;
	}

	void begin(int width, int topWidth, int bottomWidth) {
			screen.begin(width, 2);
			this->topWidth = topWidth;
			this->bottomWidth = bottomWidth;
	}

	void top(String s) {
		topLine = s;
	}

	void top(int s) { top(String(s)); }

	void bottom(String s) {
		bottomLine = s;
	}

	void bottom(int s) { bottom(String(s)); }

	void scrollTop(int amount = 1) {
		topPosition += amount;
		topPosition %= topWidth + topLine.length() - 8;
	}

	void scrollBottom(int amount = 1) {
		bottomPosition += amount;
		bottomPosition %= bottomWidth + bottomLine.length() - 8;
	}

	void forcePrintTop() {
		String top = topLine;

		if (topLine.length() > topWidth) {
			top = substring(topLine, topPosition, topPosition + topWidth);
		}

		screen.setCursor(0, 0);
		screen.print(top);
	}

	void forcePrintBottom() {
		String bottom = bottomLine;

		if (bottomLine.length() > bottomWidth) {
			bottom = substring(bottomLine, bottomPosition, bottomPosition + bottomWidth);
		}

		screen.setCursor(0, 1);
		screen.print(bottom);
	}

	void print() {
		// Prevention of Overprinting
		if (!timer.ready()) {
			return;
		}

		// Clear screen on "clean" print.
		screen.clear();

		// Check if needs scrolling and if so, do it.
		if (topLine.length() > topWidth)
			scrollTop();

		if (bottomLine.length() > bottomWidth)
			scrollBottom();

		// Actual Printing
		forcePrintTop();
		forcePrintBottom();
	}

private:
	String topLine = "";
	String bottomLine = "";

	unsigned int topWidth = 0;
	unsigned int bottomWidth = 0;

	int topPosition = 0;
	int bottomPosition = 0;

	const String padding = "        ";
	Timer timer;

	String substring(String in, unsigned int start, unsigned int end) {
		unsigned int wantedLength = end - start;
		unsigned int length = in.length();

		String result;

		// We are starting after the end of the string.
		if (start > length) {
			result = padding.substring(start - length);
		} else {
			result = in.substring(start, min(length, end));

			// If we don't have a full length string yet, add some padding.
			if (end > length) {
				result += padding;
			}
		}

		// Still don't have a long enough string.
		if (wantedLength > result.length()) {
			result += in;
		}

		return result.substring(0, wantedLength);
	}
};
