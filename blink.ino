// Define the pins
const int externalLED = 5;  // GPIO 5 (D1 on NodeMCU)
const int buttonResetPin = 4;  // GPIO 4 (D2 on NodeMCU) - Reset button
const int buttonHoldPin = 14;  // GPIO 14 (D5 on NodeMCU) - Hold button to keep LEDs on
bool firstRun = true;  // Flag to check if it's the first run

void setup() {
  // Initialize the LEDs as outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(externalLED, OUTPUT);

  // Initialize the button pins as inputs with internal pull-up resistors
  pinMode(buttonResetPin, INPUT_PULLUP);
  pinMode(buttonHoldPin, INPUT_PULLUP);

  // Initialize the random number generator with a seed
  randomSeed(analogRead(0));  // Using an unconnected analog pin to generate a random seed
}

void loop() {
  // Check if the reset button is pressed to reset the program
  if (digitalRead(buttonResetPin) == LOW) {
    resetProgram();  // Call the reset function
  }

  // Check if the hold button is pressed to keep both LEDs on
  if (digitalRead(buttonHoldPin) == LOW) {
    // Turn both LEDs on
    digitalWrite(LED_BUILTIN, LOW);  // LOW turns the built-in LED on (inverted logic)
    digitalWrite(externalLED, HIGH);  // HIGH turns the external LED on

    // Wait for the button to be released before resetting
    while (digitalRead(buttonHoldPin) == LOW);  // Hold here until the button is released
    resetProgram();  // Reset the program once the button is released
  }

  // First run: Turn the built-in LED on for 5 seconds
  if (firstRun) {
    digitalWrite(LED_BUILTIN, LOW);  // LOW turns the built-in LED on (inverted logic)
    digitalWrite(externalLED, LOW);  // Ensure the external LED is off
    delay(5000);  // Wait for 5 seconds

    firstRun = false;  // Set the flag to false so this block only runs once
  }

  // Generate random delay times between 100 and 1000 milliseconds
  int duration = random(100, 1001);  // Duration for each LED state

  // Turn the built-in LED on and the external LED off
  digitalWrite(LED_BUILTIN, LOW);  // LOW turns the built-in LED on (inverted logic)
  digitalWrite(externalLED, LOW);  // LOW turns the external LED off
  delay(duration);  // Wait for the random duration

  // Turn the built-in LED off and the external LED on
  digitalWrite(LED_BUILTIN, HIGH);  // HIGH turns the built-in LED off
  digitalWrite(externalLED, HIGH);  // HIGH turns the external LED on
  delay(duration);  // Wait for the random duration
}

// Function to reset the program and start again
void resetProgram() {
  // Turn off both LEDs immediately
  digitalWrite(LED_BUILTIN, HIGH);  // HIGH turns the built-in LED off
  digitalWrite(externalLED, LOW);  // LOW turns the external LED off

  firstRun = true;  // Reset the firstRun flag

  delay(100);  // Short delay to debounce the button

  // Wait for the button to be released before continuing
  while (digitalRead(buttonResetPin) == LOW || digitalRead(buttonHoldPin) == LOW);

  // The loop will now restart with the firstRun logic
}
