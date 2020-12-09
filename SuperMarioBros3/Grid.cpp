#include "Grid.h"
#include "Utils.h"

Grid::Grid(int width, int height, int cellSize) {
	this->m_cellSize = cellSize;
	this->m_width = width;
	this->m_height = height;
	this->m_numXCells = (int) width / cellSize;
	this->m_numYCells = (int)height / cellSize;
    this->m_cells.resize(m_numYCells * m_numXCells);
}

void Grid::addUnit(LPUNIT unit) {
	Cell* cell = this->getCell(unit->object->GetPosition());
	cell->units.push_back(unit);
	unit->ownerCell = cell;
	unit->cellVectorIndex = cell->units.size() - 1;
}

void Grid::addUnit(LPUNIT unit, Cell* cell) {
    cell->units.push_back(unit);
    unit->ownerCell = cell;
    unit->cellVectorIndex = cell->units.size() - 1;
}

Cell* Grid::getCell(int x, int y) {

	if (x < 0) x = 0;
    if (x >= m_numXCells) x = m_numXCells - 1;
    if (y < 0) y = 0;
    if (y >= m_numYCells) y = m_numYCells - 1;

    //Actually, m_cells is one dimensional array. But we describe it as two dimenional array by defined cell x, cell y.
    //So we have this statement bellow. It reflect the thing above.
    return &m_cells[y * m_numXCells + x];
}


Cell* Grid::getCell(D3DXVECTOR3 p) {
	int cellX = (int)(p.x / m_cellSize);
    int cellY = (int)(p.y / m_cellSize);

    return getCell(cellX, cellY);
}


void Grid::handleUpdate(DWORD dt) {

	  for (size_t i = 0; i < m_cells.size(); i++) {

        //Reflect two dimentions array.
        int x = i % m_numXCells;
        int y = i / m_numXCells;

        Cell& cell = m_cells[i];

        for (size_t j = 0; j < cell.units.size(); j++) {
            vector<LPUNIT> units;
            Unit* unit = cell.units[j];
   
            //residing cell
            mergeUnits(units, cell.units, j+1);

            // Update collision with neighbor cells. Reference: https://gameprogrammingpatterns.com/spatial-partition.html 

            if (x > 0) {
                // Left
                mergeUnits(units, getCell(x - 1, y)->units, 0);

                if (y > 0) {
                    // Top left
                    mergeUnits(units, getCell(x - 1, y - 1)->units, 0);
                }
                if (y < m_numYCells - 1) {
                    // Bottom left
                    mergeUnits(units, getCell(x - 1, y + 1)->units, 0);
                }
            }
            // Up cell
            if (y > 0) {
                mergeUnits(units, getCell(x, y - 1)->units, 0);
            }

            vector<LPGAMEOBJECT> objects = extractGameObjectsFromUnits(units);
            //TODO: Refactor for the whole code base. I think this not good. This against  S - Single-responsiblity principle
            unit->object->AddCoObjects(&objects);
            unit->object->Update(dt);
            Cell* newCell = this->getCell(unit->object->GetPosition());
            if (newCell != unit->ownerCell) {
                removeUnitFromCell(unit);
                addUnit(unit, newCell);
            }

            if (unit->object->is_dead) removeUnitFromCell(unit);
        }
    }
}

void Grid::handleRender() {
    for (size_t i = 0; i < m_cells.size(); i++) {

        int x = i % m_numXCells;
        int y = i / m_numXCells;

        Cell& cell = m_cells[i];

        for (size_t j = 0; j < cell.units.size(); j++) {
            cell.units[j]->object->Render();
        }
    }
}
void Grid::mergeUnits(vector<LPUNIT> &units, vector<LPUNIT> otherUnits, int startIndex) {
    for (size_t i = startIndex; i < otherUnits.size(); i++) {
        units.push_back(otherUnits[i]);
    }
}
vector<LPGAMEOBJECT> Grid::extractGameObjectsFromUnits(vector<LPUNIT> units) {
    vector<LPGAMEOBJECT> listObjects;
    for (size_t i = 0; i < units.size(); i++) {
        listObjects.push_back(units[i]->object);
    }
    return listObjects;
}

void Grid::removeUnitFromCell(LPUNIT unit) {
    vector<LPUNIT>& units = unit->ownerCell->units;
    // Normal vector swap
    units[unit->cellVectorIndex] = units.back();
    units.pop_back();
    // Update vector index
    if ((size_t)unit->cellVectorIndex < units.size()) {
        units[unit->cellVectorIndex]->cellVectorIndex = unit->cellVectorIndex;
    }
    // Set the index of unit to -1
    unit->cellVectorIndex = -1;
    unit->ownerCell = nullptr;
}