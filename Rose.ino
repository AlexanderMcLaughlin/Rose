int wLight1 = 3;
int wLight2 = 5;
int wLight3 = 6;
int MSensor = 7;
int fLight = 9;

int flag=0;

int motionDetected = LOW;

int globalCount=0;
int localRegCount=0;
int localSpcCount=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(wLight1, OUTPUT);
  pinMode(wLight2, OUTPUT);
  pinMode(wLight3, OUTPUT);
  pinMode(fLight, OUTPUT);
  pinMode(MSensor, INPUT);
}


void loop() {

  globalCount++;
  
  motionDetected = digitalRead(MSensor);
  if(motionDetected == HIGH && globalCount>2900)
  {
    globalCount=0;
    localRegCount=0;
    localSpcCount=0;
    specialSequence();
  }
  else
  {
    regularSequence();
  }
  
}

void regularSequence(){
  //Create the pulse sequence
  analogWrite(fLight, 215);

  if(localRegCount>=180)
    flag=1;
  else if(localRegCount<=4)
    flag=0;

  if(flag==0)
    localRegCount++;
  else
    localRegCount--;

  pulse(wLight1);
  pulse(wLight2);
  pulse(wLight3);
  
  delay(10);
}

void pulse(int light){
  analogWrite(light, localRegCount);
}

void specialSequence(){
  //Create the special sequence
  int currentLight=0;

  analogWrite(wLight1, 0);
  analogWrite(wLight2, 0);
  analogWrite(wLight3, 0);
  analogWrite(fLight, 0);

  delay(3500);
  
  analogWrite(fLight, 215);
  
  for(int i=0; i<100; i++)
  {
    if(i%3==0)
      currentLight=wLight1;
    else if(i%3==1)
      currentLight=wLight2;
    else
      currentLight=wLight3;

    analogWrite(currentLight, 215);

    delay((200-(i*2)));

    analogWrite(currentLight, 0);
  }

  analogWrite(currentLight, 0);

  analogWrite(wLight1, 0);
  analogWrite(wLight2, 0);
  analogWrite(wLight3, 0);
  analogWrite(fLight, 0);

  delay(3000);
  
  for(int i=40; i<215; i++)
  {
    analogWrite(wLight1, i-40);
    analogWrite(wLight2, i-40);
    analogWrite(wLight3, i-40);
    analogWrite(fLight, i);
    delay(230-i);
  }
  
  analogWrite(wLight1, 215);
  analogWrite(wLight2, 215);
  analogWrite(wLight3, 215);
  analogWrite(fLight, 215);
  
  delay(1500);
}

