
#include <iostream>
#include <string>
#include "console-cell-reader.h"
#include "utils/map-utils.h"

using namespace std;
using namespace map_utils;

Cell ConsoleCellReader::readCell() const
{
    cout << "Enter coordinates to shot at (e.g. \"A 10\")" << endl;
    string newTarget;
    getline(cin, newTarget);

    auto rowLetter = newTarget[0];
    auto rowNum = convertRowLetterToRowNumber(rowLetter) - 1;

    auto colNumberFromUserInput = stoi(newTarget.substr(newTarget.find(" ") + 1));
    auto colNum = colNumberFromUserInput - 1;

    return Cell(rowNum, colNum);
}