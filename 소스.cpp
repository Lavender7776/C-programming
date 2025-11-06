#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define MAX_PRODUCTS 5

typedef struct {
	int id;
	char name[SIZE];
	int inventory;
	int sale;
	int price;
}PRODUCT;

void Most_sold(int sale[], char product_name[][SIZE]);
void Least_sold(int sale[], char product_name[][SIZE]);
void Total_individual_inventory(int inventory[], char product_name[][SIZE], int price[]);
void Total_individual_sale(int inventory[], int sale[], char product_name[][SIZE]);
void product_status(char product_name[][SIZE], int inventory[], int sale[], int price[]);
void product_all_status(int stock[], int inventory[], int sale[], char product_name[][SIZE]);
void save_data(int inventory[], int sale[], int price[], char product_name[][SIZE]);
void load_data(int inventory[], int sale[], int price[], char product_name[][SIZE]);

int main(void)
{
	char product_name[SIZE][SIZE] = {};
	int inventory[SIZE] = {};
	int sale[SIZE] = {};
	int stock[SIZE] = {};
	int price[SIZE] = {};

	while (true)
	{
		int case_num;
		printf("=================================================================\n");
		printf("원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.개별현황, 4.전체현황 5.저장 6.불러오기 7.종료)\n");
		printf(">> ");
		scanf_s("%d", &case_num);
		printf("\n");

		switch (case_num)
		{
		case 1:
			Total_individual_inventory(inventory, product_name, price);
			break;
		case 2:
			Total_individual_sale(inventory, sale, product_name);
			break;
		case 3:
			product_status(product_name, inventory, sale, price);
			break;
		case 4:
			product_all_status(stock, inventory, sale, product_name);
			break;
		case 5:
			save_data(inventory, sale, price, product_name);
			break;
		case 6:
			load_data(inventory, sale, price, product_name);
			break;
		case 7:
			return 0;
		default:
			printf("1~5 사이의 숫자를 입력하세요.\n\n");
			break;
		}
	}
	return 0;
}

void Total_individual_inventory(int inventory[], char product_name[][SIZE], int price[])
{
	int user_id;

	printf("\n");
	printf("상품 ID를 입력하세요 (1 ~ %d): ", MAX_PRODUCTS);
	scanf_s("%d", &user_id);
	printf("\n");

	if (user_id < 1 || user_id > MAX_PRODUCTS)
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

void Total_individual_sale(int inventory[], int sale[], char product_name[][SIZE])
{
	int id;
	printf("\n");
	printf("상품ID: ");
	scanf_s("%d", &id);
	printf("\n");

	if (id < 1 || id > MAX_PRODUCTS || product_name[id][0] == '\0')
	{
		printf("오류: 해당 ID로 등록된 상품이 없거나 유효하지 않은 ID입니다.\n\n");
		return;
	}

	int current_stock = inventory[id] - sale[id];
	printf("상품명: %s, 현재 재고: %d\n", product_name[id], current_stock);

	printf("판매수량: ");
	int sell_count;
	scanf_s("%d", &sell_count);
	printf("\n");

	if (sell_count <= 0)
	{
		printf("오류: 판매 수량은 1 이상이어야 합니다.\n\n");
		return;
	}

	if (sell_count > current_stock)
	{
		printf("오류: 재고가 부족합니다.\n\n");
		return;
	}

	sale[id] += sell_count;
	printf("\n 판매 완료 (남은 재고: %d)\n\n", inventory[id] - sale[id]);
}

void product_status(char product_name[][SIZE], int inventory[], int sale[], int price[]) {
	int id;
	printf("\n");
	printf("상품ID: ");
	scanf_s("%d", &id);
	printf("\n");

	if (id < 1 || id > MAX_PRODUCTS || product_name[id][0] == '\0')
	{
		printf("오류: 해당 ID로 등록된 상품이 없거나 유효하지 않은 ID입니다.\n\n");
		return;
	}

	printf("상품명: %s\n", product_name[id]);
	printf("입고수량: %d\n", inventory[id]);
	printf("판매가격: %d원\n", price[id]);
}

void product_all_status(int stock[], int inventory[], int sale[], char product_name[][SIZE])
{
	int T_sales = 0;
	int T_inven = 0;
	int registered_products = 0; //상품 갯수 새는거

	for (int i = 1; i <= MAX_PRODUCTS; i++)
	{
		if (product_name[i][0] != '\0')
		{
			registered_products++;
			stock[i] = inventory[i] - sale[i];
			printf("ID %d (%s) 재고: %d\n", i, product_name[i], stock[i]);

			T_sales += sale[i];
			T_inven += inventory[i];

			if (stock[i] <= 2)
				printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i, product_name[i], stock[i]);
		}
	}

	if (registered_products > 0)
	{
		printf("총 판매량: %d개 (판매율 %.2f%%)\n\n", T_sales, (T_inven > 0) ? (((float)T_sales / T_inven) * 100) : 0.0);
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

	for (int i = 1; i <= MAX_PRODUCTS; i++)
	{
		if (product_name[i][0] != '\0')
		{
			if (id == -1 || sale[i] > sales)
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

	for (int i = 1; i <= MAX_PRODUCTS; i++)
	{
		if (product_name[i][0] != '\0')
		{
			if (id == -1 || sale[i] < sales)
			{
				sales = sale[i];
				id = i;
			}
		}
	}

	if (id != -1)
		printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", id, product_name[id], sales);
}

void save_data(int inventory[], int sale[], int price[], char product_name[][SIZE])
{
	FILE* fp = NULL;
	const char* filename = "shopping.bin";

	if (fopen_s(&fp, filename, "wb") != 0)
	{
		printf("%s 파일을 열 수 없습니다.\n\n", filename);
		return;
	}

	for (int i = 1; i <= MAX_PRODUCTS; i++)
	{
		if (product_name[i][0] != '\0')
		{
			PRODUCT p = {};
			p.id = i;
			strcpy_s(p.name, SIZE, product_name[i]);
			p.inventory = inventory[i];
			p.sale = sale[i];
			p.price = price[i];
			fwrite(&p, sizeof(PRODUCT), 1, fp);
		}
	}
	fclose(fp);
	printf("%s 저장됨", filename);
}

void load_data(int inventory[], int sale[], int price[], char product_name[][SIZE])
{
	FILE* fp = NULL;
	const char* filename = "shopping.bin";

	if (fopen_s(&fp, filename, "rb") != 0)
	{
		printf("%s 파일이 없습니다.\n\n", filename);
		return;
	}

	//기존 데이터 초기화 하는중VVV
	for (int i = 1; i <= MAX_PRODUCTS; i++)
	{
		inventory[i] = 0;
		sale[i] = 0;
		price[i] = 0;
		product_name[i][0] = '\0';
	}
	PRODUCT p;

	while (fread(&p, sizeof(PRODUCT), 1, fp) == 1)
	{
		int id = p.id;
		if (id >= 1 && id <= MAX_PRODUCTS)
		{
			strcpy_s(product_name[id], SIZE, p.name);
			inventory[id] = p.inventory;
			sale[id] = p.sale;
			price[id] = p.price;
		}
	}

	fclose(fp);
	printf("%s 파일에서 상품 정보를 성공적으로 불러왔습니다.\n\n", filename);
}