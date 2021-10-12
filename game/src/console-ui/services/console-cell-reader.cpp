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

    auto spacePosition = newTarget.find(" ");
    auto spaceFound = spacePosition != string::npos;
    Cell cell;
    auto isError = false;

    do
    {
        if (newTarget == "" || !spaceFound)
        {
            isError = true;
            break;
        }

        uint8_t rowNum = 0;
        try
        {
            auto rowNumberFromUserInput = stoi(newTarget.substr(0, spacePosition));

            if (rowNumberFromUserInput < 1 || rowNumberFromUserInput > Constants::MAP_SIZE)
            {
                isError = true;
                break;
            }
            rowNum = rowNumberFromUserInput - 1;
        }
        catch (exception ex)
        {
            isError = true;
            break;
        }

        auto colLetter = newTarget.substr(spacePosition + 1)[0];
        auto colNumberResult = convertRowLetterToRowNumber(colLetter);
        if (colNumberResult < 1)
        {
            isError = true;
            break;
        }

        uint8_t colNum = colNumberResult - 1;
        cell = Cell(rowNum, colNum);
    } while (false);

    if (isError)
    {
        cerr << INVALID_INPUT_ERROR_MSG << endl;
        return readCell();
    }
    else
    {
        return cell;
    }
}