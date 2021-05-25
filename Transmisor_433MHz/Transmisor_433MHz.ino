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
    digitalWrite(LED, HIGH);  //ENcendemos el led mientras se envian datos

    int brillo = analogRead(BRILLO);
    brillo = map(brillo, 0, 1023, 0, 255);
    float vbat = leerADC(VBAT, VCC, OFFSET, true);

    char buf[VW_MAX_MESSAGE_LEN]; // Cadena para enviar
    String str = "";

    //convertimos el int a String y agregamos un inicio de trama
    str = "b" + String(brillo);
    //Convertimos el float a String y agregamos un fin de trama
    str += "v" + String(vbat) + "#";
    str.toCharArray(buf, sizeof(buf)); //convertimos el String en un array
    tx_debug(buf); //Mensaje de salida al monitor serial para debugging
    vw_send((uint8_t *)buf, strlen(buf));//Enviamos los datos
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

    digitalWrite(LED, LOW); //Apagamos el LED de estatus
  }
}
//----------------------------------------------------------
