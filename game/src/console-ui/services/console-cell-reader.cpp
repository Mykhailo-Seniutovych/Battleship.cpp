
#include <iostream>
#include <string>
#include "console-cell-reader.h"
#include "utils/map-utils.h"
#include "exceptions/invalid-input-exception.h"
#include "constants.h"

using namespace std;
using namespace map_utils;

Cell ConsoleCellReader::readCell() const
{
    cout << "Enter coordinates to shoot at (e.g. \"A 10\")" << endl;
    string newTarget;
    getline(cin, newTarget);

    try
    {
        auto rowLetter = newTarget[0];
        uint8_t rowNum = convertRowLetterToRowNumber(rowLetter) - 1;
        auto colNumberFromUserInput = stoi(newTarget.substr(newTarget.find(" ") + 1));
        if (colNumberFromUserInput < 1 || colNumberFromUserInput > Constants::MAP_SIZE)
        {
            cerr << INVALID_INPUT_ERROR_MSG << endl;
            return readCell();
        }
        auto colNum = colNumberFromUserInput - 1;
        return Cell(rowNum, colNum);
    }
    catch (const exception &ex)
    {
        cout << INVALID_INPUT_ERROR_MSG << endl;
        return readCell();
    }
}