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

void Grid::addUnitToFirstOfCell(LPUNIT unit) {

	Cell* cell = this->getCell(unit->object->GetPosition());

    if (cell->head == NULL) {
        cell->head = unit;
        cell->tail = unit;
        unit->ownerCell = cell;
        return;
    }
    unit->next_ = cell->head;
    unit->prev_ = NULL;
    cell->head->prev_ = unit;
    cell->head = unit;
	unit->ownerCell = cell;

}
void Grid::addUnitToLastOfCell(LPUNIT unit) {
    
    Cell* cell = this->getCell(unit->object->GetPosition());

    Unit* head = cell->head;

    if (head == NULL) {
        cell->head = unit;
        cell->tail = unit;
        unit->ownerCell = cell;
        return;
    }
  
    unit->prev_ = cell->tail;
    cell->tail->next_ = unit;
    cell->tail = unit;
    unit->ownerCell = cell;
}

void Grid::addUnitToSpecificCell(LPUNIT unit, Cell* cell) {

    //Add into last of Cell.

    Unit* tail = cell->tail;

    if (tail == NULL) {
        cell->head = unit;
        cell->tail = unit;
        unit->ownerCell = cell;
        return;
    }
  
    unit->prev_ = cell->tail;
    cell->tail->next_ = unit;
    cell->tail = unit;
    unit->ownerCell = cell;
    
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

void Grid::extractGameObjectFromCell(Cell* cell, Unit* unit_to_start, vector<LPGAMEOBJECT> &gameObjects) {

    if (unit_to_start == NULL) unit_to_start = cell->head;

    while (unit_to_start != NULL)
    {
        gameObjects.push_back(unit_to_start->object);
        unit_to_start = unit_to_start->next_;
    }
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

        Unit* temp = cell.head;

        while (temp != NULL)
        {
            //vector<LPUNIT> units;
            vector<LPGAMEOBJECT> gameObjects;

            extractGameObjectFromCell(&cell, temp->next_, gameObjects);

            // Update collision with neighbor cells. Reference: https://gameprogrammingpatterns.com/spatial-partition.html 
            if (x > 0) {
                // Left
                extractGameObjectFromCell(getCell(x - 1, y), NULL, gameObjects);

                if (y > 0) {
                    // Top left
                    extractGameObjectFromCell(getCell(x - 1, y - 1), NULL, gameObjects);
                }
                if (y < m_numYCells - 1) {
                    // Bottom left
                    extractGameObjectFromCell(getCell(x - 1, y + 1), NULL, gameObjects);
                }
            }

            // Up cell
            if (y > 0) {
                extractGameObjectFromCell(getCell(x, y - 1), NULL, gameObjects);
            }

            temp->object->AddCoObjects(&gameObjects);
            temp->object->Update(dt);

            Cell* newCell = this->getCell(temp->object->GetPosition());

            if (newCell != temp->ownerCell) {
                removeUnitFromCell(temp);
                addUnitToSpecificCell(temp, newCell);
            }

            if (temp->object->is_dead) removeUnitFromCell(temp);

            gameObjects.clear();
            temp = temp->next_;
        }
    }
}

void Grid::handleRender() {

    for (size_t i = 0; i < m_cells.size(); i++) {

        int x = i % m_numXCells;
        int y = i / m_numXCells;

        Cell& cell = m_cells[i];

        Unit *temp = cell.head;

        while (temp != NULL) {
            temp->object->Render();
            temp = temp->next_;
        }
    }
}

void Grid::removeUnitFromCell(LPUNIT unit) {

    Cell* cell = unit->ownerCell;

    //Cell contain only one unit
    if (cell->head == cell->tail) {
        cell->tail = NULL;
        cell->head = NULL;
    }
    //if unit is head
    else if (unit == cell->head) {
        unit->next_->prev_ = NULL;
        cell->head = unit->next_;
    }
    //if unit is tail
    else if (unit == cell->tail) {
        unit->prev_->next_ = NULL;
        cell->tail = unit->prev_;
    }
    //Unit in the middle
    else {
        unit->next_->prev_ = unit->prev_;
        unit->prev_->next_ = unit->next_;
    }
  
    //update unit for moving it into new cell.
    unit->next_ = NULL;
    unit->prev_ = NULL;
    unit->ownerCell = NULL;
}

void Grid::findGameObjectsByTag(string tagName, vector<LPGAMEOBJECT>& resultObjects)
{
    for (size_t i = 0; i < m_cells.size(); i++) {

        int x = i % m_numXCells;
        int y = i / m_numXCells;

        Cell& cell = m_cells[i];

        Unit *temp = cell.head;

        while (temp != NULL) {
            if (temp->object->tag.compare(tagName) == 0)
                resultObjects.push_back(temp->object);
            temp = temp->next_;
        }
    }
}