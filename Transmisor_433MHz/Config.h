#ifndef __Config_H__
#define __COnfig_H__

//Pulsador
#define PUSH      3

//Sensor de temperatura DS18B20
#define SENSOR    10

//Pines analogos
#define VBAT      A3  //Medidor voltaje bateria
#define BRILLO    A0  //Brillo del led a controlar

//LED indicador
#define LED       13

//Enlace RF 433MHz
#define DATA      4
#define BAUDRATE  2000

//Medidor bateria
#define LECTURAS      10      //Numero de lecturas para el promedio
#define VBAT_MAX      9.0     //Maximo voltaje bateria Li-Po al 100%
#define VBAT_MIN      6.3     //Minimo voltaje bateria Li-Po al 0%
#define OFFSET        -1      //Nivel de offset para calibar el ADC
#define VCC           4.99    //Voltaje de alimentacion del MCU
#define R1            2500.0  //Resistencia serie a Vin
#define R2            2500.0  //Resistencia serie a GND

#endif
