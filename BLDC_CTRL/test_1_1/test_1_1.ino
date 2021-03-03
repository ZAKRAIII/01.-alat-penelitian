int lowA = 4;
int highA = 9;
int lowB = 3;
int highB = 10;
int lowC = 2;
int highC = 11;

int enable = 2;
int emfA = A2;
int emfB = A3;
int emfC = A4;

int fase = 1;

int IN = A5;
int tempo = 4000;

unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(lowA, OUTPUT);
  pinMode(highA, OUTPUT);
  pinMode(lowB, OUTPUT);
  pinMode(highB, OUTPUT);
  pinMode(lowC, OUTPUT);
  pinMode(highC, OUTPUT);

  pinMode(enable, OUTPUT);

  pinMode(IN, INPUT);
  pinMode(emfA, INPUT);
  pinMode(emfB, INPUT);
  pinMode(emfC, INPUT);

  digitalWrite(enable, HIGH);
  previousMillis = millis();
}

void loop()
{
  unsigned long currentMillis = millis();
  Serial.println(tempo);

  if (currentMillis - previousMillis >= tempo)
  {
    previousMillis += tempo;

    //Phase1 C-B
    switch (fase)
    {
      case 1:
        digitalWrite(lowA, LOW);
        digitalWrite(highA, LOW);
        digitalWrite(lowB, LOW);
        digitalWrite(highC, LOW);
        digitalWrite(highB, HIGH);
        digitalWrite(lowC, HIGH);
        break;

      //Phase2 A-B
      case 2:
        digitalWrite(highA, LOW);
        digitalWrite(lowB, LOW);
        digitalWrite(lowC, LOW);
        digitalWrite(highC, LOW);
        digitalWrite(lowA, HIGH);
        digitalWrite(highB, HIGH);
        break;

      //Phase3 A-C
      case 3:
        digitalWrite(highA, LOW);
        digitalWrite(lowB, LOW);
        digitalWrite(highB, LOW);
        digitalWrite(lowC, LOW);
        digitalWrite(highC, HIGH);
        digitalWrite(lowA, HIGH);
        break;

      //Phase4 B-C
      case 4:
        digitalWrite(lowA, LOW);
        digitalWrite(highA, LOW);
        digitalWrite(highB, LOW);
        digitalWrite(lowC, LOW);
        digitalWrite(lowB, HIGH);
        digitalWrite(highC, HIGH);
        break;

      //Phase5 B-A
      case 5:
        digitalWrite(lowA, LOW);
        digitalWrite(highB, LOW);
        digitalWrite(lowC, LOW);
        digitalWrite(highC, LOW);
        digitalWrite(highA, HIGH);
        digitalWrite(lowB, HIGH);
        break;

      //Phase6 C-A
      case 6:
        digitalWrite(lowA, LOW);
        digitalWrite(lowB, LOW);
        digitalWrite(highB, LOW);
        digitalWrite(highC, LOW);
        digitalWrite(lowC, HIGH);
        digitalWrite(highA, HIGH);
        break;
    }

    int t = analogRead(IN);
    tempo = map(t, 1024, 0, 1, 1000);
    if (fase < 6)
    {
      fase = fase + 1;
    }
    else
    {
      fase = 1;
    }
  }
}
