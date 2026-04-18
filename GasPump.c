#include <TM1637Display.h>

// LED Pins
const int ledPins[] = {2, 3, 4};

const int buttonPin = 7;  // Fuel selection button
const int triggerPin = 6; // Pump trigger button 

// TM1637 Displays
TM1637Display displayPrice(8, 9);  // Total price display
TM1637Display displayLitres(12, 13); // Litres pumped display
TM1637Display displayFuelPrice(10, 11); // Current fuel price display

const int prices[] = {653, 597, 721}; // 6.50, 6.00, 7.00

int currentLED = 0;              // Current Fuel Type (0 -> LED 2, 1 -> LED 3, 2 -> LED 4)
bool lastButtonState = HIGH;      // Store last button state
bool buttonPressed = false;       // Track fuel selection button press

float litresPumped = 0.0;
unsigned long lastPumpTime = 0;
const int pumpRate = 100; // Milliseconds per 0.1 litre

void setup() {
    for (int i = 0; i < 3; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    pinMode(buttonPin, INPUT);  // Fuel selection button (External pull-up)
    pinMode(triggerPin, INPUT); // Pump trigger button (External pull-up)

    // Initialize TM1637 Displays
    displayPrice.setBrightness(5);
    displayLitres.setBrightness(5);
    displayFuelPrice.setBrightness(5);

    // Turn on initial LED & Display Price
    digitalWrite(ledPins[currentLED], HIGH);
    updateDisplays();
}

void loop() {
    bool buttonState = digitalRead(buttonPin);
    bool triggerState = digitalRead(triggerPin);

    // Fuel Selection Button Logic
    if (buttonState == LOW && lastButtonState == HIGH) {
        buttonPressed = true;
    }

    if (buttonState == HIGH && buttonPressed) {
        // Change fuel selection
        digitalWrite(ledPins[currentLED], LOW);
        currentLED = (currentLED + 1) % 3;
        digitalWrite(ledPins[currentLED], HIGH);

        // Reset pumped amount when changing fuel
        litresPumped = 0;

        updateDisplays();

        buttonPressed = false;
    }
    lastButtonState = buttonState;

    // Pumping Logic (Gas Pumps when Button is NOT Pressed)
    if (triggerState == HIGH) { // Button NOT pressed -> Pump gas
        if (millis() - lastPumpTime >= pumpRate) {
            litresPumped += 0.1; // Pump 0.1 litre at a time
            lastPumpTime = millis();
            updateDisplays();
        }
    }
}

// Function to update TM1637 Displays with Decimal Point
void updateDisplays() {
    displayFuelPrice.showNumberDecEx(prices[currentLED], 0b00000010, true); 

    int litresDisplay = (int)(litresPumped * 10); 
    displayLitres.showNumberDecEx(litresDisplay, 0b00000010, true);

    int totalPrice = (int)(litresPumped * prices[currentLED]);
    displayPrice.showNumberDecEx(totalPrice, 0b00000010, true);
}