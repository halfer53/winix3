#include <sys/rex.h>

/**
 * Writes a character to serial port 1.
 **/
int kputc(const int c) {
	//TODO: buffer outkput and print via system calls.
	while(!(RexSp1->Stat & 2));
	RexSp1->Tx = c;
	return 0;
}

/**
 * Reads a character from serial port 1.
 **/
int kgetc() {
	//TODO: user interrupt-driven I/O
	while(!(RexSp1->Stat & 1));
	return RexSp1->Rx;
}

static void kputx(int n) {
	int i;

	for(i = 28; i >= 0; i -= 4) {
		int d = (n >> i) & 0xf;
		if(d < 10) {
			kputc(d + '0');
		}
		else {
			kputc(d - 10 + 'A');
		}
	}
}

static void kputd(int n) {
	int place = 1000000000;

	//zero?
	if(n == 0) {
		kputc('0');
		return;
	}

	//negative?
	if(n < 0) {
		kputc('-');
		n *= -1;
	}

	//find first digit of number
	while(place > n) {
		place /= 10;
	}

	//print the rest
	while(place) {
		int d = n / place;
		kputc(d % 10 + '0');
		place /= 10;
	}
}

static void kputs(const char *s) {
	while(*s)
		kputc(*s++);
}

int kprintf(const char *format, ...) {
	void *arg = &format;
	arg = ((char*)arg) + 1;

	//TODO: proper formats
	while(*format) {
		if(*format == '%') {
			format++;

			switch(*format) {
				case 'd':
					kputd(*((int*)arg));
					arg = ((int*)arg) + 1;
					format++;
					break;

				case 'x':
					kputx(*((int*)arg));
					arg = ((int*)arg) + 1;
					format++;
					break;

				case 's':
					kputs(*(char **)arg);
					arg = ((char *)arg) + 1;
					format++;
					break;

				default:
					kputc(*format++);
			}
		}
		else {
			kputc(*format++);
		}
	}
	return 0;
}
