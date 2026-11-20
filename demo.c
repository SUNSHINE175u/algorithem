#include <stdio.h>
#include <stdlib.h>

#define N 8

// ------------------- 归并排序 -------------------
void merge(int arr[], int tmp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = tmp[i];
}

void mergeSort(int arr[], int tmp[], int left, int right)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, tmp, left, mid);
    mergeSort(arr, tmp, mid + 1, right);
    merge(arr, tmp, left, mid, right);

    // 输出本次合并后的一趟结果
    printf("归并一趟 [left=%d,right=%d]：", left, right);
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ------------------- 快速排序 -------------------
void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    int t = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = t;
    printf("快排一趟，基准=%d，结果：", pivot);
    printArr(arr, N);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int data[N] = {49, 38, 65, 97, 76, 13, 27, 49};
    int arr[N];
    int tmp[N];

    printf("===== 任务1：8个元素演示 =====\n");
    printf("原始数组：");
    printArr(data, N);
    printf("\n----- 归并排序过程 -----\n");
    // 拷贝数组，避免互相污染
    for(int i=0;i<N;i++) arr[i] = data[i];
    mergeSort(arr, tmp, 0, N-1);

    printf("\n----- 快速排序过程 -----\n");
    for(int i=0;i<N;i++) arr[i] = data[i];
    quickSort(arr, 0, N-1);

    return 0;
}