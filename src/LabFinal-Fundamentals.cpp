/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/cademissner/Desktop/IoT/LabFinal-Fundamentals/src/LabFinal-Fundamentals.ino"
// Notifications when set points are passed 
// don't work super well because they can only
// be sent once every five seconds.

void setLightPoints();
void setup();
void loop();
#line 5 "/Users/cademissner/Desktop/IoT/LabFinal-Fundamentals/src/LabFinal-Fundamentals.ino"
SYSTEM_THREAD(ENABLED);

#include "oled-wing-adafruit.h"
#include <blynk.h>
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"

#define BUTTON_IN D2
#define DIAL_IN A0
#define RED_LED D8
#define GREEN_LED D7
#define BLUE_LED D6
#define TEMP_IN A1

OledWingAdafruit display;
VCNL4040 proxSensor;

uint16_t lightPoint1;
uint16_t lightPoint2;
char displayInfo = 't';

void setLightPoints() {
    uint16_t lightPointTemp;

    while (digitalRead(BUTTON_IN) == LOW) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Release");
        display.println("button.");
        display.display();

        uint16_t reading = analogRead(TEMP_IN);
        double voltage = (reading * 3.3) / 4095.0;
        double temperature = (voltage - 0.5) * 100;
        int temperatureF = round((1.8 * temperature) + 32.0);
        int temperatureC = round(temperature);

        Blynk.virtualWrite(V0, temperatureC);
        Blynk.virtualWrite(V1, temperatureF);
    }

    while (digitalRead(BUTTON_IN) == HIGH) {
        lightPointTemp = map(analogRead(DIAL_IN), 0, 4095, 0, 65535);
        uint16_t lightVal = proxSensor.getAmbient();

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println(lightPointTemp);
        display.setTextSize(1);
        display.print("Light: ");
        display.println(lightVal);
        display.display();

        uint16_t reading = analogRead(TEMP_IN);
        double voltage = (reading * 3.3) / 4095.0;
        double temperature = (voltage - 0.5) * 100;
        int temperatureF = round((1.8 * temperature) + 32.0);
        int temperatureC = round(temperature);

        Blynk.virtualWrite(V0, temperatureC);
        Blynk.virtualWrite(V1, temperatureF);
    }
    lightPoint1 = lightPointTemp;

    while (digitalRead(BUTTON_IN) == LOW) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Release");
        display.println("button.");
        display.display();

        uint16_t reading = analogRead(TEMP_IN);
        double voltage = (reading * 3.3) / 4095.0;
        double temperature = (voltage - 0.5) * 100;
        int temperatureF = round((1.8 * temperature) + 32.0);
        int temperatureC = round(temperature);

        Blynk.virtualWrite(V0, temperatureC);
        Blynk.virtualWrite(V1, temperatureF);
    }

    while (digitalRead(BUTTON_IN) == HIGH) {
        lightPointTemp = map(analogRead(DIAL_IN), 0, 4095, 0, 65535);
        uint16_t lightVal = proxSensor.getAmbient();

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println(lightPointTemp);
        display.setTextSize(1);
        display.print("Light: ");
        display.println(lightVal);
        display.display();

        uint16_t reading = analogRead(TEMP_IN);
        double voltage = (reading * 3.3) / 4095.0;
        double temperature = (voltage - 0.5) * 100;
        int temperatureF = round((1.8 * temperature) + 32.0);
        int temperatureC = round(temperature);

        Blynk.virtualWrite(V0, temperatureC);
        Blynk.virtualWrite(V1, temperatureF);
    }

    if (lightPointTemp > lightPoint1) {
        lightPoint2 = lightPointTemp;
    } else {
        lightPoint2 = lightPoint1;
        lightPoint1 = lightPointTemp;
    }

    display.clearDisplay();
    display.display();

}

BLYNK_WRITE(V2) {
    if (param.asInt() == 1) {
        char prevOn;
        if (digitalRead(RED_LED) == HIGH) {
            prevOn = 'r';
        } else if (digitalRead(GREEN_LED) == HIGH) {
            prevOn = 'g';
        } else if (digitalRead(BLUE_LED) == HIGH) {
            prevOn = 'b';
        } else {
            prevOn = 'n';
        }    

        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
        delay(1000);

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        delay(1000);

        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        delay(1000);

        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, HIGH);
        delay(3000);

        if (prevOn == 'r') {
            digitalWrite(RED_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
        else if (prevOn == 'g') {
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(BLUE_LED, LOW);
            digitalWrite(RED_LED, LOW);
        }
        else if (prevOn == 'b') {
            digitalWrite(BLUE_LED, HIGH);
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
        } else {
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
    }      
}

void setup() {
    Serial.begin(9600);

    pinMode(BUTTON_IN, INPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    Wire.begin();
    proxSensor.begin();
    display.setup();
    proxSensor.powerOffProximity();
    proxSensor.powerOnAmbient();
    Blynk.begin("gev9UlWHupS8yCBJ2wpDXDNm6THMu0oS", IPAddress(167, 172, 234, 162), 8080);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.display();

    setLightPoints();

    uint16_t reading = analogRead(TEMP_IN);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    int temperatureF = round((1.8 * temperature) + 32.0);
    int temperatureC = round(temperature);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(temperatureF);
    display.println(" F");
    display.print(temperatureC);
    display.println(" C");
    display.display();
}

void loop() {
    display.loop();

    char ledOn;
    if (digitalRead(RED_LED) == HIGH) {
        ledOn = 'r';
    } else if (digitalRead(GREEN_LED) == HIGH) {
        ledOn = 'g';
    } else if (digitalRead(BLUE_LED) == HIGH) {
        ledOn = 'b';
    } else {
        ledOn = 'n';
    }

    uint16_t lightVal = proxSensor.getAmbient();
    if (lightVal < lightPoint1) {
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);

        if (ledOn != 'b' && ledOn != 'n') {
            Blynk.notify("Light point passed.");
        }
    } else if (lightVal <= lightPoint2) {
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);

        if (ledOn != 'g' && ledOn != 'n') {
            Blynk.notify("Light point passed.");
        }        
    } else {
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

        if (ledOn != 'r' && ledOn != 'n') {
            Blynk.notify("Light point passed.");
        }
    }

    uint16_t reading = analogRead(TEMP_IN);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    int temperatureF = round((1.8 * temperature) + 32.0);
    int temperatureC = round(temperature);

    Blynk.virtualWrite(V0, temperatureC);
    Blynk.virtualWrite(V1, temperatureF);
    
    if (displayInfo == 't') {   
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.print(temperatureF);
        display.println(" F");
        display.print(temperatureC);
        display.println(" C");
        display.display();
    } else {
        setLightPoints();
        displayInfo = 't';
    }

    if (display.pressedA()) {
        displayInfo = 't';
    }

    if (display.pressedB()) {
        displayInfo = 'l';
    }

    Blynk.run();

    delay(100);
}