#include <iostream>
#include "ExampleHeader.h"

using namespace std;

void WriteSomething()
{
	cout << "Huhu" << endl;
}

//void WriteSomethingElse(); // Forward Declaration

void Func(int a, int& r);
void Func2(int* pA);
void Func3(int* arr, int length);
void FuncPointerInst(int* pI, int** ppI);

int main()
{
	cout << "Hello World" << endl;
	cout << 10 << endl;

	float f = 12345.6789f;
	cout << f << endl;

	cout << "int size: " << sizeof(int) << endl;
	cout << "long size: " << sizeof(long) << endl;
	cout << "long long size: " << sizeof(long long) << endl;

	cout << "float size: " << sizeof(float) << endl;
	cout << "double size: " << sizeof(double) << endl;
	cout << "long double size: " << sizeof(long double) << endl;

	WriteSomething();
	WriteSomethingElse();

	float& refF = f; // reference defintion // & - reference operator
	refF = 5.0f;

	int a = 0;
	int b = 0;
	Func(a, b);
	
	float* pF = nullptr; // pointer definition
	pF = &f; // & - address operator
	*pF = 1.0f; // * - dereference operator

	int c = 0;
	Func2(&c);

	int* pI = new int;
	Func2(pI);

	delete pI;
	pI = nullptr;

	int ints[10];
	ints[0] = 10;
	ints[1] = 20;
	for (int i = 0; i < 10; i++)
	{
		ints[i] = i * 10;
	}

	Func3(ints, 10);

	// c++ casts
	//(int) // old c-cast, don't use it
	//dynamic_cast<B*>(obj) // polymorph cast
	//static_cast<int>(n) // type conversion
	//const_cast<int>(cn) // convert a const value into a non const value
	//reinterpret_cast<int*>(pN) // reintepretation of byte order

	// pointer pointer
	int* pLocalI = nullptr;
	int* pLocalI2 = nullptr;
	FuncPointerInst(pLocalI, &pLocalI2);

	return 0;
}

void FuncPointerInst(int* pI, int** ppI)
{
	pI = new int(10);
	*ppI = new int(100);
}

void WriteSomethingElse()
{
	cout << "Haha" << endl;
}

void Func(int a, int& r) // & - reference operator
{
	a = 10;
	r = 20;
}

void Func2(int* pA)
{
	*pA = 30;
}

void Func3(int arr[], int length)
{
	arr[0] = 100;
}
