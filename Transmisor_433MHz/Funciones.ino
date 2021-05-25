float leerADC(uint8_t pin, float vMax, int offset, bool divisor) {
  int adc = 0;
  int suma = 0;

  for (int i = 0; i < LECTURAS; i++) {
    adc = analogRead(pin) + offset;
    suma += adc;
    delay(5);
  }

  int adcProm = suma / LECTURAS;
  float vAdc = (adc * vMax) / 1024;
  float vBat = vAdc / (R2 / (R1 + R2));

  if (divisor == false) {
    return vAdc;
  }
  else {
    return vBat;
  }
}
//-------------------------------------------------------------

//Para debugging por puerto serie
void tx_debug(char *temp_msg) {
  //output to serial monitor to indicate which button pressed
  Serial.print("Button was pressed, sending msg = ");
  Serial.println(temp_msg);
}
//-------------------------------------------------------------
//----------------------------------------------------------
