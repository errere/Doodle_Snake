#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#ifndef __SNACK_H__
#define __SNACK_H__

#define ERR 0
#define OK 1

typedef struct
{
	//map
	uint8_t stage_Width;
	uint8_t stage_Height;
	uint8_t* stage;//00:air,ff:wall,02:food,01:player

	//player
	uint8_t snack_length;
	uint8_t* snack_body_x;//1 to stage_Width - 2
	uint8_t* snack_body_y;//1 to stage_Height - 2
	uint8_t sanck_want_to_go_x;
	uint8_t sanck_want_to_go_y;

	//food
	bool haveFood;
	uint8_t food_x;
	uint8_t food_y;

	//input
	uint8_t opode; //0 = idle,1 = up,2 = right,3 = down,4 = left

	//other
	uint16_t foodCounter;
	bool isGameover;
} snack_t;

void init(snack_t* game, uint8_t width, uint8_t height);
void distory(snack_t* game);

//in
uint8_t tick(snack_t* game, uint8_t opcode, uint8_t foodx, uint8_t foody);
void input(snack_t* game, uint8_t opcode);
void snakeMove(snack_t* game);

//out
uint8_t* getStage(snack_t* game);
uint8_t getStageWidth(snack_t* game);
uint8_t getStageHeight(snack_t* game);
uint16_t getScore(snack_t* game);

//inside
//void setFoodRandom(snack_t *game, int (*randomFx)(void));
uint16_t posToIndex(snack_t* game, uint8_t x, uint8_t y);
uint8_t indexToPos(snack_t* game, uint16_t index, uint8_t* dst_x, uint8_t* dst_y);

bool setFood(snack_t* game, uint8_t x, uint8_t y);
bool isEat(snack_t* game);
void eat(snack_t* game);

bool isHitWall(snack_t* game);

uint8_t getSnackNextStepDisable(snack_t* game);

bool isGameOver(snack_t* game);

#endif