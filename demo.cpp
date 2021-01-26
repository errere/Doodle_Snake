#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <codecvt>
#include <io.h>
#include <queue>
#include <random>
#include <time.h>
#include <algorithm>
#include <locale>     
#include <ctype.h>
#include <map>
#include <vector>
#include "snack.h"
#pragma comment(lib, "User32.lib")

using namespace std;



void show(snack_t* s) {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            printf("%02x ", getStage(s)[(i * 10) + j]);
        }
        printf("\r\n");
    }
    printf("\r\n");
    printf("\r\n");
    printf("sl : %d\r\n", s->snack_length);
    for (size_t i = 0; i < s->snack_length; i++)
    {
        printf("ssx : %d  ,  ssy : %d\r\n", s->snack_body_x[i], s->snack_body_y[i]);
	}
	printf("want_x : %d , want_y : %d\r\n", s->sanck_want_to_go_x, s->sanck_want_to_go_y);

	printf("\r\n");
	printf("disable : %d\r\n", getSnackNextStepDisable(s));
	if (s->haveFood) {
		printf("food_x : %d , food_y : %d\r\n", s->food_x, s->food_y);
		printf("\r\n");
	}
    printf("\r\n");
    printf("\r\n");
}

void showline(const char* c) {
    printf("----------%s----------\r\n", c);
}
int main() {
    snack_t g;
    init(&g, 8, 8);
    setFood(&g, 2, 2);
    showline("init");
    show(&g);

    tick(&g, 1, 1, 1);
    tick(&g, 1, 1, 1);
    tick(&g, 1, 1, 1);

    showline("move1");
    show(&g);

    tick(&g, 4, 1, 1);
    tick(&g, 4, 1, 1);
    tick(&g, 4, 1, 1);

    showline("move2");
    show(&g);
    tick(&g, 3, 1, 1);
    tick(&g, 3, 1, 1);
    tick(&g, 3, 1, 1);

    showline("move2");
    show(&g);
    
    

    return 0;
}
