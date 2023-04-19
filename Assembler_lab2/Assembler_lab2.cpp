#include <iostream>

using namespace std;


int main()
{

	//(-153/b + d-4*a)/(1 +a*b);
	int a, b, d, x, error;
	error = 1;
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
		jo of_error;
		inc eax; <eax> = a * b + 1
		jz zero_error;
		jo of_error;
		

		push eax; в стеке a* b + 1

		; вычисление первой скобки

		mov eax, a
		imul eax, -4; <edx:eax> = -4 * a
		jo of_error;
		add eax, ecx; <eax> = -4 * a + d
		jo of_error;
		push eax; в стеке - 4 * a + d
		mov eax, -153; <eax> = -153
		or ebx, ebx;
		jz zero_error;
		cdq; расширяем регистр <eax>
		idiv ebx; <eax> = -153 / b
		pop ebx; <ebx> = -4 * a + d
		add eax, ebx; -153 / b + d - 4 * a
		jo of_error;
		pop ecx; <ecx> = a * b + 1
		cdq
		idiv ecx; <eax> = (-153 / b + d - 4 * a) / (a * b + 1)
		mov x, eax

		jmp end_if

		of_error :
			mov error, -1;
			jmp end_if;

		zero_error:
			mov error, 0;
			jmp end_if

		end_if :

	}
	 
	if (error == 0) cout << "division by zero" << endl;
	if (error == -1) cout << "overflow" << endl;
	if (error == 1) {
		cout << "asm: " << x << endl;
		cout << "C++: " << (int)(-153 / b + d - 4 * a) / (a * b + 1) << endl;
	}
	

	return 0;
}
