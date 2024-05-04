#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;

class Scene;

class position
{
private:
    float x = 0, y = 0, z = 0;

public:
    position() = default;
    position(float a, float b, float c) : x(a), y(b), z(c) {}

    void setX(float a) { x = a; }
    void setY(float b) { y = b; }
    void setZ(float c) { z = c; }

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
};

class Rectangle
{
private:
    position p[4];

public:
    Rectangle() : p{{0.9f, 0.0f, 0.0f}, {0.0f, 0.9f, 0.0f}, {-0.9f, 0.0f, 0.0f}, {0.0f, -0.9f, 0.0f}} {}
    Rectangle(position a[4]) : p{a[0], a[1], a[2], a[3]} {}

    void draw()
    {
        for (int i = 0; i < 3; ++i)
        {
            glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
            glVertex3f(p[i + 1].getX(), p[i + 1].getY(), p[i + 1].getZ());
            glEnd();
        }
        glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(p[3].getX(), p[3].getY(), p[3].getZ());
        glVertex3f(p[0].getX(), p[0].getY(), p[0].getZ());
        glEnd();
    }

    void incrementZ()
    {
        for (int i = 0; i < 4; ++i)
        {
            p[i].setX(p[i].getX() / 0.9f);
            p[i].setY(p[i].getY() / 0.9f);
        }
    }
};

#define UPDATE_TIME 750000
#define NO_OF_RECTANGLES 50

float rotationAngle = 0.0f;
float zoomScale = 1.0f;

vector<Rectangle> v;
void update(int value)
{
    for (int i = 0, n = v.size(); i < n; ++i)
        v[i].incrementZ();

    rotationAngle += 5.0f;
    zoomScale += 0.001f;
    glutPostRedisplay();
    glutTimerFunc(UPDATE_TIME, update, 0);
}

void intialScene()
{
    Rectangle r;
    position a[4];
    a[0] = position(0.01, 0.0, 0.0);
    a[1] = position(0.0, 0.01, 0.0);
    a[2] = position(-0.01, 0.0, 0.0);
    a[3] = position(0.0, -0.01, 0.0);
    r = Rectangle(a);
    v.push_back(r);
    for (int i = 0; i < NO_OF_RECTANGLES; ++i)
    {
        position a0 = a[0];
        for (int j = 0; j < 3; ++j)
        {
            a[j].setX((a[j].getX() + a[j + 1].getX()) / 2);
            a[j].setY((a[j].getY() + a[j + 1].getY()) / 2);
        }
        a[3].setX((a[3].getX() + a0.getX()) / 2);
        a[3].setY((a[3].getY() + a0.getY()) / 2);
        r = Rectangle(a);
        v.push_back(r);
    }
}

class RectangleScene : public Scene
{
public:
    RectangleScene(int id, time_t startTime, time_t endTime)
        : Scene(id, startTime, endTime), rotationAngle(0.0f), zoomScale(1.0f)
    {
    }

    void render() override
    {
        cout << "render called" << endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
        glScalef(zoomScale, zoomScale, zoomScale);

        static bool initialized = false;
        if (!initialized)
        {
            intialScene();
            initialized = true;
            cout << "Initialized" << endl;
        }

        for (int i = 0, n = v.size(); i < n; ++i)
            v[i].draw();
        glutSwapBuffers();
        updateAnimation();
    }

    void updateAnimation()
    {
        for (int i = 0, n = v.size(); i < n; ++i)
            v[i].incrementZ();

        rotationAngle += 5.0f;
        zoomScale += 0.001f;
        glutPostRedisplay();
        glutTimerFunc(UPDATE_TIME, update, 0);
    }

private:
    float rotationAngle;
    float zoomScale;
};