#include <stdio.h>
#include <stdlib.h> 
/******************************************************************************
**  汇编代码程序声明
******************************************************************************/
extern  int sort (int  *buf,int  buflen);         	/*  汇编代码程序声明            */
/******************************************************************************
** 函数名称: showdata
** 功能描述: 通过控制台输出 buffer[] 中的数据
******************************************************************************/
void  showdata (int  *buf, int  buflen)
{
   int i;
   printf("buffer data:\n");
   for(i = 0; i < buflen; i++) {
	   printf("%4d", *(buf + i));
   }
   printf("\n");
}
/******************************************************************************
** 函数名称: main
** 功能描述: 程序主函数
******************************************************************************/
int main()
{
   int  data;
   int  buffer[256];                                   	/*  数据缓冲区                  */
   int  bufferlen = 0;                                 	/*  数据缓冲区数据个数          */

   printf("data input :\n");
   while (1) {                                   			/*  键盘输入整型数 ==〉 data   */
	   scanf("%d", &data);
	   buffer[bufferlen++] = data;
	   if((data == -1) || (bufferlen >= 256)) {      	/*  输入数据为 -1 结束输入     */
		   bufferlen--;
		   break;
      }
   }
  printf("data input end!\n");

  showdata(buffer, bufferlen);                       	/*  将输入数据输出到控制台      */
  sort(buffer, bufferlen);                             	/*  对输入数据排序              */
  showdata(buffer, bufferlen);                       	/*  输出排序数据                */

  return (0);
}
