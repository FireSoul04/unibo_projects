#include "Game.h"

#include <vector>

#include <iostream>

std::vector<Mesh*> meshes;
Mesh* playerMesh;

Game::Game(const int width, const int height)
	: window(width, height, "Asteroids")
{
	this->width = width;
	this->height = height;
	
	std::vector<Vertex> points;
	float cx = width / 2;
	float cy = height / 2;
	float r = 1.0f;

	Vertex c;
	c.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	c.point = glm::vec3(cx, cy, 0.0f);
	points.push_back(c);
	int ntriangles = 40;
	float step = glm::two_pi<float>() / ntriangles;
	for (int i = 0; i <= ntriangles; i++) {
		float t = step * i;

		Vertex v;
		v.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		v.point = glm::vec3(cx + r * cos(t), cy + r * sin(t), 0.0f);
		points.push_back(v);
	}
	playerMesh = new Mesh(points, 0, ShaderClass::PLAYER, GL_TRIANGLE_FAN);

	meshes.push_back(playerMesh);
}

void Game::run() {
	float dt, currentTime, lastTime = 0.0f;
	while (!window.shouldClose()) {
		currentTime = window.getTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;
	
		update(dt);
		window.render(meshes);
	}
}

glm::vec3 pos = glm::vec3(0);

float speed = 1000.0f;

void Game::update(float dt) {
	glm::vec2 velocity = glm::vec2(0);
	if (window.isActionPressed(InputHandler::MOVE_LEFT)) {
		velocity.x -= 1.0f;
	}
	if (window.isActionPressed(InputHandler::MOVE_RIGHT)) {
		velocity.x += 1.0f;
	}
	if (window.isActionPressed(InputHandler::MOVE_DOWN)) {
		velocity.y -= 1.0f;
	}
	if (window.isActionPressed(InputHandler::MOVE_UP)) {
		velocity.y += 1.0f;
	}
	if (glm::length(velocity) > 0.0f) {
		velocity = glm::normalize(velocity);
	}
	pos += glm::vec3(velocity, 0.0f) * speed * dt;
	playerMesh->model = glm::mat4(1.0f);
	playerMesh->model = glm::translate(playerMesh->model, pos);
}