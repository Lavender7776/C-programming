#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100

typedef struct {
	int id;
	char name[SIZE];
	int inventory;
	int sale;
	int price;
}PRODUCT;

PRODUCT* g_products = NULL;
int g_capacity = 0;

void Most_sold(void);
void Least_sold(void);
void Total_individual_inventory(void);
void Total_individual_sale(void);
void product_status(void);
void product_all_status(void);
void save_data(void);
void load_data(void);
void ensure_capacity(int id);

int main(void)
{
	while (true)
	{
		int case_num;
		int scanf_result;
		printf("=================================================================\n");
		printf("원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.개별현황, 4.전체현황 5.저장 6.불러오기 7.종료)\n");
		printf(">> ");
		scanf_s("%d", &case_num);
		printf("\n");

		switch (case_num)
		{
		case 1: Total_individual_inventory(); break;
		case 2: Total_individual_sale(); break;
		case 3: product_status(); break;
		case 4: product_all_status(); break;
		case 5: save_data(); break;
		case 6: load_data(); break;
		case 7:
			free(g_products);
			return 0;
		}
	}
	return 0;
}

void ensure_capacity(int id)
{
	if (id >= g_capacity)
	{
		int new_capacity = id + 10;
		PRODUCT* new_products = (PRODUCT*)realloc(g_products, new_capacity * sizeof(PRODUCT));
		if (new_products == NULL)
		{
			printf("메모리 재할당에 실패했습니다\n");
			free(g_products);
			exit(1);
		}

		memset(new_products + g_capacity, 0, (new_capacity - g_capacity) * sizeof(PRODUCT));
		g_products = new_products;
		g_capacity = new_capacity;
	}
}

void Total_individual_inventory(void)
{
	int user_id;
	printf("\n");
	printf("상품 ID를 입력하세요 : ");
	scanf_s("%d", &user_id);

	if (user_id < 1)
	{
		printf("ID는 1 이상의 숫자여야 합니다.\n\n");
		return;
	}

	ensure_capacity(user_id);

	printf("상품명 : ");
	scanf_s("%s", g_products[user_id].name, (unsigned int)SIZE);

	printf("입고수량: ");
	scanf_s("%d", &g_products[user_id].inventory);

	printf("판매가격: ");
	scanf_s("%d", &g_products[user_id].price);

	g_products[user_id].sale = 0;
	g_products[user_id].id = user_id; 

	printf("\nID %d 상품 입고 완료.\n\n", user_id);
}

void Total_individual_sale(void)
{
	int id;
	printf("상품ID: ");
	scanf_s("%d", &id);

	if (id < 1 || id >= g_capacity || g_products[id].name[0] == '\0')
	{
		printf("해당 ID로 등록된 상품이 없거나 유효하지 않은 ID입니다.\n\n");
		return;
	}

	int current_stock = g_products[id].inventory - g_products[id].sale;
	printf("상품명: %s, 현재 재고: %d\n", g_products[id].name, current_stock);

	printf("판매수량: ");
	int sell_count;
	scanf_s("%d", &sell_count);

	if (sell_count <= 0)
		return;
	if (sell_count > current_stock)
		return;

	g_products[id].sale += sell_count;
	printf("\n 판매 완료 (남은 재고: %d)\n\n", g_products[id].inventory - g_products[id].sale);
}

void product_status(void) {
	int id;
	printf("상품ID: ");
	scanf_s("%d", &id);

	if (id < 1 || id >= g_capacity || g_products[id].name[0] == '\0')
	{
		printf("해당 ID로 등록된 상품이 없거나 유효하지 않은 ID입니다.\n\n");
		return;
	}

	printf("상품명: %s\n", g_products[id].name);
	printf("입고수량: %d\n", g_products[id].inventory);
	printf("판매가격: %d원\n", g_products[id].price);
	printf("총 판매수량: %d\n", g_products[id].sale);
	printf("현재 재고: %d\n", g_products[id].inventory - g_products[id].sale);
}

void product_all_status(void)
{
	int T_sales = 0;
	int T_inven = 0;
	int registered_products = 0;

	for (int i = 0; i < g_capacity; i++)
	{
		if (g_products[i].name[0] != '\0')
		{
			registered_products++;
			int stock = g_products[i].inventory - g_products[i].sale;
			printf("ID %d (%s) 재고: %d\n", i, g_products[i].name, stock);

			T_sales += g_products[i].sale;
			T_inven += g_products[i].inventory;

			if (stock <= 2)
				printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i, g_products[i].name, stock);
		}
	}

	if (registered_products > 0)
	{
		printf("총 판매량: %d개 (판매율 %.2f%%)\n\n", T_sales, (T_inven > 0) ? (((float)T_sales / T_inven) * 100) : 0.0);
		Most_sold();
		Least_sold();
		printf("\n");
	}
	else
		printf("아직 입고된 상품이 없습니다.\n\n");
}

void Most_sold(void)
{
	int id = -1;
	int sales = -1;

	for (int i = 0; i < g_capacity; i++)
	{
		if (g_products[i].name[0] != '\0')
		{
			if (id == -1 || g_products[i].sale > sales)
			{
				sales = g_products[i].sale;
				id = i;
			}
		}
	}
	if (id != -1)
		printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", id, g_products[id].name, sales);
}

void Least_sold(void)
{
	int id = -1;
	int sales = -1;

	for (int i = 0; i < g_capacity; i++)
	{
		if (g_products[i].name[0] != '\0')
		{
			if (id == -1 || g_products[i].sale < sales)
			{
				sales = g_products[i].sale;
				id = i;
			}
		}
	}
	if (id != -1)
		printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", id, g_products[id].name, sales);
}

void save_data(void)
{
	FILE* fp = NULL;
	const char* filename = "shopping.bin";

	if (fopen_s(&fp, filename, "wb") != 0)
		return;

	for (int i = 0; i < g_capacity; i++)
	{
		if (g_products[i].name[0] != '\0')
		{
			fwrite(&g_products[i], sizeof(PRODUCT), 1, fp);
		}
	}
	fclose(fp);
	printf("%s 저장됨\n\n", filename);
}

void load_data(void)
{
	FILE* fp = NULL;
	const char* filename = "shopping.bin";

	if (fopen_s(&fp, filename, "rb") != 0) {
		printf("%s 파일이 없습니다. 새 프로그램으로 시작합니다.\n\n", filename);
		return;
	}

	free(g_products);
	g_products = NULL;
	g_capacity = 0;

	PRODUCT p_temp;

	while (fread(&p_temp, sizeof(PRODUCT), 1, fp) == 1)
	{
		if(p_temp.id < 1)
			continue;

		ensure_capacity(p_temp.id);
		g_products[p_temp.id] = p_temp;
	}

	fclose(fp);
	printf("%s 파일에서 상품 정보를 성공적으로 불러왔습니다.\n\n", filename);
}