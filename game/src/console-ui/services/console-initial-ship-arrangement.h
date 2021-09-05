#ifndef BATTLESHIP_SRC_CONSOLE_UI_UI_CONSOLE_INITIAL_SHIP_ARRANGEMENT_H
#define BATTLESHIP_SRC_CONSOLE_UI_UI_CONSOLE_INITIAL_SHIP_ARRANGEMENT_H

#include "iinitial-ship-arrangement.h"

class ConsoleInitialShipArrangement : public IInitialShipArrangement
{
public:
    Ships getInitialShipArrangement() const override;
};

#endif
