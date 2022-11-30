#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include <vector>
#include "Circle.h"

class App: public GlutApp {
    Rect* score1;
    Rect* score2;
    Circle* O;
    
    TexRect* one;
    TexRect* two;
    TexRect* angelo;
    bool GameStarted;
    
public:
    std::vector <Rect> bar;
    std::vector <TexRect> pic;
    App(int argc, char** argv);
    
    void draw();
    void idle();
    void keyDown(unsigned char key, float x, float y);
    
    ~App();
    
};

#endif
