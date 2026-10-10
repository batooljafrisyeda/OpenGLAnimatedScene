/* Syeda Batool Jafri 22401327 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700
#define TIMER_PERIOD   20
#define PI  3.14159265358

#define STATE_START  0
#define STATE_TITLE  1
#define STATE_SCENE  2

int winWidth, winHeight;
int appState = STATE_START;
bool hoverTitle = false, hoverScene = false, hoverExit = false;

float cloudX = 300;
float carX = -450;

int btnY = 250;
int btnRadius = 45;
int titleBtnX = -200, sceneBtnX = 0, exitBtnX = 200;


void circle(int x, int y, int r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * (float)PI * (float)i / 100.0f;
        glVertex2f((float)x + r * cos(angle), (float)y + r * sin(angle));
    }
    glEnd();
}

void vprint(int x, int y, void* font, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf(str, string, ap);
    va_end(ap);
    glRasterPos2f((float)x, (float)y);
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

/* --- Drawing Functions --- */

void drawButtons() {
    // TITLE
    if (hoverTitle) {
        glColor3ub(100, 0, 0); circle(titleBtnX, btnY, btnRadius);
        glColor3ub(0, 0, 0); // BLACK TEXT ON HOVER
    }
    else {
        glColor3ub(150, 0, 0); circle(titleBtnX, btnY, btnRadius);
        glColor3ub(255, 255, 255);
    }
    vprint(titleBtnX - 25, btnY - 5, GLUT_BITMAP_HELVETICA_18, "TITLE");

    // SCENE
    if (hoverScene) {
        glColor3ub(0, 100, 0); circle(sceneBtnX, btnY, btnRadius);
        glColor3ub(0, 0, 0); // BLACK TEXT ON HOVER
    }
    else {
        glColor3ub(0, 180, 0); circle(sceneBtnX, btnY, btnRadius);
        glColor3ub(255, 255, 255);
    }
    vprint(sceneBtnX - 30, btnY - 5, GLUT_BITMAP_HELVETICA_18, "SCENE");

    // EXIT (matching your teal style)
    if (hoverExit) {
        glColor3ub(220, 220, 80); circle(exitBtnX, btnY, btnRadius);
        glColor3ub(0, 0, 0); // BLACK TEXT ON HOVER
    }
    else {
        glColor3ub(255, 255, 0); circle(exitBtnX, btnY, btnRadius);
        glColor3ub(255, 255, 255);
    }
    vprint(exitBtnX - 20, btnY - 5, GLUT_BITMAP_HELVETICA_18, "EXIT");
}

void drawTitleScreen() {
    glColor3ub(255, 255, 200);
    glRectf(-450, 180, 450, -280);

    glColor3ub(0, 0, 0);
    vprint(-150, 120, GLUT_BITMAP_9_BY_15, "BILKENT UNIVERSITY");
    vprint(-280, 70, GLUT_BITMAP_HELVETICA_18, "CTIS164 - Technical Mathematics with Programming");
    vprint(-100, 20, GLUT_BITMAP_8_BY_13, "HOMEWORK #1");
    vprint(-120, -30, GLUT_BITMAP_8_BY_13, "2025-2026 SPRING");
    vprint(-150, -80, GLUT_BITMAP_HELVETICA_18, "Syeda Batool Jafri");
    vprint(-130, -130, GLUT_BITMAP_HELVETICA_12, "Student ID: 22401327");
}

void drawSceneScreen() {
    // Define the full-width boundaries
    int xLeft = -500, xRight = 500;
    int yTop = 180, yHorizon = -50, yBottom = -280;

    // Sky and Ground (Full Width)
    glColor3ub(135, 206, 235); glRectf(xLeft, yTop, xRight, yHorizon);
    glColor3ub(34, 139, 34); glRectf(xLeft, yHorizon, xRight, yBottom);

    // Mountains (Scaled to look better in a wider window)
    glColor3ub(139, 90, 43);
    glBegin(GL_TRIANGLES);
    glVertex2f(-500, (float)yHorizon); glVertex2f(-250, (float)yTop - 20); glVertex2f(0, (float)yHorizon);
    glVertex2f(0, (float)yHorizon); glVertex2f(300, (float)yTop - 10); glVertex2f(500, (float)yHorizon);
    glEnd();

    // Road (Full Width)
    glColor3ub(50, 50, 50); glRectf(xLeft, -180, xRight, -260);

    glColor3ub(255, 255, 0);
    // Loop from -480 but stop before 500
    for (int i = -480; i < 470; i += 60) {
        glRectf((float)i, -218, (float)i + 30, -222);
    }

    // House
    glColor3ub(173, 216, 230); glRectf(100, -30, 300, -150);
    glColor3ub(200, 50, 50); glBegin(GL_TRIANGLES); glVertex2f(80, -30); glVertex2f(200, 50); glVertex2f(320, -30); glEnd();
    glColor3ub(255, 255, 255); glRectf(120, -60, 170, -100); glRectf(230, -60, 280, -100);
    glColor3ub(101, 67, 33); glRectf(180, -100, 220, -150);

    // Cloud
    glColor3ub(255, 255, 255);
    circle((int)cloudX, 120, 20); circle((int)cloudX + 25, 130, 25); circle((int)cloudX + 50, 120, 20);

    float carY = -190;

    // 1. Main Body
    glColor3ub(0, 0, 180); glRectf(carX, carY, carX + 120, carY - 40);
    // 2. Cabin/Roof
    glRectf(carX + 20, carY + 25, carX + 100, carY);
    // 3. Front Bumper
    glColor3ub(180, 180, 180); glRectf(carX + 120, carY - 25, carX + 128, carY - 38);
    // 4. Rear Bumper
    glRectf(carX - 8, carY - 25, carX, carY - 38);
    // 5. Front Wheel
    glColor3ub(0, 0, 0); circle((int)carX + 30, (int)carY - 42, 14);
    // 6. Rear Wheel
    circle((int)carX + 90, (int)carY - 42, 14);
    // 7. Headlight
    glColor3ub(255, 255, 200); glRectf(carX + 112, carY - 5, carX + 120, carY - 15);
    // 8. Taillight
    glColor3ub(220, 0, 0); glRectf(carX, carY - 5, carX + 8, carY - 15);
    // 9. Window (Front)
    glColor3ub(200, 230, 255); glRectf(carX + 25, carY + 20, carX + 55, carY + 5);
    // 10. Window (Back)
    glRectf(carX + 65, carY + 20, carX + 95, carY + 5);
    // 11. Exhaust Pipe/Tail Pipe
    glColor3ub(80, 80, 80); glRectf(carX - 15, carY - 35, carX - 5, carY - 40);
}

void display() {
    glClearColor(0, 0, 0, 1); // Entire window background is black
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Draw the actual content (Scene or Title)
    if (appState == STATE_TITLE) drawTitleScreen();
    else if (appState == STATE_SCENE) drawSceneScreen();

    // 2. Draw the "Mask" (Black bars to hide overflow)
    // This creates the 'box' effect. Anything outside -500 to 500 will be covered.
    glColor3ub(0, 0, 0);
    // Left border mask
    glRectf(-winWidth / 2, winHeight / 2, -500, -winHeight / 2);
    // Right border mask
    glRectf(500, winHeight / 2, winWidth / 2, -winHeight / 2);
    // Bottom border mask
    glRectf(-winWidth / 2, -280, winWidth / 2, -winHeight / 2);

    // 3. Draw the buttons (They stay on top)
    drawButtons();

    glutSwapBuffers();
}

void onResize(int w, int h) {
    winWidth = w; winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
}

void onPassiveMouse(int x, int y) {
    int mx = x - winWidth / 2;
    int my = winHeight / 2 - y;
    hoverTitle = (sqrt(pow(mx - titleBtnX, 2) + pow(my - btnY, 2)) < btnRadius);
    hoverScene = (sqrt(pow(mx - sceneBtnX, 2) + pow(my - btnY, 2)) < btnRadius);
    hoverExit = (sqrt(pow(mx - exitBtnX, 2) + pow(my - btnY, 2)) < btnRadius);
    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        if (hoverTitle) appState = STATE_TITLE;
        if (hoverScene) appState = STATE_SCENE;
        if (hoverExit) exit(0);
    }
    glutPostRedisplay();
}

void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    if (appState == STATE_SCENE) {
        // Cloud: Right to Left
        cloudX -= 1.8f;
        if (cloudX < -550) cloudX = 500;

        // Car: Left to Right
        carX += 4.5f;
        if (carX > 500) carX = -650;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CTIS164 HW1 2025-2026 SPRING - Syeda Batool Jafri");
    glutDisplayFunc(display);
    glutReshapeFunc(onResize);
    glutPassiveMotionFunc(onPassiveMouse);
    glutMouseFunc(onClick);
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    glutMainLoop();
    return 0;
}