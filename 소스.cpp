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
		printf("원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.상품현황, 4.상품명 입력 5.종료)\n");
		scanf_s("%d", &case_num);
		printf("\n");
		switch (case_num)
		{
		case 1:
			printf("입고수량 입력: 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n");
			scanf_s("%d", &case1_num); printf("\n");

			Total_individual_inventory(&product_num, &ID, &case1_num, &inventory[0]);
			break;
		case 2:
			printf("판매수량 입력: 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n");
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
		printf("상품 개수 입력: ");
		scanf_s("%d", product_num); printf("\n");

		printf("전체 상품의 입고수량을 입력: ");
		for (int i = 0; i < *product_num; i++)
			scanf_s(" %d", &inventory[i]); printf("\n");
		break;
	case 2:
		printf("\n");
		printf("상품ID: ");
		scanf_s("%d", ID); printf("\n");

		printf("입고수량: ");
		scanf_s("%d", &inventory[*ID]); printf("\n");
		break;
	}
}

void Total_individual_sale(int* product_num, int* ID, int* case2_num, int sale[])
{
	switch (* case2_num)
	{
	case 1:
		printf("전체 상품 판매수량을 입력(%d개): ", *product_num);
		for (int i = 0; i < *product_num; i++)
			scanf_s(" %d", &sale[i]); printf("\n");
		break;
	case 2:
		printf("\n");
		printf("상품ID: ");
		scanf_s("%d", ID); printf("\n");

		printf("판매수량: ");
		scanf_s("%d", &sale[*ID]); printf("\n");
		break;
	}
}

void product_status(int* product_num, int* ID, int* T_inven, int* T_sales, int* sale_num, int stock[], int inventory[], int sale[], char product_name[][SIZE])
{
	for (int i = 0; i < *product_num; i++)
		stock[i] = inventory[i] - sale[i];

	printf("모든 상품의 재고 수량: ");
	for (int i = 0; i < *product_num; i++)
		printf("%d ", stock[i]);
	printf("\n");

	for (int i = 0; i < *product_num; i++)
	{
		*T_sales += sale[i];
		*T_inven += inventory[i];
	}
	printf("총 판매량: %d개 (판매율 %.2f%%)\n", *T_sales, (((float)*T_sales / *T_inven) * 100));

	Most_sold(product_num, ID, sale_num, &sale[0], product_name);
	Least_sold(product_num, ID, sale_num, &sale[0], product_name);

	for (int i = 0; i < *product_num; i++)
	{
		if (stock[i] <= 2)
			printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, product_name[i
			], stock[i]);
	}
	printf("\n");
}

void Product_name(int* product_num, char product_name[][SIZE])
{
	for (int i = 0; i < *product_num; i++)
	{
		printf("ID %d 상품명 : ", i + 1);
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
	printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", *ID, product_name[*ID - 1], *sale_num);
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
	printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", *ID, product_name[*ID - 1], *sale_num);
}
