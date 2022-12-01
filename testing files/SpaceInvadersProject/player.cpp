#include "player.h"

Player::Player(float x, float y, float w, float h, float r, float g, float b, int score) : x(x), y(y), w(w), h(h), r(r), g(g), b(b), score(0) {
}

bool Player::contains(float px, float py) const {
    return px >= x && px <= x + w && py <= y && py >= y - h;
}

void Player::draw() const {
    //glColor3f(r, g, b);

    //glBegin(GL_POLYGON);

    //glVertex2f(x, y);
    //glVertex2f(x + w, y);
    //glVertex2f(x + w, y - h);
    //glVertex2f(x, y - h);

    //glEnd();
}

void Player::moveLeft() {
    x -= 0.2;
}

void Player::moveRight() {
    x += 0.2;
}

int Player::scoreplus() {
    return score++;
}

int Player::resetScore() {
    score = 0;
    return score;
}

void Player::redrawScene() {
    
}

Player::~Player() {

}
