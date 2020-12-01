//******************************************************************************
// Temporizador Digital. Usa 4 dígitos de Siete Segmentos de cátodo común
// Tiene controles para Minutos y Segundos
//==============================================================================
#include <TimerOne.h>

const int Data = 7;   	// Conexiones entre el CI 74HC595 y la placa Arduino
const int Clock = 8;  	//
const int Latch = 6;  	//

const int SEG0 = 5;   	// Conexiones para manejar los cátodos
const int SEG1 = 4;   	//
const int SEG2 = 3;   	//
const int SEG3 = 2;   	//

const int LED = 13; 	// LED

const int Min_key = 10; // Teclas
const int Sec_key = 9;	//
//const int Inic_key = 11;
//------------------------------------------------------------------------------
//-----[ VARIABLES ]-----
//------------------------------------------------------------------------------
int cc = 0;
char Value[4];
// Patrones para desplegar los dígitos (verificarlos):
const char SegData[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int MIN = 0, SEC = 0, count = 10;	// Variables y valores iniciales
//==============================================================================
//-----[ AJUSTES GENERALES ]-----
//==============================================================================
void setup() {
  Serial.begin(9600);           // Comunicación serial
  pinMode(Data, OUTPUT);        // Terminales para manejar arreglo 7 segmentos
  pinMode(Clock, OUTPUT);		    //
  pinMode(Latch, OUTPUT);		    //
  pinMode(SEG0, OUTPUT);		    //
  pinMode(SEG1, OUTPUT);		    //
  pinMode(SEG2, OUTPUT);		    //
  pinMode(SEG3, OUTPUT);		    //
  pinMode(LED, OUTPUT);		  //
  digitalWrite(LED, LOW);    // LED

  pinMode(Min_key, INPUT);      // Tecla de Minutos
  pinMode(Sec_key, INPUT);      // Tecla de Segundos
  //pinMode(Inic_key, INPUT);     //Tecla de Inicio

  digitalWrite(Min_key, HIGH);  // Ajuste de "Pull-Ups" para las entradas
  digitalWrite(Sec_key, HIGH);  //
  //digitalWrite(Inic_key, HIGH); //

  cc = 0;
  // Lo siguiente es un recurso proporcionado por una biblioteca: TimerOne
  // Ajuste de un temporizador de 100,000 microsegundos (o de 0.1 segundo,
  // o de 10 Hertz) => Un LED parpadearía 5 veces por segundo
  Timer1.initialize(1000);
  Timer1.attachInterrupt( timerIsr ); // Subrutina que atiende la Interrupción
}
//==============================================================================
//-----[ LAZO PRINCIPAL ]-----
//==============================================================================
void loop() {
  char cMIN[4], cSEC[4];

  if (count == 0) {
    count = 2.5;        
      delay(10);
    if (MIN > 0) {			// Si minutos son mayores a cero...
      if (SEC == 0) {		// Si se llegó al segundo "00"
        MIN--;
        SEC = 60;
    }
    }
    SEC--;					    // Decremento de Segundos
    
   
    // Revisar que el Temporizador está en cero
    if (MIN == 0 && SEC == 0) {		// Segundos mantenidos para evitar sonido
      digitalWrite(LED, HIGH);	// Encendido del led
    }     
  }

  //----------------------------------------
  if (MIN > 0 || SEC > 0) {	// Si los Minutos y Segundos son mayores a "0"
   count--;				//
  }
  //----------------------------------------
  if (digitalRead(Min_key) == LOW) {  // ¿Se oprimió la tecla "Minutos"?
    delay(10);                        // Para evitar "rebotes"
    MIN++;                            // Incrementa minutos
    digitalWrite(LED, LOW);        // Apagar LED
  }
  //----------------------------------------
  if (digitalRead(Sec_key) == LOW) {  // ¿Se oprimió la tecla de "Segundos"?
    delay(10);                        // Para evitar "rebotes"
    SEC++;                            // Incrementar segundos
    if (SEC > 59) {                   // 60 segundos - 1 minuto
      MIN++;                          // Ajuste...
      SEC = 0;                        // ...para reciclar
    }
    digitalWrite(LED, LOW);        // Apagar LED
  }
  //----------------------------------------
  // Si se oprimieran simultáneamente ambas teclas, se Limpia el Timer
  if (digitalRead(Sec_key) == LOW && digitalRead(Min_key) == LOW)  {
    MIN = 0;
    SEC = 0;
    digitalWrite(LED, HIGH);   // Prender led
    delay(500);
    digitalWrite(LED, LOW);
  }
  //----------------------------------------
  // Muestra de conteo en el desplegador de 7 segmentos
  sprintf(cMIN, "%02d", MIN);     // Arreglo en ASCII
  sprintf(cSEC, "%02d", SEC);     // Arreglo en ASCII
  Serial.println(cMIN);           // Imprimir el conteo en terminal serial
  // (depuración)

  Value[0] = cMIN[0] & 0x0F;      // Remover el "nibble" superior (AND con 0x0F)
  Value[1] = cMIN[1] & 0x0F;      // Por ejemplo, de 0x32 (ASCII)...
  Value[2] = cSEC[0] & 0x0F;      // ...sólo necesitamos el "2"
  Value[3] = cSEC[1] & 0x0F;
  delay(100);
}
//==============================================================================
//-----[ SUBRUTINAS ]-----
//==============================================================================
// INTERRUPCIÓN CAUSADA POR EL DESBORDAMIENTO DE TIMER 1
// (Para el desplegador de 7 segmentos)
//==============================================================================
void timerIsr() {
  cc++;             // Incremento del contador de "cátodos", asignados a dígitos
  if (cc == 5) {    // De momento sólo se tienen 4 dígitos
    cc = 1;
  }
  Scanner();        // Realiza el rastreo
  TCNT0 = 0xCC;     // Reinicia "Timer 1" para ocurrencia próxima Interrupción
}
//==============================================================================
// GENERACIÓN DE LOS DÍGITOS
//==============================================================================
void DisplayDigit(char d) {
  int i;

  for (i = 0; i < 8; i++) {   // Corrimiento, bit a bit, en...
    if ((d & 0x80) == 0x80) {  // ... registro de corrimiento
      digitalWrite(Data, HIGH);
    }
    else {
      digitalWrite(Data, LOW);
    }
    d = d << 1;               // Corrimiento...
    // Pulsos de Reloj
    digitalWrite(Clock, LOW);
    digitalWrite(Clock, HIGH);
  }
  // Captura del dato
  digitalWrite(Latch, LOW);
  digitalWrite(Latch, HIGH);
}
//==============================================================================
// FUNCIÓN DE RASTREO DEL DESPLEGADOR 
//==============================================================================
void Scanner() {
  switch (cc)           // Selección del dígito que se actualiza 
  {
    case 1:
      digitalWrite(SEG3, HIGH);
      DisplayDigit(SegData[Value[0]]);
      digitalWrite(SEG0, LOW);
      break;
    case 2:
      digitalWrite(SEG0, HIGH);
      DisplayDigit(SegData[Value[1]] | 0x80);   // Punto Decimal
      digitalWrite(SEG1, LOW);
      break;
    case 3:
      digitalWrite(SEG1, HIGH);
      DisplayDigit(SegData[Value[2]]);
      digitalWrite(SEG2, LOW);
      break;
    case 4:
      digitalWrite(SEG2, HIGH);
      DisplayDigit(SegData[Value[3]]);
      digitalWrite(SEG3, LOW);
      break;
  }
}
//******************************************************************************
