#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../lib/lcdMenuLib.cpp"

#define BUZZER 2
#define LED 3
#define BTN_1 8
#define BTN_2 9
#define BTN_3 10

unsigned int bpm = 120;
bool useBuzzer = false;
bool useLed = true;


void setup(){
	pinMode(BUZZER, OUTPUT);
	pinMode(LED, OUTPUT);
	pinMode(BTN_1, INPUT_PULLUP);
	pinMode(BTN_2, INPUT_PULLUP);
	pinMode(BTN_3, INPUT_PULLUP);
	lcd_showIntro();
	lcd_showInfo(bpm);
	lcd_showMenu(1);
	Serial.begin(9600);
}

void loop(){

	if (digitalRead(BTN_1) == LOW) {
		lcd_changeBpm(&bpm, 1);
	} else if (digitalRead(BTN_2) == LOW) {
		lcd_changeBpm(&bpm, 10);
	} else if (digitalRead(BTN_3) == LOW) {
		lcd_config(&useLed, &useBuzzer, bpm);
	}
	
	if (useBuzzer) {
		digitalWrite(BUZZER, HIGH);
	}
	if (useLed) {
		digitalWrite(LED, HIGH);
	}

	lcd_updateBeat();

	delay(6000 / bpm);
	if (useBuzzer) {
		digitalWrite(BUZZER, LOW);
	}
	if (useLed) {
		digitalWrite(LED, LOW);
	}
	delay(54000 / bpm);
		
}