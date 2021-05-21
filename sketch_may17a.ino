#include "GyverPower.h"
#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"

#include <avr/sleep.h>
#include <avr/power.h>

bool is_sleep = false;
#define sleep_pin 2
int i = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(sleep_pin, INPUT_PULLUP);
  attachInterrupt(0, sleep_funck, FALLING);
  power.setSleepMode(POWERDOWN_SLEEP);
  mp3_set_serial(Serial); // включаем передачу данных с DFPlayer mini mp3
  delay(1);               // задержка в 1ms для установки громкости
  mp3_set_volume(2);      // устанавливаем громкость от 0 до 30
  mp3_set_EQ(0);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void sleep_funck()
{
  mp3_pause();
  if (is_sleep)
  {
    //power.wakeUp();
    power_all_enable();
    is_sleep = false;
    mp3_play(3);
  }
  else
  {
    is_sleep = true;

    power_all_disable();

    //power.sleepDelay(1200000);
  }
}

void loop()
{
  mp3_play(1); // проигрываем файл mp3/0001.mp3
  delay(5000); // задержка 5 секунд

  mp3_next();  // проигрываем следующий файл
  delay(2000); // задержка 5 секунд

  mp3_next(); // проигрываем следующий файл
  delay(5000);
}