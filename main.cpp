#include <string>
#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <Image-Scene.h>

time_t programStartTime = time(nullptr);

static vector<Scene *> scenesRef; // Global variable to store the scenes reference

void renderSceneSequence(const vector<Scene *> &scenes);
static void renderTimerCallback(int);
static void displayCallback();

void renderSceneSequence(const vector<Scene *> &scenes)
{
    time_t currentTime = time(nullptr);
    currentTime -= programStartTime;

    for (const auto &scene : scenes)
    {
        if (scene->getStartTime() <= currentTime && currentTime < scene->getEndTime())
        {

            scene->render();
            break;
        }
    }

    glutSwapBuffers();
    glutTimerFunc(200, renderTimerCallback, 0);
}

static void renderTimerCallback(int)
{
    renderSceneSequence(scenesRef);
}

static void displayCallback()
{
    renderSceneSequence(scenesRef);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animation");

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black

    vector<Scene *> scenes = {
        new ImageScene(1, 0.0, 1.0, "assets/stairs.png"),
        new ImageScene(2, 1.0, 12.0, "assets/stairs.png"),
    };

    scenesRef = scenes;

    glutDisplayFunc(displayCallback);
    displayCallback();

    glutMainLoop();

    // destructor doesn't get called though
    for (auto scene : scenes)
    {
        delete scene;
    }

    return 0;
}