
#include <iostream>
#include <stdlib.h>// � ���� ����� ����������� rand(), srand()
#include <time.h>//  � ���� ����� ����������� time() // NULL c 1 ������ 1970

using namespace std;
/*
���������� ��������� �����
rand() - �������� ���������� ����� �� 0 �� 32767
srand() - ������� ��������� ��������� ����� ��������� ���������� ������
time() - ���������� ������� ����� ������������ srand

�������� 0 - 10, 0 - 100
srand(time(NUUL));
11 �� 16: 11 12 13 14 15 = 5+11
23 �� 34: = 

srand(time(NULL));
	int a = rand() % 5+11;

	cout << a << "\n";


	int array[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 99 + 1;
		cout << array[i] << "\n";
	}

*/

/*
����������� ������� - ������ = �������
���_������ ���_������� [�����_�����][�����_��������];
������
const int row = 3;// ������
	const int col = 3;// ������
	int array[row][col] = { {1,2}, {7,8} }; // ����� �������� row �� col (3x4)
	int array[row][col] = { 7,8,10,3 };
����

	const int row = 3;// ������
	const int col = 3;// ������
	int array[row][col];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			array[i][j] = rand() % 100;
			cout << array[i][j] << " ";
		}
		cout << "\n\n";
	}

// ����������� ��������� ������

*/
int main()
{
	
	// �������� ���������, ������� � ��������� �������
	// ������� ������������ ������� ������ ������.

	const int m = 10;
	const int n = 10;
	int mr[m][n]; // ��������� ����������� �������
	// ���������� ������� ���������� �������
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mr[i][j] = rand() % 100;
			cout << mr[i][j] << " ";
		}
		cout << "\n\n";
	}
	cout << "\n\n";
	for (int i = 0; i < m; i++)
	{
		int max = mr[i][0];

		for (int j = 0; j < n; j++)
		{
			if (mr[i][j] > max)
				max = mr[i][j];
		}
		cout << " Max element = " << i << " row = " << max << endl;
	}

	bool a; // 1 �����// 1 0 
	int arr[10];//40 �����
	int array[2][2];// 16 ����

	return 0;
}

