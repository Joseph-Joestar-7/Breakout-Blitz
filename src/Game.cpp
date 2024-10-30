#include "Game.hpp"
#include <iostream>
Game::Game()
{
	this->init();
}

void Game::init()
{
	m_window.create(sf::VideoMode(640, 640), "Breakout Blitz");
	m_window.setFramerateLimit(60);

	if (!m_font.loadFromFile("fonts/KillerTech.ttf")) {
		std::cerr << "Couldn't load the font\n";
		exit(-1);
	}
	m_text = sf::Text("Score: 0", m_font, 18);

	// Create references to the configurations
	PaddleConfig& p = m_paddleConfig;
	BallConfig& b = m_ballConfig;
	BrickConfig& br = m_brickConfig;

	// Hardcode the paddle configuration values
	p.SL = 100;
	p.SB = 20;
	p.CR = 50;       // Collision Radius
	p.FR = 255;      // Fill Red color component
	p.FG = 0;        // Fill Green color component
	p.FB = 0;        // Fill Blue color component
	p.OR = 255;      // Outline Red color component
	p.OG = 255;      // Outline Green color component
	p.OB = 255;      // Outline Blue color component
	p.OT = 5;        // Outline Thickness
	p.V = 4;        // Shape Vertices
	p.S = 5.0f;      // Speed

	// Hardcode the ball configuration values
	b.SR = 20;       // Shape Radius
	b.CR = 18;       // Collision Radius
	b.FR = 255;      // Fill Red color component
	b.FG = 255;      // Fill Green color component
	b.FB = 0;        // Fill Blue color component
	b.OR = 255;      // Outline Red color component
	b.OG = 255;      // Outline Green color component
	b.OB = 255;      // Outline Blue color component
	b.OT = 3;        // Outline Thickness
	b.V = 30;        // Shape Vertices
	b.S = 4.0f;      // Speed

	// Hardcode the brick configuration values
	br.SR = 40;      // Shape Radius
	br.CR = 35;      // Collision Radius
	br.FR = 0;       // Fill Red color component
	br.FG = 0;       // Fill Green color component
	br.FB = 255;     // Fill Blue color component
	br.OR = 255;     // Outline Red color component
	br.OG = 0;       // Outline Green color component
	br.OB = 0;       // Outline Blue color component
	br.OT = 4;       // Outline Thickness
	br.V = 4;        // Shape Vertices (rectangle shape)
	br.S = 0.0f;     // Speed (static bricks)

	this->spawnpaddle();
	this->spawnball();
	this->spawnBricks();
}

void Game::spawnpaddle()
{
	PaddleConfig& pC = m_paddleConfig;
	auto entity = m_entityManager.addEntity("paddle");

	// Setting paddle position near the bottom of the screen
	float X = m_window.getSize().x / 2.0f;              // Center horizontally
	float Y = m_window.getSize().y - pC.SB * 2.0f;      // Position near bottom

	// Adding Transform with the updated Y position
	entity->cTransform = std::make_shared<CTransform>(
		glm::vec2(X, Y), glm::vec2(0.0f, 0.0f), 0.0f);

	// Adding Shape with fill and outline colors
	sf::Color fillColor(pC.FR, pC.FG, pC.FB);
	sf::Color outlineColor(pC.OR, pC.OG, pC.OB);
	entity->cShape = std::make_shared<CShape>(pC.SL, pC.SB, fillColor, outlineColor, pC.OT);


	// Enabling input
	entity->cInput = std::make_shared<CInput>();

	// Enabling collisions
	entity->cCollision = std::make_shared<CCollision>(pC.CR);

	m_paddle = entity;
}

void Game::spawnball()
{
	BallConfig& bC = m_ballConfig;
	auto entity = m_entityManager.addEntity("ball");

	// Set initial position of the ball above the paddle
	float X = m_window.getSize().x -100.0f;
	float Y = m_window.getSize().y/2.0f;

	// Adding Transform with the starting position and initial velocity
	glm::vec2 initialVelocity(-bC.S/sqrt(2), bC.S / sqrt(2)); // initially towards the paddle
	entity->cTransform = std::make_shared<CTransform>(
		glm::vec2(X, Y), initialVelocity, 45.0f);

	// Adding Shape with fill and outline colors
	sf::Color fillColor(bC.FR, bC.FG, bC.FB);
	sf::Color outlineColor(bC.OR, bC.OG, bC.OB);
	entity->cShape = std::make_shared<CShape>(bC.SR,0, fillColor,
		outlineColor, bC.OT);

	// Enable collisions
	entity->cCollision = std::make_shared<CCollision>(bC.CR);

	m_ball = entity;
}

void Game::spawnBricks()
{
	BrickConfig& brC = m_brickConfig;

	// Define the brick grid layout
	int rows = 5;        // Number of brick rows
	int cols = 10;       // Number of brick columns
	float padding = 5.0f; // Space between bricks
	
	// Calculate brick size and initial position
	float brickWidth = brC.SR * 2.0f;
	float brickHeight = brC.SR;
	float startX = padding + brickWidth / 2.0f;
	float startY = padding + brickHeight / 2.0f;

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			auto entity = m_entityManager.addEntity("brick");

			// Set brick position based on row and column indices
			float X = startX + col * (brickWidth + padding);
			float Y = startY + row * (brickHeight + padding);

			entity->cTransform = std::make_shared<CTransform>(
				glm::vec2(X, Y), glm::vec2(0.0f, 0.0f), 0.0f);

			// Adding Shape with fill and outline colors
			sf::Color fillColor(brC.FR, brC.FG, brC.FB);
			sf::Color outlineColor(brC.OR, brC.OG, brC.OB);
			entity->cShape = std::make_shared<CShape>(brickWidth, brickHeight, fillColor, outlineColor, brC.OT);
			entity->cScore= std::make_shared<CScore>( UNIT_SCORE);
			// Enable collisions
			entity->cCollision = std::make_shared<CCollision>(brC.CR);
			entity->cLifespan= std::make_shared<CLifespan>(3);
		}
	}
}

void Game::sMovement()
{
	m_paddle->cTransform->velocity = { 0.0f, 0.0f };

	
     if (m_paddle->cInput->left) {
		m_paddle->cTransform->velocity.x = -m_paddleConfig.S;//Decrease x
	}
	else if (m_paddle->cInput->right) {
		 m_paddle->cTransform->velocity.x = m_paddleConfig.S;//Increase x
	}

	 for (const auto e : m_entityManager.getEntities()) {
		 e->cTransform->position += e->cTransform->velocity;
	 }
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_running = false;
			return;
		}
		// Keyboard events
		if (event.type == sf::Event::KeyPressed) {
			// Player movement
			switch (event.key.code) {
			case sf::Keyboard::A:
				m_paddle->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_paddle->cInput->right = true;
				break;
				// Exit game
			case sf::Keyboard::Q:
				m_running = false;
				break;
				// Pause game
			case sf::Keyboard::Escape:
				m_paused = !m_paused;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				// Player movement
			case sf::Keyboard::A:
				m_paddle->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_paddle->cInput->right = false;
				break;
			default:
				break;
			}
		}
	}
}

void Game::sCollision()
{
	auto& paddlePos = m_paddle->cTransform->position;
	const auto paddleSize = std::get<sf::RectangleShape>(m_paddle->cShape->shape).getSize();
	const auto winSize = m_window.getSize();

	// Constrain paddle within window bounds
	paddlePos.x = std::clamp(paddlePos.x, paddleSize.x / 2.0f, winSize.x - paddleSize.x / 2.0f);

	auto& ballPos = m_ball->cTransform->position;
	auto& ballVel = m_ball->cTransform->velocity;
	auto& ballAngle = m_ball->cTransform->angle;
	const float ballRadius = m_ball->cCollision->collisionRadius;

	// Helper lambda for ball-wall collision
	auto reflectHorizontally = [&]() {
		ballVel.x = -ballVel.x;
		ballAngle = 180.0f - ballAngle;
		};
	auto reflectVertically = [&]() {
		ballVel.y = -ballVel.y;
		ballAngle = -ballAngle;
		};

	// Ball bounds check with screen edges
	if (ballPos.x - ballRadius < 0) {
		ballPos.x = ballRadius;
		reflectHorizontally();
	}
	else if (ballPos.x + ballRadius > winSize.x) {
		ballPos.x = winSize.x - ballRadius;
		reflectHorizontally();
	}

	// Paddle collision
	if (ballPos.y + ballRadius >= paddlePos.y - paddleSize.y / 2 &&
		ballPos.x >= paddlePos.x - paddleSize.x / 2 &&
		ballPos.x <= paddlePos.x + paddleSize.x / 2)
	{
		ballPos.y = paddlePos.y - paddleSize.y / 2 - ballRadius;
		reflectVertically();
	}

	// Brick collisions
	for (const auto& brick : m_entityManager.getEntities("brick")) {
		const auto& brickPos = brick->cTransform->position;
		const auto brickSize = std::get<sf::RectangleShape>(brick->cShape->shape).getSize();

		// Check ball-brick overlap
		if (ballPos.y - ballRadius <= brickPos.y + brickSize.y / 2 &&
			ballPos.y + ballRadius >= brickPos.y - brickSize.y / 2 &&
			ballPos.x >= brickPos.x - brickSize.x / 2 &&
			ballPos.x <= brickPos.x + brickSize.x / 2)
		{
			reflectVertically();

			brick->cLifespan->remaining -= 1; // Decrease lifespan

			// Update color based on remaining lifespan
			if (brick->cLifespan->remaining == 2) {
				std::get<sf::RectangleShape>(brick->cShape->shape).setFillColor(sf::Color(255, 105, 180)); // Pink
			}
			else if (brick->cLifespan->remaining == 1) {
				std::get<sf::RectangleShape>(brick->cShape->shape).setFillColor(sf::Color(255, 255, 0)); // Yellow
			}
			else if (brick->cLifespan->remaining <= 0) {
				brick->destroy(); // Destroy brick when lifespan is zero
			}

			m_score += brick->cScore->score;
			// Adjust position outside the brick
			ballPos.y = (ballPos.y < brickPos.y) ?
				(brickPos.y - brickSize.y / 2 - ballRadius) :
				(brickPos.y + brickSize.y / 2 + ballRadius);
		}
	}
}


void Game::sRender()
{
	m_window.clear();

	for (const auto& e : m_entityManager.getEntities()) {
		// Set position based on entity's transform
		if (std::holds_alternative<sf::CircleShape>(e->cShape->shape)) {
			auto& circle = std::get<sf::CircleShape>(e->cShape->shape);
			circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);

			// Handle lifespan opacity for CircleShape
			if (e->cLifespan) {
				int opacity = 255 * e->cLifespan->remaining / e->cLifespan->total;

				// Set fill and outline color with opacity
				const sf::Color& currFill = circle.getFillColor();
				circle.setFillColor(sf::Color(currFill.r, currFill.g, currFill.b, opacity));

				const sf::Color& currOutline = circle.getOutlineColor();
				circle.setOutlineColor(sf::Color(currOutline.r, currOutline.g, currOutline.b, opacity));
			}

			// Draw the circle
			m_window.draw(circle);
		}
		else if (std::holds_alternative<sf::RectangleShape>(e->cShape->shape)) {
			auto& rectangle = std::get<sf::RectangleShape>(e->cShape->shape);
			rectangle.setPosition(e->cTransform->position.x, e->cTransform->position.y);

			// Handle lifespan opacity for RectangleShape
			if (e->cLifespan) {
				int opacity = 255 * e->cLifespan->remaining / e->cLifespan->total;

				// Set fill and outline color with opacity
				const sf::Color& currFill = rectangle.getFillColor();
				rectangle.setFillColor(sf::Color(currFill.r, currFill.g, currFill.b, opacity));

				const sf::Color& currOutline = rectangle.getOutlineColor();
				rectangle.setOutlineColor(sf::Color(currOutline.r, currOutline.g, currOutline.b, opacity));
			}

			// Draw the rectangle
			m_window.draw(rectangle);
		}
	}

	// Render score
	std::string scoreStr = "Score: " + std::to_string(m_score);
	m_text.setString(scoreStr);
	m_window.draw(m_text);

	// When paused, show instructions and game controls in middle of the screen
	if (m_paused) {
		std::string controlsStr =
			"Press A to move Left\nPress D to move Right\nPress ESC to Play/Pause\nPress Q to Exit\nClick LEFT MOUSE BUTTON to shoot bullet\nClick RIGHT MOUSE BUTTON to use special weapon";
		auto controlsText = sf::Text(controlsStr, m_font,
			m_text.getCharacterSize());

		// Centering the text
		sf::FloatRect textRect = controlsText.getLocalBounds();
		controlsText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		const auto& winWidth = m_window.getSize().x;
		const auto& winHeight = m_window.getSize().y;
		controlsText.setPosition(winWidth / 2.0f, winHeight / 2.0f);

		m_window.draw(controlsText);
	}

	m_window.display();
}


void Game::run()
{
	while (m_window.isOpen()) {
		if (!m_running) {
			m_window.close();
			return;
		}

		// If not paused, run these systems
		if (!m_paused) {
			m_entityManager.update();

			this->sMovement();
			this->sCollision();
			//this->sLifespan();
		}

		this->sUserInput();
		m_entityManager.update();

		this->sRender();

		m_currentFrame++;
	}
}