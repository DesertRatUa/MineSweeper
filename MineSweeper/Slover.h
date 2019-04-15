#pragma once
#include "MineField.h"

class Slover
{
protected:
	typedef std::vector<std::pair<int, int>> tCoordVec;

public:
	Slover();
	~Slover();

	void SloveMineField(int width, int height, int mineCount, MineField* mineField);

protected:
	void CheckAllNumbers();
	void CheckAround(int x, int y);
	bool CheckRange(int x, int y) const;

protected:
	int mWidth;
	int mHeight;
	int mMineCount;
	int mFoundMineCount;
	unsigned mCellsOpen;
	MineField* mMineField;
};

