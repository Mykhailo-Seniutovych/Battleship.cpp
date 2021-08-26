#include <iostream>
#include <string>
#include <stdint.h>
#include <bits/stdc++.h>

#include "../core/models/ship.h"
#include "../core/models/cell.h"
#include "../core/models/position.h"
#include "../core/models/map-update-data.h"
#include "../core/infrastructure/ship-manager.h"
#include "../core/interfaces/iobserver.h"

class TestObserver : public IObserver<MapUpdateData> {
    void update(MapUpdateData data) override {
        std::string text;
        
        switch (data.cellState)
        {
            case CellState::Miss: {
                text = "Miss";
                break;
            }
            case CellState::ShipDamaged: {
                text = "ShipDamaged";
                break;
            }
            case CellState::ShipSunk: {
                text = "ShipSunk";
                break;
            }
            case CellState::GameOver: {
                text = "GameOver";
                break;
            }

            default:
                text = "Zal";
                break;
        }

        text += " Point(" + std::to_string(data.cell.horCoord) + ", " + std::to_string(data.cell.verCoord) + ")";
        if(data.cellState == CellState::GameOver || data.cellState == CellState::ShipSunk) {
        }
        std::cout << text << std::endl;
    }
};

void testRunner() {
    auto carrier = Ship(Position::Horizontal, 2, {2,3,4,5,6});
    auto battleship = Ship(Position::Vertical, 8, {2,3,4,5});
    auto cruiser = Ship(Position::Horizontal, 9, {4,5,6});
    auto submarine = Ship(Position::Vertical, 10, {8,9,10});
    auto destroyer = Ship(Position::Vertical, 3, {5,6});

    auto shipManager = ShipManager();
    auto observer = TestObserver();
    shipManager.subscribe(&observer);

    shipManager.initializeShips(carrier, battleship, cruiser, submarine, destroyer);


    auto res1 = shipManager.receiveShot(Cell(5, 3));
    auto res2 = shipManager.receiveShot(Cell(6, 3));

    auto res3 = shipManager.receiveShot(Cell(5, 4));
    auto res4 = shipManager.receiveShot(Cell(6, 4));

    auto res5 = shipManager.receiveShot(Cell(9, 4));
    auto res6 = shipManager.receiveShot(Cell(9, 5));
    auto res7 = shipManager.receiveShot(Cell(9, 6));

    auto res8 = shipManager.receiveShot(Cell(2, 8));
    auto res9 = shipManager.receiveShot(Cell(1, 8));
    auto res10 = shipManager.receiveShot(Cell(3, 8));
    auto res11 = shipManager.receiveShot(Cell(4, 8));
    auto res12 = shipManager.receiveShot(Cell(5, 8));

    auto res13 = shipManager.receiveShot(Cell(1, 10));
    auto res14 = shipManager.receiveShot(Cell(8, 10));
    auto res15 = shipManager.receiveShot(Cell(9, 10));
    auto res16 = shipManager.receiveShot(Cell(10, 10));

    auto res17 = shipManager.receiveShot(Cell(2, 2));
    auto res18 = shipManager.receiveShot(Cell(2, 3));
    auto res19 = shipManager.receiveShot(Cell(2, 4));
    auto res20 = shipManager.receiveShot(Cell(2, 5));
    auto res21 = shipManager.receiveShot(Cell(2, 6));
}

enum MapCellState {
    Invisible,
    MyShip,
    MissedShot,
    DamagedShip,
    SunkShip
};

class ConsoleMaps {
public:
    void initMaps (
        ShipCoordinates t_myCarrier, 
        ShipCoordinates t_myBattleship, 
        ShipCoordinates t_myCruiser, 
        ShipCoordinates t_mySubmarine, 
        ShipCoordinates t_myDestroyer
    ) {
        //TODO: validation

        for (uint8_t row = 0; row < MAP_SIZE; row++) {
            for (uint8_t col = 0; col < MAP_SIZE; col++) {
                m_myMap[row][col] = MapCellState::Invisible;
                m_enemyMap[row][col] = MapCellState::Invisible;
            }
        }

        initShipOnMyMap(t_myCarrier);
        initShipOnMyMap(t_myBattleship);
        initShipOnMyMap(t_myCruiser);
        initShipOnMyMap(t_mySubmarine);
        initShipOnMyMap(t_myDestroyer);
    }

    void updateMyMap(MapUpdateData updateData) {
        if(updateData.cellState == CellState::ShipSunk && updateData.cellState == CellState::GameOver) {

        } else {
            auto row = updateData.cell.horCoord;
            auto col = updateData.cell.verCoord;
            m_myMap[row][col] = convertToMapState(updateData.cellState);
        }
    }

    void printMaps() {
        for (uint8_t row = 0; row <= MAP_SIZE; row++) {
            for (uint8_t col = 0; col <= MAP_SIZE; col++) {
                if (row == 0 && col == 0) {
                    std::cout << "  ";
                } else if (row == 0) {
                    std::cout << unsigned(col) << " ";
                } else if(col == 0) {
                    printRowNumber(row);
                } else {
                    printCell(m_myMap[row-1][col-1]);
                }
            }
            std::cout << std::endl;
        }
    }

private:
    static const uint8_t MAP_SIZE = 10;

    const std::string INVISIBLE_CELL = "- ";
    const std::string MISSED_SHOT_CELL = "* ";
    const std::string MY_SHIP_CELL = "\U0001F229";
    const std::string SHIP_DAMAGED = "X ";
    const std::string SHIP_SUNK_CELL = "\U0001F147 ";

    
    MapCellState m_myMap[MAP_SIZE][MAP_SIZE];
    MapCellState m_enemyMap[10][10];

    MapCellState convertToMapState(CellState cellState) {
        MapCellState result;

        switch (cellState)
        {
        case CellState::Miss :
            result = MapCellState::MissedShot;
            break;
        case CellState::ShipDamaged :
            result = MapCellState::DamagedShip;
            break;
        case CellState::ShipSunk :
            result = MapCellState::SunkShip;
            break;
        case CellState::GameOver :
            result = MapCellState::SunkShip;
            break;
        default:
            break;
        }

        return result;
    }

    void initShipOnMyMap(const ShipCoordinates& ship) {
        if(ship.position == Position::Horizontal) {
            auto row = ship.axisCoordinate;
            for(auto col : ship.cellsCoordinates) {
                m_myMap[row][col] = MapCellState::MyShip;
            }
        } else {
            auto col = ship.axisCoordinate;
            for(auto row : ship.cellsCoordinates) {
                m_myMap[row][col] = MapCellState::MyShip;
            }
        }
    }

    void printRowNumber(uint8_t rowNum) {
        switch (rowNum)
        {
            case 1:
                std::cout << "A ";
                break;
            case 2:
                std::cout << "B ";
                break;
            case 3:
                std::cout << "C ";
                break;
            case 4:
                std::cout << "D ";
                break;
            case 5:
                std::cout << "E ";
                break;
            case 6:
                std::cout << "F ";
                break;
            case 7:
                std::cout << "G ";
                break;
            case 8:
                std::cout << "H ";
                break;
            case 9:
                std::cout << "I ";
                break;
            case 10:
                std::cout << "J ";
                break;
            default:
                break;
        }

    }

    void printCell(MapCellState cellState) {
        switch (cellState)
        {
        case MapCellState::Invisible :
            std::cout << INVISIBLE_CELL;
            break;
        case MapCellState::MyShip :
            std::cout << MY_SHIP_CELL;
            break;
        case MapCellState::MissedShot :
            std::cout << MISSED_SHOT_CELL;
            break;
        case MapCellState::DamagedShip :
            std::cout << SHIP_DAMAGED;
            break;
        case MapCellState::SunkShip :
            std::cout << SHIP_SUNK_CELL;
            break;
        default:
            break;
        }
    }
};


int main() {
    auto carrier = ShipCoordinates(Position::Horizontal, 1, {1,2,3,4,5});
    auto battleship = ShipCoordinates(Position::Vertical, 7, {1,2,3,4});
    auto cruiser = ShipCoordinates(Position::Horizontal, 8, {3,4,5});
    auto submarine = ShipCoordinates(Position::Vertical, 9, {7,8,9});
    auto destroyer = ShipCoordinates(Position::Vertical, 2, {4,5});

    std::cout << std::endl;
    auto consoleMaps = ConsoleMaps();
    consoleMaps.initMaps(carrier, battleship, cruiser, submarine, destroyer);
    consoleMaps.printMaps();

    uint8_t val = 8;
    std::cout << unsigned(val);
    return 0;
}
