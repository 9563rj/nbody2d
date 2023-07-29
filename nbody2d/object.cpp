#include "object.h"

extern int windowX;
extern int windowY;
extern double deltaT;

const double G = 6.67430e-11;

Object::Object(double inputPosX, double inputPosY, double inputMass, double inputVelocityX, double inputVelocityY) {
	posX = inputPosX;
	posY = inputPosY;
	mass = inputMass;
	velocityX = inputVelocityX;
	velocityY = inputVelocityY;
	nextPosX = posX;
	nextPosY = posY;
	nextVelocityX = velocityX;
	nextVelocityY = velocityY;
}

void Object::computePosAccel(std::vector<Object*> objects) {
	double totalForceX = 0;
	double totalForceY = 0;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] != this) {
			double deltaX = objects[i]->getX() - posX;
			double deltaY = objects[i]->getY() - posY;
			double forceMagnitude = (mass * objects[i]->getMass() * G) / std::sqrt((deltaX * deltaX)+(deltaY*deltaY));
			double theta = (atan2(deltaY, deltaX));
			double forceX = forceMagnitude * cos(theta);
			double forceY = forceMagnitude * sin(theta);
			totalForceX += forceX;
			totalForceY += forceY;
		}
	}
	double accelX = totalForceX / mass;
	double accelY = totalForceY / mass;
	nextVelocityX = velocityX + accelX * deltaT;
	nextVelocityY = velocityY + accelY * deltaT;
	nextPosX = posX + .5 * deltaT * (velocityX + nextVelocityX);
	nextPosY = posY + .5 * deltaT * (velocityY + nextVelocityY);
}

void Object::updatePos() { // if bugs, clear next variables to debug value and put checks for it
	posX = nextPosX;
	posY = nextPosY;
	velocityX = nextVelocityX;
	velocityY = nextVelocityY;
}

void Object::draw(SDL_Surface* surface, Uint32 color) {
	SDL_Rect rect;
	rect.x = posX;
	rect.y = windowY - posY;
	rect.w = 1;
	rect.h = 1;
	SDL_FillRect(surface, &rect, color);
}

double Object::getX() {
	return posX;
}

double Object::getY() {
	return posY;
}

double Object::getMass() {
	return mass;
}

double Object::getVelocityX() {
	return velocityX;
}

double Object::getVelocityY() {
	return velocityY;
}