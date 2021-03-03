#define pwm 6
#define potinputPin A3
#define feedbackinputPin A2
#define LED 13

int pwmMAXVAL = 225,
    pwmMINVAL = 0,
    potinputval,
    feedbackinputval,
    pwmval,
    potInputVal,
    feedbackInputVal;

void setup() {
  TCCR0B = TCCR0B & B11111000 | B00000001;   // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
  //TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz

  Serial.begin(115200);

  pinMode(13, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(potinputPin, INPUT);
  pinMode(feedbackinputPin, INPUT);

  digitalWrite(LED, LOW);

  //  softstart
  pwmval = map(analogRead(potinputPin), 1023, 0, pwmMINVAL, pwmMAXVAL);

  for (int i = 0; i < pwmval; i++) {
    analogWrite(pwm, i);
    Serial.print(".");
    delay(850);
  }
  delay(500);
}

void loop() {
  potinputval = analogRead(potinputPin);
  potinputval = map(potinputval, 1024, 0, 0, 1024);
  feedbackinputval = analogRead(feedbackinputPin);

  if (potinputval > feedbackinputval)
  {
    pwmval = pwmval + 1;
    pwmval = constrain(pwmval, pwmMINVAL, pwmMAXVAL);
  }

  else
  {
    pwmval = pwmval - 1;
    pwmval = constrain(pwmval, pwmMINVAL, pwmMAXVAL);
  }


  analogWrite(pwm, pwmval);

  Serial.println(String(potinputval) + "\t" + String(feedbackinputval) + "===>" + String(pwmval));
}





//float potinputval, feedbackinputval;
//float pwmval, potInputVal, feedbackInputVal;
