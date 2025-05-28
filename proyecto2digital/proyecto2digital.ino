#include <Servo.h>

// Objetos servo
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;


unsigned long lastPrintTime = 0;
const unsigned long printInterval = 500;  // Intervalo de 500 ms

// Pines
#define smodos 11
#define bmas 2
#define bmenos 4

#define ledmod1 8
#define ledmod2 7

#define Poten1 A1
#define Poten2 A2
#define Poten3 A3
#define Poten4 A4

// Variables de lectura y señal para servos
int Potr1 = 0, Potr2 = 0, Potr3 = 0, Potr4 = 0;
int Servow1, Servow2, Servow3, Servow4;

// Contador de modos
int sumas = 0;

// Variables para antirebote con millis
unsigned long lastDebounceTimeMas = 0;
unsigned long lastDebounceTimeMenos = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(9600);

  pinMode(smodos, INPUT_PULLUP);
  pinMode(bmas, INPUT_PULLUP);
  pinMode(bmenos, INPUT_PULLUP);

  myservo1.attach(9);
  myservo2.attach(6);
  myservo3.attach(5);
  myservo4.attach(3);
}

void loop() {
  bool smod = digitalRead(smodos); // LOW = modo manual

  pinMode(ledmod1, OUTPUT);
  pinMode(ledmod2, OUTPUT);

  if (smod == LOW) {
    // Modo manual
    Potr1 = analogRead(Poten1);
    Potr2 = analogRead(Poten2);
    Potr3 = analogRead(Poten3);
    Potr4 = analogRead(Poten4);

    Servow1 = map(Potr1, 0, 1023, 0, 180);
    Servow2 = map(Potr2, 0, 1023, 0, 180);
    Servow3 = map(Potr3, 0, 1023, 45, 90);
    Servow4 = map(Potr4, 0, 1023, 90, 180);

    myservo1.write(Servow1);
    myservo2.write(Servow2);
    myservo3.write(Servow3);
    myservo4.write(Servow4);

    digitalWrite(ledmod1, HIGH);
    digitalWrite(ledmod2, LOW);

      unsigned long currentMillis = millis();
      if (currentMillis - lastPrintTime >= printInterval) {
        lastPrintTime = currentMillis;

        Serial.println("Modo Manual:");
        Serial.print("S1: ");
        Serial.println(Servow1);
        Serial.print("S2: ");
        Serial.println(Servow2);
        Serial.print("S3: ");
        Serial.println(Servow3);
        Serial.print("S4: ");
        Serial.println(Servow4);
      }

  } else {
    // Modo automático
    unsigned long currentMillis = millis();

    bool mas = digitalRead(bmas) == LOW;
    bool menos = digitalRead(bmenos) == LOW;

    // Botón MAS
    if (mas && (currentMillis - lastDebounceTimeMas > debounceDelay)) {
      if (sumas < 5) {
        sumas++;
        Serial.println("++");
      }
      lastDebounceTimeMas = currentMillis;
    }

    // Botón MENOS
    if (menos && (currentMillis - lastDebounceTimeMenos > debounceDelay)) {
      if (sumas > 0) {
        sumas--;
        Serial.println("--");
      }
      lastDebounceTimeMenos = currentMillis;
    }

    if (currentMillis - lastPrintTime >= printInterval) {
      lastPrintTime = currentMillis;

      digitalWrite(ledmod2, HIGH);
      digitalWrite(ledmod1, LOW);

      Serial.print("Set: ");
      Serial.println(sumas);
    }

    switch (sumas) {
      case 0:
        myservo1.write(90);
        myservo2.write(90);
        myservo3.write(45);
        myservo4.write(90);
        break;
      case 1:
        myservo1.write(180);
        myservo2.write(30);
        myservo3.write(88);
        myservo4.write(145);
        break;
      case 2:
        myservo1.write(50);
        myservo2.write(30);
        myservo3.write(45);
        myservo4.write(92);
        break;
      case 3:
        myservo1.write(180);
        myservo2.write(90);
        myservo3.write(88);
        myservo4.write(90);
        break;
      case 4:
        myservo1.write(10);
        myservo2.write(180);
        myservo3.write(45);
        myservo4.write(180);
        break;
      case 5:
        myservo1.write(180);
        myservo2.write(90);
        myservo3.write(88);
        myservo4.write(90);
        break;
      default:
        // statements
        break;
    }

  }


}