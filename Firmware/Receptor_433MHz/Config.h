#ifndef __Config_H__
#define __COnfig_H__

//LEDs indicadores
#define LED1          13      //led estado recepcion
#define LED2          12      //led bateria baja
#define LED3          5       //Led control brillo

//Enlace RF 433MHz
#define DATA          3       //pin de datos
#define BAUDRATE      2000    //velocidad de transmision bits/seg, max=4800

//Medidor bateria
#define VBAT_MAX      9.0     //Maximo voltaje bateria Li-Po al 100%
#define VBAT_MIN      6.3     //Minimo voltaje bateria Li-Po al 0%

#endif
