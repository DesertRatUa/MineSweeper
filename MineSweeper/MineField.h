#pragma once

#include <vector>

enum eCell
{
	EMPTY,
	M1,
	M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8,
	M9,
	MINE,
	CLOSED,
};

class MineField
{
public:
	virtual void GenerateMineField(int width, int height, int mineCount) = 0;

	virtual eCell OpenCell(int x, int y) = 0;
	virtual eCell GetCellAt(int x, int y) const = 0;
	virtual void SetMine(int x, int y) = 0;
	virtual std::string PrintVisibleMineField() const = 0;
};


class MineFieldImpl : public MineField
{
protected:
	typedef std::vector<eCell> tMineFieldX;
	typedef std::vector<tMineFieldX> tMineFieldMap;

public:
	MineFieldImpl();
	~MineFieldImpl();

	std::string PrintMineField() const;

public:
	virtual void GenerateMineField(int width, int height, int mineCount);

	virtual eCell OpenCell(int x, int y);
	virtual eCell GetCellAt(int x, int y) const;
	virtual void SetMine(int x, int y);
	virtual std::string PrintVisibleMineField() const;

protected:
	const char* PrintCell(eCell cell) const;
	void GenerateRandomMine();
	void IncreaseMineCountAround(int x, int y);
	void IncreaseCell(int x, int y);
	bool CheckRange(int x, int y) const;
	void OpenNearbyCells(int x, int y);

protected:
	tMineFieldMap mField;
	tMineFieldMap mVisibleField;

	int mWidth;
	int mHeight;
};

