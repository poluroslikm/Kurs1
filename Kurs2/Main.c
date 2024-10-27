#define _CRT_SECURE_NO_WARNINGS
#define D 102
#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>
int saper()
{
	int d1, d2, saper[D][D], b, c1, c2;
	for (;;)
	{
		printf("Введите длину поля (макс 100)\n");
		scanf("%d", &d1);
		if (d1 > D-2)
		{
			printf("Поле превысило максимальный размер\n");
		}
		else break;
	}
	for (;;)
	{
		printf("Введите ширину поля (макс 100)\n");
		scanf("%d", &d2);
		if (d2 > D - 2)
		{
			printf("Поле превысило максимальный размер\n");
		}
		else break;
	}
	for (;;)
	{
		printf("Введите количество бомб\n");
		scanf("%d", &b);
		if (b > d1 * d2)
		{
			printf("Количество бомб больше размера поля\n");
		}
		else break;
	}
	for (int i1 = 1; i1 <= d1; i1++)
		for (int i2 = 1; i2 <= d2; i2++)
			saper[i1][i2] = 0;
	for (int i = 1; i <= b;)
	{
		c1 = 1+ rand() % (d1);
		c2 = 1+ rand() % (d2);
		if (saper[c1][c2] < 10)
		{
			saper[c1][c2] = 20;
			for (int u1 = c1 - 1; u1 <= c1 + 1; ++u1)
				for (int u2 = c2 - 1; u2 <= c2 + 1; ++u2)
					saper[u1][u2] += 1;
			i++;
		}
	}
	printf(" _");
	for (int i2 = 1; i2 <= d2; i2++) printf("__");
	printf("\n");
	for (int i1 = 1; i1 <= d1; i1++)
	{
		printf("| ");
		for (int i2 = 1; i2 <= d2; ++i2)
		{
			if (saper[i1][i2] == 0) printf("  ");
			if ((saper[i1][i2] != 0) && (saper[i1][i2] < 9)) printf("%d ", saper[i1][i2]);
			if (saper[i1][i2] > 9) printf("* ");
		}
		printf("|\n");
	}
	FILE* pFile;
	pFile = fopen("myfile.txt", "w");
	fprintf(pFile, " _");
	for (int i2 = 1; i2 <= d2; i2++) fprintf(pFile, "__");
	fprintf(pFile, "\n");
	for (int i1 = 1; i1 <= d1; i1++)
	{
		fprintf(pFile, "| ");
		for (int i2 = 1; i2 <= d2; ++i2)
		{
			if (saper[i1][i2] == 0) fprintf(pFile, "  ");
			if ((saper[i1][i2] != 0) && (saper[i1][i2] < 9)) fprintf(pFile, "%d ", saper[i1][i2]);
			if (saper[i1][i2] > 9) fprintf(pFile, "* ");
		}
		fprintf(pFile, "|\n");
	}
	fclose(pFile);
}
void main()
{
	setlocale(LC_CTYPE, "RUS");
	saper();
	for (;;) 
	{
		char a;
		printf("Сгенировать новое поле? (Да - y, Нет - n): ");
		scanf(" %c", &a);
		if (a == 'n') break;
		if (a == 'y') saper(); else printf("Неизвестная операция\n");
	}
}