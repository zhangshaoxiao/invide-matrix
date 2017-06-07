#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#define max_num 255 

int main()
{       int max;
        printf("输入矩阵规模,N为2的n次方\n");
        scanf("%d",&max);
	int temp;
	FILE *fp;
	fp=fopen("source.txt","w");
	 
	   
		srand((int)time(0));
	for( int i=0;i<max;i++)
	{
	for( int j=0;j<max;j++)
{
		temp=rand()%max_num+1;
		fprintf(fp,"%d\n",temp);
		//fseek(fp, 0, SEEK_END);
		//fwrite((char *)temp, strlen((char *)temp),1, fp);
}
	}
	fclose(fp);
	system("pause");
} 
