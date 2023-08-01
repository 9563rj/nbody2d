#include <iostream>
#include <SDL.h>
#include "object.h"

int windowX = 2560;
int windowY = 1440;
double windowCenterX = windowX / 2;
double windowCenterY = windowY / 2;
double deltaT = 1.0e-10;

SDL_Window* window = NULL;
SDL_Surface* windowSurface = NULL;

void accelerateObjects(std::vector<Object*> objects, std::vector<forceBetween*> forcesVector) {
	//std::cout << "accelerating objects" << std::endl;
	/*for (int i = 0; i < objects.size(); i++) {
		objects[i]->computePosAccel(objects, forcesVector);
	}*/
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (j > i) {
				std::vector<double> forces = objects[i]->computeForce(objects[j]);
				double forceX = forces[0];
				double forceY = forces[1];
				objects[j]->reverseForce(forceX, forceY);
			}
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->computeAccel();
	}
}

void moveObjects(std::vector<Object*> objects, std::vector<forceBetween*> forcesVector) {
	//std::cout << "moving objects" << std::endl;
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->updatePos();
	}
	//forcesVector.clear();
}

void drawObjects(std::vector<Object*> objects) {
	Uint32 colorWhite = SDL_MapRGB(windowSurface->format, 255, 255, 255);
	Uint32 colorBlack = SDL_MapRGB(windowSurface->format, 0, 0, 0);
	Uint32 colorRed = SDL_MapRGB(windowSurface->format, 255, 0, 0);
	Uint32 colorBlue = SDL_MapRGB(windowSurface->format, 0, 0, 255);
	Uint32 colorGreen = SDL_MapRGB(windowSurface->format, 0, 255, 0);
	SDL_Rect clearRect;
	clearRect.x = 0;
	clearRect.y = 0;
	clearRect.w = windowX;
	clearRect.h = windowY;
	SDL_FillRect(windowSurface, &clearRect, colorBlack);
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getMass() > 1e30) {
			objects[i]->draw(windowSurface, colorRed);
		}
		else if (objects[i]->systemID == 0) {
			objects[i]->draw(windowSurface, colorGreen);
		}
		else if (objects[i]->systemID == 1) {
			objects[i]->draw(windowSurface, colorBlue);
		}
	}
	SDL_UpdateWindowSurface(window);
}

void computeEnergy(std::vector<Object*> objects) {
	double totalEnergy = 0;
	for (int i = 0; i < objects.size(); i++) {
		double velocity = sqrt(objects[i]->getVelocityX() * objects[i]->getVelocityX() + objects[i]->getVelocityY() * objects[i]->getVelocityY());
		double energy = .5 * objects[i]->getMass() * velocity * velocity;
		totalEnergy += energy;
	}
	//std::cout << "total energy of the system is " << totalEnergy << std::endl;
}

int main(int argc, char* argv[]) {
	window = SDL_CreateWindow("N-Body 2D Gravity Sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowX, windowY, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL." << std::endl;
	}

	bool exit = false;

	std::vector<Object*> objects;
	std::vector<forceBetween*> forcesVector;
	// 400 266 200 134
	/*objects.push_back(new Object(400, 266, 6e24, 0, 10));
	objects.push_back(new Object(200, 134, 6e24, 0, -10));*/
	/*objects.push_back(new Object(windowCenterX - (windowX / 8), windowCenterY, 6e27, 0, 1.0e10, 0));
	objects.push_back(new Object(windowCenterX + (windowX / 9), windowCenterY, 6e27, 0, -1.0e10, 0));
	objects.push_back(new Object(windowCenterX, windowCenterY - (windowY / 10), 6e27, 1.0e10, 0, 0));
	objects.push_back(new Object(windowCenterX, windowCenterY + (windowY / 11), 6e27, -1.0e10, 0, 0));
	objects.push_back(new Object(windowCenterX, windowCenterY, 1e30, 0, 0, 0));*/

	objects.push_back(new Object(windowCenterX + 451, windowCenterY, 2e30, 0, 6.0e9, 0));
	objects.push_back(new Object(windowCenterX - 451, windowCenterY, 2e30, 0, -6.0e9, 1));

	for (int i = -14; i < 10; i++) {
		for (int j = -17; j < 10; j++) {
			objects.push_back(new Object(windowCenterX + i * 10 + 550, windowCenterY + j * 10, 6e24, 0, 8.0e9, 0));
		}
	}

	for (int i = -14; i < 10; i++) {
		for (int j = -14; j < 10; j++) {
			objects.push_back(new Object(windowCenterX + i * 10 - 550, windowCenterY + j * 10, 6e24, 0, -8.0e9, 1));
		}
	}

	while (!exit) {
		accelerateObjects(objects, forcesVector);
		moveObjects(objects, forcesVector);
		drawObjects(objects);
		computeEnergy(objects);
		//std::cout << "particle count: " << objects.size() << std::endl;

		SDL_Event SDLevent;
		while (SDL_PollEvent(&SDLevent)) {
			switch (SDLevent.type) {
			case SDL_KEYDOWN:
				switch (SDLevent.key.keysym.sym) {
				case SDLK_ESCAPE:
					exit = true;
					break;
				}
				break;
			case SDL_MOUSEWHEEL:
				if (SDLevent.wheel.y > 0) { // scroll up
					deltaT = deltaT * 2;
				}
				if (SDLevent.wheel.y < 0) { // scroll down 
					deltaT = deltaT / 2;
				}
				break;
			}
		}
	}

	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	std::exit(0);
}