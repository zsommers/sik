const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int SENSOR_PIN = 0;

int DISPLAY_TIME = 100;  // In milliseconds

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(RED_PIN, HIGH);
//  digitalWrite(GREEN_PIN, HIGH);
//  digitalWrite(BLUE_PIN, HIGH);
//  delay(4294967295);
  int analogInput, colorValue;

  analogInput = analogRead(SENSOR_PIN);
  colorValue = getColorValue(analogInput);
  Serial.print("Analog Value: ");
  Serial.print(analogInput);
  Serial.print(" - Color Value: ");
  Serial.println(colorValue);
  showRGB(colorValue);
}

int getColorValue(int analogInput) {
  return (int)((float)analogInput / 1023.0 * 767.0);
}

void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  // Here we'll use an "if / else" statement to determine which
  // of the three (R,G,B) zones x falls into. Each of these zones
  // spans 255 because analogWrite() wants a number from 0 to 255.

  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
}


