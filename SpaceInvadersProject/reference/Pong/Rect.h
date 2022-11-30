#ifndef Rect_h
#define Rect_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

class Rect{
protected:
//    float x;
//    float y;
//    float w;
//    float h;
//
//    float r;
//    float g;
//    float b;
    
public:
    float x;
    float y;
    float w;
    float h;
    
    float r;
    float g;
    float b;
    
    int score;
    
    Rect(float=0.0f, float=0.0f, float=0.4f, float=0.2f, float=1.0f, float=1.0f, float=1.0f, int= 0.0);
    
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

    void moveUp();
    void moveDown();
    
   int scoreplus();
    
    bool contains(float, float) const;

    
    void redrawScene();
    
    virtual void draw() const;
    
    virtual ~Rect();
};

#endif
