#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>
#include <SDL.h>
#include <cmath>

struct forceBetween;

class Object {
public:
	Object(double inputPosX, double inputPosY, double inputMass, double inputVelocityX, double inputVelocityY, int inputSystemID);
	std::vector<double> computeForce(Object* target);
	void reverseForce(double forceX, double forceY);
	void computeAccel();
	void updatePos();
	void draw(SDL_Surface* surface, Uint32 color);
	double getX();
	double getY();
	double getMass();
	double getVelocityX();
	double getVelocityY();
	int systemID;
private:
	double posX;
	double posY;
	double mass;
	double velocityX;
	double velocityY;

	double nextPosX;
	double nextPosY;
	double nextVelocityX;
	double nextVelocityY;

	double totalForceX;
	double totalForceY;
};

struct forceBetween {
	Object* object1;
	Object* object2;
	double forceX;
	double forceY;
	forceBetween(Object* inputObject1, Object* inputObject2, double inputForceX, double inputForceY);
};

#endif