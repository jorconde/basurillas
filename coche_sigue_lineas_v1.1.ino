/*
 * esta version funcionan los dos motores e los sensores pero va demasiado rapido version cambiada para probar
 * funciona 
 * despacio
 */
const int sensorPinEsq = 0;                        // Establece el pin A10 como entrada analogica para el sensor Izquierda
const int sensorPinDel = 1;                        // Establece el pin A10 como entrada analogica para el sensor delante
const int sensorPinDir = 2;                        // Establece el pin A10 como entrada analogica para el sensor Derecha
int CNY_Val1, CNY_Val2, CNY_Val3;             // Variables de almacenamiento de los Sensores CNY 70 -Sigue Lineas
String estadoSensores,posicionSensorDerecha,posicionSensorIzquierda,posicionSensorDelante,estadoSensoresAntes;
const int blanco = 600;                                   // Establece el umbral máximo de blanco
const int negro = 700;                                    // Establece el umbral mímino de negro
const int correcionMotorEsquerdo =90;
const int speedPinEsq = 3;
const int motor1APinEsq = 6;
const int motor2APinEsq = 7;
int velocidad_motor1Esq; // value for motor speed
const int ledPin = 13;
const int speedPinDir = 2;
const int motor1APinDir = 4;
const int motor2APinDir = 5;
int velocidad_motor1Dir; // value for motor speed
bool pararTodo;


// H-bridge enable pin for speed control // H-bridge leg 1
// H-bridge leg 2
// status LED
void setup() 
{
  //Serial.begin(9600);  // Inicializa la comunicacion serie a 9600 baudios
  // set digital i/o pins as outputs:
  pinMode(speedPinEsq, OUTPUT);
  pinMode(motor1APinEsq, OUTPUT);
  pinMode(motor2APinEsq, OUTPUT);
  pinMode(ledPin, OUTPUT);
  // set digital i/o pins as outputs:
  pinMode(speedPinDir, OUTPUT);
  pinMode(motor1APinDir, OUTPUT);
  pinMode(motor2APinDir, OUTPUT);
  pararTodo = false;
 
  //delay(1000);
//admite valores de 0 a 255
//control the speed 110- 255 para andar
 velocidad_motor1Esq = 254;// + correcionMotorEsquerdo; // half speed
 velocidad_motor1Dir = 254-correcionMotorEsquerdo; // half speed
  avanza();
 
}
void loop() 
{
  programaSigueLineas();  
}

void parado()
{
  pararTodo = true;
  digitalWrite(ledPin, LOW); // status LED is always off
  digitalWrite(motor1APinEsq, LOW);
  digitalWrite(motor2APinEsq, LOW); 
  digitalWrite(motor1APinDir, LOW);
  digitalWrite(motor2APinDir, LOW);
  Serial.println("STOP");     
}

void avanza()
{
  //Serial.println("AVANZA"); 
  analogWrite(speedPinEsq, velocidad_motor1Esq); 
  analogWrite(speedPinDir, velocidad_motor1Dir); 
  digitalWrite(motor1APinEsq, HIGH); 
  digitalWrite(motor2APinEsq, LOW); 
  digitalWrite(motor1APinDir, LOW);  
  digitalWrite(motor2APinDir, HIGH);
}

void giroDerecha()
{
  //Serial.println("giroDerecha"); 
  analogWrite(speedPinEsq, velocidad_motor1Esq); 
  analogWrite(speedPinDir, velocidad_motor1Dir);
  digitalWrite(motor1APinEsq,HIGH);
  digitalWrite(motor2APinDir,LOW);
  digitalWrite(motor2APinEsq,LOW);
  digitalWrite(motor1APinDir,LOW);
}

void giroIzquierda()
{
  //Serial.println("giroIzquierda"); 
  analogWrite(speedPinEsq, velocidad_motor1Esq); 
  analogWrite(speedPinDir, velocidad_motor1Dir); 
  digitalWrite(motor2APinEsq,LOW);
  digitalWrite(motor1APinDir,LOW);
  digitalWrite(motor1APinEsq,LOW);
  digitalWrite(motor2APinDir,HIGH);   
}

void programaSigueLineas()
{
  CNY_Val1= analogRead(sensorPinDel);            // Leemos la entrada analogica (CNY delante)
  CNY_Val2= analogRead(sensorPinDir);            // Leemos la entrada analogica (CNY Dcha)
  CNY_Val3= analogRead(sensorPinEsq);            // Leemos la entrada analogica (CNY Izda)
  
  estadoSensoresAntes=estadoSensores;
  estadoSensores="";                               
 
  // Identifica posición del sensor Delante
  if (CNY_Val1> negro)               
  {               
    posicionSensorDelante="1";
  }
  else if (CNY_Val1< blanco)
  {         
    posicionSensorDelante="0";
  }
  posicionSensorDelante="1";//forzamos a 1
  // Identifica posición del sensor Derecho
  if (CNY_Val2> negro)               
  {               
    posicionSensorDerecha="1";
  }
  else if (CNY_Val2< blanco)
  {         
    posicionSensorDerecha="0";
  }
  // Identifica posición del sensor Izquierdo
  if (CNY_Val3> negro)               
  {                  
    posicionSensorIzquierda="1";
  }
  else if (CNY_Val3< blanco)
  { 
    posicionSensorIzquierda="0";    
  }
  
  // Concatena las variables parciales en la variable posicion
  estadoSensores.concat(posicionSensorIzquierda);
  estadoSensores.concat(posicionSensorDelante);
  estadoSensores.concat(posicionSensorDerecha);
 
  //Serial.println("estado sensores: " + estadoSensores); 
  // Dependiendo del valor de la variable posicion, realiza una acción
  //Si los dos laterales estan en la banda negra seguimos haciendo lo que estabamos haciendo
  if (estadoSensores=="111"){
    estadoSensores=estadoSensoresAntes;
    }
  
  if (estadoSensores=="010"){avanza();}
  if (estadoSensores=="111"){avanza();}
  if (estadoSensores=="110"){giroDerecha();}
  if (estadoSensores=="100"){giroDerecha();}
  if (estadoSensores=="011"){giroIzquierda();}
  if (estadoSensores=="001"){giroIzquierda();}
  if (estadoSensores=="000"){parado();}
  
  delay(40);
  parado();
  
}



