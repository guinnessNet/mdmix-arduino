#include "Motor.h"

Motor::Motor(int pinNum) : MOTORPIN(pinNum), spin(1) {
    pinMode(MOTORPIN, OUTPUT);
}

void Motor::increaseSpin() {
    spin++;
    Serial.print("Spin increased to ");
    Serial.print(spin);
    Serial.print(" Motor pin: ");
    Serial.println(this->MOTORPIN); // this 포인터를 사용하여 MOTORPIN 출력
}

void Motor::decreaseSpin() {
    if (spin > 1) {
        spin--;
    }
    Serial.print("Spin decreased to ");
    Serial.print(spin);
    Serial.print(" Motor pin: ");
    Serial.println(this->MOTORPIN); // this 포인터를 사용하여 MOTORPIN 출력
}

void Motor::resetSpin() {
    spin = 1;
    Serial.print("Reset Motor pin: ");
    Serial.println(this->MOTORPIN); // this 포인터를 사용하여 MOTORPIN 출력
}

void Motor::spinMotor() {
    digitalWrite(MOTORPIN, HIGH);
    startTime = millis();
    spinning = true;
    Serial.print("Motor is spinning for ");
    Serial.print(spin);
    // delay(1000 * spin);
    Serial.print(" Motor pin: ");
    Serial.println(this->MOTORPIN); // this 포인터를 사용하여 MOTORPIN 출력
    // digitalWrite(MOTORPIN, LOW);
}

void Motor::update() {
    if (spinning && (millis() - startTime >= spin * 1000)) {
        digitalWrite(MOTORPIN, LOW);
        spinning = false;
        Serial.print("Motor stopped on pin ");
        Serial.println(this->MOTORPIN);
    }
}

int Motor::getSpin(){
    return spin;
}