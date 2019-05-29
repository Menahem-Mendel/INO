// эта версия псолнечного трэкера предназнасена
// для медленного срабатывания слежки за солнцем
// "это значит что медленно реагирует на смену места освещения"
// что и нужно в данном случае

#include <Servo.h>

#define PIN_L_PHTRSR A0 // пин ввода: левый фоторезистор
#define PIN_R_PHTRSR A1 // пин ввода: правый фоторезистор
#define PIN_SRV 13		// пин вывода: на сервопривод
#define SENSITIVITY 180 // чувствительность

Servo _srv;   // сервопривод
int l_phtrsr; // значения принимамые левым фоторезистором
int r_phtrsr; // значения принимамые правым фоторезистором

void setup()
{
	_srv.attach(PIN_SRV); // определение переменной _srv на получение данных из PIN_SRV
}

void loop()
{
	l_phtrsr = analogRead(PIN_L_PHTRSR); // определение переменной l_phtrsr на получение данных из PIN_L_PHTRSR
	r_phtrsr = analogRead(PIN_R_PHTRSR); // определение переменной r_phtrsr на получение данных из PIN_R_PHTRSR

	l_phtrsr = map(l_phtrsr, 0, 1023, 0, SENSITIVITY); // настройка диапазона значений l_phtrsr
	r_phtrsr = map(r_phtrsr, 0, 1023, 0, SENSITIVITY); // настройка диапазона значений r_phtrsr
	movesrv(l_phtrsr, r_phtrsr);
}

int srv_position = 0; // текущая позиция сервопривода

void movesrv(int l, int r)
{
	while (l != r)
		if (l > r && srv_position < 180)
		{
			_srv.write(++srv_position);
			delay(25);
		}
		else if (l < r && srv_position >= 0)
		{
			_srv.write(--srv_position);
			delay(25);
		}
}

/*
поменять алгоритм на
	l_phtrsr = map(l_phtrsr, 0, 1023, 0, SENSITIVITY);
	r_phtrsr = map(r_phtrsr, 0, 1023, 0, SENSITIVITY);

	srv_position += ((l_phtrsr - r_phtrsr) / 2)				резко
															деление на 2 нужно так как нам нужно равные значения в обих фоторезисторах
		или
	srv_position += ((l_phtrsr - r_phtrsr) / 2 > 0) ? 1 : -1		постепенно
	! если значение положительное то влево
	! если значение отрицательно то вправо

алгоритм не доработан так как значение srv_position может выйти за рамки
*/