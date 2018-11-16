#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

bool binarySearch(int list[], int n, int target, int* wi)
{
	int begin = 0; int mid = 0; int end = n - 1;

	while (begin <= end)
	{
		mid = (begin + end) / 2;
		if (target > list[mid])
			begin = mid + 1;
		else if (target < list[mid])
			end = mid - 1;
		else
			begin = end + 1;
	}
	*wi = mid;
	return (target == list[mid]);
}

int hashFT(int key)
{
	return key;
}
//I had choose direct method for hashing function,because of it's simplicity :)
bool hashedSearch(int list[], int n, int key, int* wi)
{
	for (int i = 0; i<n; i++)
		if (list[i] == key)
		{
			*wi = i;
			return 1;
		}
	return 0;
}

void selection(int list[], int n)
{
	int temp, least;

	for (int i = 0; i < n; i++)
	{
		least = i;
		for (int j = i; j < n; j++)
			if (list[least] > list[j])
				least = j;
		temp = list[least];
		list[least] = list[i];
		list[i] = temp;
	}
}
void insertion(int list[], int n)
{
	int j, least;
	for (int i = 1; i<n; i++)
	{
		least = list[i];
		for (j = i; j > 0 && least < list[j - 1]; j--)
			list[j] = list[j - 1];
		list[j] = least;
	}
}
void bubble(int list[], int n)
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = n; j > 1; j--)
		{
			if (list[j - 2] > list[j - 1])
			{
				temp = list[j - 2];
				list[j - 2] = list[j - 1];
				list[j - 1] = temp;
			}
		}
	}
}
void quick(int list[], int left, int right)
{
	int pivot = 0, i = 0, j = 0, temp;

	if (left < right)
	{
		i = left, j = right, pivot = left;
		while (1)
		{
			while (list[i] < list[pivot])
				i++;
			while (list[j] > list[pivot])
				j--;
			if (j <= i)break;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			i++;
			j--;
		}
	}
	temp = list[pivot];
	list[pivot] = list[j];
	list[j] = temp;

	if (left < j - 1)
		quick(list, left, j - 1);
	if (j + 1 < right)
		quick(list, j + 1, right);
}

void merge(int list[], int left, int mid, int right)
{
	int sorted[100], k = 0;
	int i = left;
	int j = mid + 1;

	while (i <= mid || j <= right)
	{
		if (j > right || (list[i] < list[j] && i <= mid))
		{
			sorted[k] = list[i];
			k++;
			i++;
		}
		else
		{
			sorted[k] = list[j];
			k++;
			j++;
		}
	}
	for (int i = 0; i < k; i++)
		list[left + i] = sorted[i];
}

void mergeSort(int list[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort(list, low, mid);
		mergeSort(list, mid + 1, high);
		merge(list, low, mid, high);
	}
}

int main()
{
	int num = 0, wi[100], *set, test = 0, test2 = 1, target, *loc, *sorted, key, site, num1, num2;
	loc = &site;
	printf("Enter some integers(num of int be less than 100,enter char for end): ");
	while (test2 != 0)
	{
		test2 = scanf("%d", &test);
		getchar();
		wi[num] = test;
		num++;
	}

	num--;
	set = (int*)malloc(sizeof(int)*num);

	for (int i = 0; i < num; i++)
		set[i] = wi[i];

	printf("Select sorting method (1:Selection, 2:Insertion, 3:Bubble, 4:Quick, 5:Merge): ");

	scanf("%d", &test);

	switch (test)
	{
	case 1:
		selection(set, num);
		break;
	case 2:
		insertion(set, num);
		break;
	case 3:
		bubble(set, num);
		break;
	case 4:
		quick(set, 0, num - 1);
		break;
	case 5:
		mergeSort(set, 0, num - 1);
		break;
	}
	for (int i = 0; i < num; i++)
		printf(" %d", set[i]);//Á¤·Ä

	printf("\nselect searching method (1:Binary 2:Hashed): ");
	scanf("%d", &test);

	while (1)
	{
		printf("enter integer want to search(enter char for end): ");
		if (!scanf("%d", &target))
			break;
		key = target;

		switch (test)
		{
		case 1:
			if (binarySearch(set, num, target, loc))
				printf("%d is exist.\n", target);
			else
				printf("%d is not exist\n", target);
			break;
		case 2:
			if (hashedSearch(set, num, key, loc) == 1)
				printf("%d is exist.\n", target);
			else
				printf("%d is not exist\n", target);
			break;
		}
	}

	return 0;
}