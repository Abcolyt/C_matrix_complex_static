#if 78655
#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<locale.h>
#include<stdbool.h>
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
void print_M(matrix *M) {

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
void get_copy_M(const matrix *M_out,matrix *M_in)//âîçâðàùàåò êîïèþ íà òîò 2 ìåðíûé ìàññèâ êîòîðûé áûë ïåðåäàí 1 ïàðàìåòðîì
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
matrix* get_cut_M(const matrix *M_out, matrix *M_in, int nocolumn, int nostring )
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
	if(NULL!=(M->Mptr) )free((M->Mptr));
	M->Mptr = _M_malloc(str, column);
	for (int i = 0; i < (M->number_of_str); i++)
	{
		for (int j = 0; j < (M->number_of_columns); j++)
		{
			M->Mptr[j][i] =0;
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
double det_Mn_n2_iter(const matrix *const M) {

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
			pre_minus_ans *= (M->Mptr[(M->number_of_columns) - j - 1 ][(j + i) % M->number_of_columns]);
		}
		minus_ans += pre_minus_ans;
	}

	return plus_ans - minus_ans;
}


double det_Mn_n_recursion(const matrix* M) {
	double sum = 0;
	if (M->number_of_str == 1) {
		return (M->Mptr[0][0]);
	}
	if ( M->number_of_str ==2) {
		return (M->Mptr[0][0] * M->Mptr[1][1] - M->Mptr[0][1] * M->Mptr[1][0]);
	}
	for (int i = 0; i < M->number_of_columns; i++) {
		//decomposition by 1 =[0] string
		matrix(M_in);
		sum+=((i%2==0)? 1 : -1)*(M->Mptr[i][0])*det_Mn_n_recursion(get_cut_M(M,&M_in,i,0));
		free(M_in.Mptr);
	}
	return sum;
}
void swap(double *n, double *m) {
	double t = *n; *n = *m; *m = t;
}
void transp_M(matrix *M) {

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
void get_UnM(const matrix *M_out,matrix *M_in) {

	initM0(M_in, M_out->number_of_str, M_out->number_of_columns);
	for (int i = 0; i <M_in->number_of_str ; i++)
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
matrix* scalar_M_division(const matrix* M,double divisor ) {
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
matrix* get_inverse_M(const matrix* M, matrix *b) {

	initM0(&b,M->number_of_columns, M->number_of_str);
	scalar_M_division(&b, det_Mn_n_recursion(M));
	
	
		
	return b;
}

//+
matrix* multiply_M(const matrix* const M, const matrix* const M2)//the first parameter has multiplication by columns, the second by rows
{	
	if (M2->number_of_columns != M->number_of_str)
		return NULL;
	matrix*out=get_dM();
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


#define obratka_s_proverkoy {matrix(a) matrix(b) int size = 2;initM0(&a, size, size);initM0(&b, size, size);scanf_M(&a);print_M(&a);get_UnM(&a, &b);if (det_Mn_n_recursion(&a)!=0){ scalar_M_division(&b, det_Mn_n_recursion(&a));printf("the inverse matrix:\n");print_M(&b);printf("the original matrix multiplied by the inverse:\n");print_M(multiply_M(&a, &b));} else printf("error(det (M) =0)\n The matrix does not exist!!\n");}
int main()
{
	matrix(M_left)
	initM0(&M_left,1,3);


	scanf_M(&M_left);
	print_M(&M_left);
	matrix(M_right)
	initM0(&M_right, 3, 1);


	scanf_M(&M_right);
	print_M(&M_right);
	transp_M(&M_right);
	print_M(multiply_M(  &M_right, &M_left));

	//det_Mn_n_recursion(&M_left);

 


	system("pause"); 
	return 0;
}
#endif