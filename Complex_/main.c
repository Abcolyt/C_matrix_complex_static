#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<locale.h>
#pragma warning (disable: 4996)

#if 1
typedef struct Complex
{
	double R;
	double C;
}Complex;

struct Complex* add(Complex* S1, const Complex* S2) {
	S1->R = S1->R + S2->R;
	S1->C = S1->C + S2->R;
	return S1;
}
Complex* subtraction(Complex* S1, const Complex* S2) {
	S1->R = S1->R - S2->R;
	S1->C = S1->C - S2->C;
	return S1;
}
Complex* multiplicaion(Complex* S1, const Complex* S2) {
	S1->R = S1->R * S2->R - S1->C * S2->C;
	S1->C = S1->C * S2->R + S2->C * S1->R;
	return S1;
}
Complex* division(Complex* S1, Complex* S2) {
	double ZN = (S1->R * S1->R) + (S1->C * S2->C);

	S2->C = (S2->C) * (-1);
	multiplicaion(S1, S2);
	(S1->R) / ZN; (S1->C) / ZN;
	return S1;
}
int printC(const Complex* S1)
{
	printf("Real part: %lf\n", S1->R);
	printf("Imaginary part: %lf\n", S1->C);
	return 0;
}

int readC(const Complex* num) {
	printf("Enter real part(dot and numbers from 0 to 9): ");
	scanf("%lf", &num->R);
	printf("Enter imaginary part(dot and numbers from 0 to 9): ");
	scanf("%lf", &num->C);
	return 0;
}

#endif
int maijhgn() {

	Complex S1, S2;
	S1.R = 0; S1.C = 0; S2.R = 0; S2.C = 0;

	static char L = 'E';
	while (1) {

		printf("%s", "Enter Action('-','+','/','*','E') <");

		if (0 == scanf(" %c", &L))abort();
		getchar();
		if (L == 'E')
		{
			return 0;
		}
		readC(&S1);
		readC(&S2);
		switch (L)
		{
		case '+': printC(add(&S1, &S2)); break;
		case '-': printC(subtraction(&S1, &S2)); break;
		case '*': printC(multiplicaion(&S1, &S2)); break;
		case '/': printC(division(&S1, &S2)); break;
		default:abort();
		}

		//printC(&S1);
	}
	printf("%s", "ïîñëåäíåå ÷èñëî");
	printC(&S1);






#if 0
#define P 3.1415925
	struct coord
	{
		double x, y;
	}z;
	long i, j, n;
	double S = 0;
	srand((unsigned)time(0));
	setlocale(LC_ALL, "ru");
	printf("Êîë-âî ðåàëèçàöèé: \n");
	scanf("%d", &n);
	time_t beg_t = time(0), end_t;
	for (i = 0; i < n; i++) {
		z.x = (double)rand() / (double)RAND_MAX;
		z.y = (double)rand() / (double)RAND_MAX;
		z.x -= 0.5;
		z.y -= 0.5;
		if ((z.x * z.x + z.y * z.y) <= 0.25)S++;
	}
	end_t = time(0);
	printf("T=%5.2f sec\n", difftime(end_t, beg_t));
	printf("Pi=%10.8f\n", 4 * S / (double)n);

#endif

#if 0
	setlocale(LC_ALL, "ru");
	int i, n;
	double a, a1 = 1, a2 = 1;
	printf("Ñêîëüêî ÷èñåë");
	scanf("%d", &n);
	for (i = 3; i < n; i++) {
		a = a1 + a2;
		printf("i=%d\t\t\ta=%d\t\t\tx=%9.8f\n", i, (int)a, a / a2);
		a1 = a2;
	}
	printf("\n\nx=%9.8f\t\t1/x= %9.8f \t\t", (sqrt(5) - 1) / (double)2, 1 / ((sqrt(5) - 1) / (double)2));
	printf("x:(1-x)=%9.8f\n", (sqrt(5) - 1) / (double)2, 1 / ((sqrt(5) - 1) / (double)2));
#endif
	system("pause");
	return 0;
}