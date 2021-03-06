#pragma once
#include "GameObject.h"
#include "Unit.h"

//Reference: https://gameprogrammingpatterns.com/spatial-partition.html

//Cell is contain a Doubly Linked List of Unit.
struct Cell {
	Unit* head = NULL;
    Unit* tail = NULL;
};

class Grid {
    LPCWSTR filePath;
public:

    Grid(LPCWSTR filePath);
    ~Grid();

    void addUnitToLastOfCell(LPUNIT unit);
    void addUnitToSpecificCell(LPUNIT unit, Cell* cell);
    void addUnitToFirstOfCell(LPUNIT unit);
    void Load();
    void _parseSection_INFO(string line);
    void _parseSection_CELLS(string line);

    // Gets cell based on cell coordinates
    Cell* getCell(int x, int y);

    void extractGameObjectFromCell(Cell *cell, Unit *unit_to_start, vector<LPGAMEOBJECT> &gameObjects);

    // Gets cell based on window coordinates
    Cell* getCell(D3DXVECTOR3 p);

    void handleUpdate(DWORD dt);
    void handleRender();    
    void removeUnitFromCell(LPUNIT unit);
    void findGameObjectsByTag(string tagName, vector<LPGAMEOBJECT>& resultObjects);

private:
   
    vector<Cell> m_cells;
    int m_cellSize;
    int m_width;
    int m_height;
    int m_numXCells;
    int m_numYCells;
};
