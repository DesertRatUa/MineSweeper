#include "pch.h"
#include "Slover.h"
#include <iostream>

Slover::Slover() : mWidth(0), mHeight(0), mMineCount(0), mFoundMineCount(0), mCellsOpen(0), mMineField(NULL)
{
}

Slover::~Slover()
{
}

void Slover::SloveMineField(int width, int height, int mineCount, MineField* mineField)
{
	mWidth = width;
	mHeight = height;
	mMineCount = mineCount;
	mFoundMineCount = 0;
	mMineField = mineField;
	
	int centerX = width / 2;
	int centerY = height / 2;
	unsigned step = 1;

	eCell cell = mMineField->OpenCell(centerX, centerY);
	std::cout << "Step " << step << std::endl;
	std::cout << mMineField->PrintVisibleMineField().c_str() << std::endl;

	if (cell == MINE)
	{
		std::cout << "Bad luck" << std::endl;
		return;
	}

	try 
	{
		while (mFoundMineCount < mMineCount)
		{
			++step;
			mCellsOpen = 0;
			CheckAllNumbers();
			if (!mCellsOpen)
			{
				throw std::runtime_error("stuck");
			}
			std::cout << "Step " << step << std::endl;
			std::cout << mMineField->PrintVisibleMineField().c_str() << std::endl;
		}
		std::cout << "Slover done. All " << mMineCount << " mines was found in " << step << " steps" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Slover failed: "  << e.what() << std::endl;
	}
}

void Slover::CheckAllNumbers()
{
	for (int y1 = 0; y1 < mHeight; ++y1)
	{
		for (int x1 = 0; x1 < mWidth; ++x1)
		{
			eCell cell = mMineField->GetCellAt(x1, y1);
			if (cell >= M1 && cell <= M9)
			{
				CheckAround(x1, y1);
			}
		}
	}
}

void Slover::CheckAround(int x, int y)
{
	tCoordVec closedCells;
	unsigned mineCount = 0;
	for (int y1 = y - 1; y1 <= y + 1; ++y1)
	{
		for (int x1 = x - 1; x1 <= x + 1; ++x1)
		{
			if (CheckRange(x1, y1))
			{
				eCell cell = mMineField->GetCellAt(x1, y1);
				if (cell == CLOSED)
				{
					closedCells.push_back(std::pair<int, int>(x1, y1));
				}
				else if (cell == MINE)
				{
					++mineCount;
				}
			}
		}
	}
	eCell cell = mMineField->GetCellAt(x, y);
	unsigned count = cell;
	if (count == mineCount)
	{
		for (auto it : closedCells)
		{
			++mCellsOpen;
			eCell cell = mMineField->OpenCell(it.first, it.second);
			if (cell == MINE)
			{
				std::runtime_error("Mine blown");
			}
		}
	}
	else
	{
		if (count != closedCells.size())
		{
			return;
		}

		for (auto it : closedCells)
		{
			mMineField->SetMine(it.first, it.second);
			++mFoundMineCount;
			++mCellsOpen;
		}
	}
}

bool Slover::CheckRange(int x, int y) const
{
	return (x >= 0) && (x < int(mWidth)) && (y >= 0) && (y < int(mHeight));
}