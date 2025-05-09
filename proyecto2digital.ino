// Incluir la libreria de servo
#include <Servo.h>

//Crear objeto con nombre que se le asignara al servo
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// Definir el pin del potenciometro
#define Poten1 A3
#define Poten2 A4
#define Poten3 A5
#define Poten4 A2

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

  //Configurar la velocidad de comunicación entre el arduino y la pc
  Serial.begin(9600);

  // Asignación del pin del servo
  myservo1.attach(9);
  myservo2.attach(6);
  myservo3.attach(5);
  myservo4.attach(3);

}

void loop() {

  // Leer analogicamente el valor del potenciometro
  Potr1 = analogRead(Poten1);
  Potr2 = analogRead(Poten2);
  Potr3 = analogRead(Poten3);
  Potr4 = analogRead(Poten4);

  // Mapear la lectura del potenciometro a el valor de los grados del servo
  Servow1 = map(Potr1, 0, 1023, 0, 180);
  Servow2 = map(Potr2, 0, 1023, 0, 180);
  Servow3 = map(Potr3, 0, 1023, 0, 180);
  Servow4 = map(Potr4, 0, 1023, 0, 180);

  // Imprimir el valor del potenciometro en el monitor cereal
  Serial.println(Servow1);
  Serial.println(Servow2);
  Serial.println(Servow3);
  Serial.println(Servow4);
  
  // Enviar los valores de la seal de la salida al servo.
  myservo1.write(Servow1);
  myservo2.write(Servow2);
  myservo3.write(Servow3);
  myservo4.write(Servow4);

  // Pequeño delay para una buena lectura
  delay(10);

}