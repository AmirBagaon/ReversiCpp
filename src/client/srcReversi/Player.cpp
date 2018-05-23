//
// Created by amir on 02/11/17.
//

#include <iostream>
#include "../include/Player.h"

using namespace std;

Player::Player(const Value t) : sign(t) {
}
Player::~Player() {
}
Value Player::getToken() {
    return sign;
}
