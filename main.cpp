#include <GL/glut.h>
#include <string>

int progress = 0; // Current progress of the loading bar
std::string labelText = "Loading...";

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void drawLoadingBar() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the background
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(50, 50);
    glVertex2f(450, 50);
    glVertex2f(450, 100);
    glVertex2f(50, 100);
    glEnd();

    // Draw the loading bar outline
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(100, 60);
    glVertex2f(400, 60);
    glVertex2f(400, 80);
    glVertex2f(100, 80);
    glEnd();

    // Draw the filled part of the loading bar based on the progress
    glColor3f(0.4, 0.8, 0.4);
    glBegin(GL_QUADS);
    glVertex2f(100, 60);
    glVertex2f(100 + progress * 3, 60);
    glVertex2f(100 + progress * 3, 80);
    glVertex2f(100, 80);
    glEnd();

    // Draw the label
    glColor3f(1.0, 1.0, 1.0);
    drawText(200, 110, labelText);

    // Draw the progress percentage
    glColor3f(1.0, 1.0, 1.0);
    std::string progressText = std::to_string(progress) + "%";
    drawText(250 - progressText.length() * 3, 50, progressText);

    glFlush();
}

void update(int value) {
    if (progress < 100) {
        progress++;
        glutPostRedisplay(); // Trigger a redraw
        glutTimerFunc(50, update, 0); // Call update function again after 50 milliseconds
    } else {
        labelText = "Completed!";
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Loading Animation");
    glutInitWindowSize(500, 150);
    gluOrtho2D(0, 500, 0, 150);
    glutDisplayFunc(drawLoadingBar);

    // Set a timer to update the loading bar
    glutTimerFunc(50, update, 0);

    glutMainLoop();
    return 0;
}
