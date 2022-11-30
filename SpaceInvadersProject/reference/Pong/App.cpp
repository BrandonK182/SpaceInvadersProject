#include <iostream>
#include "App.h"
#include "Rect.h"
#include <vector>

bool XMax = false;
bool YMax=false;
bool player1 = false;
bool player2 = false;


App::App(int argc, char** argv): GlutApp(argc, argv){
    //one = new Rect(-1.35, 0.2, 0.05,.4, 1.0, 0.0, 0.0);
    //two = new Rect(1.3,0.2, 0.05,0.4,0.0,1.0,0.5);
    score1= new Rect(-1.60,1.0,0.15,2.0,1,1,0.0);
    score2 = new Rect(1.45,1.0,0.15,2.0,1,1,0.0);
    O=new Circle(0,0,0.1);
    angelo = new TexRect("/Users/rickytrujillo/Desktop/OpenGLTemplateFinal/angelo.png", 1.0, -0.5, 0.5, 0.5);
    GameStarted = false;
    
   one = new TexRect("/Users/rickytrujillo/Desktop/OpenGLTemplateFinal/red.png", -1.35, 0.2, 0.05,.4);
   two = new TexRect("/Users/rickytrujillo/Desktop/OpenGLTemplateFinal/blue.png",1.3,0.2, 0.05,0.4);
    //fastExplosion = new AnimatedRect("fireball.png", 6, 6, 10, 0.5, 0.5, 0.5, 0.5);
}

void App::draw() {
    one->draw(0.0);
    two->draw(0.0);
    score1->draw();
    score2->draw();
    O->draw();

        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
        glLineWidth(1.0);
    
        glVertex2f(0.0, 1.0);
        glVertex2f(0.0, 0.8);
    
        glVertex2f(0.0,0.7);
        glVertex2f(0.0,0.5);
    
        glVertex2f(0.0,0.4);
        glVertex2f(0.0, 0.20);
    
        glVertex2f(0.0, 0.10);
        glVertex2f(0.0, -0.10);
    
        glVertex2f(0.0,-0.2);
        glVertex2f(0.0, -0.4);
    
        glVertex2f(0.0,-0.5);
        glVertex2f(0.0, -0.7);
    
        glVertex2f(0.0,-0.8);
        glVertex2f(0.0, -1.0);
    
    
        glEnd();
    
    
    
    glColor3f(1.0, 1.0, 1.0);
    std::string var = "Player 1 Score: " + std::to_string(one->getScore());
    glRasterPos2f(-1.0, 0.9);
    for (int i = 0; i < var.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, var[i]);
    }

    glColor3f(1.0, 1.0, 1.0);
    std::string var2 = "Player 2 Score: " + std::to_string(two->getScore());
    glRasterPos2f(0.6, 0.9);
    for (int i = 0; i < var.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, var2[i]);
    }
    
    if(GameStarted) {
        if(one->getScore() == 7){
            player1 = true;
            one->score = 0;
            two->score=0;
            GameStarted = false;
        }else{
            player1= false;
        }
    
        if(two->getScore()== 7){
            player2 = true;
            one->score=0;
            two->score=0;
            GameStarted = false;
        }else {
            player2= false;
        }
    }
    if(player1){
        glColor3f(0.0, 1.0, 0.0);
        std::string var = "Game Over! Player 1 Wins!";
        glRasterPos2f(-0.3, 0.5);
        for (int i = 0; i < var.size(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, var[i]);
        }
        angelo->draw(0.0);
    }
    
    if(player2){
        glColor3f(0.0, 1.0, 0.0);
        std::string var = "Game Over! Player 2 Wins!";
        glRasterPos2f(-0.3, 0.5);
        for (int i = 0; i < var.size(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, var[i]);
        }
         angelo->draw(0.0);
    }

}

void App::keyDown(unsigned char key, float x, float y){
    if(key == 'f'){
        XMax = false;
    }
    
    if (key == 27){
        delete one;
        delete two;
        delete O;
        delete score1;
        delete score2;
        exit(0);
    }
    
    if(key == 32) {
        GameStarted = true;
    }
    
    if(one->y <= 1){
    if( key =='w'){
        one->moveUp();
    }
    }
    
    if(one->y - one->h >= -1){
    if( key =='s' ){
        one->moveDown();
    }
    }
    
    
    if(two->y <= 1){
    if( key == 'i'){
        two->moveUp();
    }
    }
        
    if(two->y - two->h >= -1){
    if( key =='k' ){
        two->moveDown();
    }
    }
        
        glutPostRedisplay();
}

void App::idle(){
    
    
    if (O->X + 0.1 > two->x  && O->Y < two->y && O->Y >two->y - two->h){
        XMax = true;
        O->speed += 0.005;
    } //else if( O->X > 0.75){
         //XMax = true;
    //}
    else if (O->X < one->x+0.15 && O->Y < one->y && O->Y > one->y - one->h){
        XMax = false;
        O->speed += 0.005;
    }//else if( O->X < -0.75){
        //XMax = false;
    //}
    

    
    if(O->X +0.08 < score1->x + score1->w && O->Y < 1 && O->Y > -1){
        two->scoreplus();
        O->speed = 0.03;
        O->X = 0;
        O->Y =0;
    }
    
    if(O->X +0.08 > score2->x && O->Y < 1 && O->Y > -1){
        one->scoreplus();
        O->speed = 0.03;
        O->X = 0;
        O->Y =0;
    }
    
    if( O->Y > 0.9){
         YMax = true;
    } else if( O->Y < -0.9){
         YMax = false;
    }
    
    if(GameStarted) {
        
        if(XMax){
            O->X -= O->speed * O->x_direction;
        } else{
            O->X += O->speed * O->x_direction;
        }
        if(YMax){
            O->Y -= O->speed * O->y_direction;
        }else{
            O->Y += O->speed * O->y_direction;
        }
    }
    glutPostRedisplay();
}




App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete one;
    delete two;
    delete score1;
    delete score2;
    delete O;
   // delete explosion;
   // delete fastExplosion;
}
