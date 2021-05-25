/*
  Project :Receptor_433MHz con Arduino
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
#include <VirtualWire.h>
#include "Config.h"
//----------------------------------------------------------

//Declaramos las variables globales
int brillo = 0;
float vBat = 0.0;

void setup() {
  Serial.begin(115200);	// Debugging only
  Serial.println("Inicializado Receptor RF");

  //Configuramos los parametros del modulo RF
  vw_setup(BAUDRATE);	    //tasa de bits por segundo
  vw_set_rx_pin(DATA);    //Pin de datos del modulo receptor
  vw_rx_start();          //Inicio el receptor activando el PLL

  //Set pin for LED as status indicator
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);

  //Estado inicial de los pines de salida
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}
//----------------------------------------------------------

void loop() {
  //Set buffer array based on max message length
  uint8_t buf[VW_MAX_MESSAGE_LEN];

  //Set variable to indicate buffer length
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //verificamos si hay un dato valido en el RF
  if (vw_get_message(buf, &buflen)) { // Non-blocking
    // Flash status LED to show received data
    digitalWrite(LED1, HIGH);
    // Message with a good checksum received, dump it.
    Serial.print("Mensaje recibido: ");
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

    //Imprimimos los datos decodificados en una nueva linea
    Serial.println();
    Serial.print("Datos decodificados Brillo:");
    Serial.print(brillo);
    Serial.print(" vBat:");
    Serial.println(vBat);

    //Apagamos el led de estatus
    digitalWrite(LED1, LOW);
  }
  //Cambiamos el estado de los leds acorde a los datos recibidos
  salidas(LED3, LED2);
}
//----------------------------------------------------------
