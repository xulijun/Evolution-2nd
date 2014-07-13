#include "EvolutionTest.h"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
Cell::Cell(Point pt, char cStates)
: m_ptPos(pt)
, m_cStates(cStates)
{

}

Cell::~Cell()
{

}

void Cell::ChangeStates()
{
	int nNeighNum = CellMgr::GetMgr()->GetNeighboursNum(this);

	if (m_cStates == LIVE_STATUS)
	{
		if (nNeighNum < 2 || nNeighNum > 3)
		{
			m_cStates = DEAD_STATUS;
		}
	}
	else if (m_cStates == DEAD_STATUS && nNeighNum == 3)
	{
		m_cStates = LIVE_STATUS;
	}
}

void Cell::Show()
{
	cout << m_cStates;
}

bool Cell::operator==(const Cell& other)
{
	if (this == &other)
		return true;

	if (m_ptPos.X == other.m_ptPos.X && m_ptPos.Y == other.m_ptPos.Y)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////

CellMgr* CellMgr::pCellMgr = NULL;
CellMgr* CellMgr::GetMgr()
{
	if (pCellMgr == NULL)
	{
		pCellMgr = new CellMgr;
	}

	return pCellMgr;
}

CellMgr::CellMgr()
: m_nSizeX(0)
, m_nSizeY(0)
, m_bShowOne(true)
{

}

void CellMgr::CreateAllDeadCells(unsigned int nSizeX, unsigned int nSizeY)
{
	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;

	for (int j = 0; j < nSizeY; ++j)
	{
		for (int i = 0; i < nSizeX; ++i)
		{ 
			Cell c(Point(i, j), DEAD_STATUS);
			m_vecMgrOne.push_back(c);
			m_vecMgrTwo.push_back(c);
		}
	}
}

void CellMgr::CreateLiveCell(const vector<Cell> &vecCell)
{
	for (int i = 0; i < m_vecMgrOne.size(); ++i)
	{
		for (int j = 0; j< vecCell.size(); ++j)
		{
			if (m_vecMgrOne[i] == vecCell[j])
			{
				m_vecMgrOne[i].SetStates(LIVE_STATUS);
				m_vecMgrTwo[i].SetStates(LIVE_STATUS);
			}
		}
	}
}

void CellMgr::CreateLiveCell(const vector<Point> &vecPoint, char cStates)
{
	
}

int CellMgr::GetNeighboursNum(Cell * const pCell)
{
	if (pCell == NULL)
		return -1;

	int nCount = 0;
	Cell newCell(*pCell);
	vector<Cell>::iterator iter;

	for (int j = pCell->GetPosition().Y - 1; j <= pCell->GetPosition().Y + 1; ++j)
	{
		for (int i = pCell->GetPosition().X - 1; i <= pCell->GetPosition().X + 1; ++i)
		{
			newCell.SetPoint(i, j);
			if (m_bShowOne)
			{
				iter = find(m_vecMgrTwo.begin(), m_vecMgrTwo.end(), newCell);
				if ((iter != m_vecMgrTwo.end()) && (iter->GetPosition() == newCell.GetPosition()) && (iter->GetStates() == LIVE_STATUS))
				{
					nCount++;
				}
			}
			else
			{
				iter = find(m_vecMgrOne.begin(), m_vecMgrOne.end(), newCell);
				if (iter != m_vecMgrOne.end() && iter->GetPosition() == newCell.GetPosition() && iter->GetStates() == LIVE_STATUS)
				{
					nCount++;
				}
			}

		}
	}

	return nCount;
}

void CellMgr::Evolution(unsigned int nRepeatNum)
{
	while(nRepeatNum--)
	{
		if (m_bShowOne)
		{
			for (int i = 0; i< m_vecMgrOne.size(); ++i)
			{
				if (m_vecMgrOne[i].GetPosition().X == 0 || m_vecMgrOne[i].GetPosition().X == m_nSizeX - 1 ||
					m_vecMgrOne[i].GetPosition().Y == 0 || m_vecMgrOne[i].GetPosition().Y == m_nSizeY - 1)
				{
					continue;
				}
				m_vecMgrOne[i].ChangeStates();
			}
		}
		else
		{
			for (int j = 0; j < m_vecMgrTwo.size(); ++j)
			{
				if (m_vecMgrTwo[j].GetPosition().X == 0 || m_vecMgrTwo[j].GetPosition().X == m_nSizeX - 1 ||
					m_vecMgrTwo[j].GetPosition().Y == 0 || m_vecMgrTwo[j].GetPosition().Y == m_nSizeY - 1)
				{
					continue;
				}
				m_vecMgrTwo[j].ChangeStates();
			}
		}

		ShowAllCells();

		m_bShowOne = !m_bShowOne;
	}

}

void CellMgr::ShowAllCells()
{
	if (m_bShowOne)
	{
		for (int j = 0; j < m_nSizeY; ++j)
		{
			for (int i = 0; i < m_nSizeX; ++i)
			{
				Point ptHit(i, j);
				for (int n = 0; n < m_vecMgrOne.size(); ++n)
				{
					if (m_vecMgrOne[n].GetPosition() == ptHit)
						cout << m_vecMgrOne[n].GetStates() << ' ';
				}
			}
			cout << endl;
		}
	}
	else
	{
		for (int j = 0; j < m_nSizeY; ++j)
		{
			for (int i = 0; i < m_nSizeX; ++i)
			{
				Point ptHit(i, j);
				for (int n = 0; n < m_vecMgrTwo.size(); ++n)
				{
					if (m_vecMgrTwo[n].GetPosition() == ptHit)
						cout << m_vecMgrTwo[n].GetStates() << ' ';
				}
			}
			cout << endl;
		}
	}

	cout << "=================" << endl;
}

int main()
{
	vector<Cell> vecCell;
	Point pt1(4, 5);
	Point pt2(5,4);
	Point pt3(5, 5);

	Cell c1(pt1, LIVE_STATUS);
	Cell c2(pt2, LIVE_STATUS);
	Cell c3(pt3, LIVE_STATUS);
	vecCell.push_back(c1);
	vecCell.push_back(c2);
	vecCell.push_back(c3);

	CellMgr::GetMgr()->CreateAllDeadCells(10, 10);
	CellMgr::GetMgr()->CreateLiveCell(vecCell);
	CellMgr::GetMgr()->Evolution(4);

}