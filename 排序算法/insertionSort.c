#include <stdio.h>
#include <stdbool.h>

int swap_count = 0;
int comp_count = 0;

void show(int data[], int len)
{
    int i;
    for(i=0; i<len; ++i)
    {
        printf("%d\t", data[i]);
    }
    printf("\n");
}

void insertionSort(int data[], int len)
{
    if(len <= 1)
        return;

    int i, j;
    for(i=1; i<len; i++)
    {
        int tmp = data[i];

        for(j=i-1; j>=0; j--)
        {
            comp_count++;
            if(data[j] < tmp)
            {
                break;
            }
            else
            {
                swap_count++;
                data[j+1] = data[j];
            }
        }
        swap_count++;
        data[j+1] = tmp;
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int i, data[100];
    for(i=0; i<100; ++i)
    {
        data[i] = rand() % 1000;
    }
    printf("随机序列: ");
    show(data, 100);

    printf("插入排序: ");
    insertionSort(data, 100);
    show(data, 100);

    printf("总共比较次数: %d\n", comp_count);
    printf("总共移动次数: %d\n", swap_count);

    return 0;
}