// версия 0.1.0 солнечного трэкера

#include <Servo.h>

#define PIN_L_LDR A0	// пин ввода: левый фоторезистор
#define PIN_R_LDR A1	// пин ввода: правый фоторезистор
#define PIN_UD_SRV 10   // пин вывода: на сервопривод up down
#define SENSITIVITY 180 // чувствительность от 0 до n
#define DTIME 25		// скорсть вращение. чем выше значение тем ниже скорость

Servo ud_srv; // сервопривод up down
int l_ldr;	// значения принимамые левым фоторезистором
int r_ldr;	// значения принимамые правым фоторезистором

void setup()
{
	ud_srv.attach(PIN_UD_SRV); // определение переменной ud_srv на получение данных из PIN_UD_SRV
	Serial.begin(9600);
}

void loop()
{
	if (ud_srv.attached())
	{
		l_ldr = analogRead(PIN_L_LDR); // определение переменной l_ldr на получение данных из PIN_L_LDR
		r_ldr = analogRead(PIN_R_LDR); // определение переменной r_ldr на получение данных из PIN_R_LDR

		l_ldr = map(l_ldr, 0, 1023, 0, SENSITIVITY); // настройка диапазона значений l_ldr
		r_ldr = map(r_ldr, 0, 1023, 0, SENSITIVITY); // настройка диапазона значений r_ldr

		movesrv(l_ldr, r_ldr);
	}
	else
	{
		// error
	}
}

int srv_position = ud_srv.read(); // текущая позиция сервопривода

void movesrv(int l, int r)
{
	if (l != r)
	{
		if (l > r && srv_position <= 180)
			ud_srv.write(++srv_position);
		else if (l < r && srv_position >= 0)
			ud_srv.write(--srv_position);
		delay(DTIME);
	}
}

/*
поменять алгоритм на
	l_ldr = map(l_ldr, 0, 1023, 0, SENSITIVITY);
	r_ldr = map(r_ldr, 0, 1023, 0, SENSITIVITY);

	srv_position += ((l_ldr - r_ldr) / 2)				резко
															деление на 2 нужно так как нам нужно равные значения в обих фоторезисторах
		или
	srv_position += ((l_ldr - r_ldr) / 2 > 0) ? 1 : -1		постепенно
	! если значение положительное то влево
	! если значение отрицательно то вправо

алгоритм не доработан так как значение srv_position может выйти за рамки
*/

// версия 0.1.0 солнечного трэкера

#include <Servo.h>

#define PIN_L_LDR A0  // пин ввода: левый фоторезистор
#define PIN_R_LDR A1  // пин ввода: правый фоторезистор
#define PIN_UD_SRV 10   // пин вывода: на сервопривод up down
#define SENSITIVITY 180 // чувствительность от 0 до n
#define DTIME 25    // скорсть вращение. чем выше значение тем ниже скорость

Servo ud_srv; // сервопривод up down
int l_ldr;  // значения принимамые левым фоторезистором
int r_ldr;  // значения принимамые правым фоторезистором

void setup()
{
  ud_srv.attach(PIN_UD_SRV); // определение переменной ud_srv на получение данных из PIN_UD_SRV
}

void loop()
{
  if (ud_srv.attached())
  {
    l_ldr = analogRead(PIN_L_LDR); // определение переменной l_ldr на получение данных из PIN_L_LDR
    r_ldr = analogRead(PIN_R_LDR); // определение переменной r_ldr на получение данных из PIN_R_LDR

    l_ldr = map(l_ldr, 0, 3968, 0, SENSITIVITY); // настройка диапазона значений l_ldr
    r_ldr = map(r_ldr, 0, 3968, 0, SENSITIVITY); // настройка диапазона значений r_ldr

    movesrv(l_ldr, r_ldr);
  }
  else
  {
    // error
  }
}

int srv_position = ud_srv.read(); // текущая позиция сервопривода

void movesrv(int l, int r)
{
  if (l != r)
  {
    if (l > r && srv_position <= 180)
      ud_srv.write(++srv_position);
    else if (l < r && srv_position >= 0)
      ud_srv.write(--srv_position);
    delay(DTIME);
  }
}