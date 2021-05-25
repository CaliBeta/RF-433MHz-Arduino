void salidas(uint8_t pin1, uint8_t pin2) {
  analogWrite(pin1, brillo);

  if (vBat > 0 && vBat < VBAT_MIN) digitalWrite(pin2, HIGH);
}
//-------------------------------------------------------------
