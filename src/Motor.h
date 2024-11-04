#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int pinNum);
    void increaseSpin();
    void decreaseSpin();
    void resetSpin();
    void spinMotor();
    void update();// 비동기 업데이트 함수
    int getSpin();

private:
    int MOTORPIN;
    int spin;
    unsigned long startTime;// 모터 회전 시작 시간
    bool spinning; // 모터 회전 상태
};

#endif // MOTOR_H