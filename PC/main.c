

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SERIAL_PORT "/dev/ttyS0"

int openserialport();
void serialwrite(uint8_t);
int serialread();
void *lights(void *a);
void input();
int GUI();

pthread_t bridgecontroll;
int fd;

int North = 1;
int South = 1;

int RedS = 1;
int RedN = 1;
int GreenS = 0;
int GreenN = 0;

uint8_t serialIn;

int main(void){
	fd = openserialport(); // Initializes the serial port with 9600 Baud, 8 start bits, 2 stop bits.
	//serialread();
	pthread_create(&bridgecontroll, NULL, lights, 0); // thread, attributes?, method and argument
	input();
}
int openserialport(){
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < 0){
		printf("Cannot open the file: %s\n", strerror(errno));
	}
	struct termios serterm;
	if (tcgetattr(fd, &serterm)){
		printf("Error2\n");
		exit(-1);
	}
	tcflush(fd, TCIFLUSH);
	// INPCK added....
	serterm.c_cflag = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
	serterm.c_lflag &= ~ICANON;
	serterm.c_cc[VTIME] = 10;
	serterm.c_cc[VMIN] = 1;
	cfsetispeed(&serterm, B9600);
	cfsetospeed(&serterm, B9600);
	
	if(tcsetattr(fd, TCSANOW, &serterm)){
		printf("Error3\n");
		exit(-1);
	}
	return fd;
}

void serialwrite(uint8_t b){
	// Writes to the serial port.
	int res = write(fd, &b, sizeof(b));
	if (res < 0) {
		printf("Error4\n");
	}
	b = 0;
	GUI();
}

int serialread(){
	uint8_t buf[255];
	int res;
	while(1){
		res = read(fd,buf,255);
		printf("%i\n", res);
	}
	return res;
}

void input(){
	// The main thread waits for keyboard inputs.
	while(1){
		char character = getchar();
		if(character == 's'){
			//North arrival
			serialwrite(0x1);
			North++;
			GUI();
		}else if(character == 'a'){
			//South arrival
			serialwrite(0x4);
			South++;
			GUI();
		}
	}
}

int GUI(){
	printf("         _____                    _____\n");
	printf("         |-%d-|                    |-%d-|\n", RedS,RedN);
	printf("         |-%d-|                    |-%d-|\n", GreenS, GreenN);
	printf(" --------|---|--------------------|---|---------\n");
	printf("         |---|                    |---|\n");
	printf(" SOUTH: %d                               NORTH: %d    \n", South, North);
	return 1;
}

void *lights(void *a){
	
	while(1){
		int data = read(fd, &serialIn, sizeof(serialIn));
		if(data > 0){ // In case of read error
			printf("Test");
			if((serialIn == 6) && South>0){
				South--;
				serialwrite(0x8);
				printf("%i\n South: ",South);
			}
			if((serialIn == 9) && North>0){
				North--;
				serialwrite(0x2);
				printf("%i\n North: ", North);
			}
			serialIn = 0;
		}
		//else if(data == -1){
			//	printf("Cannot read the file: %s\n", strerror(errno));
		//	}
	}
}