#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[]) {

	/*
	 *	ACA ARRANCA EL EJEMPLO DE SDL
	 */

	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("An SDL2 window",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_Quit();

	/*
	 *	ACA ARRANCA EL EJEMPLO DE BOX2D
	 */

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	for (int32 i = 0; i < 60; ++i) {
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	std::cout << "FUNCIONA!";

	return 0;
}

