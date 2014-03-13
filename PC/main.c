

#include <stdio.h>
//#include <termios.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <string.h>
//#include <unistd.h>

#define SERIAL_PORT "/dev/ttyS0"

//int serialwrite(int , char );
//int serialread(int);
//
//int main(void){
	//
	////openserialport();
	//int c = openserialport();
	////serialwrite(c, 1);
	//serialread(c);
	//// To run the file write: ./-enter_program_name
	////return 1;
//}
//int openserialport(){
	//// O_NOCTTY | O_NDELAY
	//int fd = open("/dev/ttyS0", O_RDWR);
	//
	//if (fd < 0){
		//printf("Cannot open the file: %s\n", strerror(errno));
	//}
	//
	//struct termios serterm;
	//if (tcgetattr(fd, &serterm)){
		//printf("Error2\n");
		//exit(-1);
	//}
	//
	//tcflush(fd, TCIFLUSH);
	//// INPCK added....
	//serterm.c_cflag = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
	//serterm.c_lflag &= ~ICANON;
	//serterm.c_cc[VTIME] = 10;
	//serterm.c_cc[VMIN] = 0;
	//cfsetospeed(&serterm, B9600);
	//
	//if(tcsetattr(fd, TCSANOW, &serterm)){
		//printf("Error3\n");
		//exit(-1);
	//}
	//return fd;
//}
//
//int serialwrite(int fd, char b){
	//int res = write(fd, &b, 1);
	//if (res < 0) {
		//printf("Error4\n");
	//}
	//printf("Writing!");
	//return res;
//}
//
//int serialread(int fd){
	//uint8_t buf[255];
	//int res;
	//while(1){
		//res = read(fd,buf,255);
		//printf("%i\n", res);
	//}
	//return res;
//}