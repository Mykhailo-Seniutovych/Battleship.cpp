#include "player.h"

int32_t Player::getScore() const
{
    return gamesWon - gamesLost;
}

bool Player::operator<(const Player &otherPlayer) const
{
    return getScore() < otherPlayer.getScore();
}

bool Player::operator>(const Player &otherPlayer) const
{
    return getScore() > otherPlayer.getScore();
}