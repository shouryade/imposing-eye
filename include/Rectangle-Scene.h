#include <iostream>
#include <vector>
#include <GL/glut.h>
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
