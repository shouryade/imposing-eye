#include <string>
#include <iostream>
using namespace std;
#include <GL/glut.h>

#include <Image-Scene.h>
#include <Rectangle-Scene.h>
#include <Puzzle-Scene.h>

time_t programStartTime = time(nullptr);

static vector<Scene *> scenesRef;

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
    glutPostRedisplay();
    glutSwapBuffers();
}

static void displayCallback()
{
    renderSceneSequence(scenesRef);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animation");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    vector<Scene *> scenes = {
        new RectangleScene(1, 0.0, 8.0),
        new ImageScene(2, 8.0, 11.0, "assets/stairs.png"),
        new PuzzleScene(2, 10.0, 20.0),

    };

    scenesRef = scenes;

    glutDisplayFunc(displayCallback);

    glutMainLoop();

    // destructor doesn't get called though
    for (auto scene : scenes)
    {
        delete scene;
    }

    return 0;
}