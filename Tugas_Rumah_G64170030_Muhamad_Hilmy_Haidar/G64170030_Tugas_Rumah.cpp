/* Muhamad Hilmy Haidar G64170030 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>

using namespace std;

bool steer = false;
float fovy = 60.0;
float angle = 60.0;
float tilt = 0.0;
double xpos, ypos;
const int windowHeight = 720, windowWidth = 1024;
bool sky_state = true;
void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(action)
    {
    // key pressed
    case GLFW_PRESS :
        switch(key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_LEFT:
            angle += 10.0;
            break;
        case GLFW_KEY_RIGHT:
            angle -= 10.0;
            break;
        case GLFW_KEY_UP:
            tilt += 0.1;
            break;
        case GLFW_KEY_DOWN:
            tilt -= 0.1;
            break;
        case GLFW_KEY_SPACE:
            sky_state = !sky_state;
            break;
        }
        break;
    }
}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
    fovy += y*2;
    if(fovy > 150) fovy = 150;
    else if(fovy < 30) fovy = 30;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        cout << xpos << " " << ypos << "\n";
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        cout << xpos << " " << ypos << "\n";
    }
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "Rumah - G64170030", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // Register Callback
    glfwSetKeyCallback(window, controls);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

class Land
{
private:
    float x,y,z;
    float thickness;
    float area;
    float roadPosY;

    void land()
    {
        GLfloat vertices[] =
        {
            -area, -thickness, -area,   -area, -thickness,  area,   -area,  thickness,  area,   -area,  thickness, -area,
            area, -thickness, -area,    area, -thickness,  area,    area,  thickness,  area,    area,  thickness, -area,
            -area, -thickness, -area,   -area, -thickness,  area,    area, -thickness,  area,    area, -thickness, -area,
            -area,  thickness, -area,   -area,  thickness,  area,    area,  thickness,  area,    area,  thickness, -area,
            -area, -thickness, -area,   -area,  thickness, -area,    area,  thickness, -area,    area, -thickness, -area,
            -area, -thickness,  area,   -area,  thickness,  area,    area,  thickness,  area,    area, -thickness,  area
        };

        GLfloat colors[] =
        {
            0.7, 0.5, 0.2,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,
            0.7, 0.5, 0.2,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,
            0.7, 0.5, 0.2,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,
            0, 0.7, 0,       0, 0.7, 0,       0, 0.5, 0,       0, 0.5, 0,
            0.7, 0.5, 0.2,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,
            0.7, 0.5, 0.2,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1,   0.6, 0.3, 0.1
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        glDrawArrays(GL_QUADS, 0, 24);
    }

    void road()
    {
        glPushMatrix();
        glTranslatef(-roadPosY,0.001,0);
        GLfloat vertices[] =
        {
            -area/8.0,  thickness, -area,   -area/8.0,  thickness,  area,    area/8.0,  thickness,  area,    area/8.0,  thickness, -area,
        };

        GLfloat colors[] =
        {
            0.2, 0.2, 0.2,      0.2, 0.2, 0.2,      0.2, 0.2, 0.2,      0.2, 0.2, 0.2,
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();
    }

public:
    Land(float x = 0, float y = 0, float z = 0, float area = 1, float thickness = 0.125)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->area = area;
        this->thickness = thickness;
        this->roadPosY = area-0.5;
    }
    void display()
    {
        glPushMatrix();
        glTranslatef(x,y,z);

        land();
        road();

        glTranslatef(-x,-y,-z);
        glPopMatrix();
    }

    float getThickness()
    {
        return this->thickness;
    }
};

class Car
{
private:
    float x,y,z;
    float width, height, length;

    void window(float offsetX, float offsetY, float offsetZ)
    {
        glPushMatrix();
        glTranslatef(offsetX,height+offsetY,offsetZ - 0.001);

        GLfloat vertices[] =
        {
            -width/4.0, -height/2.0, -length/4.0,   -width/4.0,  height/2.0, -length/4.0,    width/4.0,  height/2.0, -length/4.0,    width/4.0, -height/2.0, -length/4.0,
        };

        GLfloat colors[] =
        {
            0.2, 0.7, 0.9,   0.0, 0.5, 0.7,   0.2, 0.7, 0.9,   0.0, 0.5, 0.7 // samping kiri
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 4 vertices */
        glDrawArrays(GL_QUADS, 0, 4);

        glTranslatef(-offsetX,-height-offsetY,-offsetZ + 0.001);
        glPopMatrix();
    }

    void roof()
    {
        // x = depan & belakang
        // y = atas & bawah
        // z = kiri & kanan
        glPushMatrix();
        glTranslatef(0,height*2,0);
        GLfloat vertices[] =
        {
            -width, -height, -length,   -width, -height,  length,   -width,  height,  length/2.0,   -width,  height, -length/2.0,
             width, -height, -length,    width, -height,  length,    width,  height,  length/2.0,    width,  height, -length/2.0,
            -width, -height, -length,   -width, -height,  length,    width, -height,  length,    width, -height, -length,
            -width,  height, -length/2.0,   -width,  height,  length/2.0,    width,  height,  length/2.0,    width,  height, -length/2.0,
            -width, -height, -length,   -width,  height, -length/2.0,    width,  height, -length/2.0,    width, -height, -length,
            -width, -height,  length,   -width,  height,  length/2.0,    width,  height,  length/2.0,    width, -height,  length
        };

        GLfloat colors[] =
        {
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // depan
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // belakang
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // bawah
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // atas
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // samping kiri
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0  // samping kanan
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 24 vertices */
        glDrawArrays(GL_QUADS, 0, 24);

        glTranslated(0,-height*2,0);
        glPopMatrix();
    }

    void wall()
    {
        GLfloat vertices[] =
        {
            -width, -height, -length*3/2,   -width, -height,  length*3/2,   -width,  height,  length*3/2,   -width,  height, -length*3/2,
             width, -height, -length*3/2,    width, -height,  length*3/2,    width,  height,  length*3/2,    width,  height, -length*3/2,
            -width, -height, -length*3/2,   -width, -height,  length*3/2,    width, -height,  length*3/2,    width, -height, -length*3/2,
            -width,  height, -length*3/2,   -width,  height,  length*3/2,    width,  height,  length*3/2,    width,  height, -length*3/2,
            -width, -height, -length*3/2,   -width,  height, -length*3/2,    width,  height, -length*3/2,    width, -height, -length*3/2,
            -width, -height,  length*3/2,   -width,  height,  length*3/2,    width,  height,  length*3/2,    width, -height,  length*3/2
        };

        GLfloat colors[] =
        {
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // depan
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // belakang
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // bawah
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // atas
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0, // samping kiri
            0.0, 0.0, 1.0,   0.2, 0.2, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0  // samping kanan
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 24 vertices */
        glDrawArrays(GL_QUADS, 0, 24);
    }
public :
    Car(float x = 0, float y = 0, float z = 0, float width = 1, float height = 1, float length = 1)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->width = width;
        this->height = height;
        this->length = length;
    }

    void set_x(float x) {
        this->x = x;
    }
    void set_y(float y) {
        this->y = y;
    }
    void set_z(float z) {
        this->z = z;
    }

    float get_x() {
        return x;
    }
    float get_y() {
        return y;
    }
    float get_z() {
        return z;
    }

    void display()
    {
        glPushMatrix();
        glTranslated(x,y+height,z);

        wall();
        roof();

        glTranslated(-x,-y-height,-z);
        glPopMatrix();
    }
};

class House
{
private:
    float x,y,z;
    float width, height;

    void window(float offsetX, float offsetY, float offsetZ)
    {
        glPushMatrix();
        glTranslatef(offsetX,height+offsetY,offsetZ - 0.001);

        GLfloat vertices[] =
        {
            -width/4.0, -height/2.0, -width,   -width/4.0,  height/2.0, -width,    width/4.0,  height/2.0, -width,    width/4.0, -height/2.0, -width,
        };

        GLfloat colors[] =
        {
            0.2, 0.7, 0.9,   0.0, 0.5, 0.7,   0.2, 0.7, 0.9,   0.0, 0.5, 0.7 // samping kiri
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 4 vertices */
        glDrawArrays(GL_QUADS, 0, 4);

        glTranslatef(-offsetX,-height-offsetY,-offsetZ + 0.001);
        glPopMatrix();
    }

    void door()
    {
        glPushMatrix();
        glTranslatef(-0.001,y-height,0);

        GLfloat vertices[] =
        {
            -width, -height, -width/4.0,   -width, -height,  width/4.0,   -width,  height,  width/4.0,   -width,  height, -width/4.0,
        };

        GLfloat colors[] =
        {
            0.9, 0.7, 0.2,   0.7, 0.5, 0.0,   0.9, 0.7, 0.2,   0.7, 0.5, 0.0, // depan
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 4 vertices */
        glDrawArrays(GL_QUADS, 0, 4);

        glTranslatef(0.001,-y+height,0);
        glPopMatrix();
    }

    void roof()
    {
        // x = depan & belakang
        // y = atas & bawah
        // z = kiri & kanan
        glPushMatrix();
        glTranslatef(0,height*2,0);
        GLfloat vertices[] =
        {
            -width, -height, -width,   -width, -height,  width,   -width,  height,  width/2.0,   -width,  height, -width/2.0,
             width, -height, -width,    width, -height,  width,    width,  height,  width/2.0,    width,  height, -width/2.0,
            -width, -height, -width,   -width, -height,  width,    width, -height,  width,    width, -height, -width,
            -width,  height, -width/2.0,   -width,  height,  width/2.0,    width,  height,  width/2.0,    width,  height, -width/2.0,
            -width, -height, -width,   -width,  height, -width/2.0,    width,  height, -width/2.0,    width, -height, -width,
            -width, -height,  width,   -width,  height,  width/2.0,    width,  height,  width/2.0,    width, -height,  width
        };

        GLfloat colors[] =
        {
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5, // depan
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5, // belakang
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5, // bawah
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5, // atas
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5, // samping kiri
            1.0, 0.0, 0.0,   1.0, 0.2, 0.2,   1.0, 0.5, 0.5,   1.0, 0.5, 0.5  // samping kanan
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 24 vertices */
        glDrawArrays(GL_QUADS, 0, 24);

        glTranslated(0,-height*2,0);
        glPopMatrix();
    }
    void wall()
    {
        GLfloat vertices[] =
        {
            -width, -height, -width,   -width, -height,  width,   -width,  height,  width,   -width,  height, -width,
             width, -height, -width,    width, -height,  width,    width,  height,  width,    width,  height, -width,
            -width, -height, -width,   -width, -height,  width,    width, -height,  width,    width, -height, -width,
            -width,  height, -width,   -width,  height,  width,    width,  height,  width,    width,  height, -width,
            -width, -height, -width,   -width,  height, -width,    width,  height, -width,    width, -height, -width,
            -width, -height,  width,   -width,  height,  width,    width,  height,  width,    width, -height,  width
        };

        GLfloat colors[] =
        {
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1,
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1,
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1,
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1,
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1,
            0.8, 0.8, 0.8,   1, 1, 1,   1, 1, 1,   1, 1, 1
        };

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 24 vertices */
        glDrawArrays(GL_QUADS, 0, 24);
    }
public :
    House(float x = 0, float y = 0, float z = 0, float width = 1, float height = 1)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->width = width;
        this->height = height;
    }

    void display()
    {
        glPushMatrix();
        glTranslated(x,y+height,z);

        wall();
        roof();
        window(0.2,-height,0);
        window(-0.2,-height,0);
        window(0.2,-height,width*2+0.002);
        window(-0.2,-height,width*2+0.002);
        door();

        glTranslated(-x,-y-height,-z);
        glPopMatrix();
    }
};

Land land = Land(0,0,0,2.5,0.125);
House house1 = House(0.75,land.getThickness(),0.7,0.5,0.25);
House house2 = House(-0.75,land.getThickness(),0.7,0.5,0.25);
House house3 = House(0.75,land.getThickness(),-0.7,0.5,0.25);
House house4 = House(-0.75,land.getThickness(),-0.7,0.5,0.25);
House house5 = House(0.75,land.getThickness(),1.9,0.5,0.25);
House house6 = House(-0.75,land.getThickness(),1.9,0.5,0.25);
House house7 = House(0.75,land.getThickness(),-1.9,0.5,0.25);
House house8 = House(-0.75,land.getThickness(),-1.9,0.5,0.25);
Car car = Car(-2,land.getThickness(),0,0.2,0.1,0.5);

void draw()
{
    //attempt to rotate cube
    glRotatef(angle, 0, 1, tilt);

    land.display();
    house1.display();
    house2.display();
    house3.display();
    house4.display();
    house5.display();
    house6.display();
    house7.display();
    house8.display();

    if( steer == true )
        car.set_z( car.get_z() + 0.01 );
    else
        car.set_z( car.get_z() - 0.01 );

    car.display();


    if( car.get_z() > 2.0 || car.get_z() < -2.0 ) steer = !steer;
    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display( GLFWwindow* window )
{
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        if( sky_state ) glClearColor(100.0/255.0, 196.0/255.0, 237.0/255.0, 1.0);
        else glClearColor(19.0/255.0, 24.0/255.0, 98.0/255.0, 1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective(fovy, (double)windowWidth / (double)windowHeight, 1, 100);


        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,0,-5);

        draw();

        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    GLFWwindow* window = initWindow(windowWidth, windowHeight);
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
