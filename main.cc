#include <GL/glew.h>
#include <GL/glut.h>

#include <math.h>

#include <stdio.h>
#include <string.h>

// window dimentions
int WIDTH = 1024;
int HEIGHT = 768;

enum DisplayType {
    Isometric,
    Military,
    Cavalier,
    Cabinet
};

DisplayType display = Isometric;

void drawUnitCube() {
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f,0.0f);
  glVertex3f( 1.0f, 0.0f,0.0f);
  glEnd();
}

void drawCoordinateAxisZ() {
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f); // z-axis
  glVertex3f(0.0f, 0.0f, 2.0f);
  glEnd();
  glLineWidth(1);

  // z-axis tip
  glBegin(GL_TRIANGLES);
  glVertex3f( 0.0f, 0.0f, 2.0f);
  glVertex3f(-0.05f, 0.05f, 1.9f);
  glVertex3f( 0.05f, 0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f( 0.05f,  0.05f, 1.9f);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f( 0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glEnd();
}

void drawCoordinateAxisX() {
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

void drawCoordinateAxisY() {
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

/**
 * handleRender
 *  Passes the render event to the engine
 */
void handleRender() {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float m[16]; // identity
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    switch(display) {
        case Isometric: {
            float angleA = (M_PI / 180.0f) * (45.0f);
            float angleB = (M_PI / 180.0f) * (35.264);
            m[0] = sin(angleA);
            m[1] = cos(angleB)/2;
            m[2] = -sin(angleB);

            m[5] = cos(angleB);
            m[6] = sin(angleB);

            m[8] = sin(angleA);
            m[9] = -cos(angleB)/2;
            m[10] = sin(angleB);

            break;
        }
        case Military: {
            float angle = (M_PI / 180.0f) * (45.0f);
            m[0] = sin(angle);
            m[1] = sin(angle);
            m[2] = -sin(angle);

            m[8] = sin(angle);
            m[9] = -sin(angle);
            m[10] = sin(angle);
            break;
        }
        case Cavalier: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle);
            m[9] = sin(angle);

            break;
        }
        case Cabinet: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle)/2.0f;
            m[9] = sin(angle)/2.0;

            break;
        }
    }

    glLoadMatrixf(m);


    glColor3f(0.0f, 0.0f, 1.0f);
    drawCoordinateAxisZ();
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCoordinateAxisY();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCoordinateAxisX();

    drawUnitCube();

    // Do the buffer Swap
    glutSwapBuffers();
    glutReportErrors();
}

/**
 * handleIdle
 *  Passes the idle event to the engine
 */
void handleIdle() {
    glutPostRedisplay();
}

/**
 * handleReshape
 *  Passes the reshape event to the engine
 */
void handleReshape(int width, int height) {
    float aspect = (float) width / (float) height;

    // Start 2d
    glViewport(0, 0, width, height); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, -20.0f, 100.0f);
}

/**
 * handleKeydown
 *  Passes the key press event to the engine
 */
void handleKeydown(unsigned char key, int x, int y) {
    if (key=='1') {
        display = Isometric;
        glutSetWindowTitle("1 * Isometric, 2   Military, 3   Cavalier, 4   Cabinet");
    }
    if (key=='2') {
       display = Military;
       glutSetWindowTitle("1   Isometric, 2 * Military, 3   Cavalier, 4   Cabinet");
    }
    if (key=='3') {
       display = Cavalier;
       glutSetWindowTitle("1   Isometric, 2   Military, 3 * Cavalier, 4   Cabinet");
    }
    if (key=='4') {
        display = Cabinet;
        glutSetWindowTitle("1   Isometric, 2   Military, 3   Cavalier, 4 * Cabinet");
     }

    handleRender();
}

/**
 * Main
 */
int main(int argc, char* argv[]) {
    // OpenGL Declarations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("1 * Isometric, 2   Military, 3   Cavalier, 4   Cabinet");

    // Bind the render/idle/reshape events to their handlers
    glutDisplayFunc(handleRender);
    glutIdleFunc(handleIdle);
    glutReshapeFunc(handleReshape);

    // Bind the keybord events to their handlers
    glutKeyboardFunc(handleKeydown);

    // Initialize GLEW
	glewInit();

	// Hide the cursor
	glutSetCursor(GLUT_CURSOR_NONE);

    // Gray background
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();

    return 0;
}
