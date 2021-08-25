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
                text = "Zalupa";
                break;
        }

        text += " Point(" + std::to_string(data.cell.horCoord) + ", " + std::to_string(data.cell.verCoord) + ")";
        if(data.cellState == CellState::GameOver || data.cellState == CellState::ShipSunk) {
        }
        std::cout << text << std::endl;
    }
};

int main() {
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

    return 0;
}
