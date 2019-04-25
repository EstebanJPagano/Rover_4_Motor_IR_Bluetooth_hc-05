
/* include library */
#include <IRremote.h>
#include <Servo.h>

// ----------- SERVOS
Servo myservoH;  // create servo object to control a servo Horizontal
Servo myservoV;  // create servo object to control a servo Vertical

int pos = 0;    // variable to store the servo position
int PIN_H = 50;    // pin 2 conectado a señal del servo
int PIN_V = 52;    // pin 2 conectado a señal del servo

int PULSOMIN = 560;    // pulso minimo en microsegundos del servo Horizontal
int PULSOMAX = 2455;    // pulso maximo en microsegundos del servo Horizontal


// ----------- infrarrojo

int IRsensorPin = 11; // pin 11 del sensor infrarrojo
int po = 11; // pin 11 del sensor infrarrojo

IRrecv irrecv(IRsensorPin);
decode_results results;

// ----------- Puenteh

int ENA = 2;      // ENA de L298N a pin digital 5
int ENB = 3;      // ENb de L298N a pin digital 5
//derecho
int IN1 = 4;      // IN1 de L298N a pin digital 2
int IN2 = 5;      // IN2 de L298N a pin digital 3
//izquierdo
int IN3 = 6;      // IN2 de L298N a pin digital 2
int IN4 = 7;      // IN3 de L298N a pin digital 3
int speedCar = 1023;      // variable para almacenar valor de velocidad

int speedCarFast = 1023;      // variable para almacenar valor de velocidad
int speedCarSlow = 680;      // variable para almacenar valor de velocidad
int speedCarSlower = 350;      // variable para almacenar valor de velocidad


int speedOff = 0 ;
// definir led
 
int PinLED = 53;                  
int PinLED1 = 51;                  

int var =0;
void setup(){

  
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida

  
  //led
  pinMode(PinLED, OUTPUT);              
    digitalWrite(PinLED, LOW);   
  pinMode(PinLED1, OUTPUT);              
    digitalWrite(PinLED1, LOW);   
 
  
  myservoH.attach(PIN_H, PULSOMIN, PULSOMAX);  // attaches the servo on pin to the servo object y los pulsos maximo y minimo
  myservoV.attach(PIN_V, PULSOMIN, PULSOMAX);  // attaches the servo on pin to the servo object
  /* start serial communication to see hex codes */
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  
  if (irrecv.decode(&results)){    
    /* print the hex code value on the serial monitor */
    Serial.println(results.value);
    delay(5);
    /* resume function according to hex code */
    irrecv.resume();
  }
  
  /* if the incoming data is "defined hex code" then run the motors functions */
  /* instead of zeros "0000", write the hex codes of your remote control */
  if(results.value == 16718055) { MotorForward();}
  else if(results.value == 16730805) {MotorBackward();}
  else if(results.value == 16734885) {TurnRight();}
  else if(results.value == 16716015) {TurnLeft();}
  else if(results.value == 16724175) {LeftSlow();}  // diagonales boton 1
  else if(results.value == 16743045) {RigthSlow();}    // diagonales boton 3
  else if(results.value == 16728765) {LeftSuperSlow();}    // diagonales boton 7
  else if(results.value == 16732845) {RigthSuperSlow();}    // boton 9
  else if(results.value == 16769055) speedCar = speedCarSlower;   // diagonales tecla -680
  else if(results.value == 16754775) speedCar = speedCarSlow;   // diagonales tecla -
  else if(results.value == 16748655) speedCar = speedCarFast;  // diagonales tecla EQ
  else if(results.value == 16753245) {led_blink();}
  else if(results.value == 16736925) {goBaila();}
  else if(results.value == 16769565) {goLuces();}
  else if(results.value == 16712445  || results.value == 16761405 ) {goLucesOff();}
  else if(results.value == 16726215) {MotorStop(); rotarStop();}

  if(results.value == 16720605) {rotarH();}
  if(results.value == 16761405) {rotarV();}
  if(results.value == 16738455) {rotarStop();}

  
}



// Funciones de motores
/* FORWARD */
void MotorForward(){
    Serial.print(speedCar);

  goLuces();
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1, LOW); // IN1 a cero logico
  digitalWrite(IN2, HIGH);  // IN2 a uno logico

  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
  goLucesOff();
}

/* BACKWARD */
void MotorBackward(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  digitalWrite(IN1, HIGH); // IN1 a cero logico
  digitalWrite(IN2, LOW);  // IN2 a uno logico

  digitalWrite(IN3, HIGH); // IN3 a cero logico
  digitalWrite(IN4, LOW);  // IN4 a uno logicologico
}
/* TURN RIGHT */
void TurnRight(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN2,LOW);
}

/* TURN LEFT */
void TurnLeft(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,HIGH);
}

void MotorStop(){   
  analogWrite(ENA, speedOff);    // deshabilita motor A
  analogWrite(ENB, speedOff);    // deshabilita motor B
}



void RigthSlow(){
  analogWrite(ENA, speedCarSlower);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCarSlower);  // velocidad mediante PWM en ENB
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN2,LOW);
}

/* TURN LEFT */
void LeftSlow(){
  analogWrite(ENA, speedCarSlower);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCarSlower);  // velocidad mediante PWM en ENB
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,HIGH);
}


void LeftSuperSlow(){
      Serial.print("LeftSuperSlow");

  analogWrite(ENA, speedOff);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCarSlower);  // velocidad mediante PWM en ENB
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN2,LOW);
}

/* TURN LEFT */
void RigthSuperSlow(){
        Serial.print("RigthSuperSlow");

  analogWrite(ENA, speedCarSlower);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedOff);  // velocidad mediante PWM en ENB
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,HIGH);
}
// ** Motor End

void led_blink(){
  var = 0;
  while (var < 4) {
    digitalWrite(PinLED, HIGH);
    digitalWrite(PinLED1, LOW);
    delay(90);                       // wait for a second
    
    digitalWrite(PinLED1, HIGH);
    digitalWrite(PinLED, LOW);
    delay(90);                       // wait for half second
    var ++;
  }

}


void goBaila(){
  led_blink();  
  TurnRight();
  delay(500);
  
  led_blink();  
  TurnLeft();
  delay(500);

  MotorStop();
}

void goLuces(){ 
  digitalWrite(PinLED, HIGH);
  digitalWrite(PinLED1, HIGH);
}

void goLucesOff(){ 
  digitalWrite(PinLED, LOW);
  digitalWrite(PinLED1, LOW);
}

void rotarH(){
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoH.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoH.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void rotarV(){

  myservoV.write(0);    // ubica el servo a 0 grados

}

void rotarStop(){
  myservoV.write(90);
  myservoH.write(90);
}
