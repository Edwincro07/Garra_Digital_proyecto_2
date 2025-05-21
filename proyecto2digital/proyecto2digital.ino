//#include <LiquidCrystal.h>

// Incluir la libreria de servo
#include <Servo.h>
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

// Objeto liquid crystal
//LiquidCrystal_I2C lcd(0x3F, 16, 2); 

//Crear objeto con nombre que se le asignara al servo
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

//Pin de switch de modos

#define smodos 11

//Pines para aumentar modos

#define mas 2
#define menos 4

int sumas;

// Definir el pin del potenciometro
#define Poten1 A1
#define Poten2 A2
#define Poten3 A3
#define Poten4 A4

// Crear una variable para el potenciometro que inicie la lectura en 0
int Potr1 = 0;
int Potr2 = 0;
int Potr3 = 0;
int Potr4 = 0;

// Crear una variable para el valor de señal que se le dara al servo
int Servow1;
int Servow2;
int Servow3;
int Servow4;

void setup() {

  sumas = 0;

  //Configurar la velocidad de comunicación entre el arduino y la pc
  Serial.begin(9600);


  //Configurar el pin del switch de modos
  pinMode(smodos, INPUT_PULLUP);


  //Configurar los pines de los switches de set de movimientos
  pinMode(mas, INPUT_PULLUP);
  pinMode(menos, INPUT_PULLUP);

  // Asignación del pin del servo
  myservo1.attach(9);
  myservo2.attach(6);
  myservo3.attach(5);
  myservo4.attach(3);

}

//Variable para switch case de movimientos

void loop() {

//Leer switch de modos
  bool smod = digitalRead(smodos);

// Estructura de botones para cambio de modo

    if (smod == LOW) {
      //Toda la progra de modo manual

      // Leer analogicamente el valor del potenciometro
      Potr1 = analogRead(Poten1);
      Potr2 = analogRead(Poten2);
      Potr3 = analogRead(Poten3);
      Potr4 = analogRead(Poten4);

      // Mapear la lectura del potenciometro a el valor de los grados del servo
      Servow1 = map(Potr1, 0, 1023, 0, 180);
      Servow2 = map(Potr2, 0, 1023, 0, 180);
      Servow3 = map(Potr3, 0, 1023, 0, 180);
      Servow4 = map(Potr4, 0, 1023, 90, 180);

      // Imprimir el valor del potenciometro en el monitor cereal
      //Serial.println(Servow1);
      //Serial.println(Servow2);
      //Serial.println(Servow3);
      //Serial.println(Servow4);
      
      // Enviar los valores de la seal de la salida al servo.
      myservo1.write(Servow1);
      myservo2.write(Servow2);
      myservo3.write(Servow3);
      myservo4.write(Servow4);

      Serial.println (1);

    }

    else if (smod == HIGH) {
      //Toda la progra del modo automatico
      int estado = 0;

      //Esatructura para leer botones de mas y menos
      if (mas == HIGH && menos == LOW) {
        if (sumas > 4) {
          sumas = 5;
        }

        else if (sumas < 6) {
          sumas += 1;
          while (digitalRead(mas) == HIGH);
        } 
      }

      else if (menos == HIGH && mas == LOW) {
        if (sumas < 0) {
          sumas = 0;
        }
      
        else if (sumas > 0) {
          sumas -= 1;  
          while (digitalRead(menos) == HIGH);
        }
      }

      Serial.println(sumas, DEC);
      //Serial.println (2);
    }


}