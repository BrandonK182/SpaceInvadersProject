//
//  Circle.h
//  glutapp
//
//  Created by Ricky Trujillo on 12/9/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Circle_h
#define Circle_h
#include <math.h>

class Circle {
public:
    
    float X;
    float Y;
    float R; //For Circle
    float speed = 0.03;
    float x_direction = 0.5;
    float y_direction=0.5;
    
    Circle() : X(0), Y(0), R(0.15) {}
    
    Circle(float X, float Y, float R) : X(X), Y(Y), R(R) {}
    
    void draw() const {
        
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        for (float theta = 0; theta < 4 * M_PI; theta += 0.02) {
            glVertex2f(R * cos(theta) + X, R*sin(theta) + Y);
            glVertex2f(R * cos(theta) + X, R * sin(theta+ 0.1)  + Y); //draw the circle
        }
        glEnd();
    }

};

#endif /* Circle_h */
