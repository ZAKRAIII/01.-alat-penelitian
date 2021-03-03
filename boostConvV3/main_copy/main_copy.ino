#define pwm 6
#define potinputPin A7
#define feedbackinputPin A2

float potinputval, feedbackinputval;
float pwmval, potInputVal, feedbackInputVal;
int pwmMAXVAL = 200, LED = 13;
 
void setup(){
  Serial.begin(115200);
  TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
  //TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
	delay(50);
  
  pinMode(13, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(potinputPin, INPUT);
  pinMode(feedbackinputPin, INPUT);

  digitalWrite(pwm, LOW);
  digitalWrite(LED, LOW);
  pwmval = 0;
  
}

void loop(){
  potinputval = readingpotinputval();
  feedbackinputval = readingfeedbackinputval();

  if (potinputval >= feedbackinputval) { //jika nilai potensio > feedback
    Serial.println("A");
    if (pwmval > pwmMAXVAL) {
      Serial.println("A_1");
      potinputval = readingpotinputval();
      feedbackinputval = readingfeedbackinputval();
    } else {
      Serial.println("A_2");
      potinputval = readingpotinputval();
      feedbackinputval = readingfeedbackinputval();
      pwmval = pwmval + 0.5;
      analogWrite(pwm, pwmval);
    }
  }
  else { //jika nilai potensio < feedback
    Serial.println("B");
    if (pwmval <  0) {
      potinputval = readingpotinputval();
      feedbackinputval = readingfeedbackinputval();
    } else {
      potinputval = readingpotinputval();
      feedbackinputval = readingfeedbackinputval();
      pwmval = pwmval - 0.5;
      analogWrite(pwm, pwmval);
    }
  }

  //for debug
//  analogWrite(pwm, potinputval);
  Serial.println(potinputval);

}

float readingpotinputval() {
  int value = 0;
  potInputVal = analogRead(potinputPin);
  value = map(potInputVal,  0, 1023, 0, pwmMAXVAL);
  //  value = map(value, 1023,  0, 128, 0);
  digitalWrite(13,LOW);
  return value;
}

int readingfeedbackinputval() {
  int value = 0;
  feedbackInputVal = analogRead(feedbackinputPin);
  value = map(feedbackInputVal, 0, 1023,  0, 255);
  //  value = map(value, 1023,  0, 255, 0);
  return value;
}

void printval() {
  Serial.println(potInputVal);
  Serial.println(feedbackInputVal);
}
