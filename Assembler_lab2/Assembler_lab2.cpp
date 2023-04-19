#include <iostream>

using namespace std;


int main()
{

	//(-153/b + d-4*a)/(1 +a*b);
	int a, b, d, x;
	x = 0;
	cout << "Enter a, b, d: ";
	cin >> a >> b >> d;
	_asm
	{
		mov eax, a
		mov ebx, b
		mov ecx, d

		; вычисление второй скобки

		imul eax, ebx; <edx:eax> = a * b
		inc eax; <eax> = a * b + 1
		adc edx, 0
		; jo error_of

		push eax; в стеке a* b + 1

		; вычисление первой скобки

		mov eax, a
		imul eax, -4; <edx:eax> = -4 * a
		add eax, ecx; <eax> = -4 * a + d
		push eax; в стеке - 4 * a + d
		mov eax, -153; <eax> = -153
		cdq; расширяем регистр <eax>
		idiv ebx; <eax> = -153 / b
		pop ebx; <ebx> = -4 * a + d
		add eax, ebx; -153 / b + d - 4 * a
		pop ecx; <ecx> = a * b + 1
		cdq
		idiv ecx; <eax> = (-153 / b + d - 4 * a) / (a * b + 1)
		mov x, eax

	}
	
	cout <<"asm: "<< x<< endl;
	cout << "C++: " << (int)(-153 / b + d - 4 * a) / (a * b + 1);
	return 0;


}