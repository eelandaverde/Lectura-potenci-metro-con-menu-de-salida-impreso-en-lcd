#include <LiquidCrystal.h>
int rs = 8, en = 9, d4= 4, d5=5, d6=6, d7=7;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

int proceso = 0;
int contador = 0;

// creamos nuestro caracter
byte signoInterrogacion[] = {
  B00100,
  B00000,
  B00100,
  B00100,
  B01000,
  B10000,
  B10000,
  B01100
};


// C++ code
//
void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  
  
  lcd.begin(16,2);
  Serial.begin(9600);
  //lcd.begin(20,4); si tuvieramos una de 20x4
  lcd.print("Bienvenidos/as a");
  lcd.setCursor(0,1);
  lcd.print("  controlErick");
  delay(2000);
  
}
  
void loop()
{
  int lectura = digitalRead(2);
  int lecturaDos = digitalRead(12);
  int lecturaTres = digitalRead(3);
  
  if (lectura == 0)
  {
  	contador = 0;
    proceso = 1;
    delay(250);
  }
  
  if (lecturaDos == 0)
  {
    contador ++;
    if (contador == 2)
    {
    	proceso = 1;
      	contador = 0;
    }
    else
    {
    	proceso = 2;
    }
    
   delay(250);
  }
  
  if (lecturaTres == 0 && contador > 0)
  {
  	proceso = 3;
    delay(250);
  }
  
  
  switch(proceso)
  {
  	default:
    	cargarVoltaje();
    break;
    
    case 1:
    	mostrarVoltaje();
    break;
    case 2:
    	mostrarMenu();
    break;
    case 3:
    	Agradecimiento();
    break;
  }
}

void cargarVoltaje()
{
  lcd.clear();
  lcd.home();
  lcd.print("El voltaje es: ");
  lcd.blink();
  delay(200); //cargando
}

void  mostrarVoltaje() 
{
  lcd.clear();
  lcd.home();
  lcd.print("El voltaje es: ");
  
  int signal = analogRead(A0);
  int voltaje = (signal*5.0)/1023;
  lcd.setCursor(15,0);
  lcd.noBlink();
  lcd.setCursor(3,1);
  lcd.print(String(voltaje) + " Volts");
  delay(100);
}

void mostrarMenu()
{
	lcd.clear();
    lcd.setCursor(15,0);
    lcd.noBlink();
  	lcd.createChar(0, signoInterrogacion );
  	lcd.setCursor(0,0);
  	lcd.write(byte(0));
  	lcd.setCursor(1,0);
 	lcd.print("Desea salir?");
 	lcd.setCursor(3,1);
  	lcd.print("Si");
  	lcd.setCursor(12,1);
  	lcd.print("No");
  	delay(100);
}

void Agradecimiento()
{
	lcd.clear();
  	lcd.setCursor(15,0);
    lcd.noBlink();
  	for(int i=0; i < 16; i++)
    {
      	lcd.setCursor(0,0);
      	lcd.scrollDisplayLeft();
      	lcd.print("  Gracias por preferirnos");
      	delay(500);
    }
    
  
}
  
  
  


  
