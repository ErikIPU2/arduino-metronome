#include "BPMLib.cpp"

#define BTN_1 8
#define BTN_2 9
#define BTN_3 10

LiquidCrystal_I2C LCD(0x27, 16, 2);

byte ball[8] = {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110,
    0b00000
};

byte ball_full[8] = {
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00000
};

int bpmCont = 1;


void lcd_showIntro() {
    LCD.init();
    LCD.setBacklight(HIGH);
    LCD.clear();
    LCD.cursor_on();
    delay(50);
    String msg = "Metronomo!^By: Erik";
    for (unsigned int i = 0; i < msg.length(); i++) {
        if (msg.charAt(i) == '^') {
            LCD.setCursor(0, 1);
            continue;
        }
        LCD.print(msg.charAt(i));
        if (i != msg.length()) {
            delay(150);
        }
    }
    delay(300);
    LCD.cursor_off();
    LCD.clear();
    LCD.createChar(0, ball);
    LCD.createChar(1, ball_full);
}

void lcd_showMenu(int op) {
    LCD.setCursor(0, 1);
    if (op == 1) {
        LCD.print("1.> |2.>>|3.MENU");
    } else if (op == 2) {
        LCD.print("1.- |2.+ |3.EXIT");
    }
}

void lcd_showInfo(unsigned int bpm) {
    LCD.setCursor(0, 0);

    LCD.print("BPM: ");
    LCD.print(bpm);
}

void lcd_updateBeat() {

    LCD.setCursor(12, 0);

    switch (bpmCont) {
        case 1:
            LCD.write(1);
            LCD.write(0);
            LCD.write(0);
            LCD.write(0);
            bpmCont++;
            break;
        
        case 2:
            LCD.write(1);
            LCD.write(1);
            LCD.write(0);
            LCD.write(0);
            bpmCont++;
            break;
        
        case 3:
            LCD.write(1);
            LCD.write(1);
            LCD.write(1);
            LCD.write(0);
            bpmCont++;
            break;
        
        case 4:
            LCD.write(1);
            LCD.write(1);
            LCD.write(1);
            LCD.write(1);
            bpmCont = 1;
            break;
        
    }

}

void lcd_clearLine(unsigned int line) {
    LCD.setCursor(0, line);
    for (int i = 0; i < 16; i++) {
        LCD.print(" ");
    }
    LCD.setCursor(0, line);
}

void lcd_closeMenu(unsigned int bpm, int btn) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Saindo...");
    LCD.setCursor(0, 1);
    LCD.print("Solte o botao");
    while (digitalRead(btn) == LOW) {}
    LCD.clear();
    lcd_showInfo(bpm);
    lcd_showMenu(1);
}


void lcd_changeBpm(unsigned int* bpm, unsigned int speed) {
    unsigned int multiplier = 1;
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Solte o botao");
    while (digitalRead(BTN_1) == LOW || digitalRead(BTN_2) == LOW) {
        if (digitalRead(BTN_3) == LOW) {
            lcd_clearLine(0);
            multiplier *= 10;
            LCD.print(multiplier);
            LCD.print(" x");
            delay(500);
        }
    }
    LCD.clear();
    lcd_showMenu(2);
    LCD.setCursor(0, 0);
    LCD.print(*bpm);
    LCD.print(" ");
    LCD.print(getBPMname(*bpm));
    while (digitalRead(BTN_3) == HIGH) {
        if (digitalRead(BTN_1) == LOW) {
            *bpm -= speed * multiplier;
            if (*bpm == 0) {
                *bpm -= speed * multiplier;
            }
            lcd_clearLine(0);
            LCD.print(*bpm);
            LCD.print(" ");
            LCD.print(getBPMname(*bpm));
            delay(100);
        } else if (digitalRead(BTN_2) == LOW) {
            *bpm += speed * multiplier;
            if (*bpm == 0) {
                *bpm += speed * multiplier;
            }
            lcd_clearLine(0);
            LCD.print(*bpm);
            LCD.print(" ");
            LCD.print(getBPMname(*bpm));
            delay(100);
        }
    }
    lcd_closeMenu(*bpm, BTN_3);
}

void lcd_config_showInfo(bool* led, bool* buzzer) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("1. Led: ");
    if (*led) {
        LCD.print("ON");
    } else {
        LCD.print("OFF");
    }

    LCD.setCursor(0, 1);
    LCD.print("2. Sound: ");
    if (*buzzer) {
        LCD.print("ON");
    } else {
        LCD.print("OFF");
    }
}

void lcd_config(bool* led, bool* buzzer, unsigned int bpm) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Solte o botao");
    while (digitalRead(BTN_3) == LOW) {}
    lcd_config_showInfo(led, buzzer);
    while (digitalRead(BTN_3) == HIGH) {
        if (digitalRead(BTN_1) == LOW) {
            *led = !*led;
            lcd_clearLine(0);
            LCD.print("Solte o botao");
            while (digitalRead(BTN_1) == LOW) {}
            lcd_config_showInfo(led, buzzer);
        } else if (digitalRead(BTN_2) == LOW) {
            *buzzer = !*buzzer;
            lcd_clearLine(1);
            LCD.print("Solte o botao");
            while (digitalRead(BTN_2) == LOW) {}
            lcd_config_showInfo(led, buzzer);
        }
    }
    lcd_closeMenu(bpm, BTN_3);
}
