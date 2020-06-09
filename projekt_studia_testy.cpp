#include <stdio.h>
#include<stdlib.h>
#include<math.h> 
#include <cctype>
#include <iostream>
#include <cstring>
FILE* plik1, * plik2, * plikGA, * plikGH;
using namespace std;

float obliczanie_temp(float **grupa,int wiersz, float liczba)
{
	float w0, w1, w2, w3, w4, w5, w6,temperatura_ob;
	///temperatura[i][0] = grupaA[4][0] + grupaA[4][1] * 1000 / tab[i][3] + grupaA[4][2] * pow(1000 / tab[i][3], 2) + grupaA[4][3] * pow(1000 / tab[i][3], 3) + grupaA[4][4] * pow(1000 / tab[i][3], 4) + grupaA[4][5] * pow(1000 / tab[i][3], 5) + grupaA[4][6] * pow(1000 / tab[i][3], 6);
	w0 = grupa[wiersz][0];
	w1 = grupa[wiersz][1];
	w2 = grupa[wiersz][2];
	w3 = grupa[wiersz][3];
	w4 = grupa[wiersz][4];
	w5 = grupa[wiersz][5];
	w6 = grupa[wiersz][6];
	temperatura_ob = w0 + w1 * 1000 / liczba + w2 * pow(1000 / liczba, 2) + w3 * pow(1000 / liczba, 3) + w4 * pow(1000 / liczba, 4) + w5 * (1000 / liczba, 5) + w6 * pow(1000 / liczba, 6);
	return temperatura_ob;
}
int main()
{
	float** tab;
	int i, k, l, n = 0, m = 0;
	errno_t err;

	err = fopen_s(&plik1, "C:\\Users\\user\\Desktop\\C++\\Projekt_studia\\Materialy\\Char_T_R_2.txt", "r");
	char znak;
	if (err == 0)
	{
		printf("Odczyt uzyskany\n");
	}
	else
	{
		printf("Odczyt zabroniony \n");
	}


	while ((znak = getc(plik1)) != EOF)
	{
		if (znak == '\n')
			n++;
		if (isspace(znak))
			m++;
	}
	// założenie: każda kolumna jest poprzedzona spacja
	m = m / n - 1;
	printf("Plik zawiera %d wiersze oraz %d kolumn\n", n, m);

	tab = (float**)malloc(n * sizeof(float*));
	for (i = 0; i < n; i++)
	{
		tab[i] = (float*)malloc(m * sizeof(float));
	}

	rewind(plik1);

	for (k = 0;k < n;k++)
	{
		for (l = 0; l < m; l++)
		{
			fscanf_s(plik1, "%f", &tab[k][l]);

		}

	}

	/* Wyznaczanie temperatur za pomocą współczynników z dodatkowych plików oraz rezystancji z "głównej" tablicy
	*/

	int GW = 0, GK = 0;
	float** grupaA;


	err = fopen_s(&plikGA, "C:\\Users\\user\\Desktop\\C++\\Projekt_studia\\Materialy\\grupaA.txt", "r");
	while ((znak = fgetc(plikGA)) != EOF)
	{
		if (znak == '\n')
			GW++;
		if (isspace(znak))
			GK++;
	}
	GK = GK / GW;

	printf("Plik zawiera %d wiersze oraz %d kolumn\n", GW, GK);


	grupaA = (float**)malloc(GW * sizeof(float*));
	for (i = 0; i < GW; i++)
	{
		grupaA[i] = (float*)malloc(GK * sizeof(float));
	}

	rewind(plikGA);

	for (k = 0; k < GW; k++)
	{
		for (l = 0; l < GK;l++)
		{
			fscanf_s(plikGA, "%f", &grupaA[k][l]);
			///printf("%f ", grupaA[k][l]);
		}
		///printf(" \n");
	}


	/*Otwieranie pliku z grupą H*/


	float** grupaH;
	GW = 0;
	GK = 0;

	err = fopen_s(&plikGH, "C:\\Users\\user\\Desktop\\C++\\Projekt_studia\\Materialy\\grupaH.txt", "r");
	while ((znak = fgetc(plikGH)) != EOF)
	{
		if (znak == '\n')
			GW++;
		if (isspace(znak))
			GK++;
	}
	GK = GK / GW;

	printf("Plik zawiera %d wiersze oraz %d kolumn\n", GW, GK);


	grupaH = (float**)malloc(GW * sizeof(float*));
	for (i = 0; i < GW; i++)
	{
		grupaH[i] = (float*)malloc(GK * sizeof(float));
	}

	rewind(plikGH);

	for (k = 0; k < GW; k++)
	{
		for (l = 0; l < GK;l++)
		{
			fscanf_s(plikGH, "%f", &grupaH[k][l]);
			///printf("%f ", grupaH[k][l]);
		}
		///printf(" \n");
	}
	/// Uzyte czujniki R1 - 6A (4), R2 - 7A (5), R3 - 8A (6), R4 - 8H (6)
	double** temperatura;
	int nczujnikow;

	nczujnikow = 4;
	temperatura = (double**)malloc(n * sizeof(double*));
	for (i = 0; i < n; i++)
	{
		temperatura[i] = (double*)malloc(nczujnikow * sizeof(double));
	}
	/*for (i = 0;i < n;i++)
	{
		temperatura[i][0] = grupaA[4][0] + grupaA[4][1] * 1000 / tab[i][3] + grupaA[4][2] * pow(1000 / tab[i][3], 2) + grupaA[4][3] * pow(1000 / tab[i][3], 3) + grupaA[4][4] * pow(1000 / tab[i][3], 4) + grupaA[4][5] * pow(1000 / tab[i][3], 5) + grupaA[4][6] * pow(1000 / tab[i][3], 6);
		temperatura[i][1] = grupaA[5][0] + grupaA[5][1] * 1000 / tab[i][4] + grupaA[5][2] * pow(1000 / tab[i][4], 2) + grupaA[5][3] * pow(1000 / tab[i][4], 3) + grupaA[5][4] * pow(1000 / tab[i][4], 4) + grupaA[5][5] * pow(1000 / tab[i][4], 5) + grupaA[5][6] * pow(1000 / tab[i][4], 6);
		temperatura[i][2] = grupaA[6][0] + grupaA[6][1] * 1000 / tab[i][5] + grupaA[6][2] * pow(1000 / tab[i][5], 2) + grupaA[6][3] * pow(1000 / tab[i][5], 3) + grupaA[6][4] * pow(1000 / tab[i][5], 4) + grupaA[6][5] * pow(1000 / tab[i][5], 5) + grupaA[6][6] * pow(1000 / tab[i][5], 6);
		temperatura[i][3] = grupaH[0][6] + grupaH[1][6] * 1000 / tab[i][5] + grupaH[2][6] * pow(1000 / tab[i][5], 2) + grupaH[3][6] * pow(1000 / tab[i][5], 3) + grupaH[4][6] * pow(1000 / tab[i][5], 4) + grupaH[5][6] * pow(1000 / tab[i][5], 5) + grupaH[6][6] * pow(1000 / tab[i][5], 6);

	}*/
	for(i = 0; i < n; i++ )
	{
		temperatura[i][0] = obliczanie_temp(grupaA, 4, tab[i][3]);
		temperatura[i][1] = obliczanie_temp(grupaA, 5, tab[i][4]);
		temperatura[i][2] = obliczanie_temp(grupaA, 6, tab[i][5]);
		temperatura[i][3] = grupaH[0][6] + grupaH[1][6] * 1000 / tab[i][5] + grupaH[2][6] * pow(1000 / tab[i][5], 2) + grupaH[3][6] * pow(1000 / tab[i][5], 3) + grupaH[4][6] * pow(1000 / tab[i][5], 4) + grupaH[5][6] * pow(1000 / tab[i][5], 5) + grupaH[6][6] * pow(1000 / tab[i][5], 6);
	}

	/* ##### dodatkowa tablica, manipulowanie danymi z tablicy oraz tworzenie pliku #####
	0-czas 1-prąd 2-napięcie 3-R1 4-R2 5-R3 6-R4									#####	*/

	double* rez, * b_rez, b_A, b_V;

	rez = (double*)malloc(n * sizeof(double));
	b_rez = (double*)malloc(n * sizeof(double));

	for (i = 0;i < n;i++)
	{
		rez[i] = tab[i][2] / tab[i][1];

		b_A = tab[i][1] * 0.0005 + 0.00005;  //błąd natężenia prądu
		b_V = tab[i][2] * 0.000035 + 0.0000006; //błąd napięcia
		b_rez[i] = sqrt(pow(1 / tab[i][1] * b_V, 2) + pow(tab[i][2] / (pow(tab[i][1], 2)) * b_A, 2)); //obliczanie błędu rezystancji
		//printf("Rezystancja %d: %f +/- %f\n", i, rez[i], b_rez[i]);
	}

	err = fopen_s(&plik2, "C:\\Users\\user\\Desktop\\C++\\Projekt_studia\\zapis_ze_skryptu_2.txt", "w");
	fprintf(plik2, "Rez [Ohm]	B_rez [Ohm]	 T1[K]	 T2[K]	  T3[k]	   T4[K]\n");
	for (i = 0; i < (n - 1); i++)
	{
		fprintf(plik2, "%f	%f	%.5f %.5f %.5f %.5f\n", rez[i], b_rez[i], temperatura[i][0], temperatura[i][1], temperatura[i][2], temperatura[i][3]);
	}



	/*##### Bezpieczne zamknięcie programu ##### */
	free(rez);
	free(b_rez);
	for (i = 0; i < GW; i++)
	{
		free(grupaA[i]);
	}
	free(grupaA);
	for (i = 0;i < n; i++)
	{
		free(tab[i]);
	}
	free(tab);
	for (i = 0; i < n; i++)
	{
		free(temperatura[i]);
	}
	free(temperatura);
	int numclosed = _fcloseall();
	printf("Liczba zamknietych plikow: %u\n", numclosed);


	return 0;
}