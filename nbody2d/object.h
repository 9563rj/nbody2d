#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <SDL.h>
#include <cmath>


class Object {
public:
	Object(double inputPosX, double inputPosY, double inputMass, double inputVelocityX, double inputVelocityY);
	void computePosAccel(std::vector<Object*> objects);
	void updatePos();
	void draw(SDL_Surface* surface, Uint32 color);
	double getX();
	double getY();
	double getMass();
	double getVelocityX();
	double getVelocityY();
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
};

#endif