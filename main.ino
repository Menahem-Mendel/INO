#include <Servo.h>

#define PIN_SRV 13
#define SENSITIVITY 180
#define PIN_L_PHTRSR A0
#define PIN_R_PHTRSR A1

Servo _srv;
int l_phtrsr;
int r_phtrsr;
int srv_position = 0;

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
