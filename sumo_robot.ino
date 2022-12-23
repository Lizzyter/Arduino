
// Sensor Ultrasonico
int echo = 10;
int trig = 11;
int duracion, distancia;

// Sensores IR
int sensor1 = A1;
int lectura1 = 0; //"lectura1" y "lectura2" son variables para el monitor serial, no tienes que conectarle nada al arduino

int sensor2 = A2;
int lectura2 = 0;

// Motores
int izqA = 3; //Si tus motores giran al revez solo invierte los cables
int izqB = 5;
int derA = 6;
int derB = 9;

void setup() {
  Serial.begin(9600);
  delay(100);

  //----SENSOR ULTRASONICO----//
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //----MOTORES----//
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

}

void loop() {

  digitalWrite(trig, HIGH); // genera el pulso de trigger por microsegundos
  delay(0.01);
  digitalWrite(trig, LOW); 
  duracion = pulseIn(echo, HIGH); // Lee el tiempo del echo
  distancia = (duracion / 2) /29; // calcula la distancia en centimetros
  Serial.print(distancia);
  Serial.print("cm");
  delay(10);
  
  lectura1 = digitalRead(sensor1);
  lectura2 = digitalRead(sensor2);

  Serial.print("Sensor Trasero: ");
  Serial.print(lectura1);

  Serial.print("  Sensor Delantero: ");
  Serial.println(lectura2);
  delay(10);

  //Atras si detecta una linea negra
  if(lectura1 == 1 || lectura2 == 1)
  {
    analogWrite(derB, 100); //El segundo valor puedo ir desde 0 a 255, es la velocidad de los motores
    analogWrite(izqB, 100);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    delay(500);
  }
  else
  {
    //Ataca el obstaculo mas cercano de 20cm
    if(distancia <= 15)
    {
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, 120); //Este tiene mas velocidad por que mi rueda estaba chueca y le costaba girar xD
      analogWrite(izqA, 100);
      delay(50);
    }
  
    // Busca obstaculo
    if(distancia >= 16)
    {
      analogWrite(derB, 100);
      analogWrite(izqB, 0);
      analogWrite(derA, 0);
      analogWrite(izqA, 100);
      delay(10);
    }
    //Detenido
    //analogWrite(derB, 0);
    //analogWrite(izqB, 0);
    //analogWrite(derA, 0);
    //analogWrite(izqA, 0);
    //delay(10);
  }

}
