// версия 0.2.0 солнечного трэкера

#include <Servo.h>

#define PINLEFTLDR A0   // пин ввода: левый фоторезистор
#define PINRIGHTLDR A1  // пин ввода: правый фоторезистор
#define PINSERVO 10		// пин вывода: на сервопривод
#define SENSITIVITY 180 // чувствительность фоторезистора от 0 до n, чем ниже значение тем выше чувствительность
#define DTIME 1000		// скорсть реакции

Servo servo; // сервопривод

void setup()
{
	servo.attach(PINSERVO); // определение переменной servo на получение данных из PINSERVO
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
}

int leftLDR;	   // левый фоторезистор
int rightLDR;	  // правый фоторезистор
int servoPosition; // позиция сервопривода

void loop()
{
	if (servo.attached())
	{
		// определение переменных на получение данных
		leftLDR = analogRead(PINLEFTLDR);
		rightLDR = analogRead(PINRIGHTLDR);

		servoPosition = servo.read();

		// настройка диапазона значений
		leftLDR = map(leftLDR, 0, 3968, 0, SENSITIVITY);
		rightLDR = map(rightLDR, 0, 3968, 0, SENSITIVITY);

		while (leftLDR != rightLDR)
		{
			leftLDR = analogRead(PINLEFTLDR);
			rightLDR = analogRead(PINRIGHTLDR);

			// если солнца мало опустить
			if (leftLDR < SENSITIVITY - SENSITIVITY / 3 && rightLDR < SENSITIVITY - SENSITIVITY / 3)
			{
				servo.write(0);
				break;
			}

			if (leftLDR > rightLDR)
				++servoPosition;
			else if (leftLDR < rightLDR)
				--servoPosition;

			if (servoPosition == 0 || servoPosition == 180)
				break;

			servo.write(servoPosition);
		}

		delay(DTIME);
	}
	else
	{
		// error
	}
}