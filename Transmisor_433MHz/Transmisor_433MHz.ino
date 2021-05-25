/*
  Project :Transmisor_433MHz con Arduino
  Version : 1.0
  Date    : 24/05/2021 - 25/05/2021
  Author  : CARLOS ANDRES BETANCOURT PEREZ
  Company : CaliBeta
  Comments:
  Chip type               : ATmega328P-AU
  Program type            : Application
  AVR Core Clock frequency: 16.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  ------------------------------------------------------------
  Conexiones electricas
  Revisar los diagramas de Fritzing
  //----------------------------------------------------------*/

//Incluimos las librerias necesarias
#include <VirtualWire.h>    //Libreria modulos RF 433MHz
#include "Config.h"         //Cabecera de configuracion
//----------------------------------------------------------

//Configuracion
void setup() {
  Serial.begin(115200);	  //Para debugging
  Serial.println("Initialize RF Link Tx Code");

  //Configuramos los parametros del modulo RF
  vw_setup(BAUDRATE);	   //tasa de bits por segundo
  vw_set_tx_pin(DATA);   //Pin de datos del modulo transmisor

  //Set pins as input for buttons
  pinMode(PUSH, INPUT_PULLUP);
  pinMode (LED, OUTPUT);

  //Estado inicial de los pines
  digitalWrite(LED, LOW);
}
//----------------------------------------------------------

//Funcion principal
void loop() {
  if (digitalRead(PUSH) == LOW) {
    digitalWrite(13, true);  //Flash status LED to show transmitting

    int brillo = analogRead(BRILLO);
    brillo = map(brillo, 0, 1023, 0, 255);

    char *msg = "*51,2,20,6,3#"; //message to send
    tx_debug(msg); //output message to serial monitor for debugging.
    vw_send((uint8_t *)msg, strlen(msg));//send message
    vw_wait_tx(); // Wait until the whole message is gone

    digitalWrite(13, false); //Turn off status LED
  }
}

void tx_debug(char *temp_msg) {
  //output to serial monitor to indicate which button pressed
  Serial.print("Button was pressed, sending msg = ");
  Serial.println(temp_msg);
}
//----------------------------------------------------------
