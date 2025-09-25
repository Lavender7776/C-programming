#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

void Most_sold(int* product, int* ID, int* sale_num, int sale[], char product_name[][SIZE]);
void Least_sold(int* product, int* ID, int* sale_num, int sale[], char product_name[][SIZE]);
void Total_individual_inventory(int* product_num, int* ID, int*case1_num, int inventory[]);
void Total_individual_sale(int* product_num, int* ID, int* case2_num, int sale[]);
void product_status(int* product_num, int* ID, int* T_inven, int* T_sales, int* sale_num, int stock[], int inventory[], int sale[], char product_name[][SIZE]);
void Product_name(int* product_num, char product_name[][SIZE]);

int main(void)
{
	int product_num = 0;
	char product_name[SIZE][SIZE] = {};
	int inventory[SIZE] = {};
	int sale[SIZE] = {};
	int stock[SIZE] = {};
	int ID = 0;
	int T_inven = 0;
	int T_sales = 0;
	int sale_num = sale[0];

	while (true)
	{
		int case_num;
		int case1_num;
		int case2_num;
		printf("���ϴ� �޴��� �����ϼ���.(1.�԰�, 2.�Ǹ�, 3.��ǰ��Ȳ, 4.��ǰ�� �Է� 5.����)\n");
		scanf_s("%d", &case_num);
		printf("\n");
		switch (case_num)
		{
		case 1:
			printf("�԰���� �Է�: ��ü ��ǰ �԰���� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
			scanf_s("%d", &case1_num); printf("\n");

			Total_individual_inventory(&product_num, &ID, &case1_num, &inventory[0]);
			break;
		case 2:
			printf("�Ǹż��� �Է�: ��ü ��ǰ �Ǹż��� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
			scanf_s("%d", &case2_num); printf("\n");

			Total_individual_sale(&product_num, &ID, &case2_num, &sale[0]);
			break;
		case 3:
			product_status(&product_num, &ID, &T_inven, &T_sales, &sale_num, &stock[0], &inventory[0], &sale[0], product_name);
			break;
		case 4:
			Product_name(&product_num, product_name);
			break;
		case 5:
			return false;
		}
	}
	return 0;
}

void Total_individual_inventory(int* product_num, int* ID, int* case1_num, int inventory[])
{
	switch (* case1_num)
	{
	case 1:
		printf("��ǰ ���� �Է�: ");
		scanf_s("%d", product_num); printf("\n");

		printf("��ü ��ǰ�� �԰������ �Է�: ");
		for (int i = 0; i < *product_num; i++)
			scanf_s(" %d", &inventory[i]); printf("\n");
		break;
	case 2:
		printf("\n");
		printf("��ǰID: ");
		scanf_s("%d", ID); printf("\n");

		printf("�԰����: ");
		scanf_s("%d", &inventory[*ID]); printf("\n");
		break;
	}
}

void Total_individual_sale(int* product_num, int* ID, int* case2_num, int sale[])
{
	switch (* case2_num)
	{
	case 1:
		printf("��ü ��ǰ �Ǹż����� �Է�(%d��): ", *product_num);
		for (int i = 0; i < *product_num; i++)
			scanf_s(" %d", &sale[i]); printf("\n");
		break;
	case 2:
		printf("\n");
		printf("��ǰID: ");
		scanf_s("%d", ID); printf("\n");

		printf("�Ǹż���: ");
		scanf_s("%d", &sale[*ID]); printf("\n");
		break;
	}
}

void product_status(int* product_num, int* ID, int* T_inven, int* T_sales, int* sale_num, int stock[], int inventory[], int sale[], char product_name[][SIZE])
{
	for (int i = 0; i < *product_num; i++)
		stock[i] = inventory[i] - sale[i];

	printf("��� ��ǰ�� ��� ����: ");
	for (int i = 0; i < *product_num; i++)
		printf("%d ", stock[i]);
	printf("\n");

	for (int i = 0; i < *product_num; i++)
	{
		*T_sales += sale[i];
		*T_inven += inventory[i];
	}
	printf("�� �Ǹŷ�: %d�� (�Ǹ��� %.2f%%)\n", *T_sales, (((float)*T_sales / *T_inven) * 100));

	Most_sold(product_num, ID, sale_num, &sale[0], product_name);
	Least_sold(product_num, ID, sale_num, &sale[0], product_name);

	for (int i = 0; i < *product_num; i++)
	{
		if (stock[i] <= 2)
			printf("��ǰ ID %d : ��ǰ�� : %s ������(%d)\n", i + 1, product_name[i
			], stock[i]);
	}
	printf("\n");
}

void Product_name(int* product_num, char product_name[][SIZE])
{
	for (int i = 0; i < *product_num; i++)
	{
		printf("ID %d ��ǰ�� : ", i + 1);
		scanf_s("%s", product_name[i], (unsigned int)SIZE);
		printf("\n");
	}
}

void Most_sold(int* product, int* ID, int* sale_num, int sale[], char product_name[][SIZE])
{
	*ID = 1;
	*sale_num = sale[0];
	for (int i = 0; i < *product; i++)
	{
		if (*sale_num < sale[i])
		{
			*sale_num = sale[i];
			*ID = (i + 1);
		}
	}
	printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n", *ID, product_name[*ID - 1], *sale_num);
}

void Least_sold(int* product, int* ID, int* sale_num, int sale[], char product_name[][SIZE])
{
	*ID = 1;
	*sale_num = sale[0];
	for (int i = 0; i < *product; i++)
	{
		if (*sale_num > sale[i])
		{
			*sale_num = sale[i];
			*ID = (i + 1);
		}
	}
	printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n", *ID, product_name[*ID - 1], *sale_num);
}
