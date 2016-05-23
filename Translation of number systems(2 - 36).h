#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>

char ch[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void ToDec(char *vhodnoe_chyslo, int sys1)
{
	int index = 0; //Считает количество символов до запятой
	while (index < strlen(vhodnoe_chyslo))
	{
		if (vhodnoe_chyslo[index] == ',')
			break;
		index++;
	}
	for (int index1 = index; index1 < strlen(vhodnoe_chyslo); index1++)
		vhodnoe_chyslo[index1] = vhodnoe_chyslo[index1 + 1]; //Удалаяем запятую
	double vyhodnoe = 0; //Конечное число в 10 - й сс
	int power = index - 1;
	int nomer_bukvy;
	int index2 = 0; //Движемся по строке, выбирая каждую цифру в сс sys1 и переводя ее в 10 - ю
	for (int index4 = 0; index4 < strlen(vhodnoe_chyslo); index4++)
	{ //index4 - счетчик пробегания по строке vhodnoe_chyslo
		for (int index3 = 0; index3 < strlen(ch); index3++)
		{ //index3 показывает номер символа в строке ch
			if (vhodnoe_chyslo[index2] == ch[index3])
			{
				nomer_bukvy = index3;
				break;
			}
		}
		vyhodnoe += (double)nomer_bukvy * pow(sys1, power);
		index2++;
		power--;
	}
	sprintf(vhodnoe_chyslo, "%0.4f\n", vyhodnoe);
}

void FromDec(char *vhodnoe_chyslo, int sys2)
{
	int index0 = 0; //Считает количество символов до запятой
	while (index0 < strlen(vhodnoe_chyslo))
	{
		if (vhodnoe_chyslo[index0] == ',')
			break;
		index0++;
	}
	double numeral = atof(vhodnoe_chyslo); //Число в 10 - й сс записываем в переменную
	int integer = (int)numeral; //Выделяем целую часть числа
	double fraction = numeral - (int)numeral; //Выделяем дробную часть числа
	int remainder; //Остаток от деления
	char buff[10]; //Хранение остатка от деления целого числа на систему счисления
	char neperevernutoe[64] = { "" };
	memset(vhodnoe_chyslo, '\0', 64);
	int index4 = 0; //Счетчик для поиска по строке ch
					//Целая часть
	while (integer >= sys2)
	{
		remainder = integer % sys2;
		while (index4 < strlen(ch))
		{
			if (remainder == index4)
			{
				if (index4 < 10)
					sprintf(buff, "%d", index4);
				else
					sprintf(buff, "%c", ch[index4]);
				break;
			}
			index4++;
		}
		strcat(neperevernutoe, buff);
		index4 = 0;
		integer /= sys2;
	}
	while (index4 < strlen(ch))
	{
		if (remainder == index4)
		{
			if (index4 < 10)
				sprintf(buff, "%d", index4);
			else
				sprintf(buff, "%c", ch[index4]);
			break
		}
		index4++;
	}
	sprintf(buff, "%d", integer);
	strcat(neperevernutoe, buff);
	char perevernutoe[64] = { "" };
	for (int index1 = 0; index1 < strlen(neperevernutoe); index1++)
	{
		perevernutoe[index1] = neperevernutoe[strlen(neperevernutoe) - index1 - 1];
	}
	strcat(vhodnoe_chyslo, perevernutoe);
	strcat(vhodnoe_chyslo, ",");
	int index = 0; //Счетчик для поиска по строке ch
	char buff2[10]; //Строка для одного символа, выбранного из строки ch
					//Дробная часть
	for (int index2 = 0; index2 < 4; index2++)
	{ //index2 - количество символов после запятой
		fraction *= sys2;
		while (index < strlen(ch))
		{
			if ((int)fraction == index)
			{
				if (index < 10)
					sprintf(buff2, "%d", index);
				else
					sprintf(buff2, "%c", ch[index]);
				break;
			}
			index++;
		}
		strcat(vhodnoe_chyslo, buff2);
		fraction -= (int)fraction;
		index = 0;
	}
}

void ResearchNum(char *vhodnoe_chyslo, int sys1)
{
	char number[64] = { "" };
	sprintf(number, "%s", vhodnoe_chyslo);
	int index = 0;
	while (index < strlen(number))
	{
		if (number[index] == ',')
			break;
		index++;
	}
	for (int index1 = index; index1 < strlen(number); index1++)
		number[index1] = number[index1 + 1]; //Удалаяем запятую
	int index3 = 0; // Для строки ch
	for (int index2 = 0; index2 < strlen(number); index2++)
	{
		while (index3 < strlen(ch))
		{
			if (number[index2] == ch[index3])
			{
				if (index3 >= sys1)
				{
					printf("Invalid number!!!!\n");
					system("pause");
					exit(0);
				}
			}
			index3++;
		}
		index3 = 0;
	}
}

void ConvertFromTo(char *vhodnoe_chyslo, int sys1, int sys2)
{
	ResearchNum(vhodnoe_chyslo, sys1);
	if (sys1 != 10)
		ToDec(vhodnoe_chyslo, sys1);
	if (sys2 != 10)
		FromDec(vhodnoe_chyslo, sys2);
}
