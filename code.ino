#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 30

#define MATRIX_PIN 4
#define NUMPIXELS 25

int prevDistance = 0; // Предыдущее значение расстояния

const int numReadings = 5; // Количество измерений для усреднения
int total = 0; // Сумма значений для подсчета среднего
int count = 0; // Количество измерений

Adafruit_NeoPixel pixels(NUMPIXELS, MATRIX_PIN, NEO_GRB + NEO_KHZ800);
int VOLUME = 0;

void NOTIFICATION_ANIMATION()
{
  int upperBrightness = 5;
  for (int i = 0; i <= upperBrightness; ++i) {
        for (int i = 0; i < NUMPIXELS; i++)
      {
      pixels.setPixelColor(i, 255, 255, 255);
      }
        pixels.setBrightness(i); // Выводим текущее значение числа
        pixels.show();
        delay(75);
    }
  for (int i = upperBrightness; i >= 0;--i) {
        for (int i = 0; i < NUMPIXELS; i++)
      {
      pixels.setPixelColor(i, 255, 255, 255);
      }
        pixels.setBrightness(i); // Выводим текущее значение числа
        pixels.show();
        delay(50);
    }
}

void MAIN_ANIMATION()
{
  int upperBrightness = 5;
  for (int i = 0; i <= upperBrightness; ++i) {
        for (int i = 0; i < NUMPIXELS; i++)
      {
      pixels.setPixelColor(i, 255, 255, 255);
      }
        pixels.setBrightness(i); // Выводим текущее значение числа
        pixels.show();
        delay(115);
    }
  for (int i = upperBrightness; i >= 0;--i) {
        for (int i = 0; i < NUMPIXELS; i++)
      {
      pixels.setPixelColor(i, 255, 255, 255);
      }
        pixels.setBrightness(i); // Выводим текущее значение числа
        pixels.show();
        delay(115);
    }
}


void CLICK_ANIMATION()
{
  int wait = 125;
  pixels.setBrightness(5);
  int center = int(NUMPIXELS / 2);
  int scenter = int(sqrt(NUMPIXELS));
  pixels.setPixelColor(center, 255, 255, 255);
  pixels.show();
  delay(wait);

  pixels.setPixelColor(center+1, 255, 255, 255);
  pixels.setPixelColor(center-1, 255, 255, 255);
  
  pixels.setPixelColor(center+scenter, 255, 255, 255);
  pixels.setPixelColor(center-scenter, 255, 255, 255);

  
  pixels.show();
  delay(wait);

  pixels.setPixelColor(center+2, 255, 255, 255);
  pixels.setPixelColor(center-2, 255, 255, 255);
  pixels.setPixelColor(center+(scenter*2), 255, 255, 255);
  pixels.setPixelColor(center-(scenter*2), 255, 255, 255);

  pixels.setPixelColor(center+scenter+1, 255, 255, 255);
  pixels.setPixelColor(center+scenter-1, 255, 255, 255);

  pixels.setPixelColor(center-scenter+1, 255, 255, 255);
  pixels.setPixelColor(center-scenter-1, 255, 255, 255);
  pixels.show();
  delay(wait);

  pixels.setPixelColor(center+(scenter*2)+1, 255, 255, 255);
  pixels.setPixelColor(center+(scenter*2)-1, 255, 255, 255);

  pixels.setPixelColor(center-(scenter*2)+1, 255, 255, 255);
  pixels.setPixelColor(center-(scenter*2)-1, 255, 255, 255);

  pixels.setPixelColor(center+scenter+2, 255, 255, 255);
  pixels.setPixelColor(center+scenter-2, 255, 255, 255);

  pixels.setPixelColor(center-scenter+2, 255, 255, 255);
  pixels.setPixelColor(center-scenter-2, 255, 255, 255);

  pixels.show();
  delay(wait);

  pixels.setPixelColor(center+(scenter*2)+2, 255, 255, 255);
  pixels.setPixelColor(center+(scenter*2)-2, 255, 255, 255);

  pixels.setPixelColor(center-(scenter*2)+2, 255, 255, 255);
  pixels.setPixelColor(center-(scenter*2)-2, 255, 255, 255);

  pixels.show();
  delay(wait);
}

int calculate_distance()
{
digitalWrite(TRIGGER_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);
 
int time_taken = pulseIn(ECHO_PIN, HIGH);
int dist = time_taken*0.034/2;
if (dist>MAX_DISTANCE) return MAX_DISTANCE;
else if (dist<0) return 0;
return dist;
}

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pixels.begin();
  
}

void loop() {
  long distance;
  
  // Вычисляем расстояние на основе времени прохождения сигнала
  distance = calculate_distance();
  
  // Усредняем значения дистанции
  total += distance;
  count++;
  
  // Когда мы собрали достаточное количество измерений, вычисляем среднее значение и обновляем VOLUME
  if (count == numReadings) {
    int averageDistance = total / numReadings;
    VOLUME = map(averageDistance, 0, MAX_DISTANCE, 0, 100);
    VOLUME = constrain(VOLUME, 0, 100); // Ограничиваем значение VOLUME от 0 до 100
    
    // Выводим значение VOLUME в монитор порта
    Serial.print("Текущий уровень громкости (%): ");
    Serial.println(VOLUME);
    
    // Сбрасываем счетчики для новой серии измерений
    total = 0;
    count = 0;
  }

}
  
