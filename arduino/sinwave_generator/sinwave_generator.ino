const int pwmPin = 9;  // Choose a suitable PWM pin
const int pwmFrequency = 1000;  // PWM frequency in Hz (adjust as needed)
const int resolution = 256;  // Resolution of the sine wave (e.g., 8-bit)

#define TWO_PI 6.283185307179586476925286766559

// Precomputed sine wave values for one full cycle (0-255) at 8-bit resolution
uint8_t sineWave[resolution];

void calculateSineWave() {
  for (int i = 0; i < resolution; i++) {
    float radian = map(i, 0, resolution - 1, 0, TWO_PI);
    sineWave[i] = 128 + 127 * sin(radian);  // Calculate and store sine values
  }
}

void setup() {
  pinMode(pwmPin, OUTPUT);
  analogWriteFrequency(pwmPin, pwmFrequency);  // Set PWM frequency
  calculateSineWave();  // Calculate and store sine values in the array
}

void loop() {
  for (int i = 0; i < resolution; i++) {
    int dutyCycle = sineWave[i];  // Retrieve precomputed sine value
    analogWrite(pwmPin, dutyCycle);
    // No need for additional delay here, as the PWM frequency controls the output frequency
  }
}
