//header files
#include "main.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <clocale>
#include <sstream>  
#include <vector>
#include <string>
#include <cmath>
#include <list>
#include <cmath> 

#include <cassert>
#include "glut.h"
#include "Sleep.h"
#include  "ObjLibrary\ObjModel.h"
#include "ObjLibrary/DisplayList.h"



//using namespace
using namespace std;
using namespace ObjLibrary;
//prototype
void init();
void initDisplay();
void update();
void reshape(int w, int h);
void display();
void SavePoints();
void FindArc();
string error = "";
double globcommArcLength = 0;
int seqNo = 0;
int frame = 1;
int maxcount = 0;
Vector2 vel(0.0, 0.0);

class Point {
public:
	double x;
	double y;
	double z;
	int sequence;
	double segLength;
	double commArcLength;
	float u;
	int parent;
	int count;
};

std::list<Point> points;
std::list<Point> spacePoints;
std::list<Point> newPoints;

void SavePoints()
{
	Point p;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;
	p.sequence = 1;
	p.u = 0.0;
	points.push_back(p);


	p.x = 1.0;
	p.y = 3.5;
	p.z = 0.0;
	p.u = 0.1;
	p.sequence = 2;
	points.push_back(p);

	p.x = 4.8;
	p.y = 1.8;
	p.z = 0.0;
	p.u = 0.2;

	p.sequence = 3;
	points.push_back(p);

	p.x = 6.5;
	p.y = 7.0;
	p.z = 0.0;
	p.u = 0.3;

	p.sequence = 4;
	points.push_back(p);

	p.x = 9.0;
	p.y = 3.5;
	p.z = 0.0;
	p.sequence = 5;
	p.u = 0.4;

	points.push_back(p);

	p.x = 32.5;
	p.y = 4.8;
	p.z = 0.0;
	p.sequence = 6;
	p.u = 0.5;
	points.push_back(p);

	p.x = 33.2;
	p.y = 2.6;
	p.z = 0.0;
	p.sequence = 7;
	p.u = 0.6;

	points.push_back(p);

	p.x = 36.8;
	p.y = 7.0;
	p.z = 0.0;
	p.u = 0.7;

	p.sequence = 8;
	points.push_back(p);

	p.x = 37.8;
	p.y = 5.0;
	p.z = 0.0;
	p.u = 0.8;

	p.sequence = 9;
	points.push_back(p);

	p.x = 41.2;
	p.y = 20.5;
	p.z = 0.0;
	p.sequence = 10;
	p.u = 0.9;

	points.push_back(p);

	p.x = 41.5;
	p.y = 21.5;
	p.z = 0.0;
	p.sequence = 11;
	p.u = 1.0;
	points.push_back(p);



}


Point  GetPointforSphere(int sequence)
{
	std::list<Point>::iterator it;
	Point p;
	for (it = points.begin(); it != points.end(); ++it)
	{

		if (it->sequence == sequence)
		{
			p = *it;
			return p;
		}
	}
	return p;

}

Point  GetPoint(int sequenceNumber)
{
	std::list<Point>::iterator it;
	Point p;
	for (it = points.begin(); it != points.end(); ++it)
	{
		if (it->sequence == sequenceNumber)
		{
			p = *it;
			return p;
		}
	}
	return p;

}

Point  GetSequencePoint(int sequenceNumber)
{
	std::list<Point>::iterator it;
	Point p;
	for (it = spacePoints.begin(); it != spacePoints.end(); ++it)
	{
		if ((it->u) == sequenceNumber)
		{
			p = *it;
			return p;
		}
	}
	return p;

}


Point  GetNewPoint(int sequenceNumber)
{
	Point p;
	std::list<Point>::iterator iter = newPoints.begin();
	std::advance(iter, sequenceNumber);

	p = *iter;
	return p;

}

double calculateB0(double u)
{
	return ((1 - u)*(1 - u)*(1 - u)) / 6;
}
double calculateB1(double u)
{
	return  (3 * u*u*u - 6 * u*u + 4) / 6.0f;
}
double calculateB2(double u)
{
	return (-3 * u*u*u + 3 * u*u + 3 * u + 1) / 6.0f;
}

double calculateB3(double u)
{
	return u * u*u / 6.0f;
}
void SpacePoints()
{
	std::list<Point>::iterator it;
	int count = 1;
	int sequenceNo = 0;
	for (size_t i = 0; i < points.size() - 3; i++)
	{
		Point p = GetPoint(count);


	}
}



void GenerateBSpline()
{
	std::list<Point>::iterator it;
	int count = 1;
	int sequenceNo = 0;
	Point oldPoint ;
		


		
	for (size_t i = 0; i < points.size() - 3; i++)
	{
		Point p = GetPoint(count);
		sequenceNo = sequenceNo + 1;
		p.sequence = sequenceNo;
		newPoints.push_back(p);
		Point p1 = GetPoint(count + 1);
		Point p2;
		Point p3;
		if (i < points.size() - 3)
		{
			p2 = GetPoint(count + 2);
			p3 = GetPoint(count + 3);
		}
		
		for (int j = 0; j <= 500; j++)
		{

			double u = j / 500.0;    // u is a fraction between 0 and 1

			double b0 = calculateB0(u)*p.x;
			double b1 = calculateB1(u)*p1.x;
			double b3 = 0.0;
			double b2 = 0.0;
			double x;
			if (i < points.size() - 3)
			{
				b2 = calculateB2(u)*p2.x;
				b3 = calculateB3(u)*p3.x;
			}
			double by0 = calculateB0(u)*p.y;
			double by1 = calculateB1(u)*p1.y;
			double by2 = 0;
			double by3 = 0;
			if (i < points.size() - 3)
			{
				by2 = calculateB2(u)*p2.y;
				by3 = calculateB3(u)*p3.y;
			}

			x = b0 + b1 + b2 + b3;
			double y = by0 + by1 + by2 + by3;
			sequenceNo = sequenceNo + 1;

			Point newP;
			newP.x = x;
			newP.y = y;
			newP.sequence = sequenceNo;
			newP.u = u;

			//double segLngth = sqrt((newP.x - oldPoint.x)*(newP.x - oldPoint.x) + (newP.y - oldPoint.y)*(newP.y - oldPoint.y));

			//newP.segLength = segLngth;
		//	newP.commArcLength = globcommArcLength + segLngth;
			//globcommArcLength = globcommArcLength + segLngth;
			oldPoint = newP;
			newPoints.push_back(newP);

		}

		count = count + 1;
	}

}

void GenerateSpacePoints()
{
	std::list<Point>::iterator it;
	int count = 1;
	int sequenceNo = 0;	
	Point oldPoint;

	for (size_t i = 0; i < points.size() - 3; i++)
	{
		Point p = GetPoint(count);
		sequenceNo = sequenceNo + 1;
		p.sequence = sequenceNo;
		newPoints.push_back(p);
		Point p1 = GetPoint(count + 1);
		Point p2;
		Point p3;
		if (i < points.size() - 3)
		{
			p2 = GetPoint(count + 2);
			p3 = GetPoint(count + 3);
		}
		double u = 0;
	

		while (u < 0.9)
		{
			
			double b0 = calculateB0(u)*p.x;
			double b1 = calculateB1(u)*p1.x;
			double b3 = 0.0;
			double b2 = 0.0;
			double x;
			if (i < points.size() - 3)
			{
				b2 = calculateB2(u)*p2.x;
				b3 = calculateB3(u)*p3.x;
			}
			double by0 = calculateB0(u)*p.y;
			double by1 = calculateB1(u)*p1.y;
			double by2 = 0;
			double by3 = 0;
			if (i < points.size() - 3)
			{
				by2 = calculateB2(u)*p2.y;
				by3 = calculateB3(u)*p3.y;
			}

			x = b0 + b1 + b2 + b3;
			double y = by0 + by1 + by2 + by3;
			sequenceNo = sequenceNo + 1;

			Point newP;
			newP.x = x;
			newP.y = y;
			newP.sequence = sequenceNo;
			newP.u = u;
			double segLngth = 0;
			if (u == 0 && count == 1)
			{

			}
			else {
				segLngth = sqrt((newP.x - oldPoint.x)*(newP.x - oldPoint.x) + (newP.y - oldPoint.y)*(newP.y - oldPoint.y));
			}
			newP.segLength = segLngth;
			newP.commArcLength = globcommArcLength + segLngth;
			globcommArcLength = globcommArcLength + segLngth;
			oldPoint = newP;
			newP.parent = count;
			newP.count = maxcount;
			spacePoints.push_back(newP);
			u = u + 0.1;
			maxcount = maxcount + 1;
		}
		count = count + 1;
	}

}


int main(int argc, char* argv[])
{

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Programming Curve");
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 1;
}

void init()
{
	//initialize before
	initDisplay();
	SavePoints();
//	FindArc();
	GenerateBSpline();
	GenerateSpacePoints();
}

void initDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutPostRedisplay();
}

void update()
{
	// update your variables here
	Sleep(1 / 60.0);
	frame = frame + 1;

	/*seqNo = seqNo + 7;

	if (seqNo >= newPoints.size())
	{
		seqNo = 0;
	}
	Point p = GetNewPoint(seqNo);
	vel.set(p.x, p.y);*/
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}
void FindArc()
{
	std::list<Point>::iterator it;
	int count = 1;
	int sequenceNo = 0;
	std::list<Point>::iterator iter = points.begin();
	Point p;
	Point p1;
	for (it = points.begin(); it != points.end(); ++it)
	{
		p = *it;
		if (p.u != 1.0)
		{

			std::advance(iter, 1);
			p1 = *iter;
			double segLngth = sqrt((p1.x - p.x)*(p1.x - p.x) + (p1.y - p.y)*(p1.y - p.y));
			globcommArcLength = globcommArcLength + segLngth;
			iter->segLength = segLngth;
			iter->commArcLength = globcommArcLength;
		}
	}
}

Point GetArc(double arcLength)
{
	std::list<Point>::iterator it;
	Point p;
	Point p1;
	for (it = spacePoints.begin(); it != spacePoints.end(); ++it)
	{
		p = *it;
		if (p.commArcLength > arcLength)
		{
			return p;
		}
	}
}
Point GetPrevpoint(int count)
{
	std::list<Point>::iterator it;
	Point p;
	Point p1;
	for (it = spacePoints.begin(); it != spacePoints.end(); ++it)
	{
		p = *it;
		if (p.count ==count)
		{
			return p;
		}
	}
}

double LinearInterpolation(Point p, Point p1, double arcLength)
{
	double val = p.u + (arcLength - p.commArcLength) / (p1.commArcLength - p.commArcLength) * (p1.u - p.u);
	return val;
}


void DrawSphere(int frame)
{
	std::list<Point>::iterator it;
	int count = 1;
	int sequenceNo = 0;

	double d = (frame*globcommArcLength) / 300;	
	Point subPoint  = GetArc(d);
	Point subPoint1 = GetPrevpoint(subPoint.count-1);
	if (subPoint.parent != subPoint1.parent)
	{
		subPoint.u = 1.0;
	}
	double u = LinearInterpolation(subPoint1, subPoint, d);
	int parent = subPoint1.parent;	

	
	Point p = GetPoint(parent);
	Point p1= GetPoint(p.sequence + 1);
		Point p2 = GetPoint(p.sequence +2);
		Point p3 = GetPoint(p.sequence +3);

		double b0 = calculateB0(u)*p.x;
		double b1 = calculateB1(u)*p1.x;
		double b3 = 0.0;
		double b2 = 0.0;
		double x;

		b2 = calculateB2(u)*p2.x;
		b3 = calculateB3(u)*p3.x;

		double by0 = calculateB0(u)*p.y;
		double by1 = calculateB1(u)*p1.y;
		double by2 = 0;
		double by3 = 0;

		by2 = calculateB2(u)*p2.y;
		by3 = calculateB3(u)*p3.y;


		x = b0 + b1 + b2 + b3;
		double y = by0 + by1 + by2 + by3;
		vel.x = x;
		vel.y = y;

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(20.0, 12.0, 30.0,
		20.0, 8.0, 0.0,
		0.0, 1.0, 0.0);
	glColor3f(0, 0, 0);
	glPointSize(8.0f);
	std::list<Point>::iterator it;


	glPushMatrix();
	glBegin(GL_POINTS);

	for (it = points.begin(); it != points.end(); ++it)
	{
		glVertex3d(it->x, it->y, it->z);
	}

	glPopMatrix();

	glEnd();

	glColor3f(0, 0, 1);
	glPointSize(1.8f);
	glPushMatrix();
	glBegin(GL_POINTS);
	int count = 1;
	for (it = newPoints.begin(); it != newPoints.end(); ++it)
	{
		glVertex3d(it->x, it->y, 0);
	}
	glPopMatrix();
	glEnd();

	glPushMatrix();
	if (frame < 300)
	{
		DrawSphere(frame);
		glTranslatef(vel.x, vel.y, 0);
		glColor3f(1, 1, 0);
		glutSolidSphere(1.1, 23, 23);
		glPopMatrix();
		glEnd();
	}
	else {
		frame = 0;


	}


	glutSwapBuffers();
}

