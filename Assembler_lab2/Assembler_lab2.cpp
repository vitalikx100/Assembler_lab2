#include <iostream>

using namespace std;

int calc(int a, int b, int d, double s)
{
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
		mov ?, -153;
		cdq
		idiv ebx
		add eax, ? 


		

	}

}

int main()
{

	//(-153/b + d-4*a)/(1 +a*b);
	int a, b, d, s;
	s = 0;
	cin >> a >> b >> d;
	calc(a, b, d, s);
	cout << s;
	return 0;


}