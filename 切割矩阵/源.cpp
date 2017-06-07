#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
//#define max 1024
#define min_size 256
#define LINE 128
int divide_time = 0;    //表示已经切割的次数
char name[256];
bool check_deter(int **source,int x,int y,int rank,int size);   //检验矩阵是否可逆,x\y是起点，rank为阶
int divide(int **source, int x, int y, int rank,int size);  //切割函数
int main()
{
	int max;
	cout << "enter max!\n";
	cin >> max;
	FILE  *fp = NULL;          //此指针用于读取矩阵
	FILE *Config = NULL;    //此指针用于写配置文件
	char *buf;
	buf = (char *)malloc(sizeof(char) * 3);

	fopen_s(&fp, "source.txt", "r");
	//fgets(buf, LINE, fp);
	int matrix_size=max;           //矩阵大小 
	int temp_size = matrix_size;
	int rank = 0;                        //需要划分的阶，切割次数
	while (temp_size > min_size)
	{
		temp_size = temp_size / 2;
		rank++;
	}
	char temp_name[256];
	int **const source = new int *[max];                  //二级指针
	for (int i = 0; i < max; i++)
	{
		source[i] = new int[max];
	}
	for (int row = 0; row < max; row++)
		for (int col = 0; col < max; col++)
		{
			fgets(buf, LINE, fp);

			source[row][col] = atoi(buf);
			//b[row][col] = atoi(buf);
		}
	fclose(fp);                               //从文件读取矩阵
	int x = 0;
	int y = 0;
	cout << "source: \n";
	/*for (int xi = 0; xi < max; xi++)
	{
		for (int yi = 0; yi < max; yi++)
		{
			cout << source[xi][yi] << "  ";
		}
		cout << endl;
	}
	*/
	temp_size = matrix_size;
	divide(source, x, y, rank,matrix_size);                //切割操作，写入文本文件
	cout<<"success\n";
	/*for (int i = 0; i<max; i++)
		delete[] source[i];
	delete[] source;
	free(buf);
	*/
	cin.get();
	return 0;
}


int divide(int **source, int x, int y, int rank,int size)
{
	char time[4];
	
	int divide_no;           //切割成4块，每一块编号
	FILE *f = NULL;
	FILE *Config = NULL;    //此指针用于写配置文件
	char temp_name[256];
	char temp_number[2];
	
	if (size <= min_size)
	{
		return 0;
	}
	else
	{
		divide_time = divide_time + 1;
		
			
			fopen_s(&Config, "Config.txt", "a+");
			for (int i = 0; i < 4; i++)                       //将矩阵切割为4块写入4个文件
			{

				for (int no = 0; no < 256; no++)
					temp_name[no] = '\0';
				strcpy_s(temp_name, sizeof(name), name);
				_itoa_s(i, temp_number, 10);
				strcat_s(temp_name, temp_number);
				strcat_s(temp_name, ".txt");

				fopen_s(&f, temp_name, "w");
				cout << temp_name << endl;
				for (int m = x + (i /2)*(size / 2); m < x + (i / 2)*(size / 2) + size / 2; m++)
				{
					for (int c = y + (i % 2)*(size / 2); c < y + (i % 2)*(size / 2) + size / 2; c++)
					{
						fprintf(f, "%d\n", source[m][c]);
					  //	cout << source[m][c]<<" " ;
					}
					//cout << endl;
				}
				fclose(f);
				//配置文件里前4个数据为子矩阵所存储文件名
				fprintf(Config, "%s\n", temp_name);
			}
			fclose(Config);

		
		if (check_deter(source, x, y, divide_time, size=size/2) == true)          //找到第一个可逆子矩阵
		{
			_itoa_s(0,time, 10);
			strcat_s(name,time );
			strcat_s(name, "_");
			_itoa_s(0, temp_number, 10);
			strcat_s(name, temp_number);
			                                      //更新文件模板名

			fopen_s(&Config, "Config.txt", "a+");
			fprintf(Config, "%d\n%d\n%d\n0\n%d\n#\n", divide_time, x, y,size); //写配置文件  ,第5行是切割次数，第6行第7行是开始坐标，第8行是表示表示此次分割找到的第一个可逆
																	  //子矩阵是第几个,第9个数据是 矩阵尺寸，第10个是分隔符
			fclose(Config);
			return divide(source, x, y, rank = rank - 1, size );
		}

		else
		{
			if (check_deter(source, x = x + size, y, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n1\n%d\n#\n", divide_time, x, y, size);             //写配置文件
				fclose(Config);
				strcat_s(name, "_");
				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//更新文件模板名
				return divide(source, x, y, rank = rank - 1, size);
			}
			else if (check_deter(source, x = x - size, y = y + size, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n2\n%d\n#\n", divide_time, x, y, size);              //写配置文件
				fclose(Config);
				strcat_s(name, "_");
				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//更新文件模板名
				return divide(source, x, y, rank = rank - 1, size);
			}
			else if (check_deter(source, x = x + size, y, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n3\n%d\n#\n", divide_time, x, y, size);             //写配置文件
				strcat_s(name, "_");
				fclose(Config);

				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//更新文件模板名
				return divide(source, x, y, rank = rank - 1, size);
			}
		}
	}

}


bool check_deter(int **source, int x, int y, int rank, int size)
{
	return true;
}