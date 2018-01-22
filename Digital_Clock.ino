

// constants won't change. Used here to set a pin number :
const int ledPin =  9;// the number of the LED pin
const int segA = A5; //Display pin a
const int segB = 3; //Display pin b
const int segC = 4; //Display pin c
const int segD = 5; //Display pin d
const int segE = 6; //Display pin e
const int segF = 7; //Display pin f
const int segG = 8; //Display pin g
const int jam1 = 10;
const int jam2 = 11;
const int menit1 = 12;
const int menit2 = 13;
const int interval = 500;           // interval at which to blink (milliseconds)
const int sw1 = A1;
const int sw2 = A2;
const int intr = 2;

// Variables will change :
int detik = 0;
int menit = 0;
int jam = 0;
int toggle1 = 0;
unsigned long previousMillis = 0;     
unsigned long currentMillis;
volatile int state = 0;
int reads1;
int reads2;
int lastreads1;
int lastreads2;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(jam1, OUTPUT);
  pinMode(jam2, OUTPUT);
  pinMode(menit1, OUTPUT);
  pinMode(menit2, OUTPUT);
  pinMode(intr, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intr), change_state, FALLING);

  cli();//stop interrupts
  
  //set timer1 interrupt at 2Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 2hz increments
  OCR1A = 31249;// = (16*10^6 * 0.5) / (256) - 1 (must be <65536)
  // turn on CTC modet
  TCCR1B |= (1 << WGM12);
  // Set CS12  bits for 256 prescaler
  TCCR1B |= (1 << CS12);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//allow interrupts
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.
  if (state == 0)
  {
    show();
  }
  else
  {
    set(state);
  }
}

void change_state()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > 200)
  {
    previousMillis = currentMillis;
    if (state >= 4)
    {
      state = 0;
    }
    else
    {
      state++;
    } 
  }
}

void set(int state)
{
  switch (state)
  {
    case 1:
    {
      detik=0;
      digitalWrite(ledPin,LOW);
      digitalWrite(jam1, LOW);
      digitalWrite(jam2, LOW);
      digitalWrite(menit1, LOW);
      digitalWrite(menit2, HIGH);
      reads1 = digitalRead(sw1);
      if (reads1 !=lastreads1)
      {
        lastreads1 = reads1;
        if (reads1 == LOW)
        {
          if (menit >= 60)
          {
            menit = 0;
          }
          else
          {
            menit += 1;  
          }
        }
        delay(200); 
      }
      reads2 = digitalRead(sw2);
      if (reads2 !=lastreads2)
      {
        lastreads2 = reads2;
        if (reads2 == LOW)
        {
          if (menit <= 0)
          {
            menit = 59;
          }
          else
          {
            menit -= 1;  
          }
        }  
        delay(200);
      }
      lightNumber(menit%10);
      detik=0;
      break;
    }
    case 2:
    {
      detik=0;
      digitalWrite(ledPin,LOW);
      digitalWrite(jam1, LOW);
      digitalWrite(jam2, LOW);
      digitalWrite(menit1, HIGH);
      digitalWrite(menit2, LOW);
      reads1 = digitalRead(sw1);
      if (reads1 !=lastreads1)
      {
        lastreads1 = reads1;
        if (reads1 == LOW)
        {
          if (menit >= 60)
          {
            menit = 0;
          }
          else
          {
            menit += 10;  
          }
        }  
        delay(200);
      }
      reads2 = digitalRead(sw2);
      if (reads2 !=lastreads2)
      {
        lastreads2 = reads2;
        if (reads2 == LOW)
        {
          if (menit <= 0)
          {
            menit = 59;
          }
          else
          {
            menit -= 10;  
          }
        }  
        delay(200);
      }
      lightNumber(menit/10);
      detik=0;
      break;
    }
    case 3:
    {
      detik=0;
      digitalWrite(ledPin,LOW);
      digitalWrite(jam1, LOW);
      digitalWrite(jam2, HIGH);
      digitalWrite(menit1, LOW);
      digitalWrite(menit2, LOW);
      reads1 = digitalRead(sw1);
      if (reads1 !=lastreads1)
      {
        lastreads1 = reads1;
        if (reads1 == LOW)
        {
          if (jam >= 24)
          {
            jam = 0;
          }
          else
          {
            jam += 1;  
          }
        }  
        delay(200);
      }
      reads2 = digitalRead(sw2);
      if (reads2 !=lastreads2)
      {
        lastreads2 = reads2;
        if (reads2 == LOW)
        {
          if (jam <= 0)
          {
            jam = 23;
          }
          else
          {
            jam -= 1;  
          }
        }  
        delay(200);
      }
      lightNumber(jam%10);
      detik=0;
      break;
    }
    case 4:
    {
      detik=0;
      digitalWrite(ledPin,LOW);
      digitalWrite(jam1, HIGH);
      digitalWrite(jam2, LOW);
      digitalWrite(menit1, LOW);
      digitalWrite(menit2, LOW);
      reads1 = digitalRead(sw1);
      if (reads1 !=lastreads1)
      {
        lastreads1 = reads1;
        if (reads1 == LOW)
        {
          if (jam >= 24)
          {
            jam = 0;
          }
          else
          {
            jam += 10;  
          }
        }  
        delay(200);
      }
      reads2 = digitalRead(sw2);
      if (reads2 !=lastreads2)
      {
        lastreads2 = reads2;
        if (reads2 == LOW)
        {
          if (jam <= 0)
          {
            jam = 23;
          }
          else
          {
            jam -= 10;  
          }
        }  
        delay(200);
      }
      lightNumber(jam/10);
      detik = 0;
      break;
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  if (toggle1)
  {
    digitalWrite(ledPin,HIGH);
    toggle1 = 0;
  }
  else
  {
    digitalWrite(ledPin,LOW);
    detik++;
    if(detik >= 60)
    {
      menit++;
      detik=0;   
    }
    if (menit >= 60)
    {
      jam++;
      menit = 0;
    }
    if (jam >= 24)
    {
      jam = 0;
    }
    toggle1 = 1;
  }
}

void show()
{
       digitalWrite(jam1, LOW);
       digitalWrite(jam2, LOW);
       digitalWrite(menit1, LOW);
       digitalWrite(menit2, HIGH);
       lightNumber(menit%10);
       delay(5);

       digitalWrite(jam1, LOW);
       digitalWrite(jam2, LOW);
       digitalWrite(menit1, HIGH);
       digitalWrite(menit2, LOW);
       lightNumber(menit/10);
       delay(5);

       digitalWrite(jam1, LOW);
       digitalWrite(jam2, HIGH);
       digitalWrite(menit1, LOW);
       digitalWrite(menit2, LOW);
       lightNumber(jam%10);
       delay(5);

       digitalWrite(jam1, HIGH);
       digitalWrite(jam2, LOW);
       digitalWrite(menit1, LOW);
       digitalWrite(menit2, LOW);
       lightNumber(jam/10);
       delay(5);
}

void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  // all segment are ON
  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  
  }
}
