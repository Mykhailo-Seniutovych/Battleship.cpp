
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

	auto rowLetter = newTarget[0];
	auto rowNumberResult = convertRowLetterToRowNumber(rowLetter);
	if (rowNumberResult < 1)
	{
		cerr << INVALID_INPUT_ERROR_MSG << endl;
		return readCell();
	}

	try
	{
		uint8_t rowNum = rowNumberResult - 1;
		auto colNumberFromUserInput = stoi(newTarget.substr(newTarget.find(" ") + 1));
		if (colNumberFromUserInput < 1 || colNumberFromUserInput > Constants::MAP_SIZE)
		{
			cerr << INVALID_INPUT_ERROR_MSG << endl;
			return readCell();
		}
		auto colNum = colNumberFromUserInput - 1;
		return Cell(rowNum, colNum);
	}
	catch (exception ex)
	{
		cerr << INVALID_INPUT_ERROR_MSG << endl;
		return readCell();
	}

}