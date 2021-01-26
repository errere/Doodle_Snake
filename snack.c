#include "snack.h"

void init(snack_t* game, uint8_t width, uint8_t height)
{
	uint8_t real_width = width + 2;
	uint8_t real_height = height + 2;

	game->stage_Width = real_width;
	game->stage_Height = real_height;

	uint16_t stage_size = real_width * real_height;

	game->stage = nullptr;
	do
	{
		game->stage = (uint8_t*)malloc(stage_size * sizeof(uint8_t));
	} while (game->stage == nullptr);

	game->snack_body_x = nullptr;
	do
	{
		game->snack_body_x = (uint8_t*)malloc(stage_size * sizeof(uint8_t));
	} while (game->snack_body_x == nullptr);

	game->snack_body_y = nullptr;
	do
	{
		game->snack_body_y = (uint8_t*)malloc(stage_size * sizeof(uint8_t));
	} while (game->snack_body_y == nullptr);


	memset(game->stage, 0x00, (stage_size * sizeof(uint8_t)));
	memset(game->snack_body_x, 0x00, (stage_size * sizeof(uint8_t)));
	memset(game->snack_body_y, 0x00, (stage_size * sizeof(uint8_t)));

	uint16_t temp = (game->stage_Height - 1) * game->stage_Width;
	for (uint8_t i = 0; i < game->stage_Width; i++)
	{
		game->stage[i] = 0xff;
		game->stage[temp + i] = 0xff;
	}
	for (uint8_t i = 1; i < game->stage_Height - 1; i++)
	{
		game->stage[i * game->stage_Width] = 0xff;
		game->stage[(i * game->stage_Width) + (game->stage_Width - 1)] = 0xff;
	}


	game->snack_length = 1;
	game->snack_body_x[0] = game->stage_Width / 2;
	game->snack_body_y[0] = game->stage_Height / 2;
	//debug
	/*game->snack_length += 1;
	game->snack_body_x[1] = game->snack_body_x[0] + 1;
	game->snack_body_y[1] = game->snack_body_y[0];
	game->stage[posToIndex(game, game->snack_body_x[1], game->snack_body_y[1])] = 0x01;
	game->sanck_want_to_go_x = game->snack_body_x[0];
	game->sanck_want_to_go_y = game->snack_body_y[0]-1;
	game->stage[posToIndex(game, game->sanck_want_to_go_x, game->sanck_want_to_go_y)] = 0x0c;*/
	//debug
	game->stage[posToIndex(game, game->snack_body_x[0], game->snack_body_y[0])] = 0x01;
	game->sanck_want_to_go_x = 0;
	game->sanck_want_to_go_y = 0;

	game->haveFood = false;

	game->opode = 0;

	game->foodCounter = 0;
	game->isGameover = 0;
}

void distory(snack_t* game) {
	if (game->stage != 0) {
		free(game->stage);
	}
	if (game->snack_body_x != 0) {
		free(game->snack_body_x);
	}
	if (game->snack_body_y != 0) {
		free(game->snack_body_y);
	}
}
//in
uint8_t tick(snack_t* game, uint8_t opcode,uint8_t foodx,uint8_t foody)
{
	input(game, opcode);

	if (isHitWall(game)) {
		game->isGameover = 1;
		return 255;
	}

	setFood(game, foodx, foody);

	if (isEat(game)) {
		eat(game);
		return 1;
	}
	else {
		snakeMove(game);
		return 0;
	}
	
}
void input(snack_t* game, uint8_t opcode)
{
	game->opode = opcode;
	if (game->opode == getSnackNextStepDisable(game)) {
		printf("disable!!!\r\n");
		game->opode = 0;
	}
	switch (game->opode)
	{
	case 1://up
		game->sanck_want_to_go_x = game->snack_body_x[0];
		game->sanck_want_to_go_y = game->snack_body_y[0] - 1;
		break;
	case 2://right
		game->sanck_want_to_go_x = game->snack_body_x[0] + 1;
		game->sanck_want_to_go_y = game->snack_body_y[0];
		break;
	case 3://down
		game->sanck_want_to_go_x = game->snack_body_x[0];
		game->sanck_want_to_go_y = game->snack_body_y[0] + 1;
		break;
	case 4://left
		game->sanck_want_to_go_x = game->snack_body_x[0] - 1;
		game->sanck_want_to_go_y = game->snack_body_y[0];
		break;
	default:
		break;
	}
	/*if (game->opode != 0) {
		game->stage[posToIndex(game, game->sanck_want_to_go_x, game->sanck_want_to_go_y)] = 0x0c;
	}*/
}
void snakeMove(snack_t* game) {
	if (isHitWall(game)) {
		return;
	}
	game->stage[posToIndex(game, game->snack_body_x[game->snack_length - 1], game->snack_body_y[game->snack_length - 1])] = 0x00;
	for (int16_t i = (game->snack_length - 1); i >= 0 ; i--)
	{
		game->snack_body_x[i + 1] = game->snack_body_x[i];
		game->snack_body_y[i + 1] = game->snack_body_y[i];
	}
	game->snack_body_x[0] = game->sanck_want_to_go_x;
	game->snack_body_y[0] = game->sanck_want_to_go_y;
	game->stage[posToIndex(game, game->snack_body_x[0], game->snack_body_y[0])] = 0x01;
	game->sanck_want_to_go_x = 0;
	game->sanck_want_to_go_y = 0;

}
//out
uint8_t* getStage(snack_t* game)
{
	return game->stage;
}
uint8_t getStageWidth(snack_t* game)
{
	return game->stage_Width;
}
uint8_t getStageHeight(snack_t* game)
{
	return game->stage_Height;
}
uint16_t getScore(snack_t* game)
{
	return game->foodCounter;
}

//inside
uint16_t posToIndex(snack_t* game, uint8_t x, uint8_t y)
{
	return (y * game->stage_Width) + x;
}
uint8_t indexToPos(snack_t* game, uint16_t index, uint8_t* dst_x, uint8_t* dst_y) {
	if (index > (game->stage_Height * game->stage_Width)) {
		return ERR;
	}
	uint8_t x = index % game->stage_Width;
	uint8_t y = index / game->stage_Width;
	/*game->stage[index] = 0xcc;
	printf("ppx:%d,ppy:%d\n", x, y);*/
	return OK;
}

bool setFood(snack_t* game, uint8_t x, uint8_t y)
{
	if (game->haveFood == true)
	{
		return ERR;
	}
	if (x < 1 || x >= (game->stage_Width - 1))
	{
		return ERR;
	}
	if (y < 1 || y >= (game->stage_Height - 1))
	{
		return ERR;
	}
	game->stage[posToIndex(game, x, y)] = 0x02;
	game->haveFood = true;
	game->food_x = x;
	game->food_y = y;
	return OK;
}

bool isEat(snack_t* game)
{
	if (game->sanck_want_to_go_x == game->food_x) {
		if (game->sanck_want_to_go_y == game->food_y)
		{
			return 1;
		}
	}
	return 0;
}
void eat(snack_t* game) {
	if (isEat(game)) {
		game->stage[posToIndex(game, game->snack_body_x[game->snack_length - 1], game->snack_body_y[game->snack_length - 1])] = 0x00;
		for (int16_t i = (game->snack_length - 1); i >= 0; i--)
		{
			game->snack_body_x[i + 1] = game->snack_body_x[i];
			game->snack_body_y[i + 1] = game->snack_body_y[i];
		}
		game->snack_body_x[0] = game->food_x;
		game->snack_body_y[0] = game->food_y;
		game->stage[posToIndex(game, game->snack_body_x[0], game->snack_body_y[0])] = 0x01;
		game->snack_length += 1;
		game->stage[posToIndex(game, game->snack_body_x[game->snack_length - 1], game->snack_body_y[game->snack_length - 1])] = 0x01;
		game->food_x = 0;
		game->food_y = 0;
		game->haveFood = 0;
		game->foodCounter += 1;
	}
}
bool isHitWall(snack_t* game)
{
	if (game->stage[posToIndex(game, game->sanck_want_to_go_x, game->sanck_want_to_go_y)] == 0xff) {
		return 1;
	}
	return 0;
}

uint8_t getSnackNextStepDisable(snack_t* game) {
	//0:any , 1:up , 2:right , 3:down , 4:left
	if (game->snack_length <= 1)
	{
		return 0;
	}
	int8_t dx = game->snack_body_x[0] - game->snack_body_x[1];
	int8_t dy = game->snack_body_y[0] - game->snack_body_y[1];
	//printf("dx:%d , dy:%d\r\n", dx, dy);
	if (dx == 0)
	{
		if (dy >= 0)
		{
			return 1;
		}
		else {
			return 3;
		}
	}
	if (dy == 0) {
		if (dx >= 0) {
			return 4;
		}
		else {
			return 2;
		}
	}
	return 0;
}

bool isGameOver(snack_t* game)
{
	return game->isGameover;
}
