#define _CRT_SECURE_NO_WARNINGS
#define D 102
#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>
#include <time.h>
int cleaning(int saper[D][D], int d1, int d2)
{
	for (int i1 = 1; i1 <= d1; i1++) //сбросить поле, потом на функцию заменить
		for (int i2 = 1; i2 <= d2; i2++)
			saper[i1][i2] = 0;
}
int bomb(int saper[D][D], int c1, int c2)
{
		saper[c1][c2] = 20;
		for (int u1 = c1 - 1; u1 <= c1 + 1; ++u1)
			for (int u2 = c2 - 1; u2 <= c2 + 1; ++u2)
				saper[u1][u2] += 1;
}
int generation(int saper[D][D], int d1, int d2)
{
	printf(" _");
	for (int i2 = 1; i2 <= d2; i2++) printf("__"); //верхняя граница в консоли
	printf("\n");
	for (int i1 = 1; i1 <= d1; i1++)
	{
		printf("| "); //левая граница в консоли
		for (int i2 = 1; i2 <= d2; ++i2)
		{
			if (saper[i1][i2] == 0) printf("  ");
			if ((saper[i1][i2] != 0) && (saper[i1][i2] < 9)) printf("%d ", saper[i1][i2]);
			if (saper[i1][i2] > 9) printf("* "); //генерация поля
		}
		printf("|\n"); //правая граница в консоли
	}
}
int saper(FILE* saperFile, short int random)
{
	srand(time(0));
	int d1, d2, saper[D][D], b, c1, c2, k=1;
	if (random == 2)
	{
		for (;;)
		{
			printf("Введите количество полей                  >  ");
			scanf("%d", &k);
			if (k <= 0)
				printf("Количество полей должно быть больше 0 \n");
			else
				break;
		}
	} //генерация количества полей при 2 пункте
	for (;;)
	{
		printf("Введите длину поля       (максимум   100) >  ");
		scanf("%d", &d1);
		if (d1 > D-2)
			printf("Поле превысило максимальный размер\n");
		else 
			if (d1 < 1)
			printf("Размер поля не может быть меньше 1\n"); 
		else 
			break;
	} //генерация длины поля
	for (;;)
	{
		printf("Введите ширину поля      (максимум   100) >  ");
		scanf("%d", &d2);
		if (d2 > D - 2)
			printf("Поле превысило максимальный размер\n");
		else 
			if (d2 < 1)
			printf("Размер поля не может быть меньше 1\n");
		else 
			break;
	} //генерация ширины поля
	for (;;)
	{
		printf("Введите количество бомб  (максимум %5.d) >  ", d1*d2);
		scanf("%d", &b);
		if (b > d1 * d2)
			printf("Количество бомб больше размера поля\n");
		else 
			if (d1 < 1)
			printf("Количество бомб не может быть меньше 1\n");
		else 
			break;
	} //генерация количества бомб
	cleaning(saper, d1, d2); //сбросить поле
	if (random == 0) //если 3 пункт
	{
		for (int bm = 0; bm < b;)
		{
			for (;;)
			{
				printf("Введите координату бомбы (максимум %5.d) >  ", d1);
				scanf("%d", &c1);
				if ((c1 > d1) || (c1 < 0))
					printf("Координата выходит за рамки поля\n");
				else 
					break;
			} //первая корда при 3 пункте
			for (;;)
			{
				printf("Введите координату бомбы (максимум %5.d) >  ", d2);
				scanf("%d", &c2);
				if ((c2 > d2) || (c2 < 0))
					printf("Координата выходит за рамки поля\n");
				else 
					break;
			} //вторая корда при 3 пункте
			if (saper[c1][c2] < 10)
			{
				bomb(saper, c1, c2);
				bm++;
				printf("Бомба установлена\n");
				if (bm<b)
				generation(saper, d1, d2);
			} //установка бомбы и цифр, потом на функцию заменить
			else printf("По этим координатам уже установлена бомба\n");
		}
	}
	 for (int l = 0; l < k; l++) //количество полей, изначально 1
	 {
		 if (random > 0) //сбросить поле
			 cleaning(saper, d1, d2);
		if (random > 0) for (int i = 1; i <= b;)
		{
			c1 = 1 + rand() % (d1);
			c2 = 1 + rand() % (d2); //рандом корд
			if (saper[c1][c2] < 10)
			{
				bomb(saper, c1, c2);
				i++;
			}//установка бомбы и цифр, потом на функцию заменить
		}
		generation(saper, d1, d2); //отрисовка полей
		//все тоже самое для txt
		fprintf(saperFile, " _");
		for (int i2 = 1; i2 <= d2; i2++) fprintf(saperFile, "__");
		fprintf(saperFile, "\n");
		for (int i1 = 1; i1 <= d1; i1++)
		{
			fprintf(saperFile, "| ");
			for (int i2 = 1; i2 <= d2; ++i2)
			{
				if (saper[i1][i2] == 0) fprintf(saperFile, "  ");
				if ((saper[i1][i2] != 0) && (saper[i1][i2] < 9)) fprintf(saperFile, "%d ", saper[i1][i2]);
				if (saper[i1][i2] > 9) fprintf(saperFile, "* ");
			}
			fprintf(saperFile, "|\n");
		}
	}
}
void main()
{
	FILE* saperFile;
	short int random;
	saperFile = fopen("saper.txt", "w");
	setlocale(LC_CTYPE, "RUS");
	//saper(saperFile);
	for (short int br=0;br!=1;) //Повторение программы
	{
		char task;
		printf("Введите \"1\", если хотите сгенерировать одно поле\n");
		printf("Введите \"2\", если хотите сгенерировать несколько полей\n");
		printf("Введите \"3\", если хотите задать поле вручную\n");
		printf("Введите \"4\", если хотите прекратить программу\n");
		printf("Выполнить                               >>>  ");
		//printf("Сгенировать новое поле? (Да - 1, Нет - 2) > ");
		scanf(" %c", &task);
		getchar();
		switch (task)
		{
		case '1':
			random = 1;
			saper(saperFile, random);
			break;
		case '2':
			random = 2;
			saper(saperFile, random);
			break;
		case '3':
			random = 0;
			saper(saperFile, random);
			break;
		case '4':
			br = 1;
			break;
		default:
			printf("Неизвестная операция\n");
		}
	}
	fclose(saperFile);
}