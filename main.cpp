#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdio>
#include <math.h>
#include<stdlib.h>
#include <windows.h>
#include <GL\glut.h>


using namespace std;
char quote[50][50];
void gameOver();
GLfloat UpwardsScrollVelocity = -10.0;
float view = 10.0;
int numberOfQuotes = 0;


int cloudStatus = 0;
int birdStatus = 0;
int parachuteStatus = 0;
int hellicopterStatus = 0;
int obstaclehellicopterStatus = 0;
float cloudX = 0;
float cloudY = 0;
float birdX = 0;
float birdY = 0;
float parachuteX = 0;
float parachuteY = 0;
float hellicopterX = 0;
float hellicopterY = 0;
int w = 0;
int v = 0;
int u = 0;
float speed, b = .5;
bool start = false, finish = false;
int score = 0;


struct obstacle {
	float obstaclehellicopterX;
	float obstaclehellicopterY;
	float sp;
};
obstacle obs[4];

struct parachute1 {
	float parachuteX;
	float parachuteY;
	float sp1;
};

parachute1 ps[4];


void sky() {

	glBegin(GL_POLYGON); //Sky
	glColor3ub(119, 178, 255);
	glVertex2i(2000, 1500);
	glVertex2i(0, 1500);
	glColor3f(2.49, 1.87, 1.0);
	glVertex2i(0, 970);
	glVertex2i(2000, 970);
	glEnd();
}

void water()
{
	glBegin(GL_POLYGON);
	glColor3ub(205, 230, 250);
	glVertex2i(0, 470);
	glVertex2i(2000, 300);
	glVertex2i(2000, 970);
	glVertex2i(0, 970);
	glEnd();
	glFlush();
}
void DrawCircle(float cx, float cy, float r, int num_segments) {

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void cloud(int x) {
	int c1 = 2000, c2 = 2000, c3 = 2000;

	glColor3f(.447, .624, .812);
	DrawCircle(196 - c1, 1280 - 20, 60, c2);//left
	DrawCircle(236 - c1, 1350 - 20, 55, c2);//left
	DrawCircle(360 - c1, 1374 - 20, 55, c2);//right
	DrawCircle(400 - c1, 1324 - 20, 55, c2);//right
	DrawCircle(290 - c1, 1393, 60, c2);//top
	DrawCircle(296 - c1, 1296, 80, c2);//middle

	glColor3f(.933, .933, .933);
	DrawCircle(200 - c1, 1280 - 20, 60, c2);//1
	DrawCircle(240 - c1, 1350 - 20, 55, c2);//2
	DrawCircle(360 - c1, 1370 - 20, 55, c2);//3
	DrawCircle(400 - c1, 1320 - 20, 55, c2);//4
	DrawCircle(290 - c1, 1390, 60, c2);//4
	DrawCircle(300 - c1, 1300, 80, c2);//middle

	glColor3f(.447, .624, .812);
	DrawCircle(196, 1280 - 20, 60, c2);//left
	DrawCircle(236, 1350 - 20, 55, c2);//left
	DrawCircle(360, 1374 - 20, 55, c2);//right
	DrawCircle(400, 1324 - 20, 55, c2);//right
	DrawCircle(290, 1393, 60, c2);//top
	DrawCircle(296, 1296, 80, c2);//middle

	glColor3f(.933, .933, .933);
	DrawCircle(200, 1280 - 20, 60, c2);//1
	DrawCircle(240, 1350 - 20, 55, c2);//2
	DrawCircle(360, 1370 - 20, 55, c2);//3
	DrawCircle(400, 1320 - 20, 55, c2);//4
	DrawCircle(290, 1390, 60, c2);//4
	DrawCircle(300, 1300, 80, c2);//middle

	glColor3f(.447, .624, .812);//last
	DrawCircle(96 + c3, 1280 - 20, 60, c2);//left
	DrawCircle(136 + c3, 1350 - 20, 55, c2);//left
	DrawCircle(260 + c3, 1374 - 20, 55, c2);//right
	DrawCircle(300 + c3, 1324 - 20, 55, c2);//right
	DrawCircle(190 + c3, 1393, 60, c2);//top
	DrawCircle(196 + c3, 1296, 80, c2);//middle

	glColor3f(.933, .933, .933);//last
	DrawCircle(100 + c3, 1280 - 20, 60, c2);//1
	DrawCircle(140 + c3, 1350 - 20, 55, c2);//2
	DrawCircle(260 + c3, 1370 - 20, 55, c2);//3
	DrawCircle(300 + c3, 1320 - 20, 55, c2);//4
	DrawCircle(190 + c3, 1390, 60, c2);//4
	DrawCircle(200 + c3, 1300, 80, c2);//middle
}

void movecloud()

{
	if (cloudStatus == 1)
	{
		cloudX -= 5;
		w -= 1;

	}
	if (cloudX < -500)
	{
		cloudX = 2000;
	}
	glPushMatrix();
	glTranslatef(cloudX, cloudY, 0);
	cloud(1);
	glPopMatrix();



}

void parachute(int x, int y)
{
	int cx = x + 800;
	int cy = y + 1300;
	int r = 100;
	int n = 40;

	glColor3f(1.0, 0, 0);

	DrawCircle(cx, cy, r, n);//head

	glBegin(GL_POLYGON);
	glColor3f(1, 0.0, 0.0);//body

	glVertex2i(x + 760, y + 1080);
	glVertex2i(x + 840, y + 1080);
	glVertex2i(x + 900, y + 1280);
	//glVertex2i(x+700,y+1 280);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);

	glVertex2i(x + 780, y + 990);
	glVertex2i(x + 820, y + 990);
	glVertex2i(x + 820, y + 1045);
	glVertex2i(x + 780, y + 1045);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(x + 820, y + 990);
	glVertex2i(x + 760, y + 1080);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(x + 780, y + 990);
	glVertex2i(x + 840, y + 1080);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(x + 800, y + 990);
	glVertex2i(x + 800, y + 1080);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);

	glVertex2i(x + 780, y + 1080);
	glVertex2i(x + 790, y + 1080);
	glVertex2i(x + 715, y + 1355);
	glVertex2i(x + 696, y + 1300);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);

	glVertex2i(x + 805, y + 1080);
	glVertex2i(x + 815, y + 1080);
	glVertex2i(x + 900, y + 1325);
	glVertex2i(x + 880, y + 1355);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);

	glVertex2i(x + 795, y + 1075);
	glVertex2i(x + 805, y + 1085);
	glVertex2i(x + 815, y + 1400);
	glVertex2i(x + 775, y + 1400);
	glEnd();

	glFlush();
}

void bird(int x, int y)
{
	glBegin(GL_TRIANGLES);//body
	glColor3ub(187, 22, 161);
	glVertex2i(x + 180, y + 212);
	glVertex2i(x + 225, y + 211);
	glVertex2i(x + 255, y + 270);
	glEnd();

	glBegin(GL_TRIANGLES);//tail 1
	glColor3ub(102, 92, 84);
	glVertex2i(x + 225, y + 245);
	glVertex2i(x + 235, y + 225);
	glVertex2i(x + 260, y + 285);
	glEnd();

	glBegin(GL_TRIANGLES);//tail 2
	glColor3ub(136, 65, 17);
	glVertex2i(x + 215, y + 235);
	glVertex2i(x + 235, y + 235);
	glVertex2i(x + 235, y + 280);
	glEnd();

	glBegin(GL_TRIANGLES);//tail 3
	glColor3ub(102, 92, 84);
	glVertex2i(x + 225, y + 212);
	glVertex2i(x + 295, y + 220);
	glVertex2i(x + 235, y + 232);
	glEnd();

	glBegin(GL_TRIANGLES);//lip 1
	glColor3ub(187, 22, 161);
	glVertex2i(x + 175, y + 210);
	glVertex2i(x + 195, y + 210);
	glVertex2i(x + 195, y + 226);
	glEnd();


	glBegin(GL_TRIANGLES);//lip 2
	glColor3ub(187, 22, 161);
	glVertex2i(x + 180, y + 212);
	glVertex2i(x + 210, y + 230);
	glVertex2i(x + 180, y + 245);
	glEnd();

	glBegin(GL_TRIANGLES);//lip 3
	glColor3ub(220, 111, 42);
	glVertex2i(x + 180, y + 245);
	glVertex2i(x + 145, y + 223);
	glVertex2i(x + 180, y + 223);
	glEnd();

	glBegin(GL_LINES);//lips stick
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 145, y + 223);
	glVertex2i(x + 170, y + 230);
	glEnd();


	glBegin(GL_LINES); // eair
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(x + 195, y + 265);
	glVertex2i(x + 190, y + 190);
	glEnd();

	glColor3f(1.0, 1.0, 0);//eye
	DrawCircle(x + 180, y + 230, 9, 10);

	glColor3f(0.0, 0.0, 0);
	DrawCircle(x + 180, y + 230, 5, 10);

}

void movebird()

{
	if (birdStatus == 1)
	{
		birdX -= 5;
		u -= 1;

	}
	if (birdX < -500)
	{
		birdX = 2000;
	}
	glPushMatrix();
	glTranslatef(birdX, birdY, 0);
	bird(400, 1100);
	bird(800, 1100);
	bird(1150, 1100);
	glPopMatrix();



}

void field()
{

	glBegin(GL_POLYGON); //under ground
	glColor3ub(129, 184, 17);
	glVertex2i(0, 0);
	glVertex2i(2000, 0);
	glVertex2i(2000, 300);
	glVertex2i(1800, 320);
	glVertex2i(1700, 350);
	glVertex2i(1600, 370);
	glVertex2i(1500, 375);
	glVertex2i(1350, 365);
	glVertex2i(1200, 390);
	glVertex2i(1000, 410);
	glVertex2i(1700 - 700, 350 + 60);
	glVertex2i(1600 - 700, 370 + 50);
	glVertex2i(1500 - 700, 375 + 50);
	glVertex2i(1350 - 700, 365 + 50);
	glVertex2i(1200 - 700, 390 + 60);
	glVertex2i(1000 - 700, 410 + 50);
	glVertex2i(200, 455);
	glVertex2i(100, 465);
	glVertex2i(0, 485);
	glEnd();

}

void grass(int x, int y) {

	glBegin(GL_TRIANGLES);
	glColor3ub(5, 94, 2);
	glVertex2i(x + 100, y + 40);
	glVertex2i(x + 120, y + 40);
	glVertex2i(x + 110, y + 250);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3ub(5, 94, 2);
	glVertex2i(x + 95, y + 40);
	glVertex2i(x + 115, y + 40);
	glVertex2i(x + 150, y + 250);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3ub(5, 94, 2);
	glVertex2i(x + 95, y + 40);
	glVertex2i(x + 115, y + 40);
	glVertex2i(x + 80, y + 250);
	glEnd();
	glFlush();
}

void grassfield() {

	grass(-50, 0);
	grass(40, 0);
	grass(130, 0);
	grass(220, 0);
	grass(310, 0);
	grass(400, 0);
	grass(490, 0);
	grass(580, 0);
	grass(670, 0);
	grass(760, 0);
	grass(850, 0);
	grass(940, 0);
	grass(1030, 0);
	grass(1120, 0);
	grass(1210, 0);
	grass(1300, 0);
	grass(1390, 0);
	grass(1480, 0);
	grass(1570, 0);
	grass(1660, 0);
	grass(1750, 0);
	grass(1840, 0);
	grass(1930, 0);
	grass(2000, 0);


	int x = 55;
	grass(-110 + x, 150);
	grass(-50 + x, 150);
	grass(40 + x, 150);
	grass(130 + x, 150);
	grass(220 + x, 150);
	grass(310 + x, 150);
	grass(400 + x, 150);
	grass(490 + x, 150);
	grass(580 + x, 150);
	grass(670 + x, 150);
	grass(760 + x, 150);
	grass(850 + x, 150);
	grass(940 + x, 150);
	grass(1030 + x, 150);
	grass(1120 + x, 150);
	grass(1210 + x, 150);
	grass(1300 + x, 150);
	grass(1390 + x, 150);
	grass(1480 + x, 150);
	grass(1570 + x, 150);
	grass(1660 + x, 150);
	grass(1750 + x, 150);
	grass(1800 + x, 150);

}

void hellicopter()
{
	int y = 700;

	glColor3f(1.13, 0.13, 1.13);// blade start

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 49, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 83, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 83, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 49, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 83, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 104, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 104, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 83, hellicopterY + y + 192);
	glEnd();


	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 104, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 104, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 202, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 202, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 202, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 230, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 230, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 202, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 230, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 250, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 250, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 230, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 250, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 268, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 268, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 250, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 268, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 280, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 280, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 268, hellicopterY + y + 192);
	glEnd();

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 280, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 292, hellicopterY + y + 188);
	glVertex2i(hellicopterX + 292, hellicopterY + y + 192);
	glVertex2i(hellicopterX + 280, hellicopterY + y + 192); //blade end
	glEnd();

	/*glBegin(GL_LINES);
	glVertex2i(169, y+196);
	glVertex2i(292, y+196);
	glEnd();
	glFlush();

	glColor3f(1.13, 0.13, 0.13);
	glBegin(GL_LINES);
	glVertex2i(42, y+196);
	glVertex2i(169, y+196);
	glEnd();
	glFlush();// blade end*/


	glColor3f(0.13, 0.13, 0.13);//blade stand
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 162, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 176, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 176, hellicopterY + y + 202);
	glVertex2i(hellicopterX + 162, hellicopterY + y + 202);
	glEnd();

	glColor3f(0.13, 0.13, 0.13); //blade stand base
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 152, hellicopterY + y + 175);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 175);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 152, hellicopterY + y + 183);
	glEnd();

	glColor3f(0.13, 0.13, 0.13); //blade stand base side
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 118, hellicopterY + y + 175);
	glVertex2i(hellicopterX + 131, hellicopterY + y + 175);
	glVertex2i(hellicopterX + 131, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 118, hellicopterY + y + 183);
	glEnd();

	glColor3f(0.30, 0.31, 0.26); //tail begin
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 6, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 22, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 22, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 6, hellicopterY + y + 183);
	glEnd();

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 22, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 183);
	glVertex2i(hellicopterX + 22, hellicopterY + y + 183);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 6, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 6, hellicopterY + y + 176);
	glEnd();

	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 27, hellicopterY + y + 176);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 8, hellicopterY + y + 163);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 163);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 8, hellicopterY + y + 169);
	glEnd();



	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 163);
	glVertex2i(hellicopterX + 42, hellicopterY + y + 163);
	glVertex2i(hellicopterX + 42, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 35, hellicopterY + y + 169);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 12, hellicopterY + y + 157);
	glVertex2i(hellicopterX + 42, hellicopterY + y + 157);
	glVertex2i(hellicopterX + 42, hellicopterY + y + 163);
	glVertex2i(hellicopterX + 12, hellicopterY + y + 163);
	glEnd();

	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 17, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 56, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 56, hellicopterY + y + 157);
	glVertex2i(hellicopterX + 17, hellicopterY + y + 157);
	glEnd();

	glColor3f(0.20, 0.21, 0.17);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 56, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 157);
	glVertex2i(hellicopterX + 56, hellicopterY + y + 157);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 17, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 17, hellicopterY + y + 154);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 49, hellicopterY + y + 135);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 135);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 49, hellicopterY + y + 140);
	glEnd();


	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 61, hellicopterY + y + 130);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 130);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 135);
	glVertex2i(hellicopterX + 61, hellicopterY + y + 135);
	glEnd();


	glColor3f(0.23, 0.23, 0.31);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 73, hellicopterY + y + 120);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 120);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 130);
	glVertex2i(hellicopterX + 73, hellicopterY + y + 130);
	glEnd();

	glColor3f(0.20, 0.24, 0.11);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 85, hellicopterY + y + 115);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 115);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 125);
	glVertex2i(hellicopterX + 85, hellicopterY + y + 123);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 101);
	glVertex2i(hellicopterX + 143, hellicopterY + y + 101);
	glVertex2i(hellicopterX + 143, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 176);
	glEnd();


	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 143, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 176);
	glVertex2i(hellicopterX + 143, hellicopterY + y + 176);
	glEnd();


	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 239, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 239, hellicopterY + y + 169);
	glVertex2i(hellicopterX + 179, hellicopterY + y + 169);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 239, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 162);
	glVertex2i(hellicopterX + 239, hellicopterY + y + 162);
	glEnd();


	glColor3f(0.13, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 162);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 162);
	glEnd();

	glColor3f(0.13, 0.13, 0.13); //wind shild
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 258, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 258, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 156);
	glEnd();


	glColor3f(0.88, 0.87, 0.89);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 156);
	glEnd();


	glColor3f(0.68, 0.76, 0.87);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 147);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 147);
	glVertex2i(hellicopterX + 245, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 152);
	glEnd();


	glColor3f(0.28, 0.32, 0.29);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 235, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 152);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 156);
	glVertex2i(hellicopterX + 235, hellicopterY + y + 156);
	glEnd();


	glColor3f(0.68, 0.76, 0.87);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 232, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 147);
	glVertex2i(hellicopterX + 232, hellicopterY + y + 147);
	glEnd();


	glColor3f(0.68, 0.76, 0.87);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 270, hellicopterY + y + 140);
	glVertex2i(hellicopterX + 270, hellicopterY + y + 147);
	glVertex2i(hellicopterX + 252, hellicopterY + y + 147);
	glEnd();


	glColor3f(0.88, 0.87, 0.89);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 249, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 249, hellicopterY + y + 147);
	glVertex2i(hellicopterX + 240, hellicopterY + y + 147);
	glEnd();

	glColor3f(0.88, 0.87, 0.89);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 249, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 143);
	glVertex2i(hellicopterX + 249, hellicopterY + y + 143);
	glEnd();


	glColor3f(0.88, 0.87, 0.89);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 272, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 272, hellicopterY + y + 132);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 132);
	glEnd();

	glColor3f(0.88, 0.87, 0.89);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 272, hellicopterY + y + 132);
	glVertex2i(hellicopterX + 278, hellicopterY + y + 132);
	glVertex2i(hellicopterX + 278, hellicopterY + y + 138);
	glVertex2i(hellicopterX + 272, hellicopterY + y + 138);
	glEnd();


	glColor3f(0.68, 0.76, 0.87);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 127);
	glEnd();

	glColor3f(0.68, 0.76, 0.87);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 132);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 132);
	glVertex2i(hellicopterX + 266, hellicopterY + y + 139);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 139);
	glEnd();

	glColor3f(0.58, 0.66, 0.77);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 243, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 127);
	glVertex2i(hellicopterX + 243, hellicopterY + y + 127);
	glEnd();

	glColor3f(0.58, 0.66, 0.77);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 118);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 118);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 123);
	glEnd();

	glColor3f(0.68, 0.76, 0.77);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 118);
	glVertex2i(hellicopterX + 256, hellicopterY + y + 118);
	glVertex2i(hellicopterX + 256, hellicopterY + y + 123);
	glVertex2i(hellicopterX + 253, hellicopterY + y + 123);
	glEnd();

	glColor3f(0.18, 0.16, 0.17);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 242, hellicopterY + y + 114);
	glVertex2i(hellicopterX + 288, hellicopterY + y + 114);
	glVertex2i(hellicopterX + 288, hellicopterY + y + 122);
	glVertex2i(hellicopterX + 242, hellicopterY + y + 122);
	glEnd();

	glColor3f(0.18, 0.16, 0.17);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 270, hellicopterY + y + 122);
	glVertex2i(hellicopterX + 279, hellicopterY + y + 122);
	glVertex2i(hellicopterX + 279, hellicopterY + y + 128);
	glVertex2i(hellicopterX + 270, hellicopterY + y + 128);
	glEnd();


	glColor3f(0.30, 0.31, 0.26);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 224, hellicopterY + y + 108);
	glVertex2i(hellicopterX + 279, hellicopterY + y + 108);
	glVertex2i(hellicopterX + 279, hellicopterY + y + 114);
	glVertex2i(hellicopterX + 224, hellicopterY + y + 114);
	glEnd();


	glColor3f(0.33, 0.33, 0.36);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 122, hellicopterY + y + 100);
	glVertex2i(hellicopterX + 222, hellicopterY + y + 100);
	glVertex2i(hellicopterX + 222, hellicopterY + y + 108);
	glVertex2i(hellicopterX + 122, hellicopterY + y + 108);
	glEnd();


	glColor3f(0.33, 0.33, 0.36);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 214, hellicopterY + y + 100);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 100);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 148);
	glVertex2i(hellicopterX + 214, hellicopterY + y + 148);
	glEnd();


	glColor3f(0.13, 0.13, 0.18);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 214, hellicopterY + y + 148);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 148);
	glVertex2i(hellicopterX + 233, hellicopterY + y + 158);
	glVertex2i(hellicopterX + 214, hellicopterY + y + 158);
	glEnd();

	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 128, hellicopterY + y + 88);
	glVertex2i(hellicopterX + 163, hellicopterY + y + 88);
	glVertex2i(hellicopterX + 163, hellicopterY + y + 93);
	glVertex2i(hellicopterX + 128, hellicopterY + y + 93);
	glEnd();

	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 138, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 153, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 153, hellicopterY + y + 88);
	glVertex2i(hellicopterX + 138, hellicopterY + y + 88);
	glEnd();

	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 142, hellicopterY + y + 75);
	glVertex2i(hellicopterX + 149, hellicopterY + y + 75);
	glVertex2i(hellicopterX + 149, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 142, hellicopterY + y + 82);
	glEnd();


	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 93);
	glVertex2i(hellicopterX + 225, hellicopterY + y + 93);
	glVertex2i(hellicopterX + 125, hellicopterY + y + 88);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 88);
	glEnd();

	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 220, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 220, hellicopterY + y + 88);
	glVertex2i(hellicopterX + 192, hellicopterY + y + 88);
	glEnd();

	glColor3f(0.23, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 200, hellicopterY + y + 75);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 75);
	glVertex2i(hellicopterX + 115, hellicopterY + y + 82);
	glVertex2i(hellicopterX + 200, hellicopterY + y + 82);
	glEnd();


	glColor3f(0.13, 0.23, 0.28);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 122, hellicopterY + y + 93);
	glVertex2i(hellicopterX + 222, hellicopterY + y + 93);
	glVertex2i(hellicopterX + 222, hellicopterY + y + 100);
	glVertex2i(hellicopterX + 122, hellicopterY + y + 100);
	glEnd();

	glColor3f(0.01, 0.01, 0.01);
	glBegin(GL_POLYGON);
	glVertex2i(hellicopterX + 137, hellicopterY + y + 110);
	glVertex2i(hellicopterX + 144, hellicopterY + y + 110);
	glVertex2i(hellicopterX + 144, hellicopterY + y + 154);
	glVertex2i(hellicopterX + 137, hellicopterY + y + 154);
	glEnd();
	glFlush();
};

void obstacleHellicopter(int x, int z)
{

	int x1 = x;
	int x2 = x;
	int  y = z + 280;
	int  y2 = z + 280;
	int a1 = 0, a2 = 02, b1 = 0, b2 = 0;

	a1 = x1 + 136;
	a2 = x2 + 280;
	b1 = y + 328;
	b2 = y2 + 336;
	glColor3ub(68, 80, 22); //blade
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 192;
	a2 = x2 + 200;
	b1 = y + 280;
	b2 = y2 + 328;
	glColor3ub(68, 80, 22);//blade
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 208;
	a2 = x2 + 216;
	b1 = y + 280;
	b2 = y2 + 328;
	glColor3ub(68, 80, 22); //blade
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 168;
	a2 = x2 + 248;
	b1 = y + 272;
	b2 = y2 + 280;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 160;
	a2 = x2 + 256;
	b1 = y + 264;
	b2 = y2 + 272;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 128;
	a2 = x2 + 264;
	b1 = y + 256;
	b2 = y2 + 264;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 120;
	a2 = x2 + 128;
	b1 = y + 248;
	b2 = y2 + 256;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 160;
	a2 = x2 + 272;
	b1 = y + 248;
	b2 = y2 + 256;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 112;
	a2 = x2 + 120;
	b1 = y + 240;
	b2 = y2 + 248;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 160;
	a2 = x2 + 280;
	b1 = y + 240;
	b2 = y2 + 248;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 104;
	a2 = x2 + 112;
	b1 = y + 200;
	b2 = y2 + 240;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 160;
	a2 = x2 + 288;
	b1 = y + 232;
	b2 = y2 + 240;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 160;
	a2 = x2 + 352;
	b1 = y + 208;
	b2 = y2 + 232;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 352;
	a2 = x2 + 360;
	b1 = y + 192;
	b2 = y2 + 248;
	glColor3ub(68, 80, 22);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 360;
	a2 = x2 + 368;
	b1 = y + 184;
	b2 = y2 + 256;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 368;
	a2 = x2 + 376;
	b1 = y + 176;
	b2 = y2 + 248;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 376;
	a2 = x2 + 384;
	b1 = y + 184;
	b2 = y2 + 240;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 152;
	a2 = x2 + 280;
	b1 = y + 200;
	b2 = y2 + 208;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 80;
	a2 = x2 + 280;
	b1 = y + 192;
	b2 = y2 + 200;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 72;
	a2 = x2 + 280;
	b1 = y + 176;
	b2 = y2 + 192;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 80;
	a2 = x2 + 272;
	b1 = y + 168;
	b2 = y2 + 176;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 88;
	a2 = x2 + 264;
	b1 = y + 160;
	b2 = y2 + 168;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();


	a1 = x1 + 142;
	a2 = x2 + 150;
	b1 = y + 144;
	b2 = y2 + 160;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 232;
	a2 = x2 + 240;
	b1 = y + 144;
	b2 = y2 + 160;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 124;
	a2 = x2 + 248;
	b1 = y + 136;
	b2 = y2 + 144;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 116;
	a2 = x2 + 124;
	b1 = y + 128;
	b2 = y2 + 136;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	a1 = x1 + 248;
	a2 = x2 + 256;
	b1 = y + 128;
	b2 = y2 + 136;
	glColor3ub(68, 80, 22);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(a1, b1);
	glVertex2i(a2, b1);
	glVertex2i(a2, b2);
	glVertex2i(a1, b2);
	glEnd();

	glFlush();
}

void moveparachute()
{
	if (ps[0].parachuteY < -800)
	{
		gameOver();

	}
	ps[0].parachuteY -= (5 + ps[0].sp1);
	parachute(ps[0].parachuteX, ps[0].parachuteY);

}

void movehellicopter(int x, int b)
{
	if (hellicopterStatus == 1)
	{
		hellicopterX += b + speed;
	}
	if (hellicopterX > 1500)
	{
		hellicopterX = 1500;
	}

	if (hellicopterX < 0)
	{
		hellicopterX = 0;
	}
	if (hellicopterY > 500)
	{
		hellicopterY = 500;
	}
	if (hellicopterY < -350)
	{
		hellicopterY = -350;
	}
	hellicopter();
}

void moveobstacleHellicopter()
{
	for (int i = 0; i < 4; i++) {

		if (obs[i].obstaclehellicopterX < -380)
		{
			obs[i].obstaclehellicopterX = 2000;
			score++;

		}

		obs[i].obstaclehellicopterX -= (5 + obs[i].sp);
		obstacleHellicopter(obs[i].obstaclehellicopterX, obs[i].obstaclehellicopterY);
	}

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'R' || key == 'r')
		// start
	{
		cloudStatus = 1;
		birdStatus = 1;
		parachuteStatus = 1;
		hellicopterStatus = 1;
		b = +.5;
		speed = .5;
		obstaclehellicopterStatus = 1;
		start = true;
	}

	//else if (key == 'n' || key =='N')
	//	//new game
	//{
	//	 cloudStatus = 1;r
	//	birdStatus=1;
	//	parachuteStatus = 1;
	//	hellicopterStatus = 1;
	//	b = +.5;
	//	speed = .5;
	//	obstaclehellicopterStatus = 1;
	//	start=true;
	//}


	if (start) {
		if (key == 'd' || key == 'D')
			//hellicopter speed up
		{
			hellicopterStatus = 1;
			b = +.5;
			speed = 2.5;
		}
		else if (key == 'a' || key == 'A')
			//hellicopter speed low
		{
			hellicopterStatus = 1;
			b = -.5;
			speed = -1.0;
		}

		else if (key == 'w' || key == 'W')
			//hellicopter up
		{
			hellicopterStatus = 1;
			hellicopterY += 15.0;

		}
		else if (key == 's' || key == 'S')
			//hellicopter down
		{
			hellicopterStatus = 1;
			hellicopterY -= 15.0;
		}


	}
}
void initparachute(int x, int y) {
	ps[0].sp1 = .5;
	ps[0].parachuteX = x - 600;
	ps[0].parachuteY = y - 300;

}

void collision() {

	for (int i = 0; i < 4; i++)
	{
		//cout<<"for "<<i<<" obs x="<< obs[i].obstaclehellicopterX<<" y="<<obs[i].obstaclehellicopterY<<" HX="<<hellicopterX<<" HY="<<hellicopterY<<endl;

		if ((obs[i].obstaclehellicopterX < hellicopterX + 150 && obs[i].obstaclehellicopterX > hellicopterX - 150) && (obs[i].obstaclehellicopterY < hellicopterY + 350 + 100 && obs[i].obstaclehellicopterY > hellicopterY + 350 - 120))

		{
			start = false;
			finish = true;
			cout << "colide" << endl;

			initparachute(hellicopterX, hellicopterY);
			//gameOver();
		}
	}


}

void timeTick(void) {
	if (UpwardsScrollVelocity < -600)
		view -= 0.000011;
	if (view < 0) {
		view = 20;
		UpwardsScrollVelocity = -10.0;
	}
	//  exit(0);
	UpwardsScrollVelocity -= 0.1;
	glutPostRedisplay();

}
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}
void RenderToDisplay() {
	int l, lenghOfQuote, i;

	glTranslatef(0.0, 15, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	for (l = 0; l < numberOfQuotes; l++) {
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), -(l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity / 10) + 300 + (l * 10), (UpwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
		}
		glPopMatrix();
	}

}
void myDisplayFunction(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();
}
void gameOver() {
	char* str = new char[30];
	sprintf(str, "%d", score);

	strcpy(quote[0], "Game Over!");
	strcpy(quote[1], "Your Score :");
	strcpy(quote[2], str);
	strcpy(quote[3], "Press n for New game!");
	numberOfQuotes = 5;
	glutDestroyWindow(1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(2000, 1500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game Finish");
	glClearColor(0.71, 0.37, 0.2, 1);
	glLineWidth(3);

	glutDisplayFunc(myDisplayFunction);
	glutReshapeFunc(reshape);
	//glutIdleFunc(timeTick);
	glutMainLoop();
	keyboard(0, 0, 0);
}


void initObstacle()
{
	int x = 1500;
	int y = 100;
	for (int i = 0; i < 4; i++)
	{
		obs[i].sp = i + 1; // DeFINES THE SPEED OF THE OBSTRUCKLE HELICOPTER
		obs[i].obstaclehellicopterX = x;
		obs[i].obstaclehellicopterY = y;
		x -= 550;
		y += 240;
	}

}


void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	sky();
	water();
	field();

	grassfield();

	movecloud();
	movebird();

	if (start) {
		moveobstacleHellicopter();

		movehellicopter(b, speed);
		collision();
	}
	else if (finish) {
		movehellicopter(b, speed);
		moveobstacleHellicopter();
		moveparachute();
		hellicopterStatus = 0;
		speed = 0;
		obstaclehellicopterStatus = 0;
	}

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();

}

void myInit(void) {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 2000.0, 0.0, 1500.0);
}

int main(int argc, char** argv) {

	cout << "Wings Over Water";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(2000, 1500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Wings Over Water");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(myDisplay);
	initObstacle();
	myInit();
	glutMainLoop();

	return 0;
}

