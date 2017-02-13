#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target) {
    int* retIndices = (int*)malloc(sizeof(int)*2);
    for(int i=0; i< numsSize; i++){
        for(int j=i+1;j<numsSize;j++){
            if(*(nums+i)+*(nums+j) == target){
                *retIndices = i;
                *(retIndices+1) = j;
                return retIndices;
            }else{
                continue;
            }
        }
    }
    return retIndices;
}

int main(){
   int nums[] = {11, 7, 2, 15};
   int target = 9;
   int* ret = twoSum(nums, sizeof(nums), target);
   printf("Hello World.\n %d, %d\n", *ret, *(ret+1));
   return 0;
}

