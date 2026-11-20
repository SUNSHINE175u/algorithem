#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 归并辅助函数
void merge(int arr[], int tmp[], int left, int mid, int right)
{
    int i = left, j = mid+1, k = left;
    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while(i <= mid) tmp[k++] = arr[i++];
    while(j <= right) tmp[k++] = arr[j++];
    for(i = left; i <= right; i++) arr[i] = tmp[i];
}

void mergeSort(int arr[], int tmp[], int left, int right)
{
    if(left >= right) return;
    int mid = (left + right)/2;
    mergeSort(arr, tmp, left, mid);
    mergeSort(arr, tmp, mid+1, right);
    merge(arr, tmp, left, mid, right);
}

// 快排辅助函数
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for(int j=low; j<high; j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    int t = arr[i+1]; arr[i+1] = arr[high]; arr[high] = t;
    return i+1;
}

void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// 生成随机数组
void randomArray(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i] = rand() % 1000000;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    printf("===== 任务2：时间复杂度对比实验 =====\n");
    int test_size[] = {10000, 50000, 100000, 200000};
    int cnt = sizeof(test_size)/sizeof(int);

    for(int s=0; s<cnt; s++)
    {
        int n = test_size[s];
        int *a1 = (int*)malloc(n * sizeof(int));
        int *a2 = (int*)malloc(n * sizeof(int));
        int *tmp = (int*)malloc(n * sizeof(int));

        randomArray(a1, n);
        // 拷贝一份给快排
        for(int i=0;i<n;i++) a2[i] = a1[i];

        clock_t start, end;
        double time_merge, time_quick;

        start = clock();
        mergeSort(a1, tmp, 0, n-1);
        end = clock();
        time_merge = (double)(end - start)/CLOCKS_PER_SEC;

        start = clock();
        quickSort(a2, 0, n-1);
        end = clock();
        time_quick = (double)(end - start)/CLOCKS_PER_SEC;

        printf("数据量 = %6d | 归并排序耗时：%.4f s | 快速排序耗时：%.4f s\n",
                n, time_merge, time_quick);

        free(a1);
        free(a2);
        free(tmp);
    }

    printf("\n===== 复杂度分析总结 =====\n");
    printf("归并排序：O(n log n)，最好/平均/最坏一致，稳定排序，需要额外数组空间\n");
    printf("快速排序：平均 O(n log n)，最坏 O(n²)，不稳定，原地排序；随机数据下常数更小，通常更快\n");
    return 0;
}