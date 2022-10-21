#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void bubbleSort(int arr[],int size){
    for(int i = 0;i<size -1 ;++i){
        _Bool flag = 1;
        for (int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr[j+1]){
                flag = 0;
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
        if(flag) break;
    }
}

int binarySearch(int arr[], int left, int right, int target){
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if(target == arr[mid]) return mid + 1;   //如果插入元素跟中间元素相等，直接返回后一位
        else if (target < arr[mid])  //如果大于待插入元素，说明插入位置肯定在左边
            right = mid - 1;   //范围划到左边
        else
            left = mid + 1;   //范围划到右边
    }
    return left;   //不断划分范围，left也就是待插入位置了
}

void insertSort(int arr[], int size){
    for(int i = 1; i < size;++i){
        int tmp = arr[i];
        int j = binarySearch(arr,0,i-1,tmp);
        for(int k = i;k>j;k--) arr[k] = arr[k-1];
        arr[j] = tmp;
    }
}

void swap(int * a,int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectSort(int arr[],int size){
    int left = 0, right = size - 1;
    while (left < right) {
        int min = left, max =right;
        for (int i = left; i <= right; ++i) {
            if (arr[i] < arr[min]) min = i;
            if (arr[i] > arr[max]) max = i;
        }
        swap(&arr[max],&arr[right]);
        if(min == right) min = max;
        swap(&arr[min],&arr[left]);
        left++;
        right--;
    }
}

void quickSort(int arr[],int start,int end){
    if(start >= end) return;
    int left = start,right = end,pivot = arr[left];
    while (left < right){
        while (left < right && arr[right] >= pivot) right--;
        arr[left] = arr[right];
        while (left < right && arr[left] <= pivot) left++;
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    quickSort(arr,start,left - 1);
    quickSort(arr,left + 1,end);
}

void dualPivotQuickSort(int arr[],int start,int end){
    if(start >= end) return;
    if(arr[start] > arr[end])
        swap(&arr[start],&arr[end]);
    int pivot1 = arr[start],pivot2 = arr[end];
    int left = start,right = end,mid = left + 1;
    while (mid < right){
        if(arr[mid] <= pivot1)
            swap(&arr[++left],&arr[mid++]);
        else if(arr[mid] <= pivot2){
            mid++;
        } else{
            while(arr[--right] > pivot2 && right > mid);
            if(mid>=right) break;
            swap(&arr[mid],&arr[right]);
        }
    }
    swap(&arr[start],&arr[left]);
    swap(&arr[end],&arr[right]);
    dualPivotQuickSort(arr,start,left - 1);
    dualPivotQuickSort(arr,left + 1,right - 1);
    dualPivotQuickSort(arr,right + 1,end);
}

void shellSort(int arr[],int size){
    int delta = size/2;
    while (delta >= 1){
        for (int i = delta; i < size; ++i) {
            int j = i,tmp = arr[i];
            while (j >= delta && arr[j-delta] > tmp){
                arr[j] = arr[j - delta];
                j -= delta;
            }
            arr[j] = tmp;
        }
        delta /= 2;
    }
}

int main(){
    int arr[] = {3,5,7,2,9,0,6,1,8,4};

    shellSort(arr,10);

    for(int i = 0; i< 10; ++i){
        printf("%d ",arr[i]);
    }
}