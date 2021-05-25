// RF LINK RECEIVER CODE
#include <VirtualWire.h>

int brillo = 0;
float vBat = 0.0;

void setup() {
  Serial.begin(115200);	// Debugging only
  Serial.println("Initialize RF Link Rx Code");

  //Initialize the IO and ISR
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	    // Bits per sec
  vw_set_rx_pin(3);         //Pin 3 is connected to "Digital Output" of receiver
  vw_rx_start();           // Start the receiver PLL running

  //Set pins for LED Output
  pinMode(8, OUTPUT);

  //Set pin for LED as status indicator
  pinMode (13, OUTPUT);

}

void loop() {
  //Set buffer array based on max message length
  uint8_t buf[VW_MAX_MESSAGE_LEN];

  //Set variable to indicate buffer length
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //verificamos si hay un dato valido en el RF
  if (vw_get_message(buf, &buflen)) { // Non-blocking
    // Flash status LED to show received data
    digitalWrite(13, true);
    // Message with a good checksum received, dump it.
    Serial.print("Received message: ");
    String data = "";
    uint8_t dato = 0;

    for (int i = 0; i < buflen; i++) {
      // Print message received in buffer through this loop
      Serial.print(buf[i]);
      if (dato == 1) {
        data.concat((char)buf[i]);
      }
      else if (dato == 2) {
        data.concat((char)buf[i]);
      }


      if (buf[i] == 'b') {
        dato = 1;
      }
      else if (buf[i] == 'v') {
        brillo = data.toInt();
        dato = 2;
        data = "";
      }
      else if (buf[i] == '#') {
        vBat = data.toFloat();
      }
    }
    //Print next character on new line
    Serial.println();
    Serial.print("Datos decodificados Brillo:");
    Serial.print(brillo);
    Serial.print(" vBat:");
    Serial.println(vBat);

    //Turn off status LED
    digitalWrite(13, false);
  }
}
