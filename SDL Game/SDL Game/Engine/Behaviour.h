#pragma once

class BehavioursManager;
class GameObject;


class Behaviour
{
public:
	friend class BehavioursManager;
	friend class GameObject;

	virtual ~Behaviour();

	GameObject * gameObject();
	virtual void start() = 0;
	virtual void update() = 0;

protected:
	Behaviour();

private:
	GameObject * m_gameObject;
	bool m_started;
};
