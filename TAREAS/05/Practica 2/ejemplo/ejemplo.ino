
//Se declaran 3 contastes de tipo byte para asignar a los pines 8, 9, 10 para conectar los leds
const byte ledPin1 = 8;
const byte ledPin2 = 9;
const byte ledPin3 = 10;

//Se declaran 3 constantes de tipo byte para asignar a las interrpciones en los pines 1, 3, 21
const byte interruptPin1 = 2;
const byte interruptPin2 = 3;
const byte interruptPin3 = 21;

//3 variables detipo volatile para los estados de los leds
volatile byte state1 = HIGH;
volatile byte state2 = HIGH;
volatile byte state3 = HIGH;

void setup() {

  //Asignamos los pines como salidas
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  //Le asigamos las 3 insterrupciones para crear un estado de entrada alto y bajo
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);

  //Se asignas los pines para las interrupciones y donde van actuar
  attachInterrupt(digitalPinToInterrupt(interruptPin1), led1ON, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), led2ON, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), led3ON, CHANGE);
}

void loop() {

  //Le asignamos el valor del estado a cada uno de los leds
  digitalWrite(ledPin1, state1);
  digitalWrite(ledPin2, state2);
  digitalWrite(ledPin3, state3);
}

//Interrupcion para el led 1
void led1ON() {
  state1 = !state1;

}

//Interrupcion para el led 2
void led2ON(){
  state2 = !state2;
}

//Interrupcion para el led 3
void led3ON() {
  state3 = !state3;

}
