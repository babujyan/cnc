#ifndef DEFINES

	#define DEFINES

	#define F_CPU 16000000UL
	#define BAUD 9600UL
	#define MY_UBRR (F_CPU/16/BAUD-1)

	#define ON 0x01
	#define OFF 0x00

#endif //DEFINES