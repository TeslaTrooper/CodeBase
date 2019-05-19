#ifndef GAME_WORLD
#define GAME_WORLD

#include <vector>
#include "Entity.h"

#define WORLD_TYPE_BORDER	0	
#define WORLD_TYPE_LOOP		1

class GameWorld {

	const int width, height, type;

	void stopOnOutOfBounds(const vector<Entity*>& entities) const {
		for (Entity* e : entities) {
			Vec2 position = e->getPosition();
			Vec2 bbox = e->getBbox();

			if (position.x < 0) {
				e->setMovement(Vec2(0, e->getMovement().y));
				e->setPosition(Vec2(1, e->getPosition().y));
			}

			if (position.x + bbox.x > width) {
				e->setMovement(Vec2(0, e->getMovement().y));
				e->setPosition(Vec2(width - bbox.x, e->getPosition().y));
			}

			if (position.y < 0) {
				e->setMovement(Vec2(e->getMovement().x, 0));
				e->setPosition(Vec2(e->getPosition().x, 1));
			}

			if (position.y + bbox.y > height) {
				e->setMovement(Vec2(e->getMovement().x, 0));
				e->setPosition(Vec2(e->getPosition().x, height - bbox.y));
			}
		}
	}

	void loopOnOutOfBounds(const vector<Entity*>& entities) const {
		for (Entity* e : entities) {
			Vec2 cPos = e->getPosition();
			// Take width as crop box for repositioning
			Vec2 entityBbox = e->getBbox();

			int x = (int) ((int) (width + cPos.x) % (int) width);
			int y = (int) ((int) (height + cPos.y) % (int) height);

			// It works, but it would be better, if we can get rid of these if-conditions
			// and replace it with some calculations

			// Update correspondig value, only if necessary
			if (cPos.x > width)
				e->setPosition(Vec2((float) (x - entityBbox.x), cPos.y));
			if (cPos.x < -entityBbox.x)
				e->setPosition(Vec2((float) (x + entityBbox.x), cPos.y));

			cPos = e->getPosition();

			if (cPos.y > height)
				e->setPosition(Vec2(cPos.x, (float) (y - entityBbox.y)));
			if (cPos.y < -entityBbox.y)
				e->setPosition(Vec2(cPos.x, (float) (y + entityBbox.y)));
		}
	}

public:

	GameWorld(int width, int height, int type) : type(type), width(width), height(height) {}

	void update(const float dt, const vector<Entity*>& entities) const {
		if (type == WORLD_TYPE_BORDER)
			stopOnOutOfBounds(entities);

		if (type == WORLD_TYPE_LOOP)
			loopOnOutOfBounds(entities);
	}

};

#endif GAME_WORLD