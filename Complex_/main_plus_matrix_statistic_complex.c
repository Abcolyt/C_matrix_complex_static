#if 1
#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<locale.h>
#include<stdbool.h>
//комплексные числа начало

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

void complex_calc() {

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







	system("pause");

}
//комплексные числа конец


//статистика начало
double MatOg(double* x, int size) {//с равно вероятными x[i]
	double ans = 0;
	for (int i = 0; i < size; i++)
	{
		ans += x[i];
	}
	return (ans / size);
}//https://ru.wikipedia.org/wiki/    Математическое_ожидание

//Функция для вычисления дисперсии массива :
double Despersion(double arr[], int size) {
	double m_value = MatOg(arr, size);
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += (arr[i] - m_value) * (arr[i] - m_value);
	}
	return sum / size;
}

//стандартное отклонение=sqrt(standart_devitetion)

double KofkorPirs(double x[], double y[], int n) {
	double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;

	for (int i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2 += x[i] * x[i];
		sum_y2 += y[i] * y[i];
	}
	double mean_x = sum_x / n;
	double mean_y = sum_y / n;
	double std_x = sqrt((sum_x2 - 2 * mean_x * sum_x + n * mean_x * mean_x) / n);
	double std_y = sqrt((sum_y2 - 2 * mean_y * sum_y + n * mean_y * mean_y) / n);

	return (n * sum_xy - sum_x * sum_y) / (sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y)));
}// https://wikimedia.org/api/rest_v1/media/math/render/svg/b87fab4bd95646a6aa894efe96e894761c94498f 

void Static()//задание на 17,11,23
{
	int s, size, i = 0;
	FILE* in, * out;

	if (NULL!=(in = fopen("in.txt", "r"))  && NULL != (out = fopen("out.txt", "w")))
	{

		fscanf(in, "%d", &size);//читаем первое число(количество пар рост вес)

		double* rIn = (double*)malloc(size * sizeof(double));//массив для ростов
		double* vIn = (double*)malloc(size * sizeof(double));//массив для весов

		while (i < size)
		{
			(fscanf(in, "%lf", &rIn[i]));//читаем и записываем очередное число в массив с ростами

			i++;
		}
		i = 0;
		while (i < size)
		{
			(fscanf(in, "%lf", &vIn[i]));//читаем и записываем очередное число в массив с весами

			i++;
		}

		fprintf(out, "MatOgidanie rost=%lf\nMatOgidanie ves=%lf\n", MatOg(rIn, size), MatOg(vIn, size));
		fprintf(out, "Despersion(rost)=%lf\Despersion(ves)=%lf\n", Despersion(rIn, size), Despersion(vIn, size));
		fprintf(out, "standard_deviation(rost)=%lf\nstandard_deviation(ves)=%lf\n", sqrt(Despersion(rIn, size)), sqrt(Despersion(vIn, size)));
		fprintf(out, "coef korrelatii pirsona=%lf\n", KofkorPirs(rIn, vIn, size));

		printf("MatOgidanie rost=%lf\nves=%lf\n", MatOg(rIn, size), MatOg(vIn, size));
		printf("Despersion(rost)=%lf\nDespersion(ves)=%lf\n", Despersion(rIn, size), Despersion(vIn, size));
		printf("standard_deviation(rost)=%lf\nstandard_deviation(ves)=%lf\n", sqrt(Despersion(rIn, size)), sqrt(Despersion(vIn, size)));
		printf("coef korrelacii pirsona=%lf\n", KofkorPirs(rIn, vIn, size));
		/*
	http://www.mathprofi.ru/linejnyj_koefficient_korrelyacii.html
	*/
		double rost_d, ves_d;
		char r_v_c;
		printf("vvedite rost ");
		scanf_s(" %lf", &rost_d);
		double a0, a1;

		a0 = MatOg(vIn, size) - (Despersion(vIn, size) / Despersion(rIn, size)) * KofkorPirs(rIn, vIn, size) * MatOg(rIn, size);

		a1 = (Despersion(vIn, size) / Despersion(rIn, size)) * KofkorPirs(rIn, vIn, size);
		printf("Vash ves?\n==%lf", (a0 + (a1 * rost_d)));

	}


	

	system("pause");

}
//статистика конец


//матрицы начало и решение слау начало
typedef struct matrix
{
	int number_of_str, number_of_columns;//str,colm
	double** Mptr;
}matrix;
#define matrix(out) matrix out; out.number_of_str=0;out.number_of_columns=0;out.Mptr = NULL; 
#define Dmatrix(out) matrix* out = (matrix*)malloc(sizeof(matrix)); out->number_of_str = 0; out->number_of_columns = 0; out->Mptr = NULL;
matrix* get_dM() {
	matrix* out = (matrix*)malloc(sizeof(matrix)); out->number_of_str = 0; out->number_of_columns = 0; out->Mptr = NULL;
}

//+
void print_M(matrix* M) {

	if (M->Mptr != NULL) {
		printf("![col][str]\n");
		for (int i = 0; i < (M->number_of_str); i++)
		{
			for (int j = 0; j < (M->number_of_columns); j++)
			{
				printf("M[%d][%d]=%lf\t", j, i, M->Mptr[j][i]);
			}printf("\n");
		}
		printf("ptr=%p number_of_str=%d number_of_columns= %d\n", M->Mptr, M->number_of_str, M->number_of_columns);
	}
}
//+
void scanf_M(matrix* M) {
	if (NULL != M->Mptr) {


		for (int i = 0; i < (M->number_of_str); i++)
		{
			for (int j = 0; j < (M->number_of_columns); j++)
			{
				scanf("%lf", &(M->Mptr[j][i]));
			}

		}

	}
}
//+
double** _M_malloc(int str, int column) {
	double** M = (double**)malloc(column * sizeof(double*) + column * str * sizeof(double));
	double* start = (double*)((char*)M + column * sizeof(double*));
	for (int i = 0; i < column; i++)
	{
		M[i] = ((start)+i * str);
	}
	return M;
}

extern void initM0(matrix* M, int str, int column);







//+
void get_copy_M(const matrix* M_out, matrix* M_in)//âîçâðàùàåò êîïèþ íà òîò 2 ìåðíûé ìàññèâ êîòîðûé áûë ïåðåäàí 1 ïàðàìåòðîì
{
	initM0(M_in, M_out->number_of_str, M_out->number_of_str);


	for (int i = 0; i < (M_in->number_of_str); i++)
	{
		for (int j = 0; j < (M_in->number_of_columns); j++)
		{
			M_in->Mptr[i][j] = M_out->Mptr[i][j];
		}
	}


}


//+
matrix* get_cut_M(const matrix* M_out, matrix* M_in, int nocolumn, int nostring)
{

	initM0(M_in, M_out->number_of_str - 1, M_out->number_of_columns - 1);
	for (int i, i_ = i = 0; i < (M_in->number_of_str); i_++, i++)
	{
		if (i == nocolumn) i_++;
		for (int j, j_ = j = 0; j < (M_in->number_of_columns); j_++, j++)
		{
			if (j == nostring)  j_++;
			(M_in->Mptr)[i][j] = M_out->Mptr[i_][j_];
		}
	}
	return M_in;
}

//+
void initM0(matrix* M, int str, int column)
{
	M->number_of_str = str;
	M->number_of_columns = column;
	if (NULL != (M->Mptr))free((M->Mptr));
	M->Mptr = _M_malloc(str, column);
	for (int i = 0; i < (M->number_of_str); i++)
	{
		for (int j = 0; j < (M->number_of_columns); j++)
		{
			M->Mptr[j][i] = 0;
		}
	}
}
//+

double det_Mn_n_1_iter(const double* M, const int n) //((double*)M, not working with struct matrix object
{
	double plus_ans = 0, minus_ans = 0;
	for (int i = 0; i < n; i++)
	{
		double pre_plus_ans = 1;
		for (int j = 0; j < n; j++) {
			pre_plus_ans *= M[((j + i) % n) * n + j];
		}
		plus_ans += pre_plus_ans;
	}

	for (int i = 0; i < n; i++)
	{
		double pre_minus_ans = 1;
		for (int j = 0; j < n; j++) {
			pre_minus_ans *= M[((j + i) % n) * n + (n - j - 1)];
		}
		minus_ans += pre_minus_ans;
	}

	return plus_ans - minus_ans;
}
//+
double det_Mn_n2_iter(const matrix* const M) {

	double plus_ans = 0, minus_ans = 0;
	for (int i = 0; i < M->number_of_columns; i++)
	{
		double pre_plus_ans = 1;
		for (int j = 0; j < M->number_of_str; j++)
		{
			pre_plus_ans *= M->Mptr[j][((j + i) % M->number_of_columns)];
		}
		plus_ans += pre_plus_ans;
	}

	for (int i = 0; i < M->number_of_columns; i++)
	{
		double pre_minus_ans = 1;
		for (int j = 0; j < M->number_of_str; j++)
		{
			pre_minus_ans *= (M->Mptr[(M->number_of_columns) - j - 1][(j + i) % M->number_of_columns]);
		}
		minus_ans += pre_minus_ans;
	}

	return plus_ans - minus_ans;
}


double det_Mn_n_recursion(const matrix* M) {
	double sum = 0;
	if ((M->number_of_str == 1) & (M->number_of_columns == 1)) {
		return (M->Mptr[0][0]);
	}
	if (M->number_of_str == 2) {
		return (M->Mptr[0][0] * M->Mptr[1][1] - M->Mptr[0][1] * M->Mptr[1][0]);
	}
	for (int i = 0; i < M->number_of_columns; i++) {
		//decomposition by 1 =[0] string
		matrix(M_in);
		sum += ((i % 2 == 0) ? 1 : -1) * (M->Mptr[i][0]) * det_Mn_n_recursion(get_cut_M(M, &M_in, i, 0));
		free(M_in.Mptr);
	}
	return sum;
}
void swap(double* n, double* m) {
	double t = *n; *n = *m; *m = t;
}
void transp_M(matrix* M) {

	for (int i = 0; i < M->number_of_columns; i++)
	{
		for (int j = i; j < M->number_of_str; j++)
		{
			swap(&(M->Mptr[i][j]), &(M->Mptr[j][i]));
		}
	}

}
void transp_M_all(matrix* M) {
	matrix(M_new)

		for (int i = 0; i < M->number_of_columns; i++)
		{
			for (int j = i; j < M->number_of_str; j++)
			{
				swap(&(M->Mptr[i][j]), &(M->Mptr[j][i]));
			}
		}

}
void get_UnM(const matrix* M_out, matrix* M_in) {

	initM0(M_in, M_out->number_of_str, M_out->number_of_columns);
	for (int i = 0; i < M_in->number_of_str; i++)
	{
		for (int j = 0; j < M_in->number_of_columns; j++)
		{
			matrix(M_preans)
				get_cut_M(M_out, &M_preans, j, i);
			//printf("str=%j\tcol=%i\n",j,i);
			//print_M(&M_preans);
			//printf("det[%j][%i]=%lf",j,i, det_Mn_n_recursion(&M_preans));
			(M_in->Mptr[j][i]) = (((i + j) % 2 == 1) ? -1 : 1) * det_Mn_n_recursion(&M_preans);
			free(M_preans.Mptr);
		}



	}
	transp_M(M_in);

}


//+
matrix* scalar_M_division(const matrix* M, double divisor) {
	for (int i = 0; i < M->number_of_columns; i++)
	{
		for (int j = 0; j < M->number_of_str; j++)
		{
			(M->Mptr[i][j]) /= divisor;
		}
	}
	return M;
}
//-
matrix* get_inverse_M(const matrix* M, matrix* b) {

	initM0(&b, M->number_of_columns, M->number_of_str);
	scalar_M_division(&b, det_Mn_n_recursion(M));



	return b;
}

//+
matrix* multiply_M(const matrix* const M, const matrix* const M2)//the first parameter has multiplication by columns, the second by rows
{
	if (M2->number_of_columns != M->number_of_str)
		return NULL;
	matrix* out = get_dM();
	initM0(out, M->number_of_str, M2->number_of_columns);
	for (int i = 0; i < M->number_of_str; i++)
	{
		for (int j = 0; j < M2->number_of_columns; j++)
		{
			for (int k = 0; k < M2->number_of_str; k++)
			{
				out->Mptr[i][j] += M2->Mptr[i][k] * M->Mptr[k][j];
			}
		}
	}
	return out;
}
//матрицы и решение слау конец

//вычисление через разложение в ряд
double expon_x(double degree, double accuracy) {
	double e = 1, ans = 0, n = 1;
	
	while (e > accuracy)
	{
		ans += e;
		e *=  (degree / n); 
		
		n++;
		printf("%lf\n", ans);
	}
	return ans;
}
//вычисление через разложение в ряд конец

//


//

//tests, not work
void tests() {

}
//

//код ниже обеспечивает работу всего выше написанного одновременно
enum TypeLogik //перечисление режимов работы)
{
	Test = -1,
	CramerMatrixSolver = 0,
	reversefinder = 1,
	complex_calculator=2,
	Statistc =3,
	Exponent_calc=4
};

typedef struct TpLg
{
	enum TypeLogik log;
} TpLg;
//

int main()
{

	TpLg l1;
	printf("CramerMatrixSolver(0) or reversefinder(1) or complex_calculator(2) or Statistc(3) or Exponent_calc(4) ?\n");
	scanf("%d", &l1.log);
	time_t beg_t=time(NULL), end_t;
	//printf("%d\n", l1.log);


	switch (l1.log)
	{
	case Test:tests(); break;
	case Exponent_calc: printf("degree?:"); double degree; scanf("%lf", &degree); printf("%-16.15lf", expon_x(degree, 1e-6)); break;
	case reversefinder: {
		int size = 2;
		printf("enter Marix size(int type ,the square matrix): ");
		scanf("%d", &size);

		matrix(a)
		matrix(b)
		initM0(&a, size, size);
		initM0(&b, size, size);

		printf("enter matrix elements");
		scanf_M(&a);
		print_M(&a);
		get_UnM(&a, &b);
		if (det_Mn_n_recursion(&a) != 0)
		{
			scalar_M_division(&b, det_Mn_n_recursion(&a));
			printf("the inverse matrix:\n");
			print_M(&b);
			printf("the original matrix multiplied by the inverse:\n");
			print_M(multiply_M(&a, &b));
		}
		else printf("error(det (M) =0)\n The matrix does not exist!!\n");
		break;
	}
	case CramerMatrixSolver:
	{
		int size = 2;

		printf("enter Marix size(int type,the square matrix): ");
		scanf("%d", &size);
		matrix(a)
			matrix(b)
			initM0(&a, size, size);
		initM0(&b, size, size);
		printf("enter matrix elements\n");
		scanf_M(&a);
		
		if (det_Mn_n_recursion(&a) != 0) {
			printf("+\n");
			matrix(free_members);
			initM0(&free_members, 1, size);
			get_copy_M(&a, &b);
			scanf_M(&free_members);
			for (int j = 0; j < size; j++)
			{
				get_copy_M(&a, &b);
				for (int i = 0; i < size; i++) {

					b.Mptr[j][i] = free_members.Mptr[i][0];//вставляем в массив а столбец свободных коэффициентов

				}
				printf("%lf\n", (det_Mn_n_recursion(&b) / det_Mn_n_recursion(&a)));
			}

			break;
		}
		else printf("error(det (M) =0)\n");

	}
	case complex_calculator: 
	{ complex_calc(); break; }
	case Statistc: {Static(); break; }
	default:
		printf("%s", "unknown command");
		return 666666;
	}






	end_t = time(NULL);

	printf("\nwork_time=%5.2lfsec\n",difftime(end_t,beg_t));
	system("pause");
	return 0;
}
#endif