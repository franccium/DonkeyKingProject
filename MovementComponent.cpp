//#include "MovementComponent.h"
//#include "stdafx.h"
//
////constr/destr
//MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,
//	float acceleration, float deceleration)
//	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
//{
//
//}
//
//MovementComponent::~MovementComponent()
//{
//
//}
//
//
////accessors
//
//const sf::Vector2f& MovementComponent::getVelocity() const
//{
//	return this->velocity;
//}
//
//const float& MovementComponent::getMaxVelocity() const
//{
//	return this->maxVelocity;
//}
//
//void MovementComponent::addVelocity(const float modifier, const sf::Vector2f& direction)
//{
//	std::cout << "modified dodge\n";
//
//	/*this->sprite.setPosition(this->sprite.getPosition().x + velocity.x / modifier,
//		this->sprite.getPosition().y + velocity.y / modifier);*/
//
//	this->sprite.setPosition(this->sprite.getPosition().x + velocity.x / modifier,
//		this->sprite.getPosition().y + velocity.y / modifier);
//}
//
//
////functions
//
//const bool MovementComponent::getState(const short unsigned state) const
//{
//	switch (state)
//	{
//	case IDLE:
//		if (this->velocity.x == 0.f && this->velocity.y == 0.f) return true;
//		break;
//	case MOVING:
//		if (this->velocity.x != 0.f || this->velocity.y != 0.f) return true;
//		break;
//	case MOVING_LEFT:
//		if (this->velocity.x < 0.f) return true;
//		break;
//	case MOVING_RIGHT:
//		if (this->velocity.x > 0.f) return true;
//		break;
//	case MOVING_UP:
//		if (this->velocity.y < 0.f) return true;
//		break;
//	case MOVING_DOWN:
//		if (this->velocity.y > 0.f) return true;
//		break;
//	}
//	return false;
//}
//
//void MovementComponent::stopVelocity()
//{
//	this->velocity.x = 0.f;
//	this->velocity.y = 0.f;
//}
//
//void MovementComponent::stopVelocityX()
//{
//	this->velocity.x = 0.f;
//}
//
//void MovementComponent::stopVelocityY()
//{
//	this->velocity.y = 0.f;
//}
//
//void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
//{
//	//accelerate
//	this->velocity.x += this->acceleration * dir_x * dt;
//	this->velocity.y += this->acceleration * dir_y * dt;
//}
//
//void MovementComponent::move(const sf::Vector2f direction, const float& dt)
//{
//	//accelerate
//	this->velocity.x += this->acceleration * direction.x * dt;
//	this->velocity.y += this->acceleration * direction.y * dt;
//}
//
//void MovementComponent::move(const float speed_modifier, const sf::Vector2f direction, const float& dt)
//{
//	this->velocity.x += this->acceleration * direction.x * dt * speed_modifier * 200000.f;
//	this->velocity.y += this->acceleration * direction.y * dt * speed_modifier * 200000.f;
//}
//
//void MovementComponent::update(const float& dt)
//{
//	//decelerate
//	if (this->velocity.x > 0.f) {
//		//max vel check right
//		if (this->velocity.x > this->maxVelocity)
//			this->velocity.x = this->maxVelocity;
//		//decelerate right
//		this->velocity.x -= deceleration * dt;
//		if (this->velocity.x < 0.f) this->velocity.x = 0.f;
//	}
//	else if (this->velocity.x < 0.f) {
//		//max vel check left
//		if (this->velocity.x < -this->maxVelocity)
//			this->velocity.x = -this->maxVelocity;
//		//decelerate left
//		this->velocity.x += deceleration * dt;
//		if (this->velocity.x > 0.f) this->velocity.x = 0.f;
//	}
//
//	if (this->velocity.y > 0.f) {
//		//max vel check down
//		if (this->velocity.y > this->maxVelocity)
//			this->velocity.y = this->maxVelocity;
//		//decelerate down
//		this->velocity.y -= deceleration * dt;
//		if (this->velocity.y < 0.f) this->velocity.x = 0.f;
//	}
//	else if (this->velocity.y < 0.f) {
//		//max vel check up
//		if (this->velocity.y < -this->maxVelocity)
//			this->velocity.y = -this->maxVelocity;
//		//decelerate up
//		this->velocity.y += deceleration * dt;
//		if (this->velocity.y > 0.f) this->velocity.y = 0.f;
//	}
//	//move after velocity calculation
//	this->sprite.move(this->velocity * dt);
//}
//
//void MovementComponent::setRadianDir(const float degrees)
//{
//	float radians = degrees * static_cast<float>(M_PI) / 180.f;
//	this->direction.x = -std::cos(radians);
//	this->direction.y = -std::sin(radians);
//}
//
////odrzut po uderzeniu
//void MovementComponent::intertiaPush(const sf::Vector2f push_direction, float push_force, const float& dt)
//{
//	this->velocity -= push_force * push_direction;
//}
//
//void MovementComponent::updateInSetDir(const float& dt)
//{
//	this->move(direction, dt);
//	//decelerate
//	if (this->velocity.x > 0.f) {
//		//max vel check right
//		if (this->velocity.x > this->maxVelocity)
//			this->velocity.x = this->maxVelocity;
//		//decelerate right
//		this->velocity.x -= deceleration * dt;
//		if (this->velocity.x < 0.f) this->velocity.x = 0.f;
//	}
//	else if (this->velocity.x < 0.f) {
//		//max vel check left
//		if (this->velocity.x < -this->maxVelocity)
//			this->velocity.x = -this->maxVelocity;
//		//decelerate left
//		this->velocity.x += deceleration * dt;
//		if (this->velocity.x > 0.f) this->velocity.x = 0.f;
//	}
//
//	if (this->velocity.y > 0.f) {
//		//max vel check down
//		if (this->velocity.y > this->maxVelocity)
//			this->velocity.y = this->maxVelocity;
//		//decelerate down
//		this->velocity.y -= deceleration * dt;
//		if (this->velocity.y < 0.f) this->velocity.x = 0.f;
//	}
//	else if (this->velocity.y < 0.f) {
//		//max vel check up
//		if (this->velocity.y < -this->maxVelocity)
//			this->velocity.y = -this->maxVelocity;
//		//decelerate up
//		this->velocity.y += deceleration * dt;
//		if (this->velocity.y > 0.f) this->velocity.y = 0.f;
//	}
//	//move after velocity calculation
//	this->sprite.move(this->velocity * dt);
//}
