#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pacific (0x1)
#define atlantic (0x2)
#define both (0x3)
#define land (0x4)



unsigned char gogo(int** matrix, int matrixRowSize, int matrixColSize, 
                    unsigned char** map, int x, int y, 
                    int* returnSize){
    if(map[x][y]){
        return map[x][y];
    }
    if(x==0){
        map[x][y] = map[x][y] | pacific;
    }else{
        //x-1
        if(matrix[x][y] >= matrix[x-1][y]){// Can flow to x-1
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x-1, y, returnSize);
            // if((map[x][y]&both) == both ){
            //     //Can flow to both the Pacific and Atlantic ocean 
            //     return map[x][y];
            // }
        }
    }
    if(x == (matrixRowSize-1)){
        map[x][y] = map[x][y] | atlantic;
    }else{
        //x+1
        if(matrix[x][y] >= matrix[x+1][y]){ // Can flow to x+1
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x+1, y, returnSize);
            // if((map[x][y]&both) == both ){
            //     //Can flow to both the Pacific and Atlantic ocean 
            //     return map[x][y];
            // }
        }
    }
    if(y == 0){
        map[x][y] = map[x][y] | pacific;
    }else{
        //y-1
        if(matrix[x][y] >= matrix[x][y-1]){ // Can flow to y-1
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x, y-1, returnSize);
            // if((map[x][y]&both) == both ){
            //     //Can flow to both the Pacific and Atlantic ocean 
            //     return map[x][y];
            // }
        }
    }
    if(y == (matrixColSize-1)){
        map[x][y] = map[x][y] | atlantic;
    }else{
        //y+1
        if(matrix[x][y] >= matrix[x][y-1]){ // Can flow to y+1
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x, y+1, returnSize);
            // if((map[x][y]&both) == both ){
            //     //Can flow to both the Pacific and Atlantic ocean 
            //     return map[x][y];
            // }
        }
    }

    if(map[x][y]==0){
        map[x][y] = land;
    }else  if((map[x][y]&both) == both ){
        //Can flow to both the Pacific and Atlantic ocean 
        *returnSize += 1;
    }
    return map[x][y];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** matrix, int matrixRowSize, int matrixColSize, int** columnSizes, int* returnSize) {
    *returnSize = 0;
    unsigned char** map = (unsigned char**)malloc(sizeof(unsigned char*) * matrixRowSize);
    for(int i=0;i<matrixRowSize;i++){
        *map = (unsigned char*)malloc(sizeof(unsigned char)*matrixColSize);
        memset(map, 0, (size_t)matrixColSize);
    }
    for(int i=0; i<matrixRowSize; i++){
        for(int j=0; j<matrixColSize; i++){
            gogo(matrix, matrixRowSize, matrixColSize, map, i, j, returnSize);
        }
    }

    int** ret = (int**)malloc(sizeof(int*) * (*returnSize));
    int* retcs = (int*)malloc(sizeof(int) * (*returnSize));
    int k = 0;
    for(int i=0; i<matrixRowSize; i++){
        for(int j=0; j<matrixColSize; i++){
            if((map[i][j]&both) == both){
                //
                ret[k] = (int*)malloc(sizeof(int)*2);
                ret[k][0] = i;
                ret[k][1] = j;
                retcs[k] = 2;
                k++;
            }
        }
    }

    *columnSizes = retcs;
    return ret;
}

int main(){


    return 0;
}