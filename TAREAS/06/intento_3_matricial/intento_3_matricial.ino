/*Los botones que se ocupan para seleccionar son:
   simulacion     Teclado fisico
      7                 1
      8                 2
      9                 3
      4                 4
      5                 5
  Regresar
      ON/C              *
  Iniciar
      /                 A
  Bajar
      X                 B
  Derecha
      2                 8
      3                 9 
*/
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11


int LED = 6;
int LED2 = 7; ////////////////////////////////////////////////////
volatile byte state1 = HIGH; ////////////////////////////////////

float LDR = A0;
int val;
int ilum;
int toque1=0;
int toque2=0;
int toque3=0;
int toque4=0;
int veces;
int decision=0;

DHT dht(DHTPIN, DHTTYPE);

int conta;
long tiempo = 0;

int subconta;
int subconta1;
int subconta2;


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {2, 3, 4, 5};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 20, 4);


//Función menú principal
void menu0()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");////////////////////////////////////////////////7
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");

}

//Funcion submenus
void menu1()
{


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1)LED 1"); ///////////////////////77
  lcd.setCursor(0, 1);
  lcd.print("2)LED 2"); /////////////////////////////////7
  lcd.setCursor(0, 2);
  lcd.print("3)Temperatura");
  lcd.setCursor(2, 3);
  lcd.print("y Humedad");
}

void menu2()
{


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("4)Sensor Luz"); ///////////////////////77
  lcd.setCursor(0, 1);
  lcd.print("5)Integrantes"); /////////////////////////////////7

}

byte grados[8] =
{
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);//////////////////////////////////////
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  conta = 4;
  menu0();
  dht.begin();
}



void loop()
{

  char Key = customKeypad.getKey();
  if (millis() - tiempo > 3000)
  {
    tiempo = millis();
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("*Equipo 2*");////////////////////////////////////////////////7
    lcd.setCursor(3, 1);
    lcd.print("Menu Opciones");
    
    switch(decision){
      
           
        case 1:
        lcd.setCursor(4,3);
  lcd.print("Boton 1: ");
  lcd.setCursor(14,3);
      lcd.print(toque1);
      conta=4;
        break;

        case 2:
        lcd.setCursor(4,3);
  lcd.print("Boton 2: ");
  lcd.setCursor(14,3);
lcd.print(toque2);
conta=4;
        break;

        case 3:
        lcd.setCursor(4,3);
  lcd.print("Boton 3: ");
  lcd.setCursor(14,3);
lcd.print(toque3);
conta=4;
        break;

        case 4:
        lcd.setCursor(4,3);
  lcd.print("Boton 4: ");
  lcd.setCursor(14,3);
lcd.print(toque4);
        conta=4;
        break;

        

  default:
  break;
    }
    conta = 4;
  }

  if (Key == 'A' && conta == 4)
  {
    tiempo = millis();
    millis() - tiempo;
    subconta = 1;
    menu1();
  }

  if (Key == 'B' && conta == 4)
  {
    tiempo = millis();
    millis() - tiempo;
    subconta = 2;
    menu2();
  }

  

  if (Key == '1' && subconta == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    led1ONOFF();
    digitalWrite(LED, state1);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("LED Verde");
    lcd.setCursor(6, 1);
    lcd.print("ON-OFF");
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
    conta = 1;
    if(Key=='1')
    {
      toque1++;
    }
  }


  if (Key == '2' && subconta == 1)
  {
    //----------------------------------//
    tiempo = millis();
    millis() - tiempo;
    led1ONOFF();                        //
    digitalWrite(LED2, state1);         //
    lcd.clear();                        //
    lcd.setCursor(5, 0);                //
    lcd.print("LED Yellow");            //
    lcd.setCursor(6, 1);                //
    lcd.print("ON-OFF");                 //
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
    conta = 1;                           //
    if(Key=='2')
    {
      toque2++;
    }
    //-----------------------------------
  }

  if (Key == '3' && subconta == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    lcd.clear();
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      lcd.clear();
      lcd.println("Fallo en la lectura del sensor DHT!");
      conta=1;
    }
    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.setCursor(13, 1);
    lcd.print(h);
    lcd.setCursor(19, 1);
    lcd.print("%");
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(13, 0);
    lcd.print(t);
    lcd.setCursor(19, 0);
    lcd.print("C");

    conta = 1;
    lcd.setCursor(0, 3);
    lcd.print("* para salir");
    if(Key=='3')
    {
      toque3++;
    }
  }

  if (Key == '4' && subconta == 2)
  {
    tiempo = millis();
    millis() - tiempo;
    conta = 2;
  }
  if (conta == 2)
  {
    lcd.clear();
    val = analogRead(LDR);
    ilum = ((long)val * 1000 * 10) / ((long)15 * 10 * (1024 - val));
    lcd.setCursor(0, 0);
    lcd.print("Luz");
    lcd.setCursor(14, 1);
    lcd.print(ilum);
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
    delay(100);
    conta = 5;
    if(Key=='4')
    {
      toque4++;
    }
  }

  if (Key == '5' && subconta == 2)
  {

    tiempo = millis();
    millis() - tiempo;
    nombre0();
    subconta1 = 1;
    subconta = 3;
    conta = 5;
  }

if(Key=='7' && conta==4)
{
  decision=9;
  menu0();
}

  if (Key == '6' && conta == 4)
  {
    boton1();
    subconta2=1;
    decision=1;
    veces=1;
  }

if ((Key == '#') && (subconta2 == 1))
  {
    tiempo = millis();
    millis() - tiempo;
    veces++;
    decision++;
    if(decision>4)
    {
      decision=1;
    }
    
    switch (veces)
    {
      case 1:
        boton1();
        break;

      case 2:
        boton2();
        break;

      case 3:
        boton3();
        break;

      case 4:
        boton4();
        break;

        case 5:
        veces=1;
        boton1();
        break;
    }
    conta=4;    
  }

  if ((Key == '0') && (subconta2 == 1))
  {
    tiempo = millis();
    millis() - tiempo;
    veces--;
    decision--;
    if(decision<1)
    {
      decision=4;
    }
    switch (veces)
    {
      case 0:
        veces = 4;
        boton4();
        break;

      case 1:
        boton1();
        break;

      case 2:
        boton2();
        break;

      case 3:
        boton3();
        break;

        case 4:
        boton4();
        break;
    }
    conta=4;
  }

  if ((Key == '9') && (subconta == 3))
  {
    subconta1++;
    tiempo = millis();
    millis() - tiempo;
    switch (subconta1)
    {
      case 1:
        nombre0();
        break;

      case 2:
        nombre1();
        break;

      case 3:
        nombre2();
        break;

      case 4:
        subconta1 = 1;
        nombre0();
        break;
    }
    conta = 5;
  }

  if (Key == '8' && subconta == 3)
  {
    subconta1--;
    tiempo = millis();
    millis() - tiempo;
    switch (subconta1)
    {
      case 0:
        subconta1 = 3;
        nombre2();
        break;

      case 1:
        nombre0();
        break;

      case 2:
        nombre1();
        break;

      case 3:
        nombre2();
        break;
    }
    conta = 5;
  }

  if ((Key == '*') && (conta == 0 || conta == 1 || conta == 2))
  {
    menu1();
    conta = 4;

  }

  if ((Key == '*') && (conta == 5))
  {
    menu2();
    conta = 4;
    subconta = 2;
  }
}

void nombre0()
{
  if (subconta1 = 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fernandez Salinas");
    lcd.setCursor(0, 1);
    lcd.print("Violeta Margarita");
    lcd.setCursor(0, 2);
    lcd.print("<---8");
    lcd.setCursor(16, 2);
    lcd.print("9-->");
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
  }
}

void nombre1()
{
  if (subconta1 = 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Salazar Aguilar");
    lcd.setCursor(0, 1);
    lcd.print("Luis Gerardo");
    lcd.setCursor(0, 2);
    lcd.print("<---8");
    lcd.setCursor(16, 2);
    lcd.print("9-->");
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
  }
}

void nombre2()
{
  if (subconta1 = 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Velasquez Castaneda");
    lcd.setCursor(0, 1);
    lcd.print("Mauricio");
    lcd.setCursor(0, 2);
    lcd.print("<---8");
    lcd.setCursor(16, 2);
    lcd.print("9-->");
    lcd.setCursor(8, 3);
    lcd.print("* para salir");
  }
}

void boton1()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");////////////////////////////////////////////////7
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");
  lcd.setCursor(4,3);
  lcd.print("Boton 1: ");
  lcd.setCursor(14,3);
  lcd.print(toque1);
}

void boton2()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");////////////////////////////////////////////////7
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");
  lcd.setCursor(4,3);
  lcd.print("Boton 2: ");
  lcd.setCursor(14,3);
  lcd.print(toque2);
}

void boton3()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");////////////////////////////////////////////////7
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");
  lcd.setCursor(4,3);
  lcd.print("Boton 3: ");
  lcd.setCursor(14,3);
  lcd.print(toque3);
}

void boton4()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");////////////////////////////////////////////////7
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");
  lcd.setCursor(4,3);
  lcd.print("Boton 4: ");
  lcd.setCursor(14,3);
  lcd.print(toque4);
}

//Función LED
//--------------------//
void led1ONOFF() {    //
  state1 = !state1;   //
  return state1;      //
}                   //
//-------------------//
