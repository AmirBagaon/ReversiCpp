//
// Created by or on 24/12/17.
//

#include "GameInfo.h"

GameInfo::GameInfo(string name, int socket) {
    gameName= name;
    clientFirst = socket;
    clientSecond = -1; // temp var at start
    started = false;
}
string GameInfo::getName() const {
    return gameName;
}
int GameInfo::getFirstClient() const {
    return clientFirst;
}
int GameInfo::getSecondClient() const {
    return clientSecond;
}
void GameInfo::setSecondClient(int &socket) {
    clientSecond = socket;
}
bool GameInfo::wasStarted() {
    return started;
}
void GameInfo::setStarted() {
    started = true;
}
