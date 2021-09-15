#include <unordered_set>
#include <cstdint>
#include "cell.h"

using namespace std;

Cell::Cell(uint8_t t_hor_coord, uint8_t t_ver_coord)
	: horCoord(t_hor_coord),
	  verCoord(t_ver_coord)
{
}

bool Cell::operator==(const Cell &otherCell) const
{
	return horCoord == otherCell.horCoord && verCoord == otherCell.verCoord;
};

size_t Cell::HashFunction::operator()(const Cell &cell) const
{
	auto horCoordHash = hash<uint8_t>()(cell.horCoord);
	auto verCoordHash = hash<uint8_t>()(cell.horCoord);
	return horCoordHash ^ (verCoordHash << 1);
};