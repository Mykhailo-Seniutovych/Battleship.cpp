#ifndef BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_ISTATISTICS_UI_H
#define BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_ISTATISTICS_UI_H

class IStatisticsUi
{
public:
    virtual void showBestPlayers() const = 0;
    virtual void showWorstPlayers() const = 0;
};

#endif
