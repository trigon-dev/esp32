#include <Adafruit_TinyUSB.h>

// TinyUSB HID + CDC composite:
Adafruit_USBD_HID usb_hid;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000);

  TinyUSBDevice.begin();
  usb_hid.begin();
}

void loop() {
  // Replace this with your real input source (buttons, sensors, etc.)
  // For demo, we read from Serial (if you echo to it manually).
  if (!Serial.available()) return;

  char c = Serial.read();
  if (c < 32 || c > 126) return;  // skip non-printable

  // 1) Send as USB-HID keystroke:
  usb_hid.keyboardReport(
    HID_KEYBOARD_MODIFIER_NONE,
    keycodeFromASCII(c),
    0,0,0,0,0,0
  );
  delay(5);  // ensure host registers key

  // 2) Echo it back over USB-Serial for the PC helper to read:
  Serial.write(c);
}
