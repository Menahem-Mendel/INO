// эта версия псолнечного трэкера предназнасена
// для медленного срабатывания слежки за солнцем
// "это значит что медленно реагирует на скорсть смены места освещения"

#include <Servo.h>

#define PIN_L_PHTRSR A0 // пин ввода: левый фоторезистор
#define PIN_R_PHTRSR A1 // пин ввода: правый фоторезистор
#define PIN_SRV 13		// пин вывода: на сервопривод
#define SENSITIVITY 180 // чувствительность

Servo _srv;			  // сервопривод
int l_phtrsr;		  // значения принимамые левым фоторезистором
int r_phtrsr;		  // значения принимамые правым фоторезистором
int srv_position = 0; // текущая позиция сервопривода

void setup()
{
	_srv.attach(PIN_SRV);
}

void loop()
{
	l_phtrsr = analogRead(PIN_L_PHTRSR);
	r_phtrsr = analogRead(PIN_R_PHTRSR);

	l_phtrsr = map(l_phtrsr, 0, 1023, 0, SENSITIVITY);
	r_phtrsr = map(r_phtrsr, 0, 1023, 0, SENSITIVITY);

	while (l_phtrsr != r_phtrsr)
		if (l_phtrsr > r_phtrsr && srv_position < 180)
			_srv.write(++srv_position);
		else if (l_phtrsr < r_phtrsr && srv_position >= 0)
			_srv.write(--srv_position);
}
