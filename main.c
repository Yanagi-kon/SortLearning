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

//这个函数就是对start顶点位置的子树进行堆化
void makeHeap(int* arr, int start, int end) {
    while (start * 2 + 1 <= end) {    //如果有子树，就一直往下，因为调整之后有可能子树又不满足性质了
        int child = start * 2 + 1;    //因为下标是从0开始，所以左孩子下标就是i * 2 + 1，右孩子下标就是i * 2 + 2
        if(child + 1 <= end && arr[child] < arr[child + 1])   //如果存在右孩子且右孩子比左孩子大
            child++;    //那就直接看右孩子
        if(arr[child] > arr[start])   //如果上面选出来的孩子，比父结点大，那么就需要交换，大的换上去，小的换下来
            swap(&arr[child], &arr[start]);
        start = child;   //继续按照同样的方式前往孩子结点进行调整
    }
}

//堆排序
void heapSort(int arr[], int size) {
    for(int i= size/2 - 1; i >= 0; i--)   //我们首选需要对所有非叶子结点进行一次堆化操作，需要从最后一个到第一个，这里size/2计算的位置刚好是最后一个非叶子结点
        makeHeap(arr, i, size - 1);
    for (int i = size - 1; i > 0; i--) {   //接着我们需要一个一个把堆顶元素搬到后面，有序排列
        swap(&arr[i], &arr[0]);    //搬运实际上就是直接跟倒数第i个元素交换，这样，每次都能从堆顶取一个最大的过来
        makeHeap(arr, 0, i - 1);   //每次搬运完成后，因为堆底元素被换到堆顶了，所以需要再次对根结点重新进行堆化
    }
}

//归并排序·合
void merge(int arr[], int tmp[], int left, int leftEnd, int right, int rightEnd){
    int i = left, size = rightEnd - left + 1;   //这里需要保存一下当前范围长度，后面使用
    while (left <= leftEnd && right <= rightEnd) {   //如果两边都还有，那么就看哪边小，下一个就存哪一边的
        if(arr[left] <= arr[right])   //如果左边的小，那么就将左边的存到下一个位置（这里i是从left开始的）
            tmp[i++] = arr[left++];   //操作完后记得对i和left都进行自增
        else
            tmp[i++] = arr[right++];
    }
    while (left <= leftEnd)    //如果右边看完了，只剩左边，直接把左边的存进去
        tmp[i++] = arr[left++];
    while (right <= rightEnd)   //同上
        tmp[i++] = arr[right++];
    for (int j = 0; j < size; ++j, rightEnd--)   //全部存到暂存空间中之后，暂存空间中的内容都是有序的了，此时挨个搬回原数组中（注意只能搬运范围内的）
        arr[rightEnd] = tmp[rightEnd];
}

//归并排序 分+调用合
void mergeSort(int arr[], int tmp[], int start, int end){   //要进行归并排序需要提供数组和原数组大小的辅助空间
    if(start >= end) return;   //依然是使用递归，所以说如果范围太小，就不用看了
    int mid = (start + end) / 2;   //先找到中心位置，一会分两半
    mergeSort(arr, tmp, start, mid);   //对左半和右半分别进行归并排序
    mergeSort(arr, tmp, mid + 1, end);
    merge(arr, tmp, start, mid, mid + 1, end);
    //上面完事之后，左边和右边都是有序状态了，此时再对整个范围进行一次归并排序即可
}

int main(){
    int arr[] = {3,5,7,2,9,0,6,1,8,4};
    int tmp[10];

    mergeSort(arr,tmp,0,9);

    for(int i = 0; i< 10; ++i){
        printf("%d ",arr[i]);
    }
}