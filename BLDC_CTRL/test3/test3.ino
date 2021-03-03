byte motor_speed,
     bldc_step,
     pwm_pin = 2;

void setup() {
  DDRD  |= 0b11111100;                     // Configure pins 2, 3, 4, 5, 6 and 7 as outputs
  PCICR  = 1;                        // Enable pin change interrupt for pins 8 to 13
  PCMSK0 = 7;                        // Enable pin change interrupt for pins 8, 9 and 10
  // Timer2 configuration
  TCCR2A = 0;
  TCCR2B = 2;                        // Timer2 prescaler = 1/8 (Timer2 clock = 2MHz)
  TCNT2  = 0;                        // Timer2 preload value = 0
  // ADC module configuration
  ADMUX  = 0b01100000;                     // Configure ADC module and select channel 0
  ADCSRA = 0b10000100;                     // Enable ADC module with 16 division factor (ADC clock = 1MHz)
  // BLDC motor first move
  bldc_step = PINB & 7;              // Read hall effect sensors status (PINB: read from PORTB which is arduino pins 8..13)
  bldc_move();                       // Move the BLDC motor (first move)
}

ISR (PCINT0_vect) {
  bldc_step = PINB & 7;              // Read and save hall effect sensors status (PINB: read from PORTB which is arduino pins 8..13)
  bldc_move();                       // Move the BLDC motor
}

void bldc_move() {                   // BLDC motor move function according to hall effect sensors status
  switch (bldc_step) {
    case 1:
      PORTD = 0b01001000;
      pwm_pin = 2;
      break;
    case 2:
      PORTD = 0b00100100;
      pwm_pin = 4;
      break;
    case 3:
      PORTD = 0b01100000;
      pwm_pin = 4;
      break;
    case 4:
      PORTD = 0b10010000;
      pwm_pin = 6;
      break;
    case 5:
      PORTD = 0b00011000;
      pwm_pin = 2;
      break;
    case 6:
      PORTD = 0b10000100;
      pwm_pin = 6;
      break;
    default:
      PORTD = 0;
      break;
  }
}
void loop() {
  ADCSRA |= 1 << ADSC;               // Start conversion
  while (ADCSRA & 0b01000000);       // Wait for conversion complete
  motor_speed = ADCH;                // Read ADC data (8 bits)
  // Software PWM
  if (motor_speed < 250) {
    while (TCNT2 < motor_speed) ;
    digitalWrite(pwm_pin, LOW);
  }
  if (motor_speed > 0) {
    while (TCNT2 >= motor_speed) ;
    digitalWrite(pwm_pin, HIGH);
  }
}
