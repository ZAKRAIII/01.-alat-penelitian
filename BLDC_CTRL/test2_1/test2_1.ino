byte step,
    speed;

void setup()
{
  Serial.begin(115200);
  DDRD |= 0b00011100;
  PORTD = 0b00000000;
  DDRB |= 0b00001110;
  PORTB = 0b00110001;

  TCCR1A = 0;
  TCCR1B = 0b00000001;
  TCCR2A = 0;
  TCCR2B = 0b00000001;

  // ADC configuration
  ADMUX = 0b01100000; // Configure ADC module and select channel 0
  ADCSRA = 0b10000100;

  bldc_move();
}

void bldc_move()
{
  switch (step)
  {
  case 1:
    AH_CL();
    break;
  case 2:
    BH_AL();
    break;
  case 3:
    BH_CL();
    break;
  case 4:
    CH_BL();
    break;
  case 5:
    AH_BL();
    break;
  case 6:
    CH_AL();
    break;
  default:
    PORTD = 0;
    break;
  }
}

void loop()
{
  ADCSRA |= 1 << ADSC; // Start conversion
  while (ADCSRA & 0b01000000)
    ;           // Wait for conversion complete
  speed = ADCH; // Read ADC data=
  Serial.println(speed);
  SET_PWM_DUTY(speed);
}

void AH_BL()
{
  PORTD &= ~0b00010100;
  PORTD |= 0b00001000;
  TCCR2A = 0;
  TCCR1A = 0b10000001;
}
void AH_CL()
{
  PORTD &= ~0b00001100;
  PORTD |= 0b00010000;
  TCCR2A = 0;
  TCCR1A = 0b10000001;
}
void BH_CL()
{
  PORTD &= ~0b00001100;
  PORTD |= 0b00010000;
  TCCR2A = 0;
  TCCR1A = 0b00100001;
}
void BH_AL()
{
  PORTD &= ~0b00011000;
  PORTD |= 0b00000100;
  TCCR2A = 0;
  TCCR1A = 0b00100001;
}
void CH_AL()
{
  PORTD &= ~0b00011000;
  PORTD |= 0b00000100;
  TCCR1A = 0;
  TCCR2A = 0b10000001;
}
void CH_BL()
{
  PORTD &= ~0b00010100;
  PORTD |= 0b00001000;
  TCCR1A = 0;
  TCCR2A = 0b10000001;
}

void SET_PWM_DUTY(byte duty)
{
  OCR1A = duty;
  OCR1B = duty;
  OCR2A = duty;
}
