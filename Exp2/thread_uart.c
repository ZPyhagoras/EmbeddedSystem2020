/*
 * thread_uart.c
 *
 * Created on: 2015-11-11
 * Author: qi
 * Modified on: 2020-11-29
 * Author: Zhang Qiyang
 * StudentID: PT2000186
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <sys/sem.h>

int		ret;
int		nread;
int		nwrite;
int		fd_tty;
char	buff[512];
sem_t	read_sem;
sem_t	write_sem;

void  *thread_read_function (void  *arg)
{
	while(1) {
		sem_wait(&read_sem);
	   	nread = read(fd_tty, buff, 255);
	   	if (nread == 0) {
			printf("meet the end\n");
		}
		else if (nread == -1) {
			printf("read error\n");
		}
	   	if (nread == 0 || nread == -1) {
			exit(-1);
		}
		sem_post(&write_sem);
		sem_post(&read_sem);
	}

   pthread_exit(NULL);
   return  (NULL);
}

void  *thread_write_function (void  *arg)
{

	while(1) {
		sem_wait(&write_sem);
		sem_wait(&read_sem);
		if (nread > 0) {
			nwrite = write(fd_tty, buff, 255);
		}
		if (nwrite == -1) {
			printf("write error\n");
			exit(-1);
		}
		sem_post(&read_sem);
		sem_post(&write_sem);
	}

   pthread_exit(NULL);
   return  (NULL);
}

int set_speed (int fd, int speed)
{
	int ret;
	struct termios 	opt;
	ret = tcgetattr(fd, &opt);           /*获取串口的 termios 信息   */
	if (ret !=  0) {
		printf("Get Serial speed failed");
		return (1);
	}
	tcflush(fd, TCIOFLUSH);               /*  刷新输入输出数据 */
	// Todo：设置输入波特率
	cfsetispeed(&opt, speed);
	// Todo：设置输出波特率
	cfsetospeed(&opt, speed); 
  	/* 用于设置终端的相关参数, TCSANOW 不等数据传输完毕就立即改变属性	 */
	ret = tcsetattr(fd, TCSANOW, &opt);
	if (ret != 0) {
		printf("Setup Serial speed failed");
		return (2);
	}
	return (0);
}

int  set_parity (int  fd, int  databits, int  stopbits, int  parity)
{
	int             ret;
	struct termios  options;

	ret = tcgetattr(fd, &options);
	if (ret !=  0) {
		printf("Setup Serial failed");
		return  (1);
	}

	options.c_cflag &= ~CSIZE;
	switch (databits) {

	case 5:
		options.c_cflag |= CS5;
		break;

	case 6:
		options.c_cflag |= CS6;
		break;

	case 7:
		options.c_cflag |= CS7;
		break;

	case 8:
		options.c_cflag |= CS8;
		break;

	default:
		printf("Unsupported data size\n");
		return  (2);
	}

	switch (parity) {

	case 'n':
	case 'N':
		options.c_cflag &= ~PARENB;
		options.c_iflag &= ~INPCK;
		break;

	case 'o':
	case 'O':
		options.c_cflag |= (PARODD | PARENB);
		options.c_iflag |= INPCK;
		break;

	case 'e':
	case 'E':
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK;
		break;

	default:
		printf("Unsupported parity\n");
		return  (3);
	}

	switch (stopbits) {

	case 1:
		options.c_cflag &= ~CSTOPB;
		break;

	case 2:
		options.c_cflag |= CSTOPB;
		break;

	default:
		printf("Unsupported stop bits\n");
		return  (4);
	}

	tcflush(fd, TCIOFLUSH);

	ret = tcsetattr(fd, TCSANOW, &options);
	if (ret != 0) {
		printf("Setup Serial failed");
		return  (5);
	}
	return  (0);
}

int main (int  argc, char  *argv[])
{
	int			ret;
	int			i;
	pthread_t	tid[2];
	int			new_speed = 115200;

	if (argc < 2) {
		printf("useage: %s dev\n", argv[0]);
		return  (-1);
	}

	fd_tty = open(argv[1], O_RDWR);
	if (fd_tty < 0) {
		printf("open device %s faild\n", argv[1]);
		return  (-1);
	}

	 //Todo：设置串口波特率
	ret = set_speed(fd_tty, new_speed);
	if (ret != 0) {
		close(fd_tty);
		return  (-1);
	}

	//Todo：设置串口参数
	ret = set_parity(fd_tty, 8, 1, 'n');
	if (ret != 0) {
		close(fd_tty);
		return  (-1);
	}

	//Todo
	sem_init(&read_sem, 0, 1);
	sem_init(&write_sem, 0, 0);
	int a = 0, b = 1;
	ret = pthread_create(&tid[0], NULL, thread_read_function, (void *)a);
	if (ret != 0) {
	    printf("read thread create failed\n");
	    exit(-1);
	}
	ret = pthread_create(&tid[1], NULL, thread_write_function, (void *)b);
	if (ret != 0) {
	    printf("write thread create failed\n");
	    exit(-1);
	}

	pthread_exit(NULL);
	sem_destroy(&read_sem);
	sem_destroy(&write_sem);

    return 0;
}
