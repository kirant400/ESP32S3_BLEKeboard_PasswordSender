/**
 * This turns the ESP32S3 mini into a Bluetooth LE keyboard that writes passwords
 * Author : KTB
 * Version: V1.0
 * Date   : 2025/09/06
 */
#include <Adafruit_NeoPixel.h>
#include <BleKeyboard.h>
// #define touch_pin_numer T0
#define password "XXXXXXXXX"
#define RGB_PIN 21 // Onboard RGB LED pin
#define NUM_PIXELS 1 // Only one LED
const int buttonPin = 4;  // the number of the pushbutton pin
BleKeyboard bleKeyboard("Kiran");
const int VALUE_THRESHOLD = 70;
int TOUCH_SENSOR_VALUE;
// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  pixel.begin();
  pixel.setBrightness(100); // Adjust brightness (0-255)
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    static uint16_t hue = 0; // Hue goes from 0 to 65535 for full cycle

    // Convert HSV to RGB and set LED color
    uint32_t color = pixel.gamma32(pixel.ColorHSV(hue));
    pixel.setPixelColor(0, color);
    pixel.show();

    hue += 256; // Smooth step (smaller = slower transition)
    delay(20); // Adjust speed of transition

#ifdef touch_pin_numer
  TOUCH_SENSOR_VALUE = touchRead(touch_pin_numer);
  Serial.print(TOUCH_SENSOR_VALUE);
  if(TOUCH_SENSOR_VALUE < VALUE_THRESHOLD) {
    ///digitalWrite(LED_PIN_NUMBER, HIGH);
    bleKeyboard.print(password);
    delay(1000);

    //Serial.println("Sending Enter key...");
    bleKeyboard.write(KEY_RETURN);

    delay(500);
    Serial.println("On");
  }
#else
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  if (buttonState == LOW) {
    bleKeyboard.print(password);
    delay(1000);
    bleKeyboard.write(KEY_RETURN);

    delay(500);
    Serial.println("On");

  }
#endif  
 
  }else{
    Serial.println("Waiting ...");
    pixel.setPixelColor(0, 0);
    pixel.show();
  }

  delay(250);
}
