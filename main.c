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

int main(){
    int arr[] = {3,5,7,2,9,0,6,1,8,4};

    quickSort(arr,0,9);

    for(int i = 0; i< 10; ++i){
        printf("%d ",arr[i]);
    }
}