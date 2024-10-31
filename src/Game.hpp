#pragma once
#include "EntityManager.hpp"

#define UNIT_SCORE 10

struct PaddleConfig {
	int SL,SB, CR, FR, FG, FB, OR, OG, OB, OT, V;
	float S;
};
//Shape Radius, Collision Radius, Fill RGB, Outline RGB, Outline Thickness,Shape Vertices
//Speed

struct BallConfig {
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
	float S;
};

struct BrickConfig {
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
	float S;
};

class Game {
	sf::RenderWindow m_window;  // window to draw to
	EntityManager m_entityManager;
	sf::Font m_font;
	sf::Text m_text;
	PaddleConfig m_paddleConfig;
	BallConfig m_ballConfig;
	BrickConfig m_brickConfig;
	uint32_t m_score = 0;
	uint32_t m_lives = 3;
	uint64_t m_currentFrame = 0;
	bool m_paused = false;
	bool m_running = true;

	std::shared_ptr<Entity> m_paddle;
	std::shared_ptr<Entity> m_ball;
	// initialize game state with config file
	void init();

	void sMovement();      // System: Entity position/movement update
	void sUserInput();     // System: User input
	void sLifespan();      // System: Lifespan
	void sRender();	       // System: Render
	void sCollision();     // System:  Collision

	void spawnpaddle();
	void spawnball();
	void spawnBricks();

public:
	Game();

	void run();
};