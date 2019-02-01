#include <Servo.h>// libreria para los servo motores 

// 180 horizontal MAXIMO
Servo horizontal; // declaramos el valor para el servo horizontal
int ServoH = 180;        

int ServoHLimSup = 180; //limite en posicion superior
int ServoHLimInf = 65; //limite para posicion inferior


Servo vertical;   // vertical servo 
int ServoV = 45;    
int ServoVLimSup = 80;
int ServoVLimInf = 15;



int ldrIS = 0; // conexion a las resistencias LDR
int ldrDS = 1; 
int ldrII = 2; 
int ldrDI = 3; 

void setup() 
{
  Serial.begin(9600);
  horizontal.attach(9); //servo horizontal pin digital 9 
  vertical.attach(10); // servo vertical pin digital 10 
  horizontal.write(180);
  vertical.write(90);
  delay(3000);
}

void loop() 
{
  int IS = analogRead(ldrIS); // (superior izquierdo)
  int DS = analogRead(ldrDS); // (superior derecho)
  int II = analogRead(ldrII); // (inferior izquierdo)
  int DI = analogRead(ldrDI); // (inferior derecho)
  
  // int dtime = analogRead(4)/20; // Opcional si utilizamos potenciometros para la velocidad 
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  
  int VSUPM = (IS + DS) / 2; // valor superior maximo
  int VINFM = (II + DI) / 2; // valor inferior maximo
  int VIM = (IS + II) / 2; // valor izquierdo maximo
  int VDM = (DS + DI) / 2; // valor derecho maximo

  int DifVert = VSUPM - VINFM; // diferencia entre superior e inferior
  int DifHoriz = VIM - VDM;// diferencia entre izquierdo y derecho
  
  
  Serial.print(VSUPM);   // Imnprimir valores  de posicion en monitor serial
  Serial.print(" ");
  Serial.print(VINFM);   
  Serial.print(" ");
  Serial.print(VIM);
  Serial.print(" ");
  Serial.print(VDM);
  Serial.print("   "); 
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" "); 
  
    
  if (-1*tol > DifVert || DifVert > tol) // revisar la diferencia para cambiar al angulo vertical
  {
  if (VSUPM > VINFM)
  {
    ServoV = ++ServoV;
     if (ServoV > ServoVLimSup) 
     { 
      ServoV = ServoVLimSup;
     }
  }
  else if (VSUPM < VINFM)
  {
    ServoV= --ServoV;
    if (ServoV < ServoVLimInf)
  {
    ServoV = ServoVLimInf;
  }
  }
  vertical.write(ServoV);
  }
  
  if (-1*tol > DifHoriz || DifHoriz > tol) // revisar la diferencia para cambiar al angulo horizontal 
  {
  if (VIM > VDM)
  {
    ServoH = --ServoH;
    if (ServoH < ServoHLimInf)
    {
    ServoH = ServoHLimInf;
    }
  }
  else if (VIM < VDM)
  {
    ServoH = ++ServoH;
     if (ServoH > ServoHLimSup)
     {
     ServoH = ServoHLimSup;
     }
  }
  else if (VIM = VDM)
  {
    
  }
  horizontal.write(ServoH);
  }
   delay(dtime);
   }
