#define pwmPin 3

void setup()
{
    Serial.begin(115200);
    pinMode(pwmPin, OUTPUT);
}

void loop()
{
    int temp = map(analogRead(A1), 0, 1023, 0, 255);
    analogWrite(pwmPin, temp);
    Serial.println(String(temp));
}
