#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <iostream>

# define PI 3.14159
static float R = 5.0;
static float xAngle = 0.0;
static float yAngle = 0.0;
static float zAngle = 0.0;
static float xLocation = 0.0;
static float yLocation = 0.0;
static float zLocation = 0.0;
static float planetRotationAngle = 0.0; // Birinci gezegen dönme açısı
static float planetRotationSpeed = 0.001; // Birinci gezegen dönme hızı
static float planetX, planetY, planetZ = 0.0; // Birinci gezegenin konumu

static float moonOrbitAngle = 0.0;    // İkinci gezegen yörünge dönme açısı
static float moonOrbitSpeed = 0.002;  // İkinci gezegen yörünge dönme hızı
static float moonRotationAngle = 0.0; // İkinci gezegen dönme açısı
static float moonRotationSpeed = 0.01; // İkinci gezegen dönme hızı

static float meteorX = 0.0;
static float meteorY = 15.0; // Initial position above the solar system
static float meteorSpeed = 0.001; // Meteor movement speed

static bool explosion = false; // Explosion state
static bool explosionoever = false; // Explosion state 2
static float explosionOvertime = 0.0; // Explosion duration 2
static float explosionTimer = 0.0; // Explosion duration


void drawMeteor(float radius) {
    glPushMatrix();

    if (explosion) {
        // Color change for explosion effect
        glColor3f(1.0 - explosionTimer, 0.5 * (1.0 - explosionTimer), 0.0);
    }
    else {
        // Meteor color
        glColor3f(1.0, 0.0, 0.0); // Red color for meteor
    }

    glTranslatef(meteorX, meteorY, 0.0);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}


void updateMeteor() {

    if (explosion) {
        // Update explosion duration
        explosionTimer += 0.01;

        // Reset explosion state when the duration is over
        if (explosionTimer >= 1.0) {
            explosion = false;
            if (explosionOvertime > 10.0) {
                explosionoever = true;
                
            }
            explosionTimer = 0.0;
        }
    }
    if (explosionoever) {
        printf("Meteor explosion is over!\n");
        explosionOvertime= 0.0;
        meteorX = 0.0;
		meteorY = 15.0;
		explosionoever = false;
    }
    else {
        // Update meteor movement towards the planet
        float dirX = planetX - meteorX;
        float dirY = planetY - meteorY;
        float length = sqrt(dirX * dirX + dirY * dirY);
        dirX /= length;
        dirY /= length;
        meteorX += dirX * meteorSpeed;
        meteorY += dirY * meteorSpeed;

        // Collision check
        float distanceToPlanet = sqrt(pow(meteorX - planetX, 2) + pow(meteorY - planetY, 2));
        if (distanceToPlanet <= 1.0) {
            explosionOvertime += 0.01;
            printf("Meteor hit the planet!\n");
            explosion = true;
        }
    }
}

void drawSolarPlanet(float radius, int slices, int stacks) {
    glPushMatrix();
    glRotatef(planetRotationAngle, 0.0, 0.0, 1.0); // Rotate the entire 3D half-sphere

    for (int i = 0; i < stacks; ++i) {
        float theta1 = (PI * i) / stacks;
        float theta2 = (PI * (i + 1)) / stacks;

        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float phi = (2 * PI * j) / slices;

            float x1 = radius * sin(theta1) * cos(phi);
            float y1 = radius * sin(theta1) * sin(phi);
            float z1 = radius * cos(theta1);

            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * sin(theta2) * sin(phi);
            float z2 = radius * cos(theta2);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glPopMatrix();
}

void drawPlanetOrbit(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = (2.0 * PI * i) / segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(x, y, 0.0);
    }
    glEnd();
}

void drawPlanet(float radius) {
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); // Green color
    glRotatef(planetRotationAngle, 0.0, 0.0, 1.0);
    glTranslatef(8.0, 0.0, 0.0);
    glutSolidSphere(radius, 50, 50);

    planetX = 8.0 * cos(planetRotationAngle * PI / 180.0);
    planetY = 8.0 * sin(planetRotationAngle * PI / 180.0);

    glPopMatrix();
}

void drawMoonOrbit(float radius, int segments, float planetX, float planetY) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = (2.0 * PI * i) / segments;
        float x = radius * cos(theta) + planetX;
        float y = radius * sin(theta) + planetY;
        glVertex3f(x, y, 0.0); // First planet's position
    }
    glEnd();
}

void drawMoon(float radius) {
    glPushMatrix();
    glRotatef(planetRotationAngle, 0.0, 0.0, 1.0); // Planet's rotation
    glTranslatef(8.0, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5);
    // Draw the moon's orbit line using the updated angle and the position of the first planet
    drawMoonOrbit(2.0, 100, 0.0, 0.0); // Updated to use the correct parameters

    glRotatef(moonOrbitAngle, 0.0, 0.0, 1.0); // Moon's orbit around the planet
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(moonRotationAngle, 0.0, 0.0, 1.0); // Moon's rotation around its axis
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Uzak bir mesafeden bakmak için translasyon yapılıyor
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(xLocation, yLocation, zLocation);

    glColor3f(0.0, 0.0, 0.0);
    drawSolarPlanet(R, 100, 50); // Güneş
    drawPlanetOrbit(8.0, 100);    // Birinci gezegenin yörüngesi
    drawPlanet(1.0);               // Birinci gezegen

    drawMeteor(0.3);
    updateMeteor();

    moonOrbitAngle += moonOrbitSpeed;
    moonRotationAngle += moonRotationSpeed;
    drawMoon(0.5);                 // İkinci gezegen (Birinci gezegenin etrafında)

    planetRotationAngle += planetRotationSpeed; // Birinci gezegenin otomatik dönme açısını güncelle

    glutSwapBuffers();
    glutPostRedisplay(); // Sürekli olarak ekrana yeniden çizim talep et
}



void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 5.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case '7':
        zLocation += 0.1;
        glutPostRedisplay();
        break;
    case '9':
        zLocation -= 0.1;
        glutPostRedisplay();
        break;
    case '4':
        xLocation += 0.1;
        glutPostRedisplay();
        break;
    case '2':
        yLocation += 0.1;
        glutPostRedisplay();
        break;
    case '6':
        xLocation -= 0.1;
        glutPostRedisplay();
        break;
    case '8':
        yLocation -= 0.1;
        glutPostRedisplay();
        break;
    case 'x':
        xAngle += 5.0;
        if (xAngle > 360.0) xAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        xAngle -= 5.0;
        if (xAngle < 0.0) xAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        yAngle += 5.0;
        if (yAngle > 360.0) yAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        yAngle -= 5.0;
        if (yAngle < 0.0) yAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        zAngle += 5.0;
        if (zAngle > 360.0) zAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        zAngle -= 5.0;
        if (zAngle < 0.0) zAngle += 360.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Solar System");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glEnable(GL_DEPTH_TEST);

    init();

    glutMainLoop();

    return 0;
}
