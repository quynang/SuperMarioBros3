#pragma once
#include "GameObject.h"
#include "Unit.h"

//Reference: https://gameprogrammingpatterns.com/spatial-partition.html

struct Cell {
	vector<LPUNIT> units;
};

 static int counter = 0;

class Grid {
public:

    Grid(int width, int height, int cellSize);
    ~Grid();

    void addUnit(LPUNIT unit);
    void addUnit(LPUNIT unit, Cell* cell);

    // Gets cell based on cell coordinates
    Cell* getCell(int x, int y);


    // Gets cell based on window coordinates
    Cell* getCell(D3DXVECTOR3 p);

    vector<LPGAMEOBJECT> extractGameObjectsFromUnits(vector<LPUNIT> units);
    void handleUpdate(DWORD dt);
    void handleRender();

    void mergeUnits(vector<LPUNIT> &units, vector<LPUNIT> otherUnits, int startIndex);
    
    void removeUnitFromCell(LPUNIT unit);

private:
   
    vector<Cell> m_cells;
    int m_cellSize;
    int m_width;
    int m_height;
    int m_numXCells;
    int m_numYCells;
};
