// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;


//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

byte leds[8]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};

void setup() {
  // Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

	// Setup Serial Monitor
	Serial.begin(9600);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);


//set pins to output so you can control the shift register
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
}
void loop() {




currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
		}
counter %= 8;
		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
    digitalWrite(latchPin, LOW);
// shift out the bits:
shiftOut(dataPin, clockPin, MSBFIRST, leds[counter]);
//take the latch pin high so the LEDs will light up:
digitalWrite(latchPin, HIGH);


	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);




// // count from 0 to 255 and display the number
// // on the LEDs
// for (int i = 0; i < 8; i++) {
// // take the latchPin low so
// // the LEDs don't change while you're sending in bits:
// digitalWrite(latchPin, LOW);
// // shift out the bits:
// shiftOut(dataPin, clockPin, MSBFIRST, leds[i]);
// //take the latch pin high so the LEDs will light up:
// digitalWrite(latchPin, HIGH);
// // pause before next value:
// delay(500);
// }
}