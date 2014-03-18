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
void input();
void *GUI(void *a);
void *lights(void *a);
void *Gate(void *a);

pthread_t bridgecontroll;
pthread_t gui;
pthread_t gate;

int fd;
int North = 0;
int South = 0;
int RedS = 1;
int RedN = 1;
int GreenS = 0;
int GreenN = 0;
int i = 0;
int x = 10;
int j;
uint8_t serialIn;

int main(void){
	printf("\033[2J");
	openserialport(); // Initializes the serial port with 9600 Baud, 8 start bits, 2 stop bits.
	pthread_create(&bridgecontroll, NULL, lights, 0); // thread, attributes?, method and argument
	//serialread();
	pthread_create(&gui, NULL, GUI, 0); // thread, attributes?, method and argument
	pthread_create(&gate, NULL, Gate, 0);
	input();
}

void *GUI(void *a){

	printf("\033[2J");

	printf("     R%i          R%i \n", RedN, RedS);
	printf("     G%i          G%i \n", GreenN , GreenS);
	printf("-----N%i", North);
	printf("----------S%i----", South);
	
	while(1){
		fflush(stdout);
		if(RedS == 1 && RedN == 1){usleep(500000);}
		//usleep(250000);
		printf("\033[1;7H");
		printf("%i", RedN);
	
		printf("\033[2;7H");
		printf("%i", GreenN);
	
		printf("\033[3;7H");
		printf("%i-", North);
	
		printf("\033[1;19H");
		printf("%i", RedS);
	
		printf("\033[2;19H");
		printf("%i", GreenS);
	
		printf("\033[3;19H");
		printf("%i-", South);
		printf("\033[5;0H");

		if(RedS == 0){
			//printf("                 ");
			printf("\033[17C");
			printf("\033[%iD",i);
			printf("c");
			if(i<10){
				i++;
			}else if(i == 10){
				//printf("\033[1D");
				i = 0;
			}
			usleep(500000);
			printf("\n\033[1A\033[2K");
			

		}
		if(RedN == 0){
			//printf("                 ");
			printf("\033[17C");
			printf("\033[%iD",x);
			printf("c");
			if(x>0){
				x--;
			}else if(x == 0){
				//printf("\033[1D");
				//printf("-");
				x = 10;
			}
			usleep(500000);
			printf("\n\033[1A\033[2K");
			

		}
	}
	
	/*
	while(1){
		if(RedS == 1 && RedN == 1){usleep(500000);}
		printf("\033[1;0H");
        printf("     R%i          R%i \n", RedN, RedS);
        printf("     G%i          G%i \n", GreenN , GreenS);
        printf("-----N%i", North);
		printf("----------S%i----\n", South);
		
		if(RedS == 0){
			printf("       ----------");
			printf("\033[%iD",i);
			printf("c");
			if(i<10){
				i++;
			}else if(i == 10){
				printf("\033[1D");
				printf("-");
				i = 0;
			}
			printf("\n\033[1A\033[2K");
			usleep(500000);
		}
		if(RedN == 0){
			printf("       ----------");
			printf("\033[%iD",x);
			printf("c");
			if(x>0){
				x--;
			}else if(x == 0){
				printf("\033[1D");
				printf("-");
				x = 10;
			}
			printf("\n\033[1A\033[2K");
			usleep(500000);
		}
        printf("\n\033[1A\033[2K");
	}
	*/
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
	serterm.c_lflag &= ~(ECHO | ECHONL | ICANON);
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
	//printf("Writing!");
	int res = write(fd, &b, sizeof(b));
	if (res < 0) {
		printf("Error4\n");
	}
}

int serialread(){
	//uint8_t buf[255];
	uint8_t ch;
	int res;
	printf("\033[2J");
	fflush(stdin);
	while(1){
		//res = read(fd,buf,255);
		//printf("%i\n", res);
		read(fd, &ch, sizeof(ch));
		
		//printf("\033[1;0H");
		printf("%i\n", ch);
		printf("\n\033[1A\033[2K");
		//fflush(stdin);
		usleep(500000);
	}	
	return res;
}

void input(){
	
	fd_set rfds;
	fcntl(fileno(stdin), F_SETFL, O_NONBLOCK);
	
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~(ICANON | ECHO);
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

	
	// The main thread waits for keyboard inputs.
	while(1){
		
		//FD_ZERO(&rfds);
		//FD_SET(fileno(stdin), &rfds);

		char character = getchar();
		
		if(character == 'a'){
		serialwrite(0x1);	// Northbound car arrival, bit 0
		North++;
		}
		if(character == 's'){
		serialwrite(0x4);	// Southbound car arrival, bit 2
		South++;
		}
		fflush(stdin);
		//}
	}
}

void *Gate(void *a){
	
	/*
	while(1){
		if(GreenN == 1 && RedN == 0){
			North--;
			serialwrite(0x2);	// Northbound bridge entry
			usleep(1000000); // 1 sec
		}else if(GreenS == 1 && RedS == 0){
			South--;
			serialwrite(0x8);	// Southbound bridge entry
			usleep(1000000); // 1 sec
		}
	}
	*/
	while(1){
		while(GreenN == 1 && RedN == 0){
			North--;
			serialwrite(0x2);	// Northbound bridge entry
			usleep(1000000); // 1 sec
		}
		if(RedS == 0){
			usleep(5000000); // 5 sec
			i = 0;
			x = 10;
		}
		
		while(GreenS == 1 && RedS == 0){
			South--;
			serialwrite(0x8);	// Southbound bridge entry
			usleep(1000000); // 1 sec
		}
		if(RedN == 0){
			usleep(5000000); // 5 sec
			i = 0;
			x = 10;
		}
	}
}

void *lights(void *a){
	while(1){
		int data = read(fd, &serialIn, sizeof(serialIn));
		if(data > 0){ // In case of read error
		if((serialIn == 0x6)){	// North Red, South Green
			RedN = 1;
			RedS = 0;
			GreenS = 1;
			GreenN = 0;	
		}else if((serialIn == 0x9)){	// North Green, South Red
			RedN = 0;
			RedS = 1;
			GreenS = 0;
			GreenN = 1;
		}else if((serialIn == 0xa)){	// North Red, South Red
			RedN = 1;
			RedS = 1;
			GreenN = 0;
			GreenS = 0;
			}
		}
		usleep(50000);
	}
}
