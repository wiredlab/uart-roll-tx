/*
 * UART transmitter
 *
 * Used for ECE 341 ultrasonic receiver project as the transmitter side.
 * txA pin keys a MOPA (master oscillator power amplifier) that drives an
 * ultrasonic transducer.  The project is to build a receiver for the
 * ultrasound that can decode from at least N meters away.
 */


// allows us to send/receive UART via software from (almost) any pin
#include <SoftwareSerial.h>


/*
 * Configuration
 */
// too fast of a baud rate yields a signal with bandwidth larger
// than the transmitter can handle
const int baudRate = 150;

// pin definitions
const byte rxAll = 6;
const byte txA = 2;
const byte txB = 3;
const byte txC = 4;


// NOTE: this text is stored in RAM, a limited resource
// TODO: put this string in PROGMEM
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
char text[] = {
  "\r\n\r\n\r\n\r\n"
  "We're no strangers to love\r\n"
  "You know the rules and so do I\r\n"
  "A full commitment's what I'm thinking of\r\n"
  "You wouldn't get this from any other guy\r\n"
  "\r\n"
  "I just wanna tell you how I'm feeling\r\n"
  "Gotta make you understand\r\n"
  "\r\n"
  "Never gonna give you up\r\n"
  "Never gonna let you down\r\n"
  "Never gonna run around and desert you\r\n"
  "Never gonna make you cry\r\n"
  "Never gonna say goodbye\r\n"
  "Never gonna tell a lie and hurt you\r\n"
  "\r\n"
  "We've known each other for so long\r\n"
  "Your heart's been aching, but\r\n"
  "You're too shy to say it\r\n"
  "Inside, we both know what's been going on\r\n"
  "We know the game and we're gonna play it\r\n"
  "\r\n"
  "And if you ask me how I'm feeling\r\n"
  "Don't tell me you're too blind to see\r\n"
  "\r\n"
  "Never gonna give you up\r\n"
  "Never gonna let you down\r\n"
  "Never gonna run around and desert you\r\n"
  "Never gonna make you cry\r\n"
  "Never gonna say goodbye\r\n"
  "Never gonna tell a lie and hurt you\r\n"
  "\r\n"
  "Never gonna give you up\r\n"
  "Never gonna let you down\r\n"
  "Never gonna run around and desert you\r\n"
  "Never gonna make you cry\r\n"
  "Never gonna say goodbye\r\n"
  "Never gonna tell a lie and hurt you\r\n"
};




SoftwareSerial serialA(rxAll, txA);




void setup() {
  pinMode(rxAll, INPUT);
  pinMode(txA, OUTPUT);
  //pinMode(txB, OUTPUT);
  //pinMode(txC, OUTPUT);

  serialA.begin(baudRate);
  //serialB.begin(baudRate);
  //serialC.begin(baudRate);
}




void loop() {
  unsigned int i = 0;
  
  for (i = 0; i < sizeof(text); i++) {
    Serial.print(text[i]);
    serialA.print(text[i]);

    // pause for 1 character time in ms (8 + start + stop bit)
    // not needed, but it makes it easier to visually identify
    // start and end of each transmission
    delay(floor(10 * 1000.0 / baudRate));
  }
  delay(1000);
  Serial.println("*** Repeating ***");
}
