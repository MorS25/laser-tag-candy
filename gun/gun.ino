
int IRledPin =  2; 
int triggerPin =  0; 

void setup() {
  // put your setup code here, to run once:
  pinMode(IRledPin, OUTPUT);  
  digitalWrite(IRledPin, LOW);

  pinMode(triggerPin, INPUT);
//  cli();  // this turns off any background interrupts
}

void loop() {
//  pulseIR(1000);
//  delay(1);
  while (digitalRead(triggerPin)) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
      delayMicroseconds(5);         // hang out for 10 microseconds, you can also change this to 9 if its not working
      digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
      delayMicroseconds(5);         // hang out for 10 microseconds, you can also change this to 9 if its not working 
    }
  }
}

void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(5);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(5);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

