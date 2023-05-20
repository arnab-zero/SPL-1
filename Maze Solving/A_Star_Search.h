#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include<stdio.h>

class AStarSearch{

private:
    int sum;

public:
    AStarSearch(){
        sum = 0;
    }

public:
    void add(int n){

        sum += n;

    }

    void printSum(){

        printf("The sum is: %d\n", sum);
    }

};

#endif
