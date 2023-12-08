#if 78655
#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<locale.h>
typedef struct matrix
{
	int number_of_str, number_of_columns;//str,colm
	double** Mptr;
}matrix;
#define matrix(out) matrix out; out.number_of_str=0;out.number_of_columns=0;out.Mptr = NULL; 


//+
void print_M(matrix *M) {

	if (M->Mptr != 0) {
		printf("str,col\n");
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

double** _M_malloc(int column, int str);
void get_copy_M(const matrix *M_out, matrix *M_in);
void initM0(matrix* M, int str, int column);
//matrix* add_M(matrix* a, matrix* b);
//matrix* multiplicaion_M(matrix* a, matrix* b);






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

//void get_cut_M(const matrix *M_out, matrix *M_in,int nox,int noy)//âîçâðàùàåò êîïèþ íà òîò 2 ìåðíûé ìàññèâ êîòîðûé áûë ïåðåäàí 1 ïàðàìåòðîì
//{
//	initM0(M_in, M_out->number_of_str-1, M_out->number_of_str-1);
//	for (int i, i_=i =( (0 != noy) ?0 :1 ); i < (M_in->number_of_str); i_++,i++)
//	{
//		if (i == noy) {i_+=2; continue;}
//		for (int j, j_=j = ((0 != nox) ? 0 : 1);  j < (M_in->number_of_columns); j_++,j++)
//		{
//			if (j == nox) { j_+=2; continue; }
//			(M_in->Mptr)[i][j] = M_out->Mptr[i_][j_];
//		}
//	}
//
//}

void get_cut_M(const matrix *M_out, matrix *M_in, int nox, int noy)
{
	initM0(M_in, M_out->number_of_str - 1, M_out->number_of_columns - 1);
	for (int i, i_ = i = 0; i < (M_in->number_of_str); i_++, i++)
	{
		if (i == noy) i_++;
		for (int j, j_ = j = 0; j < (M_in->number_of_columns); j_++, j++)
		{
			if (j == nox)  j_++;
			(M_in->Mptr)[i][j] = M_out->Mptr[i_][j_];
		}
	}
}

//+
void initM0(matrix* M, int str, int column) 
{
	M->number_of_str = str;
	M->number_of_columns = column;
	if(NULL!=M->Mptr )free((M->Mptr));
	M->Mptr = _M_malloc(str, column);
	for (int i = 0; i < (M->number_of_str); i++)
	{
		for (int j = 0; j < (M->number_of_columns); j++)
		{
			M->Mptr[i][j] =0;
		}
	}
}


int main()
{

	matrix(out);

	initM0(&out, 3, 3);
	print_M(&out);
	scanf_M(&out);
	matrix(M2);
	print_M(&M2);
	print_M(&out);

	get_cut_M(&out,&M2,3,0);
	print_M(&M2);
	print_M(&out);
	system("pause");
	return 0;
}
#endif