#include <AudioFrequencyMeter.h>

AudioFrequencyMeter meter;
long previousMillis = 0;   // stores last time when loop was entered      
long interval = 3000; // intervals between each successive frequency report
float HighestFrequency = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("started");

  meter.setBandwidth(70.00, 1500);    // Ignore frequency out of this range
  meter.begin(A0, 45000);             // Intialize A0 at sample rate of 45kHz
}

void loop() {
  // put your main code here, to run repeatedly:  
  float frequency = meter.getFrequency();
  if (frequency > 0)
  {
    Serial.print(frequency);
    Serial.println(" Hz");
  }

  if(Frequency > HighestFrequency)
    HighestFrequency = Frequency;
  
  //unsigned long currentMillis = millis(); // irrelavant variable
  if(millis() - previousMillis > interval) { // when a certain-time limit is exceeded, reset variables and report highest
    previousMillis = currentMillis;
    if(HighestFrequency != 0)// to avoid outputs when nothing has been spoken
      Serial.println(HighestFrequency);
    HighestFrequency = 0;
  }
}
