//Pins 3, 5, and 7 would be used for base lights, pin 9 would be used for 
int wLight1 = 3;
int wLight2 = 5;
int wLight3 = 6;
int MSensor = 7;
int fLight = 9;

//Used for triggering the motion sensor sequence
int flag=0;

//LOW is a constant that says motion has not been detected yet (sets to false)
int motionDetected = LOW;

//Global count will keep track of how many times the loop() function has executed
//it will be utilized as a global timer rather than trying to deal with the internal
//timing of the microcontroller
int globalCount=0;
int localRegCount=0;
int localSpcCount=0;

void setup() 
{
  // Set up pins for lights to output and motion sensor for input
  pinMode(wLight1, OUTPUT);
  pinMode(wLight2, OUTPUT);
  pinMode(wLight3, OUTPUT);
  pinMode(fLight, OUTPUT);
  pinMode(MSensor, INPUT);
}

void loop() 
{
  globalCount++;
  
  //Read from the motion sensor to see if it has been activated
  motionDetected = digitalRead(MSensor);
  
  //If it has been and the global count has gone past 2900 iterations of the loop() function
  //(roughly 30 seconds) then reset global counters and initiate sequence
  //This delay of 2900 iterations is used to prevent the motion sensor from constantly triggering
  //the sequence, this would be quite unpleasant if it were consistently going off
  if(motionDetected == HIGH && globalCount>2900)
  {
    //Reset global counters
    globalCount=0;
    localRegCount=0;
    localSpcCount=0;
    
    //Iniate special sequence
    specialSequence();
  }
  else
  {
    //Otherwise it will simply do a normal light pulsing which is very pleasant and gradual
    regularSequence();
  }
  
}

void regularSequence()
{
  //Output a solid intensity to the light in the flower
  analogWrite(fLight, 215);

  //Will determine the intensity between 4 and 180 which is fairly easy on the eyes,
  //and keeps the resistance in the LEDs from affecting the other LEDs
  if(localRegCount>=180)
  {
    flag=1;
  }
  else if(localRegCount<=4)
  {
    flag=0;
  }

  //Once the number of iterations falls outside of [4,180] it will begin to 
  //increase/decrease respectively
  if(flag==0)
  {
    localRegCount++;
  }
  else
  {
    localRegCount--;
  }

  //Will be happening independently, but will be such a subtle change it will be unnoticable
  pulse(wLight1);
  pulse(wLight2);
  pulse(wLight3);
  
  //Happens every 10ms
  delay(10);
}

void pulse(int light)
{
  //Simply sets the light to the current intensity
  analogWrite(light, localRegCount);
}

void specialSequence()
{
  int currentLight=0;

  //Will turn off all the lights
  analogWrite(wLight1, 0);
  analogWrite(wLight2, 0);
  analogWrite(wLight3, 0);
  analogWrite(fLight, 0);

  //Pause for 3.5s for dramatic effect
  delay(3500);
  
  //Light up the flower light to full intensity
  analogWrite(fLight, 215);
  
  //Perform a sequence which will cycle through the three base lights
  //and while rotating in a triangular pattern around the base turning on
  //and off and increasing in intensity repetitively until a threshold is 
  //reached (100 iterations)
  for(int i=0; i<100; i++)
  {
    if(i%3==0)
    {
      currentLight=wLight1;
    }
    else if(i%3==1)
    {
      currentLight=wLight2;
    }
    else
    {
      currentLight=wLight3;
    }

    analogWrite(currentLight, 215);

    //Will speed up how quickly the lights flash depending on how many iterations 
    //have been performed
    delay((200-(i*2)));
    
    analogWrite(currentLight, 0);
  }
  
  //Turn off all the lights in the flower
  analogWrite(currentLight, 0);

  analogWrite(wLight1, 0);
  analogWrite(wLight2, 0);
  analogWrite(wLight3, 0);
  analogWrite(fLight, 0);

  //Pause 3s for dramatic effect
  delay(3000);
  
  //On all lights gradually increase intensity of light until all base lights 
  //are 215-40 and the flower light is 215
  for(int i=40; i<215; i++)
  {
    analogWrite(wLight1, i-40);
    analogWrite(wLight2, i-40);
    analogWrite(wLight3, i-40);
    analogWrite(fLight, i);
    delay(230-i);
  }
  
  //Light up all lights to max intensity and pause for 1.5s before returning 
  //to pulse sequence
  analogWrite(wLight1, 215);
  analogWrite(wLight2, 215);
  analogWrite(wLight3, 215);
  analogWrite(fLight, 215);
  
  delay(1500);
}

