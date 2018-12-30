#pragma once

#include "structs.h"

using namespace PhysX;
using namespace Binding;

class Entity {

	Mat4 transformation;
	RigidBody* const body;

public:

	Entity(RigidBody* const body) : body(body) {};
	~Entity() { delete body; };

	void setPosition(const Vec2& value) { body->position = value; };
	void setDirection(const Vec2& value) { body->direction = value; };
	void setMovement(const Vec2& value) { body->movement = value; };
	void setAcceleration(const float value) { body->acceleration = value; };
	void setVMax(const float value) { body->vmax = value; };
	//void setCollision(const Collision value) { collision = value; };
	void setTransformation(const Mat4& value) { this->transformation = value; };

	Vec2 getPosition() const { return body->position; };
	Vec2 getDirection() const { return body->direction; };
	Vec2 getMovement() const { return body->movement; };
	float getAcceleration() const { return body->acceleration; };
	float getVMax() const { return body->vmax; };
	//Collision getCollision() { return collision; };
	//bool hasCollision() const { return collision.entity != nullptr; };
	Mat4 getTransformation() const { return transformation; };


	/*
		Implement this method for defining, if this entity can collide with
		other entities. This can be used to skip collision detections on non-collidable
		entities.
		@returns	true, if this entity can collide whith other entities. In this case
					a collision detection gets performed between this specific entity
					and all other existing entities.
					false, otherwise. In this case, the collision detection gets
					skipped completely for this specific entity.
	*/
	virtual bool canCollide() const = 0;


	/*
		Implement this method to decide, whether this entity can actually collide
		with the given entity e, or not. In contrast to method canCollide(),
		this method only affects on single collision detection.
		@param		e specifies the entity to check against.
		@returns	true, if this entity can collide with entity e. In this
					case a collision detection gets performed between them.
					false, otherwise. In this case, the collision detection gets
					skipped for these two entites.
	*/
	virtual bool canCollideWith(const Entity* const e) const = 0;


	/*
		Use this method to recalculate the transformation matrix of this entity
		for the current frame.
	*/
	virtual void updateTransformation() = 0;


	/*
		In order to perform a collision detection on an entity, the vertex data
		of an entity is required.
	*/
	virtual VertexData getVertexData() const = 0;


	/*
		The collision detection is based on point-in-traingle-detection. Therefore,
		the model of an entity has to be triangulated. The indices specifing the
		tringales are required and have to be returned by this method.
	*/
	virtual IndexData getTriangulatedIndexData() const = 0;
};