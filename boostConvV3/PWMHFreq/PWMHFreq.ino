#include <PWM.h>

#define pwm 9
#define potinputPin A3
#define feedbackinputPin A2

float potinputval, feedbackinputval;
float pwmval, potInputVal, feedbackInputVal;
int pwmMAXVAL = 200,
    pwmMINVAL = 0;
int32_t frequency = 100000; //frequency (in Hz)

void setup() {
  Serial.begin(115200);
  //TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
  //TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
  delay(100);
  InitTimersSafe();

  //pinMode(13, OUTPUT);
  //  pinMode(pwm, OUTPUT);
  pinMode(potinputPin, INPUT);
  pinMode(feedbackinputPin, INPUT);

//  digitalWrite(pwm, LOW);
//  digitalWrite(LED, LOW);

  bool success = SetPinFrequencySafe(pwm, frequency);

  //if the pin frequency was set successfully, turn pin 13 on
  if (success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
  }

}

void loop() {
  potinputval = analogRead(potinputPin);
  feedbackinputval = analogRead(feedbackinputPin);

  if (potinputval > feedbackinputval)
  {
    pwmval = pwmval + 1;
    pwmval = constrain(pwmval, pwmMINVAL, pwmMAXVAL);
    //analogWrite(pwm, pwmval);
    //potinputval = readingpotinputval();
    //feedbackinputval = readingfeedbackinputval();
  }

  else
  {
    pwmval = pwmval - 1;
    //    if (pwmval < pwmMINVAL) pwmval = pwmMINVAL;
    pwmval = constrain(pwmval, pwmMINVAL, pwmMAXVAL);

    //analogWrite(pwm, pwmval);
    //potinputval = readingpotinputval();
    //feedbackinputval = readingfeedbackinputval();
  }

  analogWrite(pwm, pwmval);

  Serial.println(String(potinputval) + "\t" + String(feedbackinputval) + "===>" + String(pwmval));
}
