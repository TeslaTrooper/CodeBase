#ifndef ENTITY
#define ENTITY

#include "structs.h"

using namespace PhysX;
using namespace Binding;

class Entity {

	BodyDefinition* const bodyDef;
	FixtureDefinition* const fixtureDef;

public:

	Entity() : Entity(BodyType::DYNAMIC) {};
	Entity(const BodyType& bodyType) : bodyDef(new BodyDefinition(bodyType)), fixtureDef(new FixtureDefinition()) {};
	~Entity() { delete bodyDef; delete fixtureDef; };

	void setPosition(const Vec2& value) { bodyDef->position = value; };
	void setDirection(const Vec2& value) { bodyDef->direction = value; };
	void setMovement(const Vec2& value) { bodyDef->movement = value; };
	void setBbox(const Vec2& value) { bodyDef->bbox = value; };
	virtual void setAcceleration(const float value) { bodyDef->acceleration = value; };
	void setVMax(const float value) { bodyDef->vmax = value; };
	void setTransformation(const Mat4& value) { fixtureDef->transformation = value; };

	Vec2 getPosition() const { return bodyDef->position; };
	Vec2 getDirection() const { return bodyDef->direction; };
	Vec2 getMovement() const { return bodyDef->movement; };
	Vec2 getBbox() const { return bodyDef->bbox; };
	float getAcceleration() const { return bodyDef->acceleration; };
	float getVMax() const { return bodyDef->vmax; };
	Mat4 getTransformation() const { return fixtureDef->transformation; };


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

#endif ENTITY