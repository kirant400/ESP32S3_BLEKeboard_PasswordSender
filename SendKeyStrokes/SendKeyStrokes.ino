/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <Adafruit_NeoPixel.h>
#include <BleKeyboard.h>
// #define touch_pin_numer T0

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

#ifdef touch_pin_numer
    TOUCH_SENSOR_VALUE = touchRead(touch_pin_numer);
    Serial.print(TOUCH_SENSOR_VALUE);
    if(TOUCH_SENSOR_VALUE < VALUE_THRESHOLD)
    {
    ///digitalWrite(LED_PIN_NUMBER, HIGH);
    bleKeyboard.print("AmmuParu40025.");
    delay(1000);

    //Serial.println("Sending Enter key...");
    bleKeyboard.write(KEY_RETURN);

    delay(500);
    Serial.print("On");
    }
    else{
    //digitalWrite(LED_PIN_NUMBER, LOW);
    Serial.print("Off");
    }
#else
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
        ///digitalWrite(LED_PIN_NUMBER, HIGH);
    bleKeyboard.print("AmmuParu40025.");
    delay(1000);

    //Serial.println("Sending Enter key...");
    bleKeyboard.write(KEY_RETURN);

    delay(500);
    Serial.println("On");
  }
#endif  
   // Serial.println("Sending 'Hello world'...");
   // bleKeyboard.print("Hello world");

   // delay(1000);

    //Serial.println("Sending Enter key...");
   // bleKeyboard.write(KEY_RETURN);

   // delay(1000);

   // Serial.println("Sending Play/Pause media key...");
   // bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

    //delay(1000);

   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    /*
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
  }else{
    Serial.println("Waiting ...");
    static uint16_t hue = 0; // Hue goes from 0 to 65535 for full cycle

    // Convert HSV to RGB and set LED color
    uint32_t color = pixel.gamma32(pixel.ColorHSV(hue));
    pixel.setPixelColor(0, color);
    pixel.show();

    hue += 256; // Smooth step (smaller = slower transition)
      delay(20); // Adjust speed of transition
  }

  delay(250);
}
