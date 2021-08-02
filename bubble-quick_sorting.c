#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_SIZE 20

#define FALSE 0
#define TRUE 1

#define NUM_INDEX 0
#define MODEL_INDEX 1
#define COLOR_INDEX 2
#define STORAGE_INDEX 3
#define PRICE_INDEX 4
#define AVAILABLE_STOCK_INDEX 5

int data_size;
int step;

typedef struct phone
{
	int num;
	char model[MAX_STRING_SIZE];
	char color[MAX_STRING_SIZE];
	char storage[MAX_STRING_SIZE];
	int price;
	int available_stock;
}Phones;

void read_data(Phones *data, FILE* indatafile);
int add_data(Phones *data);

int sort_data(Phones *data);

void bubble_sort(Phones *data, int sort_index);

void quick_sort(Phones *data, int p, int q, int sort_index);
void split(Phones *data, int m, int *up, int sort_index);
void data_step(Phones *data);

void swap_value(Phones *i, Phones *j);

int delete_data(Phones *data);
int print_data(Phones *data);
int file_print_data(Phones *data, FILE* outdatafile);

int main(int argc, char* argv[])
{
	Phones *data;
	FILE *indatafile, *outdatafile;
	int menu_index = 0;

	data_size = 30;
	data = (Phones*)malloc(sizeof(Phones) * data_size);
	indatafile = fopen("report2_2017112596_data.txt", "rt");
	outdatafile = fopen("report2_2017112596_sorting_result.txt", "at");
	
	printf("reading data...\n");
	read_data(data, indatafile);
	
	clock_t startTime, endTime;
	
	////////////////// 메뉴 출력 //////////////////
	while(1)
	{
		printf("\n================== MENU ==================\n");
		printf("| 1. Add data	\n");
		printf("| 2. Sorting data \n");
		printf("| 3. Delete data \n");
		printf("| 4. Print data \n");
		printf("| 5. Print data to file\n");
		printf("| 6. Exit \n");
		printf("===========================================\n");
		printf(">> ");
		scanf("%d", &menu_index);
		rewind(stdin);
		
		switch (menu_index)
		{
			case 1:
				add_data(data);
				break;
			case 2:
				sort_data(data);
				break;
			case 3:
				delete_data(data);
				break;
			case 4:
				startTime = clock();
				print_data(data);
				endTime = clock();
				printf("\nPrint Data Time: %.3lf ms\n", (double)(endTime - startTime));
				break;
			case 5:
				startTime = clock();
				file_print_data(data, outdatafile);
				endTime = clock();
				printf("print result to report2_2017112596_sorting_result.txt\n");
				printf("\nPrint Data to File Time: %.3lf ms\n", (double)(endTime - startTime));
				break;
			case 6:
				printf("\nExit Program...\nThank you :)\n");
				return 0;
			default:
				printf("\nPlease enter an integer between 1 and 5\n");
		}
	}
	
	fclose(indatafile);
	fclose(outdatafile);
	free(data);
}

////////////////// 데이터 읽어오는 함수  //////////////////
void read_data(Phones *data, FILE* indatafile)
{
	int i = 0;
	
	while(!feof(indatafile))
	{
		fscanf(indatafile, "%d, %[^','], %[^','], %[^','], %d, %d", &data[i].num, &data[i].model, &data[i].color, &data[i].storage, &data[i].price, &data[i].available_stock);
		i++;
	}
	
	data_size = i;
	realloc(data, sizeof(Phones) * data_size);

	printf("----------------Read Data----------------\n");
	print_data(data);
}

////////////////// 데이터 추가  //////////////////
int add_data(Phones *data)
{
	int x;
	
	clock_t startTime, endTime;
	startTime = clock();
	
	data_size++;
	realloc(data, sizeof(Phones) * data_size);
	
	printf("Add Data\n");
	
	printf("Num: ");
	scanf("%d", &data[data_size - 1].num);
	rewind(stdin);
	
	printf("Model: ");
	scanf("%s", &data[data_size - 1].model);
	rewind(stdin);
	
	printf("Color: ");
	scanf("%s", &data[data_size - 1].color);
	rewind(stdin);
	
	printf("Storage: ");
	scanf("%s", &data[data_size - 1].storage);
	rewind(stdin);
	
	printf("Price: ");
	scanf("%d", &data[data_size - 1].price);
	rewind(stdin);
	
	printf("Available Stock: ");
	scanf("%d", &data[data_size - 1].available_stock);
	rewind(stdin);

	print_data(data);
	endTime = clock();
	printf("\nEnter Data Time: %.3lf ms\n", (double)(endTime - startTime));
	return 0;
}

////////////////// 데이터 정렬  //////////////////
int sort_data(Phones *data)
{
	int algorithm_index = 0;
	int sort_index = 0;
	clock_t startTime, endTime;

	while(algorithm_index != 1 && algorithm_index != 2)
	{
		printf("Select Sorting Algorithm\n");
		printf("BUBBLE SORTING: 1 QUICK SORTING: 2\n");
		printf(">> ");
		scanf("%d", &algorithm_index);
		rewind(stdin);
		
		while(1)
		{
			printf("Select the index to sort\n");
			printf("NUM: 0 MODEL: 1 COLOR: 2 STORAGE: 3 PRICE: 4 AVAILABLE STOCK: 5\n");
			printf(">> ");
			scanf("%d", &sort_index);
			rewind(stdin);
			
			if(sort_index < 0 || sort_index > 5)
			{
				printf("Please enter an integer between 0 and 5 when select index\n");
			}
			else
				break;
		}
		
		switch (algorithm_index)
		{
			////////////////// bubble sort 호출 //////////////////
			case 1:
				startTime = clock();
				bubble_sort(data, sort_index);
				endTime = clock();
				
				printf("\nBubble Sort Data Time: %.3lf ms\n", (double)(endTime - startTime));
				break;
			////////////////// quick sort 호출 //////////////////
			case 2:
				printf("Before Sort:\n");
				print_data(data);
				
				startTime = clock();
				step = 0;
				quick_sort(data, 0, data_size, sort_index);
				endTime = clock();

				printf("\nQuick Sort Data Time: %.3lf ms\n", (double)(endTime - startTime));
				break;
			default:
				printf("\nPlease enter an integer 1 or 2 when select algorithm\n");
		}
	}

	return 0;
}

////////////////// bubble sort  //////////////////
void bubble_sort(Phones *data, int sort_index)
{
	printf("Before Sort:\n");
	print_data(data);
	
	int i, k, loops;
	int isNotFinish = TRUE;
	k = data_size;
	loops = 0;

	while (isNotFinish)
	{
		k = k - 1;
		isNotFinish = FALSE;
		loops = loops + 1;
		
		for (i = 0; i < k; i++)
		{
			switch (sort_index)
			{
				case NUM_INDEX:
					if (data[i].num > data[i+1].num)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
				case MODEL_INDEX:
					if (strcmp(data[i].model, data[i+1].model) > 0)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
				case COLOR_INDEX:
					if (strcmp(data[i].color, data[i+1].color) > 0)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
				case STORAGE_INDEX:
					if (strcmp(data[i].storage, data[i+1].storage) > 0)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
				case PRICE_INDEX:
					if (data[i].price > data[i+1].price)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
				case AVAILABLE_STOCK_INDEX:
					if (data[i].available_stock > data[i+1].available_stock)
					{
						swap_value(&data[i], &data[i+1]);
						isNotFinish = TRUE;
					}
					break;
			}
		}
		printf("\n%2d loops step: \n", loops);
		print_data(data);
	}
}

////////////////// quick sort  //////////////////
void quick_sort(Phones *data, int p, int q, int sort_index)
{
	int j;
	j = q + 1;
	if(p >= q)
		return;
		
	split(data, p, &j, sort_index);
	data_step(data);
	quick_sort(data, p, j - 1, sort_index);
	quick_sort(data, j + 1, q, sort_index);
}

////////////////// 데이터 비교하는 부분 //////////////////
void split(Phones *data, int m, int *up, int sort_index)
{
	int low = m;
	if(*up > data_size)
		*up = data_size;
	
	switch (sort_index)
	{
		case NUM_INDEX:
			while(1)
			{
				do
					low++;
				while(data[low].num < data[m].num);
		
				do
					--*up;
				while(data[*up].num > data[m].num);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
		case MODEL_INDEX:
			while(1)
			{
				do
					low++;
				while(strcmp(data[low].model, data[m].model) < 0);
		
				do
					--*up;
				while(strcmp(data[*up].model, data[m].model) > 0);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
		case COLOR_INDEX:
			while(1)
			{
				do
					low++;
				while(strcmp(data[low].color, data[m].color) < 0);
		
				do
					--*up;
				while(strcmp(data[*up].color, data[m].color) > 0);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
		case STORAGE_INDEX:
			while(1)
			{
				do
					low++;
				while(strcmp(data[low].storage, data[m].storage) < 0);
		
				do
					--*up;
				while(strcmp(data[*up].storage, data[m].storage) > 0);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
		case PRICE_INDEX:
			while(1)
			{
				do
					low++;
				while(data[low].price < data[m].price);
		
				do
					--*up;
				while(data[*up].price > data[m].price);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
		case AVAILABLE_STOCK_INDEX:
			while(1)
			{
				do
					low++;
				while(data[low].available_stock < data[m].available_stock);
		
				do
					--*up;
				while(data[*up].available_stock > data[m].available_stock);
		
				if (low < *up)
					swap_value(&data[low], &data[*up]);
				else
					break;
			}
			swap_value(&data[m], &data[*up]);
			break;
	}
}
	
////////////////// 하나의 단계가 끝난 뒤 데이터 출력 //////////////////
void data_step(Phones *data)
{
	step = step + 1;

	printf("\n%2d loops step: \n", step);
	print_data(data);
}

////////////////// 데이터 바꿔주는 함수 //////////////////
void swap_value(Phones *i, Phones *j)
{
	Phones temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

////////////////// 데이터 삭제하는 함수 //////////////////
int delete_data(Phones *data)
{
	int i, j;
	int x;
	int isDelete = FALSE;
	
	clock_t startTime, endTime;
	
	printf("\n----------------Before Delete----------------\n");
	print_data(data);
	printf("Enter the NUM of data you want to delete: ");
	scanf("%d", &x);
	rewind(stdin);

	startTime = clock();
	
	for(i = 0; i < data_size; i++)
	{
		if(x == data[i].num)
		{
			printf("\ndelete data: %-5d %-20s %-20s %-10s %-10d %-5d\n", data[i].num, data[i].model, data[i].color, data[i].storage, data[i].price, data[i].available_stock);
			for(j = i; j < data_size; j++)
			{
				data[j] = data[j + 1];
			}
			data_size--;
			isDelete = TRUE;
			break;
		}
	}
	
	if(!isDelete)
	{
		printf("\nThere is no data which num is %d\n", x);
	}
	else
	{
		realloc(data, sizeof(Phones) * data_size);
		printf("\n----------------After Delete----------------\n");
		print_data(data);
	}
	
	endTime = clock();
	printf("\nDelete Data Time: %.3lf ms\n", (double)(endTime - startTime));
	return 0;
}

////////////////// 데이터 프린트하는  함수 //////////////////
int print_data(Phones *data)
{
	int i;
	
	printf("%-5s %-20s %-20s %-10s %-10s %-20s\n", "Num", "Model", "Color", "Storage", "Price", "Available Stock");
	for(i = 0; i < data_size; i++)
	{
		printf("%-5d %-20s %-20s %-10s %-10d %-5d\n", data[i].num, data[i].model, data[i].color, data[i].storage, data[i].price, data[i].available_stock);
	}
	
	return 0;
}

////////////////// 데이터 파일에 프린트하는 함수 //////////////////
int file_print_data(Phones *data, FILE *outdatafile)
{
	int i;

	fprintf(outdatafile, "%-5s %-20s %-20s %-10s %-10s %-20s\n", "Num", "Model", "Color", "Storage", "Price", "Available Stock");
	for(i = 0; i < data_size; i++)
	{
		fprintf(outdatafile, "%-5d %-20s %-20s %-10s %-10d %-5d\n", data[i].num, data[i].model, data[i].color, data[i].storage, data[i].price, data[i].available_stock);
	}
	fprintf(outdatafile, "\n");
	
	return 0;
}
