#include "pch.h"
#include <iostream>
#include "MineField.h"
#include "Slover.h"

unsigned FIELD_SIZE_X = 10;
unsigned FIELD_SIZE_Y = 10;
unsigned MINE_COUNT = 10;

int main()
{
	MineFieldImpl mField;
	mField.GenerateMineField(FIELD_SIZE_X, FIELD_SIZE_Y, MINE_COUNT);
	std::cout << "Original map" << std::endl;
	std::cout << mField.PrintMineField().c_str() << std::endl;

	Slover slover;
	slover.SloveMineField(FIELD_SIZE_X, FIELD_SIZE_Y, MINE_COUNT, &mField);
}
