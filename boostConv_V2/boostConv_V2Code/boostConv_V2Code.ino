#define pwm 6
#define potinputPin A3
#define feedbackinputPin A2
#define LED 13

int potinputval;
int feedbackinputval;
float pwmval;

void setup() {
  Serial.begin(115200);
  //  TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
  //TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
  delay(100);
  pinMode(pwm, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(potinputPin, INPUT);
  pinMode(feedbackinputPin, INPUT);
  digitalWrite(pwm, LOW);
  digitalWrite(LED, LOW);
  pwmval = 0;
}

void loop() {
  potinputval = readingpotinputval();
  feedbackinputval = readingfeedbackinputval();
  printval();

  //  if (analogRead(feedbackinputPin) > 421) {//750 =
  //    Serial.println("HERE");
  //    analogWrite(pwm, 105);
  //    digitalWrite(LED, HIGH);
  //    digitalWrite(LED, LOW);
  //  } else {
  //    Serial.println("~HERE");
  if (potinputval >= feedbackinputval) { //jika nilai potensio > feedback
    Serial.println("A");
    if (pwmval > 250) {
      Serial.println("A_a");
      potinputval = readingpotinputval();
      feedbackinputval = readingfeedbackinputval();
    } else {
      Serial.println("A_b");
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
  //  }
}

int readingpotinputval() {
  int val = analogRead(potinputPin);
  val = map(val,  0, 1023, 0, 128);
  //  val = map(val, 1023,  0, 128, 0);
  return val;
}

int readingfeedbackinputval() {
  int val = analogRead(feedbackinputPin);
  val = map(val, 0, 1023,  0, 255);
  //  val = map(val, 1023,  0, 255, 0);
  return val;
}

void printval() {
  Serial.print(analogRead(potinputPin));
  Serial.print(" = ");
  Serial.print(potinputval);
  Serial.print("\t|\t");
  Serial.print(analogRead(feedbackinputPin));
  Serial.print(" = ");
  Serial.println(feedbackinputval);
}
