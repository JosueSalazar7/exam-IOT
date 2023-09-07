#define BLYNK_TEMPLATE_ID "TMPL25nTTw4bg"
#define BLYNK_TEMPLATE_NAME "PROYECTO2"
#define BLYNK_AUTH_TOKEN "1Z0BrTiNhGuEo8BOZstDT7jF7ma2a6qT"

/* Comenta esto para desactivar las impresiones y ahorrar espacio */
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Tus credenciales WiFi.
// Deja el campo de contraseña en blanco ("") si es una red abierta.
char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "Josue";
//char pass[] = "josue1234";
char ssid[] = "Wilson";
char pass[] = "Wilo08JA";
// O bien, utiliza Software Serial en Arduino Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);  // RX, TX

// Velocidad de comunicación con el módulo ESP8266:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

// Define los pines para el sensor de distancia ultrasónico
const int Trigger = 8;   //Pin digital 2 para el Trigger del sensor
const int Echo = 9;   //Pin digital 3 para el Echo del sensor

void setup() {

   
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0


  // Consola de depuración
  Serial.begin(115200);

  // Establece la velocidad de comunicación del módulo ESP8266
  EspSerial.begin(ESP8266_BAUD);
  delay(10);


 

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
}

void loop() {
  Blynk.run();

    long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);


  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);          //Hacemos una pausa de 100ms

  Blynk.virtualWrite(V5, d);
  Serial.print(d);

  delay(100);
}