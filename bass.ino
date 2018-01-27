
#define N 128 

const int analogInPin = A0;
const uint8_t LEDpin = 2;
uint32_t startTime_uS;
uint32_t endTime_uS;
int16_t values[N];
float p = 0;

float Single_Point_DFT(int16_t inputArray[], float sampleFreq, float freqToSampleFor){
  float k = freqToSampleFor * N / sampleFreq; 
  float radiansPerSample = 2.0 * 3.14159 * k / N;

  float RealSum = 0;
  float ImaginarySum = 0;
  
  for (int n = 0; n < N; n++){
    float angle = n * radiansPerSample;
    float voltage = inputArray[n] * (5.0 / 1023.0);

    RealSum += voltage * cos(angle);
    ImaginarySum -= voltage * sin(angle);
  }

  return sqrt(RealSum*RealSum + ImaginarySum*ImaginarySum) / N;
}

void setup(){
  Serial.begin(115200);
}

void loop() {
    startTime_uS = micros();
    for(uint8_t n = 0; n < N; n++)
    {
      values[n] = analogRead(analogInPin);
    }
    endTime_uS = micros();

    float sampleFreq = N * 1000000.0/(endTime_uS - startTime_uS);
    float result = Single_Point_DFT(values, sampleFreq, 120);
    
    analogWrite(LEDpin,(p-result)*250);
    analogWrite(LED_BUILTIN,(result-p)*250);

    p=result;    
}
