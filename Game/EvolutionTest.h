#ifndef __CELLMGR_H__
#define  __CELLMGR_H__

const char DEAD_STATUS = '.';
const char LIVE_STATUS = '*';
const int ROW_NUM = 10;		//map's size
const int COL_NUM = 10;

#include <iostream>
#include <vector>
using namespace std;

class CellMgr;

//class point to record the x-coordination and y-coordination info
class Point
{
public:
	Point();
	Point(int x, int y):X(x), Y(y){}
	const Point& operator=(const Point &other);
	bool operator==(const Point &other);

	int X;
	int Y;
};

const Point& Point::operator=(const Point &other)
{
	if (this == &other)
		return *this;
	this->X = other.X;
	this->Y = other.Y;
	return *this;
}

bool Point::operator==(const Point &other)
{
	if (this == &other)
		return true;

	if (X == other.X && Y == other.Y)
		return true;
	else
		return false;
}

//a cell whose state is live or dead, and can change its states
class Cell
{
public:
	Cell(Point pt, char cStates);
	virtual ~Cell();
	void ChangeStates();
	void Show();	
	bool operator==(const Cell &other);
	inline void SetPoint(int nX, int nY){m_ptPos.X = nX; m_ptPos.Y = nY;}
	inline Point GetPosition(){return m_ptPos;}
	inline char GetStates(){return m_cStates;}
	inline void SetStates(const char &c){m_cStates = c;}

private:
	Point m_ptPos;						
	char m_cStates;
};


//a singleton to manage the cells
class CellMgr
{
public:
	static CellMgr* GetMgr();
private:
	CellMgr(void);
	static CellMgr *pCellMgr;


public:
	void CreateAllDeadCells(unsigned int nSizeX, unsigned int nSizeY);				//1. first invoke to set width and height of a two-dimension
	void CreateLiveCell(const vector <Point> &vecPoint, char cStates);				//2. Create live cell by the overloaded function.
	void CreateLiveCell(const vector <Cell> &vecCell);
	int GetNeighboursNum(Cell *const pCell);																//get the number of pCell's neighbour 
	void Evolution(unsigned int nRepeatNum);																							//evolution to next generation
private:
	void ShowAllCells();																						//print result

private:
	vector <Cell> m_vecMgrOne;																		
	vector <Cell> m_vecMgrTwo;
	bool m_bShowOne;
	unsigned int m_nSizeX, m_nSizeY;
};

#endif