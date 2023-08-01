#include "object.h"

extern int windowX;
extern int windowY;
extern double deltaT;

const double G = 6.67430e-11;

forceBetween::forceBetween(Object* inputObject1, Object* inputObject2, double inputForceX, double inputForceY) {
	object1 = inputObject1;
	object2 = inputObject2;
	forceX = inputForceX;
	forceY = inputForceY;
}

Object::Object(double inputPosX, double inputPosY, double inputMass, double inputVelocityX, double inputVelocityY, int inputSystemID) {
	posX = inputPosX;
	posY = inputPosY;
	mass = inputMass;
	velocityX = inputVelocityX;
	velocityY = inputVelocityY;
	nextPosX = posX;
	nextPosY = posY;
	nextVelocityX = velocityX;
	nextVelocityY = velocityY;
	systemID = inputSystemID;
	totalForceX = 0;
	totalForceY = 0;
}

std::vector<double> Object::computeForce(Object* target) {
	/*
	double totalForceX = 0;
	double totalForceY = 0;
	for (int i = 0; i < objects.size(); i++) {
		bool calcAlreadyDone = false;
		double prevCalcForceX = 0;
		double prevCalcForceY = 0;
		for (int j = 0; j < forcesVector.size(); j++) {
				if (forcesVector[j]->object1 == this && forcesVector[j]->object2 == objects[i]) {
					calcAlreadyDone = true;
					prevCalcForceX = forcesVector[j]->forceX;
					prevCalcForceY = forcesVector[j]->forceY;
				}
				else if (forcesVector[j]->object1 == objects[i] && forcesVector[j]->object2 == this) {
					calcAlreadyDone = true;
					prevCalcForceX = 0 - forcesVector[j]->forceX;
					prevCalcForceY = 0 - forcesVector[j]->forceY;
				}
		}
		if (objects[i] != this && !calcAlreadyDone) {
			double deltaX = objects[i]->getX() - posX;
			double deltaY = objects[i]->getY() - posY;
			double forceMagnitude = (mass * objects[i]->getMass() * G) / std::sqrt((deltaX * deltaX)+(deltaY*deltaY));
			double theta = (atan2(deltaY, deltaX));
			double forceX = forceMagnitude * cos(theta);
			double forceY = forceMagnitude * sin(theta);
			totalForceX += forceX;
			totalForceY += forceY;
			forcesVector.push_back(new forceBetween(this, objects[i], forceX, forceY));
			//std::cout << "Stored a new calculation between object " << this << " and object " << objects[i] << " with forces " << forceX << " and " << forceY << std::endl;
		}
		else if (calcAlreadyDone) {
			totalForceX += prevCalcForceX;
			totalForceY += prevCalcForceY;
			//std::cout << "Used a previous calculation involving object " << this << " with forces " << prevCalcForceX << " and " << prevCalcForceY << std::endl;
		}
	}*/
	double deltaX = target->getX() - posX;
	double deltaY = target->getY() - posY;
	double forceMagnitude = (mass * target->getMass() * G) / std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
	double theta = (atan2(deltaY, deltaX));
	double forceX = forceMagnitude * cos(theta);
	double forceY = forceMagnitude * sin(theta);
	totalForceX += forceX;
	totalForceY += forceY;
	std::vector<double> forces;
	forces.push_back(forceX);
	forces.push_back(forceY);
	return forces;
}

void Object::reverseForce(double forceX, double forceY) {
	totalForceX -= forceX;
	totalForceY -= forceY;
}

void Object::computeAccel() {
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
	totalForceX = 0;
	totalForceY = 0;
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