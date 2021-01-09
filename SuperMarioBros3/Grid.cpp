#include "Grid.h"
#include "Utils.h"
#include <fstream>
#include "PlayScence.h"

#define GRID_SECTION_UNKNOWN -1
#define MAX_GRID_LINE   1024
#define GRID_SECTION_INFO   1
#define GRID_SECTION_CELLS  2

Grid::Grid(LPCWSTR filePath) {

    this->filePath = filePath;

	/*this->m_cellSize = cellSize;
	this->m_width = width;
	this->m_height = height;
	this->m_numXCells = (int) width / cellSize;
	this->m_numYCells = (int)height / cellSize;
    this->m_cells.resize(m_numYCells * m_numXCells);*/
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

void Grid::_parseSection_INFO(string line)
{
    vector<string> tokens = split(line);

    int numXCells = atoi(tokens[0].c_str());
    int numYCells = atoi(tokens[1].c_str());
    int cellSize = atoi(tokens[2].c_str());

    this->m_numXCells = numXCells;
    this->m_numYCells = numYCells;
    this->m_cellSize = cellSize;
    this->m_cells.resize(numYCells * numXCells);

}

void Grid::_parseSection_CELLS(string line)
{
    vector<string> tokens = split(line);

    int x = atoi(tokens[0].c_str());
    int y = atoi(tokens[1].c_str());
    Cell* cell = this->getCell(x, y);
    int index_flag = 2;

    while (index_flag < tokens.size())
    {
        int object_id = atoi(tokens[index_flag].c_str());
        CGameObject* obj = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->findObjectById(object_id);
        Unit* unit = new Unit();
        unit->object = obj;
        this->addUnitToSpecificCell(unit, cell);
        index_flag++;
    }
}

void Grid::Load()
{
    DebugOut(L"[INFO] Start loading grid from file: %s \n", filePath);

    ifstream f;
    f.open(this->filePath);

    int section = GRID_SECTION_UNKNOWN;

    char str[MAX_GRID_LINE];

    while (f.getline(str, MAX_GRID_LINE))
    {
        string line(str);

        if (line[0] == '#') continue;	// skip comment lines

        if (line == "[INFO]") { section = GRID_SECTION_INFO; continue; }
        if (line == "[CELLS]") { section = GRID_SECTION_CELLS; continue; }

        switch (section)
        {
        case GRID_SECTION_INFO: _parseSection_INFO(line); break;
        case GRID_SECTION_CELLS: _parseSection_CELLS(line); break;
        }

    }
    f.close();
}