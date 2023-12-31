#define DIGIT_1_COLUMN 0  // first digit on clock starts in column 0
#define DIGIT_2_COLUMN 4  // second digit on clock starts in column 4
#define DIGIT_3_COLUMN 9  // third digit on clock starts in column 9
#define DIGIT_4_COLUMN 13 // last digit on clock starts in column 13
#define COLON_COLUMN 8    // which column to show the colon in, either 7 or 8

void showClockLEDs() {
  // Set the LEDs for each individual digit, if it's not hidden (ie. if it's
  // not currently flashing in edit mode)
  if (c.isHourDigit1Visible()) {
    showDigitLEDs(c.getHourDigit1(), DIGIT_1_COLUMN);
  }
  if (c.isHourDigit2Visible()) {
    showDigitLEDs(c.getHourDigit2(), DIGIT_2_COLUMN);
  }
  if (c.isMinuteDigit1Visible()) {
    showDigitLEDs(c.getMinuteDigit1(), DIGIT_3_COLUMN);
  }
  if (c.isMinuteDigit2Visible()) {
    showDigitLEDs(c.getMinuteDigit2(), DIGIT_4_COLUMN);
  }
}

void showDigitLEDs(int digit, int startColumn) {
  // Get a 3x5 mapping of which pixels to display for this digit
  Digit d = digits[digit];

  // Loop through this 3x5 array pixels and set the LEDs
  for (int x = 0; x < DIGIT_WIDTH; x++) {
    for (int y = 0; y < DIGIT_HEIGHT; y++) {
      // The pixels array tells us to show this LED or set it to Black
      if (d.showPixel(x, y)) {
        leds(startColumn + x, y) = getColor(startColumn + x);
      } else {
        leds(startColumn + x, y) = CRGB::Black;
      }
    }
  }
}

CHSV getColor(int column) {
  // Get a color of the rainbow according to which column we're on
  // Map the current column 0 -> 16 to a hue 0 -> 255
  int hue = map(column, 0, WIDTH, 255, 0);
  return CHSV(hue, 255, BRIGHTNESS);
}

void showColonLEDs() {
  // If the colon is flashed on, set the 2 LEDs to white in the middle column,
  // rows 1 and 3
  if (c.isColonVisible()) {
    CHSV white = CHSV(0, 0, BRIGHTNESS);
    leds(COLON_COLUMN, 1) = white;
    leds(COLON_COLUMN, 3) = white;
  }
}
