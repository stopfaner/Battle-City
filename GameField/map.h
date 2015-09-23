#ifndef MAP_H
#define MAP_H

#include "fieldelement.h"
#include "gamewidget.h"
#include <fstream>
#include <vector>

using namespace std;

class Map {

private:
    string path;

    int** matrix;
    const int rowCount = 13;
    const int columnCount = 20;

    FieldElement** gameField;

    void fillMatrix() {
        ifstream stream;
        stream.open(path);
        for(int i = 0; i < rowCount; i++) {
            matrix[i] = new int[columnCount];
            for(int j = 0; j < columnCount; j++) {
                stream>>matrix[i][j];
            }
        }
    }

    void fillElements() {
        for(int i = 0; i < rowCount; i++) {
            gameField[i] = new FieldElement[columnCount];
            for(int j = 0; j < columnCount; j++) {
                gameField[i][j].setXpoz(j * BLOCK_SIZE);
                gameField[i][j].setYpoz(i * BLOCK_SIZE);
                switch(matrix[i][j]) {
                    case 0 :
                        gameField[i][j].setType(FieldType::GROUND);
                        break;
                    case 1 :
                        gameField[i][j].setType(FieldType::BRICK);
                        break;
                    case 2 :
                        gameField[i][j].setType(FieldType::WATER);
                        break;
                }
            }
        }
    }

public:
    static const int BLOCK_SIZE = 80;

    Map() {
        path = "C:\\Users\\Denys\\Documents\\Tanks\\Map.txt";
        matrix = new int*[rowCount];
        gameField = new FieldElement*[rowCount];
        fillMatrix();
        fillElements();
    }

    int getRowCount() {
        return rowCount;
    }

    int getColCount() {
        return columnCount;
    }

    FieldElement** getField() {
        return gameField;
    }

    int** getMatrix() {
        return matrix;
    }
};

#endif // MAP_H
