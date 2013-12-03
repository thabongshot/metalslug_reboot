#include "physicsManager2d.h"

PhysicsManager2D *PhysicsManager2D::pInstance;

class ContactListener : public b2ContactListener
{
public:
	ContactListener();

	virtual void BeginContact(b2Contact *contact);

	virtual void EndContact(b2Contact *contact);

	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

ContactListener *contactListener;

PhysicsManager2D::PhysicsManager2D()
{
	pWorld = new b2World(b2Vec2(0.0f, -9.8f));

	contactListener = new ContactListener();
	pWorld->SetContactListener(contactListener);
}

PhysicsManager2D *PhysicsManager2D::getInstance()
{
	if(!pInstance)
	{
		pInstance = new PhysicsManager2D();
	}

	return pInstance;
}

b2Body *PhysicsManager2D::createRectangleBody(b2BodyType bodyType, float x, float y, float width, float height, float originX, float originY, float angle)
{
	b2Body *body;
	b2BodyDef *bodyDef;
	b2FixtureDef *fixtureDef;
	b2PolygonShape *boxshape;

	boxshape = new b2PolygonShape();
	boxshape->SetAsBox(width / 2, height / 2, b2Vec2(originX, originY), angle);

	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = boxshape;
	fixtureDef->density = 1;

	bodyDef = new b2BodyDef();
	bodyDef->type = bodyType;
	bodyDef->angularDamping = 0;

	body = pWorld->CreateBody(bodyDef);
	body->CreateFixture(fixtureDef);

	body->SetTransform(b2Vec2(x, y), angle);

	return body;
}

void PhysicsManager2D::update(float delta)
{
	pWorld->Step(delta, 8, 5);
}

ContactListener::ContactListener() : b2ContactListener()
{

}

void ContactListener::BeginContact(b2Contact *contact)
{
	
}

void ContactListener::EndContact(b2Contact *contact)
{

}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

}