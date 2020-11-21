//Libreria de LCD
#include <LiquidCrystal.h>

//Datos
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Timbre porton
const int pinBuzzer = 10; // speaker

int boton = 8;  //pulsador para activación del sistema
int boton2 = 9; //pulsador para speaker

//Potenciometro
float Potenciometro = 0;
float Velocidad = 0;

///BOTON  ALMACENAMIENTO DEL ESTADO DE LOS BOTONES
int buttonState = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;

//BOTON 2  ALMACENAMIENTO DEL ESTADO
int buttonState2 = 0;
int lastButton = 0;
int buttonPushCounter2 = 0;

// SE CREA LA CADENA PARA PODER DESPLAZAR LA PALABRA
String texto_fila = "Abriendo Porton";
String texto_fila1 = "Cerrando Porton";
//Sensor PIR
int PIR = 13;
int valorPIR;
void setup() {
  pinMode(boton, INPUT);    //declaramos tipo entrada
  pinMode(boton2, INPUT);   //declaramos tipo entrada
  Serial.begin(9600);       // Activamos el puerto serial
 
  pinMode(PIR, INPUT);  //Entrada de Sensor PIR
  pinMode(1,OUTPUT);     //Salida para Integrado L293D
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
//IMPRIMIR
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("INICIANDO");
  lcd.setCursor(6,1);
  lcd.print("Sistema");
  delay(800);
  lcd.clear();
  
//IMPRIMIR
  lcd.setCursor(4,0);
  lcd.print("Porton");
  lcd.setCursor(2,1);
  lcd.print("Automatico");
}

// ciclo
void loop() 
{
  Potenciometro = analogRead(A1); //Leemos el potenciometro
  Velocidad = map(Potenciometro,0,1023,0,255); //Mapeo de potenciometer
  delay(100);// breve demora segundo
  ////_______CONTROL DEL PORTON__________ ////
  
  // Lectura de la entrada del boton
  buttonState = digitalRead(boton);
  Serial.println(buttonState);
    // Si el estado del boton ha cambiado
  if (buttonState ==0 && lastButton == 0){
    lastButton = 1;        
    //// IMPRIMIMOS EL TEXTO DESPLAZADO "ABRIENDO PORTON ////
    // Obtenemos el tamaño del texto
    int tam_texto=texto_fila.length();
    // Mostramos entrada texto por la izquierda
    for(int i=tam_texto; i>0 ; i--){
      String texto = texto_fila.substring(i-1);
      // Limpiamos pantalla
      lcd.clear();
      //Situamos el cursor
      lcd.setCursor(0, 0);
      // Escribimos el texto
      lcd.print(texto);
      // Esperamos
      delay(100);
    }    
    //Encendemos el motor para abrir el porton
    analogWrite(1, Velocidad);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    delay(1000);
    lcd.clear();
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    //Mensaje para que entre persona
    for(int i=10; i>=0; --i){
      lcd.clear(); 
      lcd.print("Porton Abierto"); // mensaje en terminal. Pase por favor
      lcd.setCursor(0,1);
      lcd.print(i);
      delay(1000);
    }
    //// DESPLAZAMIENTO DE PALABRA "CERRANDO PORTON" ////    
    int tam_texto1=texto_fila1.length();
    // Mostramos entrada texto por la izquierda
    for(int i=tam_texto1; i>0 ; i--){
      String texto_1 = texto_fila1.substring(i-1);
      // Limpiamos pantalla
      lcd.clear();
      //Situamos el cursor
      lcd.setCursor(0, 0);
      // Escribimos el texto
      lcd.print(texto_1);
      // Esperamos
      delay(100);
    }
    //Encendemos el motor para cerrar el porton
    analogWrite(1, Velocidad);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    }
    
  //Programacion de sonido atraves de PIR, para detectar personas
  valorPIR = digitalRead(PIR);
  if (valorPIR == HIGH){
    tone(pinBuzzer,600);
    delay(4);
    noTone(pinBuzzer);
    delay(5);
  }
  //Boton de porton
  // Lectura de la entrada del boton
  buttonState2 = digitalRead(boton2);
  if (buttonState2 == 0){
    tone(pinBuzzer,150, 200);
    delay(4);
    noTone(pinBuzzer);
    delay(5);
  }
}
