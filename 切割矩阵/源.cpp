#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
//#define max 1024
#define min_size 256
#define LINE 128
int divide_time = 0;    //��ʾ�Ѿ��и�Ĵ���
char name[256];
bool check_deter(int **source,int x,int y,int rank,int size);   //��������Ƿ����,x\y����㣬rankΪ��
int divide(int **source, int x, int y, int rank,int size);  //�и��
int main()
{
	int max;
	cout << "enter max!\n";
	cin >> max;
	FILE  *fp = NULL;          //��ָ�����ڶ�ȡ����
	FILE *Config = NULL;    //��ָ������д�����ļ�
	char *buf;
	buf = (char *)malloc(sizeof(char) * 3);

	fopen_s(&fp, "source.txt", "r");
	//fgets(buf, LINE, fp);
	int matrix_size=max;           //�����С 
	int temp_size = matrix_size;
	int rank = 0;                        //��Ҫ���ֵĽף��и����
	while (temp_size > min_size)
	{
		temp_size = temp_size / 2;
		rank++;
	}
	char temp_name[256];
	int **const source = new int *[max];                  //����ָ��
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
	fclose(fp);                               //���ļ���ȡ����
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
	divide(source, x, y, rank,matrix_size);                //�и������д���ı��ļ�
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
	
	int divide_no;           //�и��4�飬ÿһ����
	FILE *f = NULL;
	FILE *Config = NULL;    //��ָ������д�����ļ�
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
			for (int i = 0; i < 4; i++)                       //�������и�Ϊ4��д��4���ļ�
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
				//�����ļ���ǰ4������Ϊ�Ӿ������洢�ļ���
				fprintf(Config, "%s\n", temp_name);
			}
			fclose(Config);

		
		if (check_deter(source, x, y, divide_time, size=size/2) == true)          //�ҵ���һ�������Ӿ���
		{
			_itoa_s(0,time, 10);
			strcat_s(name,time );
			strcat_s(name, "_");
			_itoa_s(0, temp_number, 10);
			strcat_s(name, temp_number);
			                                      //�����ļ�ģ����

			fopen_s(&Config, "Config.txt", "a+");
			fprintf(Config, "%d\n%d\n%d\n0\n%d\n#\n", divide_time, x, y,size); //д�����ļ�  ,��5�����и��������6�е�7���ǿ�ʼ���꣬��8���Ǳ�ʾ��ʾ�˴ηָ��ҵ��ĵ�һ������
																	  //�Ӿ����ǵڼ���,��9�������� ����ߴ磬��10���Ƿָ���
			fclose(Config);
			return divide(source, x, y, rank = rank - 1, size );
		}

		else
		{
			if (check_deter(source, x = x + size, y, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n1\n%d\n#\n", divide_time, x, y, size);             //д�����ļ�
				fclose(Config);
				strcat_s(name, "_");
				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//�����ļ�ģ����
				return divide(source, x, y, rank = rank - 1, size);
			}
			else if (check_deter(source, x = x - size, y = y + size, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n2\n%d\n#\n", divide_time, x, y, size);              //д�����ļ�
				fclose(Config);
				strcat_s(name, "_");
				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//�����ļ�ģ����
				return divide(source, x, y, rank = rank - 1, size);
			}
			else if (check_deter(source, x = x + size, y, divide_time, size) == true)
			{
				fopen_s(&Config, "Config.txt", "a+");
				fprintf(Config, "%d\n%d\n%d\n3\n%d\n#\n", divide_time, x, y, size);             //д�����ļ�
				strcat_s(name, "_");
				fclose(Config);

				_itoa_s(0, temp_number, 10);
				strcat_s(name, temp_number);
				//�����ļ�ģ����
				return divide(source, x, y, rank = rank - 1, size);
			}
		}
	}

}


bool check_deter(int **source, int x, int y, int rank, int size)
{
	return true;
}