#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int LED = 6;
int LED2 = 7;
int val;
float LDR = A0;
int ilum;

long tiempo2;
int refresh = 1000;

int contador1;
int contador2;
int subcontador1;
int subcontador2;
int subcontador3;
int subcontador4;

long tiempo;
volatile byte state1 = HIGH;

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 20, 4);

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
  pinMode(LED2, OUTPUT);
  lcd.init();
  lcd.backlight();
  menuprincipal();
  dht.begin();
}

void loop()
{
  char Key = customKeypad.getKey();
  if (millis() - tiempo > 7000) ////////////////////////////////////////7
  {
    tiempo = millis();
    lcd.clear();
    menuprincipal();
  }

  if (Key == '5' && contador1 == 0)
  {
    tiempo = millis();
    millis() - tiempo;
    lcd.clear();

    subcontador1++;
    switch (subcontador1)
    {
      case 1:
        menu1();
        break;

      case 2:
        submenu1();
        break;

      case 3:
        submenu1();
        subcontador1 = 1;
        break;
    }
    contador2 = 1;
  }

  if (Key == '5' && contador1 == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    submenu2();
  }

  if (Key == '5' && contador1 == 2)
  {
    tiempo = millis();
    millis() - tiempo;
    submenu3();
  }

  if (Key == '5' && contador1 == 3)
  {
    tiempo = millis();
    millis() - tiempo;
    submenu4();
  }

  if (Key == '5' && contador1 == 4)
  {
    tiempo = millis();
    millis() - tiempo;
    submenu5();
  }

  if (Key == '8' && contador2 == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    FlechaAbajo();
  }

  if (Key == '2' && contador2 == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    FlechaArriba();
  }

  if (Key == '2' && subcontador4 == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    adelantenombre();
  }

  if (Key == '8' && subcontador4 == 1)
  {
    tiempo = millis();
    millis() - tiempo;
    atrasnombre();
  }
}

void menuprincipal()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("*Equipo 2*");
  lcd.setCursor(3, 1);
  lcd.print("Menu Opciones");
  contador1 = 0;
  contador2 = 0;
  subcontador1 = 0;
  subcontador2 = 0;
  subcontador3 = 0;
  subcontador4 = 0;
}

void menu1()
{
  lcd.setCursor(0, 0);
  lcd.print(">LED 1");
  lcd.setCursor(1, 1);
  lcd.print("LED 2");
  lcd.setCursor(1, 2);
  lcd.print("Temperatura");
  lcd.setCursor(5, 3);
  lcd.print("y Humedad");
}

void menu2()
{
  lcd.setCursor(0, 0);
  lcd.print(">Sensor de Luz");
  lcd.setCursor(1, 1);
  lcd.print("Integrantes");
}

void submenu1()
{
  led1ONOFF();                            //Funcion ON-OFF LED's
  digitalWrite(LED, state1);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("LED Rojo");
  lcd.setCursor(6, 1);
  lcd.print("ON-OFF");
}

void submenu2()
{
  contador2 = 0;
  led1ONOFF();                            //Funcion ON-OFF LED's
  digitalWrite(LED2, state1);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("LED Azul");
  lcd.setCursor(6, 1);
  lcd.print("ON-OFF");
}

void submenu3()
{
  contador2 = 0;
  tiempo2 = millis();
  while (millis() < tiempo2 + refresh)
  {
    if (millis() - tiempo > 7000)
    {
      break;
    }
    tiempo2 = millis();
    lcd.clear();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t))                                   //Condición por si el sensor falla
    {
      lcd.clear();
      lcd.println("Fallo en la lectura del sensor DHT!");
      return;
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
    lcd.setCursor(4, 3);
    lcd.print("Sensor DHT11");
  }
}

void submenu4()
{
  contador2 = 0;
  tiempo2 = millis();
  while (millis() < tiempo2 + refresh)
  {
    if (millis() - tiempo > 7000)
    {
      break;
    }
    tiempo2 = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luz");
    val = analogRead(LDR);
    ilum = ((long)val * 1000 * 10) / ((long)15 * 10 * (1024 - val));
    lcd.setCursor(14, 0);
    lcd.print(ilum);
    lcd.setCursor(4, 2);
    lcd.print("Fotoresistor LDR");
  }
}

void submenu5()
{
  contador2 = 0;
  nombre0();
  subcontador3 = 1;
  subcontador4 = 1;
  contador1 = 10;
}

void adelantenombre()
{
  subcontador3++;
  switch (subcontador3)
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
      subcontador3 = 1;
      nombre0();
      break;
  }
}

void atrasnombre()
{
  subcontador3--;
  switch (subcontador3)
  {
    case 0:
      subcontador3 = 3;
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
}

void nombre0()
{
  if (subcontador3 = 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fernandez Salinas");
    lcd.setCursor(0, 1);
    lcd.print("Violeta Margarita");
  }
}

void nombre1()
{
  if (subcontador3 = 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Salazar Aguilar");
    lcd.setCursor(0, 1);
    lcd.print("Luis Gerardo");
  }
}

void nombre2()
{
  if (subcontador3 = 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Velasquez Castaneda");
    lcd.setCursor(0, 1);
    lcd.print("Mauricio");
  }
}

void FlechaAbajo()
{
  contador1++;
  if (contador1 > 4)
  {
    contador1 = 0;
  }
  subcontador2++;
  switch (subcontador2)
  {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(">");
      break;

    case 2:
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(0, 2);
      lcd.print(">");
      break;

    case 3:
      lcd.clear();
      menu2();
      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(">");
      break;

    case 5:
      lcd.clear();
      menu1();
      subcontador2 = 0;
      break;
  }
}

void FlechaArriba()
{
  contador1--;
  if (contador1 < 0)
  {
    contador1 = 4;
  }
  subcontador2--;
  switch (subcontador2)
  {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print(">");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      break;

    case 1:
      lcd.setCursor(0, 1);
      lcd.print(">");
      lcd.setCursor(0, 2);
      lcd.print(" ");
      break;

    case 2:
      lcd.clear();
      menu1();
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 2);
      lcd.print(">");
      break;

    case 3:
      lcd.clear();
      menu2();
      break;

    default:
      lcd.clear();
      menu2();
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(">");
      subcontador2 = 4;
      break;
  }
}

void led1ONOFF()
{
  state1 = !state1;
  return state1;
}
