#pragma once

class Player {
private:
    float x;
    float y;
    float w;
    float h;

    float r;
    float g;
    float b;

public:

    int score;

    Player(float = 0.0f, float = 0.0f, float = 0.4f, float = 0.2f, float = 1.0f, float = 1.0f, float = 1.0f, int = 0.0);

    float getX() const;
    float getY() const;
    float getW() const;
    float getH() const;

    float getR() const;
    float getG() const;
    float getB() const;

    void setX(float);
    void setY(float);
    void setW(float);
    void setH(float);
    int getScore()const;

    void setR(float);
    void setG(float);
    void setB(float);

    void moveRight();
    void moveLeft();

    int scoreplus();
    int resetScore();

    bool contains(float, float) const;

    void redrawScene();

    virtual void draw() const;

    ~Player();
};