#include "serialSend.h"
#include <iostream>



using namespace std;

int main()
{
    /*串口相关的设置*/
	int fd;                            //文件描述符
	int err;                           //返回调用函数的状态
	int len;
	unsigned char send_buf[8]={0};
	struct termios options;


	/* 打开串口，返回文件描述符，在此之前必须先给串口写权限，否则会报错  */

	fd = open( "/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);

	int volumeAcc=500;

	while(1)
	{
		/*若打开串口失败，则退出*/
		if  ( tcgetattr( fd,&options)  !=  0)
		   {
			  perror("Setup Serial Failed");
			  return(FALSE);
		   }




        send_buf[2]=((int)volumeAcc)%256;
		send_buf[3]=((int)volumeAcc)/256;


		serial_send(fd,&options,send_buf);

		cout<<"volumeACC is "<<volumeAcc<<endl;


		volumeAcc++;

		if(volumeAcc>1000) break;

        sleep(1);
    }
}

