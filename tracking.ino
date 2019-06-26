// версия 0.1.0 солнечного трэкера

#include <Servo.h>

#define PINLEFTLDR A0  // пин ввода: левый фоторезистор
#define PINRIGHTLDR A1 // пин ввода: правый фоторезистор
#define PINSERVO 10	// пин вывода: на сервопривод up down
#define SENSITIVITY 1  // чувствительность фоторезистора от 0 до n, чем ниже значение тем выше чувствительность
#define DTIME 1000	 // скорсть реакции

Servo servo; // сервопривод up down

void setup()
{
	servo.attach(PINSERVO); // определение переменной servo на получение данных из PINSERVO
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
}

int leftLDR;					  // значения принимамые левым фоторезистором
int rightLDR;					  // значения принимамые правым фоторезистором
int servoPosition = servo.read(); // текущая позиция сервопривода

void loop()
{
	if (servo.attached())
	{
		leftLDR = analogRead(PINLEFTLDR);   // определение переменной leftLDR на получение данных из PINLEFTLDR
		rightLDR = analogRead(PINRIGHTLDR); // определение переменной rightLDR на получение данных из PINRIGHTLDR

		leftLDR = map(leftLDR, 0, 3968, 0, SENSITIVITY);   // настройка диапазона значений leftLDR
		rightLDR = map(rightLDR, 0, 3968, 0, SENSITIVITY); // настройка диапазона значений rightLDR

		while (leftLDR != rightLDR)
		{
			leftLDR = analogRead(PINLEFTLDR);
			rightLDR = analogRead(PINRIGHTLDR);

			if (leftLDR > rightLDR)
			{
				servo.write(++servoPosition);
			}
			else if (leftLDR < rightLDR)
			{
				servo.write(--servoPosition);
			}

			if (servoPosition == 0 || servoPosition == 180)
			{
				break;
			}
		}

		delay(DTIME);
	}
	else
	{
		// error
	}
}

#include <Servo.h>

int leftLDR;
int rightLDR;
Servo servo;

void setup()
{
	servo.attach(10);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
}

int servoPosition = servo.read();

void loop()
{
	leftLDR = analogRead(A0);
	rightLDR = analogRead(A1);

	while (leftLDR != rightLDR)
	{
		if (leftLDR > rightLDR && servoPosition <= 180)
		{
			servo.write(++servoPosition);
		}
		else if (leftLDR < rightLDR && servoPosition >= 0)
		{
			servo.write(--servoPosition);
		}
	}
	delay(10);
}