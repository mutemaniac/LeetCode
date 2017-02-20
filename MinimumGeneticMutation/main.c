#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Is there only ONE single character changed in the gene string?
int canMutation(char* rsh, char* lsh){  
    int ret = 0;
    for(int i=0 ; rsh[i]!='\0'; i++){
        if(rsh[i] != lsh[i]){
            if(++ret > 1){
                return ret;
            }
        }
    }
    return ret;
}

int minMutation(char* start, char* end, char** bank, int bankSize) {
    //Build Graph
    int endIndex = -1;
    int row = bankSize+1;
    int col = bankSize>strlen(start)?strlen(start):bankSize;
    int** graph = (int**)malloc(row*sizeof(int*));
    int* mutationsSize = (int*)malloc(row);
    for(int i=0; i<row-1; i++){
        graph[i] = (int*)malloc(col*sizeof(int));
        memset(graph[i], 0, col*sizeof(int));
        int mutationCnt = 0;
        for(int j=0; j<bankSize; j++){
            if(i!=j && 1==canMutation(bank[i],bank[j])){
                graph[i][mutationCnt++] = j;
            }
        }
        mutationsSize[i]=mutationCnt;
        if(0==canMutation(bank[i], end)){
            endIndex = i;
        }
    }
    if(-1 == endIndex){
        for (int i = 0; i < row-1; i++)
            free(graph[i]);
        free(mutationsSize);
        free(graph);
        return -1;
    }
    //init start
    {
        int i = row-1;
        graph[i] = (int*)malloc(col*sizeof(int));
        memset(graph[i], 0, col*sizeof(int));
        int mutationCnt = 0;
        for(int j=0; j<bankSize; j++){
            if(1==canMutation(start,bank[j])){
                graph[i][mutationCnt++] = j;
            }
        }
        mutationsSize[i]=mutationCnt;
    }
    
    //
    int mutationCnt = 0;
    unsigned char* mark = (unsigned char *)malloc(bankSize);
    memset(mark, 0, bankSize);
    int** pipes = (int**)malloc(sizeof(int*)*2);
    pipes[0] = (int*)malloc(sizeof(int)*bankSize);
    memset(pipes[0], 0, sizeof(int)*bankSize);
    pipes[1] = (int*)malloc(sizeof(int)*bankSize);
    memset(pipes[1], 0, sizeof(int)*bankSize);

    int pipesSize[2] = {1, 0};
    pipes[0][0] = row-1;
    mark[row-1] = 1;
    int pipeIndex = 0;

    do{
        int anotherPipe = (pipeIndex+1)%2;
        if(pipesSize[pipeIndex] > 0){
            for(int i=0; i<pipesSize[pipeIndex]; i++){
                int oneGen = pipes[pipeIndex][i];
                if(oneGen == endIndex){
                    free (pipes[1]);
                    free (pipes[0]);
                    free (pipes);
                    free (mark);
                    for (int i = 0; i < row; i++)
                        free (graph[i]);
                    free (mutationsSize);
                    free (graph);
                    return mutationCnt;
                }else{
                    for(int j=0;j<mutationsSize[oneGen]; j++){
                        if(!mark[graph[oneGen][j]]){
                            //pipesSize[(pipeIndex+1%2)]++;
                            pipes[anotherPipe][pipesSize[anotherPipe]]=graph[oneGen][j];
                            pipesSize[anotherPipe] += 1;
                            mark[graph[oneGen][j]] = 1;
                        }
                    }
                }
            }
        }else{
            break;
        }
        mutationCnt++;
        pipesSize[pipeIndex] = 0;
        pipeIndex = (pipeIndex+1)%2;
    }while(1);

    free (pipes[1]);
    free (pipes[0]);
    free (pipes);
    free (mark);
    for (int i = 0; i < row; i++)
        free (graph[i]);
    free (mutationsSize);
    free (graph);
    return -1;    
}


int main(){
    char*  start6 = "AAAAAAAA";
    char*  end6 = "AAGTAAAA";
    char*  bank6[] = {"CAAAAAAA","CCAAAAAA","CCATAAAA","CCGTAAAA","CAGTAAAA","AAGTAAAA"};
    int ret6 = minMutation(start6, end6, bank6, 6);
    printf("ret=%d\n", ret6);
    // char* start = "AACCGGTT";
    // char* end =   "AACCGGTA";
    // char* bank[] = {"AACCGGTA"};
    // char* start = "AACCGGTT";
    // char* end = "AAACGGTA";
    // char* bank[] = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    // char*  start = "AAAAACCC";
    // char*  end =   "AACCCCCC";
    // char*  bank[] = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    char*  start8 = "AAAACCCC";
    char*  end8 = "CCCCCCCC";
    char*  bank8[] = {"AAAACCCA","AAACCCCA","AACCCCCA","AACCCCCC","ACCCCCCC","CCCCCCCC","AAACCCCC","AACCCCCC"};
    int ret = minMutation(start8, end8, bank8, 8);
    printf("ret=%d\n", ret);
    
    
    return 0;
}
