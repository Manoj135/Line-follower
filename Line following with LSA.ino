int mleft=8 ,mright=9 ,mleft1=12 ,mleft2=13 ,mright1=10 ,mright2=11 ;
int leftPWM, rightPWM, lspeed=130, rspeed=130;
int error=0, derror=0, pError=0, correction=0,kp=15,kd=9 ;
int spin[8],weight[8];
int wsum=0, select=0;
 
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
analogWrite(mright,140);
analogWrite(mleft,140);
}
 
void moveleft(){
  digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,HIGH);
digitalWrite(mright2,LOW);
}
 
void moveright(){
  digitalWrite(mleft1,HIGH);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,HIGH);
}
 
void Stop(){
  digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,LOW);
digitalWrite(mright,LOW);
digitalWrite(mleft,LOW);
}
 
 
void setup() {
digitalWrite(mleft1,LOW);
digitalWrite(mleft2,LOW);
digitalWrite(mright1,LOW);
digitalWrite(mright2,LOW);
 
spin[0]=22;
spin[1]=23;
spin[2]=24;
spin[3]=25;
spin[4]=26;
spin[5]=27;
spin[6]=28;
spin[7]=29;
 
    for(byte i=0; i<8; i++){
      pinMode(spin[i],INPUT);
    }
pinMode(mleft,OUTPUT);
pinMode(mleft1,OUTPUT);
pinMode(mleft2,OUTPUT);
pinMode(mright,OUTPUT);
pinMode(mright1,OUTPUT);
pinMode(mright2,OUTPUT);
 
 
 
 weight[0]=-8;
  weight[1]=-6;
   weight[2]=-4;
    weight[3]=-2;
     weight[4]=2;
      weight[5]=4;
       weight[6]=6;
        weight[7]=8;
 
}
 
void loop() {
  select=0;
  wsum=0;
  for(int i=1; i<8;i++){
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
    analogWrite(mleft,200);
    analogWrite(mright,0);
 
  }
 
  if(wsum<=-6){
    moveleft();
    analogWrite(mleft,0);
    analogWrite(mright,255);
 
  }
 if(select==0){
  backward();
  delay(250);
 }
  //if(select==8||select==0 )forward();
 
 if(select == 7){
  Stop();
 }
 
delay(100);
 
 
}
