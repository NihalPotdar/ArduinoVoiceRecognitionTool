const int pinAdc = A0;
long interval2 = 5000; // the duration for the blinking
long interval = 3000;
String Input;
boolean Check1 = false;
boolean Check2 = false;
long soft;
long loud;
long previousMillis = 0; // a long for the previous time

void setup()
{
  Serial.begin(115200);
}

void loop()
{ // calibration start
  if (Check1 == false)
  {
    Serial.println("Ready? (y/n)");
    while (Check1 == false)
    {
      if (Serial.available() > 0) {
        Input = Serial.readString();
        Serial.println(Input); // test
        Check1 = true;
      }
    }

    if (Input == "y" || Input == "Y")
    {
      Serial.println("Play soft sound");
      soft = findHighest();
      Serial.println(soft);
    }
  }
  if (Check2 == false)
  {
    Serial.println("Ready? (y/n)");
    while (Check2 == false)
    {
      if (Serial.available() > 0) {
        Input = Serial.readString();
        Serial.println(Input); // test
        Check2 = true;
      }
    }

    if (Input == "y" || Input == "Y")
    {
      Serial.println("Play loud sound");
      loud = findHighest();
      Serial.println(loud);
    }
  }
  // Calibration end

  long sum = Measure();

  if (sum > 100)
  {
    int Loud = 0;
    int Medium = 0;
    int Soft = 0;

    unsigned long currentMillis = millis();

    // Making it so that the sound must play for atleast 3 seconds

    if (sum > loud)
    {
      //Serial.println("Loud");
      Loud++;
    }
    else if (sum < soft)
    {
      // Serial.println("Soft");
      Soft++;
    }
    else
    {
      // Serial.println("Medium");
      Medium++;
    }

    if (currentMillis - previousMillis > interval) { // in the event that the difference between the current and previous times exceeds 3000
      previousMillis = currentMillis;
      // find highest among the individual comparisons of each intensity of sound
      Serial.println("*******************************");
      if (Loud > Medium && Loud > Soft)
        Serial.println("Loud");
      if (Medium > Loud && Medium > Soft)
        Serial.println("Medium");
      if (Soft > Medium && Soft > Loud)
        Serial.println("Soft");
      Serial.println("*******************************");

      // resetting the variable
      Loud = 0;
      Soft = 0;
      Medium = 0;
    }

    delay(10);
  }
}

long findHighest()
{ // hears a sequence of sound over a period of 3 seconds to find the highest pitch
  long previousMillis2 = 0; // a long for the previous time
  long Highest = 0;
  unsigned long currentMillis = 0;
  while (currentMillis - previousMillis2 < interval2) {
    currentMillis = millis();
    long sum = Measure();
    if (sum > Highest)
    {
      Highest = sum;
    }
  }
  Serial.println("Stop Sound");
  return Highest;
}

long Measure()
{
  long sum = 0;
  for (int i = 0; i < 32; i++)
  {
    sum += analogRead(pinAdc);
  }
  sum >>= 5; // shifts the bits 5 to the right (divide by successive intervals of 2)
  return sum;
}
