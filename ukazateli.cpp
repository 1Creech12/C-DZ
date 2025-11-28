
#include <iostream>
using namespace std;
/*
”казатель Ч это переменна€, содержаща€ адрес другой переменной
int x = 0;
px = &x; px - указатель на перемную x, &(получени€ адреса) - унарный оператор выдает адрес объекта 
унарна€ операци€ *(разименовать) -  рассматривает свой операнд,
как адрес конечной цели, и обращаетс€ по этому адресу,
чтобы извлечь содержимое.

px = &x;
y = *px;

x == y

int x, y:
int* px

 // присваивает y значение,
 // на 1 большее значени€ x;
 y = *px + 1;
 cout<< *px; // выводит текущее значение x;
 d = sqrt((double) *px) // получает в d квадратный
 // корень из x,
*/
void ShowArray(int arr[], int size)
{
	for (int i = 0; i < size; i++) {
		cout << *(arr + i) << " ";
	}
}
int GetAmout(int* ptr, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += *(ptr + i);
	}
	return sum;
}
void swap(int x, int y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}
void pswap(int* px, int* py)
{
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}

void p1swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}


int main()
{
	int x = 10;
	int y = 5;

	int* px;
	int* py;

	//«аписываем адрес переменной x в px
	px = &x;

	cout << px << "  " << &x << endl; 

	cout << *px << "  " << x << endl;

	*px = 89;

	cout << *px   << endl;

	py = &y;

	cout << py << endl;

	py = px;

	cout << *px << " " << *py << "  " << x << endl << endl;

	cout << "---------------------------------------------" << endl;
	int a[10];
	int* pa;
	pa = &a[0]; // pa + 1 = a[1], pa - 1 = pa[0] pa-i, i - индекс массиа
	cout << "---------------------------------------------" << endl;

	const int size = 5;
	int arr[size] = { 22,33,44,55,66 };
	int* ptr = arr;

	cout << *ptr << endl;

	for (int i = 0; i < size; i++)
	{
		cout << *(ptr + i) << " ";
	}
	*(ptr + 1) = 55;
	*(ptr + 2) = 11;
	*(ptr + 3) = 11;
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << *(ptr + i) << " ";
	}
	cout << "---------------------------------------------" << endl;


	ShowArray(arr, size);
	cout << endl << endl;
	cout << GetAmout(arr, size) << endl << endl;

	ShowArray(&arr[0], size);
	cout << "---------------------------------------------" << endl;

	int av = 5, bv = 9;
	p1swap(&av, &bv);
	cout << av << " " << bv << endl;

	// NULL и nullptr
	// 0x00ded0f0efef0e 00000000000000001
	//int* prtr = 1;
	// if (ptr != 0) ......
	// // int *ptr = NULL; // c
	// int *ptr = nullptr; // C++
	//cout << *prtr;
	cout << "---------------------------------------------" << endl;
	/*
	  ”казатель не инициализирован
	  ¬ нем случайное значение
	*/
	int* ppp;
	ppp = 0; // C
	cout << ppp << endl;

	ppp = NULL;// ”старевший способ
	cout << ppp << endl; 

	ppp = nullptr; // »—ѕќЋ№«”≈ћ —++!!!!!
	cout << ppp << endl;
	if (ppp == nullptr)
	{
		cout << "\n Null pointer was found!\n" << endl;

	}
	return 0;



}

