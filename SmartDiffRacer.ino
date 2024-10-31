#include <Encoder.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PID_v1.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Encoder and control variables
Encoder steeringEncoder(2, 3);
volatile long steeringAnglePosition = 0;

// PID Variables
double setPoint; // Desired speed
double inputL, inputR; // Current speed for left and right motors
double outputL, outputR; // PID output for left and right motors

// PID setup
PID pidLeft(&inputL, &outputL, &setPoint, 2.0, 5.0, 1.0, DIRECT);
PID pidRight(&inputR, &outputR, &setPoint, 2.0, 5.0, 1.0, DIRECT);

const int menuButtonPin = 6; // Button pin for menu encoder
volatile bool menuButtonPressed = false;
unsigned long lastButtonPress = 0; // For debouncing

// Motor Pins
const int AnalogOut1 = 9; // Front wheel motor
const int AnalogOut2 = 10; // Left rear motor
const int AnalogOut3 = 11; // Right rear motor

void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }
    display.clearDisplay();
    display.display();
}

// ISR for menu button press
void IRAM_ATTR handleMenuButton() {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPress > 200) {  // Debounce 200ms
        menuButtonPressed = true;
        lastButtonPress = currentTime;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(menuButtonPin, INPUT_PULLUP);

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(menuButtonPin), handleMenuButton, FALLING);
    
    // Initialize PID
    pidLeft.SetMode(AUTOMATIC);
    pidRight.SetMode(AUTOMATIC);

    initDisplay();
}

void loop() {
    // Read steering angle
    long steeringAngle = steeringEncoder.read();
    float steeringAngleRad = map(steeringAngle, -500, 500, -M_PI, M_PI); // Convert to radians

    // Read throttle input from analog pin
    int analogSpeed = analogRead(A0);
    setPoint = map(analogSpeed, 179, 780, 0, 100); // Scale to percentage

    // Calculate rear wheel speeds using e-diff logic
    float trackWidth = 0.5; // Distance between rear wheels in meters
    float r = 1.0 / tan(steeringAngleRad); // Calculate turn radius
    float halfTrack = trackWidth / 2;

    // Calculate speeds for left and right rear wheels
    double vRight = ((r + halfTrack) / r) * setPoint;
    double vLeft = ((r - halfTrack) / r) * setPoint;

    // Constrain speeds
    vRight = constrain(vRight, 0, 100);
    vLeft = constrain(vLeft, 0, 100);

    // Update PID input for both motors
    inputL = analogRead(AnalogOut2); // Read current speed for left wheel
    inputR = analogRead(AnalogOut3); // Read current speed for right wheel

    // Compute PID outputs
    pidLeft.Compute();
    pidRight.Compute();

    // Write outputs to motors
    analogWrite(AnalogOut2, map(outputL, 0, 100, 0, 255)); // Left rear motor
    analogWrite(AnalogOut3, map(outputR, 0, 100, 0, 255)); // Right rear motor

    // Front motor speed control
    analogWrite(AnalogOut1, map(setPoint, 0, 100, 0, 255)); // Front wheel motor

    // Display current status
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Steering Angle: ");
    display.println(steeringAngleRad);
    display.print("Set Speed: ");
    display.println(setPoint);
    display.print("Left Speed: ");
    display.println(outputL);
    display.print("Right Speed: ");
    display.println(outputR);
    display.display();

    // Delay for stability
    delay(100);
}
