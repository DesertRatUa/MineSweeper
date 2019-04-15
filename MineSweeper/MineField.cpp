#include "pch.h"
#include "MineField.h"
#include <time.h>

MineFieldImpl::MineFieldImpl() : mWidth(0), mHeight(0)
{
}

MineFieldImpl::~MineFieldImpl()
{
}

void MineFieldImpl::GenerateMineField(int width, int height, int mineCount)
{
	mWidth = width;
	mHeight = height;

	tMineFieldX line(width, EMPTY);
	mField = tMineFieldMap(height, line);

	tMineFieldX vline(width, CLOSED);
	mVisibleField = tMineFieldMap(height, vline);

	int totalCells = width * height;

	if (mineCount > totalCells)
	{
		throw std::runtime_error("Mine > total cells");
	}

	srand(time(NULL));

	for (int i = 0; i < mineCount; ++i)
	{
		GenerateRandomMine();
	}
}

void MineFieldImpl::GenerateRandomMine()
{
	int x = rand() % mWidth;
	int y = rand() % mHeight;

	eCell &cell = mField[x][y];
	if (cell != MINE)
	{
		cell = MINE;
		IncreaseMineCountAround(x, y);
	}
	else
	{
		GenerateRandomMine();
	}
}

void MineFieldImpl::IncreaseMineCountAround(int x, int y)
{
	for (int y1 = y - 1; y1 <= y + 1; ++y1)
	{
		for (int x1 = x - 1; x1 <= x + 1; ++x1)
		{
			IncreaseCell(x1, y1);
		}
	}
}

void MineFieldImpl::IncreaseCell(int x, int y)
{
	if (CheckRange(x,y))
	{
		eCell &cell = mField[x][y];
		if (cell == MINE)
		{
			return;
		}
		else
		{
			cell = eCell(cell + 1);
		}
	}
}

bool MineFieldImpl::CheckRange(int x, int y) const
{
	return (x >= 0) && (x < int(mWidth)) && (y >= 0) && (y < int(mHeight));
}

eCell MineFieldImpl::OpenCell(int x, int y)
{
	if (!CheckRange(x, y))
	{
		throw std::runtime_error("Out of field range");
	}

	eCell cell = mVisibleField[x][y];
	if (cell != CLOSED)
	{
		return cell;
	}

	cell = mVisibleField[x][y] = mField[x][y];
	if (cell == MINE)
	{
		return cell;
	}

	OpenNearbyCells(x, y);

	return cell;
}

void MineFieldImpl::OpenNearbyCells(int x, int y)
{
	for (int y1 = y - 1; y1 <= y + 1; ++y1)
	{
		for (int x1 = x - 1; x1 <= x + 1; ++x1)
		{
			if (!CheckRange(x1, y1))
			{
				continue;
			}
			eCell cell = mVisibleField[x1][y1];
			if (cell != CLOSED)
			{
				continue;
			}
			cell = mField[x1][y1];
			if (cell == MINE)
			{
				continue;
			}
			mVisibleField[x1][y1] = cell;
			if (cell == EMPTY)
			{
				OpenNearbyCells(x1, y1);
			}
		}
	}
}

eCell MineFieldImpl::GetCellAt(int x, int y) const
{
	if (!CheckRange(x, y))
	{
		throw std::runtime_error("Out of field range");
	}
	return mVisibleField[x][y];
}

void MineFieldImpl::SetMine(int x, int y)
{
	if (!CheckRange(x, y))
	{
		throw std::runtime_error("Out of field range");
	}
	mVisibleField[x][y] = MINE;
}

std::string MineFieldImpl::PrintMineField() const
{
	std::string field;
	for (auto ity : mField)
	{
		for (auto itx : ity)
		{
			field += PrintCell(itx);
		}
		field += "\n";
	}
	return field;
}

std::string MineFieldImpl::PrintVisibleMineField() const
{
	std::string field;
	for (auto ity : mVisibleField)
	{
		for (auto itx : ity)
		{
			field += PrintCell(itx);
		}
		field += "\n";
	}
	return field;
}

const char* MineFieldImpl::PrintCell(eCell cell) const
{
	switch (cell)
	{
	case EMPTY:
		return ".";
		break;
	
	case M1:
		return "1";
		break;
	
	case M2:
		return "2";
		break;
	
	case M3:
		return "3";
		break;

	case M4:
		return "4";
		break;

	case M5:
		return "5";
		break;

	case M6:
		return "6";
		break;

	case M7:
		return "7";
		break;

	case M8:
		return "8";
		break;

	case M9:
		return "9";
		break;

	case MINE:
		return "M";
		break;
	
	case CLOSED:
		return "C";
		break;
	}
}