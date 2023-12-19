#if 0
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#pragma warning(disable:4996)

double MatOg(double* x, int size) {//ñ ðàâíî âåðîÿòíûìè x[i]
	double ans = 0;
	for (int i = 0; i < size; i++)
	{
		ans += x[i];
	}
	return (ans / size);
}//https://ru.wikipedia.org/wiki/    Ìàòåìàòè÷åñêîå_îæèäàíèå

//Ôóíêöèÿ äëÿ âû÷èñëåíèÿ äèñïåðñèè ìàññèâà :
double Despersion(double arr[], int size) {
	double m_value = MatOg(arr, size);
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += (arr[i] - m_value) * (arr[i] - m_value);
	}
	return sum / size;
}

//ñòàíäàðòíîå îòêëîíåíèå=sqrt(standart_devitetion)

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
	/*FILE* out = fopen("out.txt", "w");
	fprintf(out, "dispersia x=%lf\ndispersia y=%lf\n", (sum_x2 - sum_x * sum_x) / n, (sum_y2 - sum_y * sum_y) / n);
	printf("dispersia x=%lf\ndispersia y=%lf\n", (sum_x2 - sum_x * sum_x), (sum_y2 - sum_y * sum_y));
	fprintf(out, "standartnoe otclonenie x=%lf\nstandartnoe otclonenie y=%lf\n", sqrt((sum_x2 - sum_x * sum_x) / n), sqrt((sum_y2 - sum_y * sum_y) / n));
	printf("standartnoe otclonenie x=%lf\nstandartnoe otclonenie y=%lf\n", sqrt((sum_x2 - sum_x * sum_x) / n), sqrt((sum_y2 - sum_y * sum_y) / n));*/

	return (n * sum_xy - sum_x * sum_y) / (sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y)));
}//https://wikimedia.org/api/rest_v1/media/math/render/svg/b87fab4bd95646a6aa894efe96e894761c94498f 

void Static()//çàäàíèå íà 17,11,23
{
	int s, size, i = 0;
	FILE* in, * out;

	if ((in = fopen("in.txt", "r")) != NULL && NULL != (out = fopen("out.txt", "w")))
	{

		fscanf(in, "%d", &size);//÷èòàåì ïåðâîå ÷èñëî(êîëè÷åñòâî ïàð ðîñò âåñ)

		double* rIn = (double*)malloc(size * sizeof(double));//ìàññèâ äëÿ ðîñòîâ
		double* vIn = (double*)malloc(size * sizeof(double));//ìàññèâ äëÿ âåñîâ

		while (i < size)
		{
			(fscanf(in, "%lf", &rIn[i]));//÷èòàåì è çàïèñûâàåì î÷åðåäíîå ÷èñëî â ìàññèâ ñ ðîñòàìè

			i++;
		}
		i = 0;
		while (i < size)
		{
			(fscanf(in, "%lf", &vIn[i]));//÷èòàåì è çàïèñûâàåì î÷åðåäíîå ÷èñëî â ìàññèâ ñ âåñàìè

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
		printf("vvedite rost");
		scanf_s(" %lf", &rost_d);
		double a0, a1;

		a0 = MatOg(vIn, size) - (Despersion(vIn, size) / Despersion(rIn, size)) * KofkorPirs(rIn, vIn, size) * MatOg(rIn, size);

		a1 = (Despersion(vIn, size) / Despersion(rIn, size)) * KofkorPirs(rIn, vIn, size);
		printf("Vash ves?\n==%lf", (a0 + (a1 * rost_d)));

	}


	
	system("pause");

}

int main() {
	Static();
	return 0;
}
#endif