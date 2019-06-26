// версия 0.2.0 солнечного трэкера

#include <Servo.h>

#define PINLEFTLDR A0   // пин ввода: левый фоторезистор
#define PINRIGHTLDR A1  // пин ввода: правый фоторезистор
#define PINSERVO 10		// пин вывода: на сервопривод
#define SENSITIVITY 180 // чувствительность фоторезистора от 0 до n, чем ниже значение тем выше чувствительность
#define DTIME 1000		// скорсть реакции

Servo servo_10; // сервопривод

void setup()
{
	// определение переменных на получение данных по проводам
	servo_10.attach(PINSERVO);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
}

int leftLDR;  // левый фоторезистор
int rightLDR; // правый фоторезистор
int servoPos; // позиция сервопривода

void loop()
{
	if (servo_10.attached())
	{
		// определение переменных на получение данных
		leftLDR = analogRead(PINLEFTLDR);
		rightLDR = analogRead(PINRIGHTLDR);

		servoPos = servo_10.read();

		// настройка диапазона значений
		leftLDR = map(leftLDR, 0, 3968, 0, SENSITIVITY);
		rightLDR = map(rightLDR, 0, 3968, 0, SENSITIVITY);

		while (leftLDR != rightLDR)
		{
			leftLDR = analogRead(PINLEFTLDR);
			rightLDR = analogRead(PINRIGHTLDR);

			// если солнца мало, опустить
			if (leftLDR < SENSITIVITY - SENSITIVITY / 3 && rightLDR < SENSITIVITY - SENSITIVITY / 3)
			{
				servo_10.write(0);
				break;
			}

			if (leftLDR > rightLDR)
				++servoPos;
			else if (leftLDR < rightLDR)
				--servoPos;

			if (servoPos == 0 || servoPos == 180)
				break;

			servo_10.write(servoPos);
		}

		delay(DTIME);
	}
	else
	{
		// error
	}
}