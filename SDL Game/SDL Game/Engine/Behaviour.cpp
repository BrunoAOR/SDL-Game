#include "Behaviour.h"


Behaviour::Behaviour()
{
	m_gameObject = nullptr;
	m_started = false;
}


Behaviour::~Behaviour()
{

}


GameObject * Behaviour::gameObject()
{
	return m_gameObject;
}
