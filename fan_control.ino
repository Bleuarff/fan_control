
const int outPin1 = 5;
const int outPin2 = 3;

const int input1 = A5;
const int input2 = A2;

const int sleepTime = 5000; // 5 sec

void setup()
{
  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);

  Serial.begin(9600);
}

// get temperature
float sense(int input, float offset)
{
  int baseVal = analogRead(input);
  float voltage = (baseVal / 1024.0) * 4.98;
  float temp = voltage * 100 - 273.15 + offset;

  Serial.print("Value: ");
  Serial.print(baseVal);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 4);
  Serial.print("\tTemp: ");
  Serial.print(temp, 1);

  return temp;
}

// set fan speed
void regulateFan(float temp, int outPin)
{
  int pwm = 0;

  if (temp > 25 && temp <= 30)
  {
    pwm = 85;
  }
  else if (temp > 30 && temp <= 35)
  {
    pwm = 170;
  }
  else if (temp > 35)
  {
    pwm = 255;
  }
  Serial.print("\tPwm level: ");
  Serial.println(pwm);
  analogWrite(outPin, pwm);
}

void loop()
{
  // Temp sensing
  int temp1 = sense(input1, 0.5);
  regulateFan(temp1, outPin1);

  int temp2 = sense(input2, 2.9);
  regulateFan(temp2, outPin2);

  delay(sleepTime);
}
