//#pragma once
//
//enum movement_states {
//	IDLE = 0,
//	MOVING,
//	MOVING_LEFT,
//	MOVING_RIGHT,
//	MOVING_UP,
//	MOVING_DOWN
//};
//
//class MovementComponent
//{
//private:
//	sf::Sprite& sprite;
//	sf::Vector2f velocity;
//	float maxVelocity;
//	float acceleration;
//	float deceleration;
//
//
//	float dirX;
//	float dirY;
//	sf::Vector2f direction;
//
//public:
//	MovementComponent(sf::Sprite& sprite,
//		float maxVelocity,
//		float acceleration,
//		float deceleration);
//	virtual ~MovementComponent();
//
//	//accesors
//	const sf::Vector2f& getVelocity() const;
//	const float& getMaxVelocity() const;
//
//	//modifiers
//	void addVelocity(const float distance, const sf::Vector2f& direction);
//
//	//functions
//	const bool getState(const short unsigned state) const;
//	//odrzut po uderzeniu
//	void intertiaPush(const sf::Vector2f push_direction, float push_force, const float& dt);
//	//set velocity to 0, used in collision
//	void stopVelocity();
//	void stopVelocityX();
//	void stopVelocityY();
//	//move the sprite
//	void move(const float x, const float y, const float& dt);
//	void move(const sf::Vector2f direction, const float& dt);
//	void move(const float speed_modifier, const sf::Vector2f direction, const float& dt);
//	void update(const float& dt);
//	//set movement direction in radians
//	void setRadianDir(const float degrees);
//	void updateInSetDir(const float& dt);
//};
//
