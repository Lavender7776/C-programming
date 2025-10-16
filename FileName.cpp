#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

void Most_sold(int sale[], char product_name[][SIZE]);
void Least_sold(int sale[], char product_name[][SIZE]);
void Total_individual_inventory(int* product_num, int* ID, int* case1_num, int inventory[], char product_name[][SIZE], int price[]);
void Total_individual_sale(int* ID, int inventory[], int sale[], char product_name[][SIZE]);
void product_status(int* ID, char product_name[][SIZE], int inventory[], int price[]);
void product_all_status(int* product_num, int* ID, int* T_inven, int* T_sales, int* sale_num, int stock[], int inventory[], int sale[], char product_name[][SIZE], int price[]);
//void Product_name(int* product_num, char product_name[][SIZE]);

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
	int price[SIZE] = {};

	while (true)
	{
		int case_num;
		int case1_num;
		int case2_num;
		printf("원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.개별현황, 4.전체현황 5.종료)\n");
		scanf_s("%d", &case_num);
		printf("\n");
		switch (case_num)
		{
		case 1:
			Total_individual_inventory(&product_num, &ID, &case1_num, &inventory[0], product_name, &price[0]);
			break;
		case 2:
			Total_individual_sale(&ID, &inventory[0], &sale[0], product_name);
			break;
		case 3:
			product_status(&ID, product_name, &inventory[0], &price[0]);
			break;
		case 4:
			product_all_status(&product_num, &ID, &T_inven, &T_sales, &sale_num, &stock[0], &inventory[0], &sale[0], product_name, &price[0]);
			//Product_name(&product_num, product_name);
			break;
		case 5:
			return false;
		}
	}
	return 0;
}

void Total_individual_inventory(int* product_num, int* ID, int* case1_num, int inventory[], char product_name[][SIZE], int price[])
{
	int user_id;

	printf("\n");
	printf("상품 ID를 입력하세요 (1 ~ %d): ", 5);
	scanf_s("%d", &user_id);
	printf("\n");

	if (user_id < 1 || user_id > 5)
	{
		printf("오류: ID는 1부터 %d 사이의 숫자만 입력할 수 있습니다.\n", 5);
		return;
	}

	int index = user_id;
	printf("상품명 : ");
	scanf_s("%s", product_name[index], (unsigned int)SIZE);
	printf("\n");

	printf("입고수량: ");
	scanf_s("%d", &inventory[index]);
	printf("\n");

	printf("판매가격: ");
	scanf_s("%d", &price[index]);
	printf("\n");
}

void Total_individual_sale(int* ID, int inventory[], int sale[], char product_name[][SIZE]) 
{
	printf("\n");
	printf("상품ID: ");
	scanf_s("%d", ID);
	printf("\n");

	if (product_name[*ID][0] == '\0') {
		printf("오류: 해당 ID로 등록된 상품이 없습니다.\n\n");
		return;
	}

	int current_stock = inventory[*ID] - sale[*ID];
	printf("상품명: %s, 현재 재고: %d\n", product_name[*ID], current_stock);

	printf("판매수량: ");
	int sell_count;
	scanf_s("%d", &sell_count);
	printf("\n");

	if (sell_count > current_stock)
	{
		printf("오류: 재고가 부족합니다!\n\n");
		return;
	}

	sale[*ID] += sell_count;
	printf("판매 완료, (남은 재고: %d)\n\n", inventory[*ID] - sale[*ID]);
}

void product_status(int* ID, char product_name[][SIZE], int inventory[], int price[])
{
	printf("\n");
	printf("상품ID: ");
	scanf_s("%d", ID); printf("\n");

	printf("상품명: %s", product_name[*ID]);
	printf("\n");

	printf("입고수량: %d", inventory[*ID]);
	printf("\n");

	printf("판매가격: %d", price[*ID]);
	printf("\n");
}

void product_all_status(int* product_num, int* ID, int* T_inven, int* T_sales, int* sale_num, int stock[], int inventory[], int sale[], char product_name[][SIZE], int price[])
{
	*T_sales = 0;
	*T_inven = 0;
	/*for (int i = 0; i < *product_num; i++)
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
			printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, product_name[i], stock[i]);
	}
	printf("\n");*/

	for (int i = 0; i < SIZE; i++)
	{
		if (product_name[i][0] != '\0')
		{
			stock[i] = inventory[i] - sale[i];
			printf("ID %d (%s) 재고: %d\n", i + 1, product_name[i], stock[i]);

			*T_sales += sale[i];
			*T_inven += inventory[i];

			if (stock[i] <= 2)
				printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, product_name[i], stock[i]);
		}
	}

	if (*T_inven > 0) 
	{
		printf("총 판매량: %d개 (판매율 %.2f%%)\n\n", *T_sales, (((float)*T_sales / *T_inven) * 100));
		Most_sold(&sale[0], product_name);
		Least_sold(&sale[0], product_name);
		printf("\n");
	}
	else 
		printf("아직 입고된 상품이 없습니다.\n\n");

}

void Most_sold(int sale[], char product_name[][SIZE]) 
{
	int id = -1;
	int sales = -1;

	for (int i = 0; i < SIZE; i++)
	{
		if (product_name[i][0] != '\0')
		{
			if (id == -1)
			{
				sales = sale[i];
				id = i;
			}
			else if (sale[i] > sales)
			{
				sales = sale[i];
				id = i;
			}
		}
	}
	
	if (id != -1)
		printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", id, product_name[id], sales);
}

void Least_sold(int sale[], char product_name[][SIZE]) 
{
	int id = -1;
	int sales = -1;

	for (int i = 0; i < SIZE; i++)
	{
		if (product_name[i][0] != '\0')
		{
			if (id == -1)
			{
				sales = sale[i];
				id = i;
			}
			else if (sale[i] < sales)
			{
				sales = sale[i];
				id = i;
			}
		}
	}

	if (id != -1)
		printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", id, product_name[id], sales);
}