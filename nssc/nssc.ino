int mleft=7 ,mright=2 ,mleft1=6 ,mleft2=5 ,mright1=4 ,mright2=3;
int leftPWM=0, rightPWM=0, lspeed=130, rspeed=130;
int error=0, derror=0, pError=0, correction=0,kp=15,kd=9 ;
int S0=45, S1=43, S2=39 ,S3=41, sensorOut=37, VCC=35;
int red=0, blue=0, green=0;
int spin[8],weight[8];
int wsum=0, select=0;

void color(){
  digitalWrite(VCC,HIGH);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, HIGH);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print("  ");
  //delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, HIGH);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print("  ");
  //delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, HIGH);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}

void forward(){
  digitalWrite(mleft1,HIGH);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,HIGH);
digitalWrite(mright2,LOW);
}

void backward(){
  digitalWrite(mleft1,LOW);
digitalWrite(mleft2,HIGH);
digitalWrite(mright1,LOW);
digitalWrite(mright2,HIGH);
digitalWrite(mright,HIGH);
digitalWrite(mleft,HIGH);
}

void moveleft(){
  digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,HIGH);
digitalWrite(mright2,LOW);
analogWrite(mright,180);
}

void moveright(){
  digitalWrite(mleft1,HIGH);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,LOW);
analogWrite(mleft,180);
}

void Stop(){
  digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,LOW);
}


void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(VCC,LOW);
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

spin[0]=28;
spin[1]=29;
spin[2]=26;
spin[3]=27;
spin[4]=24;
spin[5]=25;
spin[6]=22;
spin[7]=23;

    for(byte i=0; i<8; i++){
      pinMode(spin[i],INPUT);
    }
    
pinMode(mleft,OUTPUT);
pinMode(mleft1,OUTPUT);
pinMode(mleft2,OUTPUT);
pinMode(mright,OUTPUT);
pinMode(mright1,OUTPUT);
pinMode(mright2,OUTPUT);

digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,LOW);

weight[0]=-8;
weight[1]=-6;
weight[2]=-4;
weight[3]=-2;
weight[4]=2;
weight[5]=4;
weight[6]=6;
weight[7]=8;

 Serial.begin(9600);
}

void loop() {
  select=0;
  wsum=0;
  for(int i=0; i<8;i++){
          if(digitalRead(spin[i])){
            wsum+=weight[i];
            select++;
          }
  }
  error= wsum/select;
  derror=error-pError;
  pError=error;
  correction= kp*error +kd*derror;
  leftPWM= lspeed + correction;
  rightPWM= rspeed - correction;

  forward();
  analogWrite(mleft,leftPWM);
  analogWrite(mright,rightPWM);
  
  if(wsum>=6){
    moveright();
    analogWrite(mleft,180);
    analogWrite(mright,0);
  
  }
  
  if(wsum<=-6){
    moveleft();
    analogWrite(mleft,0);
    analogWrite(mright,180);
  
  }
    if(select==0){
      Stop();
      delay(100);
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
      color();
      delay(200);
      digitalWrite(VCC,LOW);
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
    
      if(red<130 && green>130 && blue>130){
        moveleft();
      }  
    
    else {
        moveright();
    }
    delay(100);
  }
}
