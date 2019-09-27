/*
    Muhamad Hilmy Haidar
    G64170030
*/
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

/* Predefined Color */
#define merah glColor3ub(187,21,66)
#define orange glColor3ub(235,95,93)
#define kuning glColor3ub(250,188,116)
#define hijau glColor3ub(35,159,149)
#define biru glColor3ub(65,105,225)
#define putih glColor3ub(255,255,255)
#define hitam glColor3ub(0,0,0)

const string nama = "hilmy";
const int resolutionOfWindowHight = 720;
const int resolutionOfWindowWidth = 1280;
class Base {
    protected:
        static const float pixelSize = 32.0;

        // draw a box
        void sizedBox(float x0, float y0, bool color  = false ,float sizes = pixelSize) {
            glBegin(GL_QUADS);
            if(!color) pickColor(rand());
            glVertex2f(x0,y0);
            glVertex2f(x0 + sizes,y0);
            glVertex2f(x0 + sizes, y0 + sizes);
            glVertex2f(x0,y0 + sizes);
            glEnd();
        }

        // draw a triangle
        void triangle(float x0, float y0, float sides) {
            glBegin(GL_TRIANGLES);
            glVertex2d(x0 - sides, y0 + sides/2.0 + sides/4.0 );
            glVertex2d(x0 + sides, y0 + sides/2.0 + sides/4.0 );
            glVertex2d(x0 , y0 - sides );
            glEnd();
        }

        // draw a quarter rounded circle
        void quarterRounded(float x0, float y0, int degree, float radius, string direction) {
            glBegin(GL_POLYGON);
            int dir;
            if( direction == "UL" ) dir = 1;
            else if( direction == "UR" ) dir = 2;
            else if( direction == "DL" ) dir = 3;
            else if( direction == "DR" ) dir = 4;

            for(int i=0; i<degree; i++){
                float theta = i * 3.14/180;

                switch(dir) {
                case 1:
                    glVertex2d(x0 - radius * cos(theta) , y0 - radius * sin(theta) );
                    break;
                case 2:
                    glVertex2d(x0 + radius * cos(theta) , y0 - radius * sin(theta) );
                    break;
                case 3:
                    glVertex2d(x0 - radius * cos(theta) , y0 + radius * sin(theta) );
                    break;
                case 4:
                    glVertex2d(x0 + radius * cos(theta) , y0 + radius * sin(theta) );
                    break;
                }
            }
            glVertex2d(x0,y0);
            glEnd();
        }

        void halfRounded(float x0, float y0, int degree, float radius, char direction) {
            switch(direction) {
            case 'U':
                quarterRounded(x0,y0,degree,radius,"UL");
                quarterRounded(x0,y0,degree,radius,"UR");
                break;
            case 'R':
                quarterRounded(x0,y0,degree,radius,"UR");
                quarterRounded(x0,y0,degree,radius,"DR");
                break;
            case 'D':
                quarterRounded(x0,y0,degree,radius,"DL");
                quarterRounded(x0,y0,degree,radius,"DR");
                break;
            case 'L':
                quarterRounded(x0,y0,degree,radius,"UL");
                quarterRounded(x0,y0,degree,radius,"DL");
                break;
            }
        }

        // draw line from sized box
        void lineFromSizedBox(float x0, float y0, int length, char direction, bool color = false, float sizes = pixelSize) {
            float trailingBox = 0.0;
            switch(direction) {

            // U for UP
            case 'U':
                for(int i=0; i<length; i++){
                    sizedBox(x0, y0 - trailingBox, color, sizes);
                    trailingBox += sizes;
                }
                break;

            // D for Down
            case 'D':
                for(int i=0; i<length; i++){
                    sizedBox(x0, y0 + trailingBox, color, sizes);
                    trailingBox += sizes;
                }
                break;

            // L for Left
            case 'L':
                for(int i=0; i<length; i++){
                    sizedBox(x0 - trailingBox, y0, color, sizes);
                    trailingBox += sizes;
                }
                break;

            // R for Right
            case 'R':
                for(int i=0; i<length; i++){
                    sizedBox(x0 + trailingBox, y0, color, sizes);
                    trailingBox += sizes;
                }
                break;
            }
        }

        // pick color
        void pickColor(int luckyNumber) {
            switch(luckyNumber % 5) {
            case 1:
                merah;
                break;
            case 2:
                orange;
                break;
            case 3:
                kuning;
                break;
            case 4:
                hijau;
                break;
            default :
                biru;
                break;
            }
        }
};


/* use 3x5 pixel for drawing ( 1 word use 96px ) */
class Word : public Base {
    private:
        char alphabet;
        float start_x;
        float start_y;

    public :
        // constructor
        Word(char c, float x0 = 0.0, float y0 = 0.0)
        {
            alphabet = c;
            start_x = x0;
            start_y = y0;
        }

        // display word
        void display(float x, float y)
        {
            // builder
            switch(alphabet)
            {
            case 'h':
            case 'H' :
                lineFromSizedBox(x,y,5,'D');
                sizedBox(x + pixelSize,y + 2*pixelSize);
                lineFromSizedBox(x + 2*pixelSize,y,5,'D');
                break;
            case 'i':
            case 'I':
                lineFromSizedBox(x,y,5,'D');
                break;
            case 'l':
            case 'L':
                lineFromSizedBox(x,y,5,'D');
                lineFromSizedBox(x+pixelSize,y+4*pixelSize,3,'R');
                break;
            case 'm':
            case 'M':
                lineFromSizedBox(x,y,5,'D');
                sizedBox(x + pixelSize,y);
                sizedBox(x + 3*pixelSize,y);
                sizedBox(x + 2*pixelSize,y);
                sizedBox(x + 2*pixelSize,y + pixelSize);
                sizedBox(x + 2*pixelSize,y + 2*pixelSize);
                lineFromSizedBox(x + 4*pixelSize,y,5,'D');
                break;
            case 'y':
            case 'Y':
                lineFromSizedBox(x,y,3,'D');
                lineFromSizedBox(x+2*pixelSize,y,3,'D');
                lineFromSizedBox(x+pixelSize,y+2*pixelSize,3,'D');
                break;
            default:
                halfRounded(x,y,90,pixelSize/2.0, 'D');
                break;
            }
        }

};

// generate every word that needed
void generateWord(string sentence, float x, float y) {
    float pixelSize = 32.0;
    float spacing = 0;

    // initialize random seed
    srand(time(NULL));

    for(int i=0; i<sentence.length(); i++){

        if(i)   // cek from the second letter from spacing between letter
        switch(sentence[i-1])
        {
        case 'l':
        case 'L':
            spacing += pixelSize*(4+1);
            break;
        case 'i':
        case 'I':
            spacing += pixelSize*(1+1);
            break;
        case 'm':
        case 'M':
            spacing += pixelSize*(5+1);
            break;
        default:
            spacing += pixelSize*(3+1);
            break;
        }
        Word(sentence[i]).display(x + spacing,y);
    }
}
class Triangle : public Base {
private:
    float x0;
    float y0;
    float sides;
public:
    // constructor
    Triangle(float x = 600, float y = 600, float side = pixelSize/2.0) {
        x0 = x;
        y0 = y;
        sides = side;
    }

    void display() {
        hitam;
        glPushMatrix();
        glTranslated(x0,y0,0);
        glRotatef(glfwGetTime()*1000, 0, 0, 1);
        glTranslated(-x0,-y0,0);
        triangle(x0,y0,sides);
        glPopMatrix();
    }

    void follow(float xpos, float ypos) {
        x0 = xpos;
        y0 = ypos;
    }

};

class Ball : public Base {
private:
    float size;
    float resHeight;
    float resWidth;
    float movX;
    float movY;
    float x;
    float y;
    int changeColor;
    int tmp;
    bool collusion;

    void isHitWall() {
        if( x + movX > resWidth || x + movX < 0 ) {
            movX *= -1;
            tmp = rand() % 4;
            if( changeColor != tmp ) changeColor = tmp;
            else changeColor = (tmp+1) % 4;
        }
        if( y + movY > resHeight || y + movY < 0 ) {
            movY *= -1;
            tmp = rand() % 4;
            if( changeColor != tmp ) changeColor = tmp;
            else changeColor = (tmp+1) % 4;
        }
    }

    bool isInsideBall(float xpos, float ypos) {
        float dx = xpos - x;
        float dy = ypos - y;
        double distances = sqrt( dx * dx + dy * dy );
        if( distances <= size ) return true;
        else return false;
    }

public:
    // constructor
    Ball(float ballSize = 32, float height = 600, float width = 600) {
        size = ballSize;
        resHeight = height;
        resWidth = width;
        movX = 3;
        movY = 3;
        x = width/2.0;
        y = height/2.0;
        collusion = false;
    }
    void display() {
        isHitWall();
        x += movX;
        y += movY;

        if(collusion) hitam;
        else putih;
        halfRounded(x,y,360,size,'U');
    }
    void whichColor () {
        pickColor(changeColor);
    }

    void checkCollusion(float xpos, float ypos) {
        if( isInsideBall(xpos, ypos) ) collusion = true;
        else collusion = false;
    }
};

class Mushroom : public Base {
private:
    double width;
    double height;
    double x;
    double y;
    double sizes;

    void mushroomStructure() {
        float level = y;
        hitam;
        lineFromSizedBox(x-sizes*2, level,6,'R', true ,sizes);
        level += sizes;
        // level 1
        hitam;
        lineFromSizedBox(x-sizes*4,level,3,'R', true ,sizes);
        merah;
        sizedBox(x-sizes,level,true,sizes);
        putih;
        lineFromSizedBox(x,level,2,'R',true,sizes);
        merah;
        sizedBox(x+sizes*2,level,true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*3,level,3,'R',true,sizes);
        level += sizes;

        // level 2
        hitam;
        lineFromSizedBox(x-sizes*5,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes*3,level,3,'R',true,sizes);
        putih;
        lineFromSizedBox(x,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x+sizes*2,level,3,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*5,level,2,'R',true,sizes);
        level += sizes;

        // level 3
        hitam;
        lineFromSizedBox(x-sizes*5,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes*3,level,3,'R',true,sizes);
        putih;
        lineFromSizedBox(x,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x+sizes*2,level,3,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*5,level,2,'R',true,sizes);
        level += sizes;

        // level 4
        hitam;
        sizedBox(x-sizes*5,level,true,sizes);
        putih;
        sizedBox(x-sizes*4,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*3,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes,level,4,'R',true,sizes);
        merah;
        lineFromSizedBox(x+sizes*3,level,2,'R',true,sizes);
        putih;
        sizedBox(x+sizes*5,level,true,sizes);
        hitam;
        sizedBox(x+sizes*6,level,true,sizes);
        level += sizes;

        // level 5
        hitam;
        lineFromSizedBox(x-sizes*6,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*4,level,10,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*6,level,2,'R',true,sizes);
        level += sizes;

        // level 6
        hitam;
        lineFromSizedBox(x-sizes*7,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes*5,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*3,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes,level,4,'R',true,sizes);
        putih;
        lineFromSizedBox(x+sizes*3,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x+sizes*5,level,2,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*7,level,2,'R',true,sizes);
        level += sizes;

        // level 7
        hitam;
        sizedBox(x-sizes*7,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*6,level,3,'R',true,sizes);
        putih;
        sizedBox(x-sizes*3,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*2,level,6,'R',true,sizes);
        putih;
        sizedBox(x+sizes*4,level,true,sizes);
        merah;
        lineFromSizedBox(x+sizes*5,level,3,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*8,level,true,sizes);
        level += sizes;

        // level 8
        hitam;
        sizedBox(x-sizes*7,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*6,level,3,'R',true,sizes);
        putih;
        sizedBox(x-sizes*3,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*2,level,6,'R',true,sizes);
        putih;
        sizedBox(x+sizes*4,level,true,sizes);
        merah;
        lineFromSizedBox(x+sizes*5,level,3,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*8,level,true,sizes);
        level += sizes;

        // level 9
        hitam;
        sizedBox(x-sizes*7,level,true,sizes);
        merah;
        lineFromSizedBox(x-sizes*6,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*4,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes*2,level,6,'R',true,sizes);
        putih;
        lineFromSizedBox(x+sizes*4,level,2,'R',true,sizes);
        merah;
        lineFromSizedBox(x+sizes*6,level,2,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*8,level,true,sizes);
        level += sizes;

        // level 10
        hitam;
        sizedBox(x-sizes*7,level,true,sizes);
        putih;
        lineFromSizedBox(x-sizes*6,level,5,'R',true,sizes);
        merah;
        lineFromSizedBox(x-sizes,level,4,'R',true,sizes);
        putih;
        lineFromSizedBox(x+sizes*3,level,5,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*8,level,true,sizes);
        level += sizes;

        // level 10
        hitam;
        sizedBox(x-sizes*7,level,true,sizes);
        putih;
        lineFromSizedBox(x-sizes*6,level,2,'R',true,sizes);
        hitam;
        lineFromSizedBox(x-sizes*4,level,10,'R',true,sizes);
        putih;
        lineFromSizedBox(x+sizes*6,level,2,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*8,level,true,sizes);
        level += sizes;

        // level 11
        hitam;
        lineFromSizedBox(x-sizes*7,level,4,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*3,level,2,'R',true,sizes);
        hitam;
        sizedBox(x-sizes,level,true,sizes);
        putih;
        lineFromSizedBox(x,level,2,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*2,level,true,sizes);
        putih;
        lineFromSizedBox(x+sizes*3,level,2,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*5,level,4,'R',true,sizes);
        level += sizes;

        // level 12
        hitam;
        lineFromSizedBox(x-sizes*6,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*4,level,3,'R',true,sizes);
        hitam;
        sizedBox(x-sizes,level,true,sizes);
        putih;
        lineFromSizedBox(x,level,2,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*2,level,true,sizes);
        putih;
        lineFromSizedBox(x+sizes*3,level,3,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*6,level,2,'R',true,sizes);
        level += sizes;

        // level 13
        hitam;
        sizedBox(x-sizes*5,level,true,sizes);
        putih;
        lineFromSizedBox(x-sizes*4,level,10,'R',true,sizes);
        hitam;
        sizedBox(x+sizes*6,level,true,sizes);
        level += sizes;

        // level 14
        hitam;
        lineFromSizedBox(x-sizes*5,level,2,'R',true,sizes);
        putih;
        lineFromSizedBox(x-sizes*3,level,8,'R',true,sizes);
        hitam;
        lineFromSizedBox(x+sizes*5,level,2,'R',true,sizes);
        level += sizes;

        // level 15
        hitam;
        lineFromSizedBox(x-sizes*4,level,10,'R',true,sizes);
    };

    bool isHitWall(float tempX, float tempY) {
        if( tempX-sizes*8 > 0 && tempX+sizes*9 < width && tempY > 0 && tempY+sizes*18 < height ) return false;
        else return true;
    }
public:
    Mushroom(float width, float height, float sizes){
        this->width = width;
        this->height = height;
        this->x = width/2.0;
        this->y = height/2.0;
        this->sizes = sizes;
    }
    void display() {
        mushroomStructure();
    }
    void keyPressed(int key, int action) {
        if( action == GLFW_PRESS)
        switch(key)
        {
        case GLFW_KEY_UP :
            if( !isHitWall(x, y-sizes*5) ) y-=sizes*5;
            break;
        case GLFW_KEY_DOWN :
            if( !isHitWall(x, y+sizes*5) ) y+=sizes*5;
            break;
        case GLFW_KEY_LEFT :
            if( !isHitWall(x-sizes*5, y) ) x-=sizes*5;
            break;
        case GLFW_KEY_RIGHT :
            if( !isHitWall(x+sizes*5, y) ) x+=sizes*5;
            break;

        }
    }

};

class Background : public Base {
private:
    float width;
    float height;

    void element() {
        for(int i=0; i<resolutionOfWindowWidth; i+= rand() % 100 + 20){
            for(int j=0; j<resolutionOfWindowHight; j+= rand() % 100 + 20){
                sizedBox(i,j,false, rand() % 8);
            }
        }
    }

public:
    // constructor
    Background(float x, float y) {
        width = x;
        height = y;
    }
    void display() {
        // create background
        glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(width,0);
        glVertex2f(width,height);
        glVertex2f(0,height);
        glEnd();

        // create element in background
        element();
    }
};

Triangle triangle = Triangle();
Mushroom jamur = Mushroom(1280,720,4);
Ball ball = Ball(32,resolutionOfWindowHight,resolutionOfWindowWidth);

static void error_callback(int error, const char* description){
  fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

    jamur.keyPressed(key,action);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    triangle.follow(xpos,ypos);
    ball.checkCollusion(xpos,ypos);
}

// function that responsible for rendering
void Render(GLFWwindow* window, float resolutionWidth, float resolutionHight) {

    int speedText = -50;
    bool directionText = false;

    while (!glfwWindowShouldClose(window)){
    // initiation
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // check direction
    if( directionText ) {
        speedText++;
        if(speedText > 0 ) directionText = !directionText;
    }
    else {
        speedText--;
        if(speedText < -200 ) directionText = !directionText;
    }

    // set canvas size
    glOrtho(0,width,height,0,0,1);

    // create background
    ball.whichColor();
    Background(resolutionWidth,resolutionHight).display();

    glPushMatrix();
    glTranslated( 100.0 + speedText ,0.0,0.0);
    // generating from sentences
    generateWord(nama,resolutionWidth/2.0 - resolutionWidth/4.0,resolutionHight/2.0);
    glPopMatrix();

    // create a ball
    ball.display();

    // create a mushroom
    jamur.display();

    // display triangle
    triangle.display();

    glfwSwapBuffers(window);
    glfwPollEvents();
    }
}

// function that responsible for exit
void Exit(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

// function that responsible for display
void Display() {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(1280, 720, "Muhamad Hilmy Haidar G64170030", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Register Callback
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Start Drawing
    Render(window,1280,720);

    // Exit Window
    Exit(window);
}

int main(void) {
    Display();
}
