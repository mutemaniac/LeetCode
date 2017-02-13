#include <stdio.h>
#include <stdlib.h>
#include "time.h" 

#define debug 0

int fromFront(int);
int fromEnd(int);
int fronts[1024]={0};
int ends[1024]={0}; 

int fromFront(int n){
    if(2 == n){
        return 2;
    }
    if(3 == n){
        return 2;
    }
    if(n<1024){
        if(fronts[n]){
            return fronts[n];
        }else{
            fronts[n] = fromEnd(n>>1)<<1;
            return fronts[n];
        }
    }
    return fromEnd(n>>1)<<1;
}

int fromEnd(int n){
    if(2 == n){
        return 1;
    }
    if(3 == n){
        return 2;
    }
    if(n<1024){
        if(ends[n]){
            return ends[n];
        }else{
            int removed = n>>1;
            if (n & 0x01){
                //奇数
                ends[n] =  fromFront(removed)<<1;
            }else{
                //偶数
                ends[n] = (fromFront(removed)<<1)-1;
            }
            return ends[n];
        }
    }

    int removed = n>>1;
    if (n & 0x01){
        //奇数
        return fromFront(removed)<<1;
    }else{
        //偶数
        return (fromFront(removed)<<1)-1;
    }
}

int lastRemaining1(int n) {
    if(1==n){
        return 1;
    }
    return fromFront(n);
}

int lastRemaining(int n) {
    int i = 1;  //正向 or 反向
    int val = 1;
    int subtrahend = 0;
    do{
        if(1==n){
            val= val;
            break;
        }
        if(i&0x01){//正向  
            if(2 == n){
                val = val<<1;
                break;
            }
            if(3 == n){
                val = val<<1;
                break;
            }
            val = val << 1;
            n = n >> 1;
        }else{//反向
            if(2 == n){
                break;
            }
            if(3 == n){
                val = val << 1;
                break;
            }
            if (n & 0x01){
                //奇数
                val = val << 1;
            }else{
                //偶数
                subtrahend = subtrahend + val; 
                val = val << 1;
            }
            n = n >> 1;
        }
        i++;
    } while(true);
    return val-subtrahend;
}


int main(){
    #if debug
    int i = 12;
    int ret = lastRemaining(i);
    printf("%d -- %d\n", i, ret);
    #else
    clock_t start, end;
    int nums[] = {1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096,
        1002, 300099, 94967293, 2678, 76543689, 1234567, 87654321, 3692634, 1024, 4096};
    start = clock(); 
    for(int i=0;i<100;i++){
        int ret = lastRemaining1(nums[i]);
    }
    end = clock();
    printf("lastRemaining1 = %lu\n", end-start);


    start = clock(); 
    for(int i=0;i<100;i++){
        int ret = lastRemaining(nums[i]);
    }
    end = clock();
    printf("lastRemaining = %lu\n", end-start);

   
    for(int i=0;i<100;i++){
        if(lastRemaining(nums[i]) != lastRemaining1(nums[i])){
            printf("!!!!!!!!!");
        }
    }
    #endif

    printf("hello world!\n");
    return 0;
}