#include "stdafx.h"
#include "CppUnitTest.h"

// 16ms for 60 FPS
#define SIMULATION_RESOLUTION 0.016f
// Duration in ms (10s)
#define SIMULATION_DURATION 10000
#define SIMULATION_STEPS SIMULATION_DURATION / (SIMULATION_RESOLUTION * 1000)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeBaseTest {

	class Mock : public CollisionCallback {

	public:

		void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override {
			e1->setAcceleration(1);
			e2->setAcceleration(1);

			Logger::WriteMessage("Collision!");
		}

	};

	class CombinedCollisionResolver : public CollisionCallback {

	public:

		void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override {
			Vec2 p1 = e1->getPosition();

			if (p1.y > 0) {
				Vec2 v = e1->getMovement();
				e2->setMovement(v);
			} else {
				Vec2 v = e2->getMovement();
				e1->setMovement(v);
			}
		}
	};

	static PhysicsEngine* engine;
	static Mock* mock;
	static vector<Entity*> entities;

	TEST_MODULE_INITIALIZE(init) {
		mock = new Mock();
		engine = new PhysicsEngine(mock);

		Logger::WriteMessage("Testing...");
	}

	TEST_MODULE_CLEANUP(cleanup) {
		delete mock;
		delete engine;

		Logger::WriteMessage("Finalizing...");
	}

	TEST_CLASS(CollisionTest) {

		void assert(const vector<Entity*>& entities, int expected) {
			for each (Entity* e in entities) {
				Assert::AreEqual(expected, (int) e->getAcceleration());
			}
		}

		void assertCollision(const vector<Entity*>& entities) {
			assert(entities, 1);
		}

		void assertNoCollision(const vector<Entity*>& entities) {
			assert(entities, 0);
		}

		TEST_METHOD(SimpleSquaresCollision) {
			entities.push_back(Sqaure::create(Vec2(), 5));
			entities.push_back(Sqaure::create(Vec2(4, 0), 5));

			engine->update(entities, 0);
			assertCollision(entities);
		}

		TEST_METHOD(ConvexCollision) {
			entities.push_back(Convex::create(Vec2(), 1));
			entities.push_back(Convex::create(Vec2(2.4f, 0), 1));

			engine->update(entities, 0);
			assertCollision(entities);
		}

		TEST_METHOD(ConvexCollision2) {
			entities.push_back(Convex::create(Vec2(0, 0), 1));
			entities.push_back(Convex::create(Vec2(2.4f, 1), 1));

			engine->update(entities, 0);
			assertNoCollision(entities);
		}

		TEST_METHOD(ConcaveCollision) {
			entities.push_back(Concave::create(Vec2(0, 0), 1));
			entities.push_back(TriangleData::create(Vec2(0.6f, 0), 1));

			engine->update(entities, 0);
			assertNoCollision(entities);
		}

		TEST_METHOD(ConcaveCollision2) {
			entities.push_back(Concave::create(Vec2(0, 0), 1));
			entities.push_back(TriangleData::create(Vec2(0.6f, 1), 1));

			engine->update(entities, 0);
			assertCollision(entities);
		}

		TEST_METHOD_CLEANUP(cleanTestMethod) {
			entities.clear();
		}

	};

	TEST_CLASS(MovementTest) {

		void simulate() {
			for (int i = 0; i < SIMULATION_STEPS; i++) {
				engine->update(entities, SIMULATION_RESOLUTION);
			}
		}

		TEST_METHOD(StaticMovement) {
			Entity* e = Sqaure::create(Vec2(), 1);
			e->setMovement(Vec2(5, 0));
			e->setVMax(e->getMovement().length());
			e->setAcceleration(5);
			e->setDirection(Vec2(1, 0));
			entities.push_back(e);

			simulate();
			Assert::AreEqual(SIMULATION_STEPS * e->getMovement().length(), e->getPosition().x);
			Assert::AreEqual(5.f, e->getMovement().length());
		}

		TEST_METHOD(Acceleration) {
			Entity* e = Sqaure::create(Vec2(), 1);
			e->setAcceleration(1);
			e->setDirection(Vec2(1, 0));
			entities.push_back(e);

			simulate();
			Assert::IsTrue(e->getMovement().length() < 2);
		}

		TEST_METHOD(AccelerationWithVMax) {
			Entity* e = Sqaure::create(Vec2(), 1);
			e->setAcceleration(10);
			e->setDirection(Vec2(1, 0));
			e->setVMax(5);
			entities.push_back(e);

			simulate();
			Assert::IsTrue(e->getMovement().length() == 5);
		}

		TEST_METHOD(MovementWithAcceleration) {
			Entity* e = Sqaure::create(Vec2(), 1);
			e->setAcceleration(1);
			e->setDirection(Vec2(-1, 0));
			e->setMovement(Vec2(5, 0));
			e->setVMax(e->getMovement().length());
			entities.push_back(e);

			simulate();
			Assert::IsTrue(e->getMovement().x < -1);
		}

		TEST_METHOD_CLEANUP(cleanTestMethod) {
			entities.clear();
		}

	};
}