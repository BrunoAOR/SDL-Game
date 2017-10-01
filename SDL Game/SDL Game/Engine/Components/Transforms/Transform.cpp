#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Engine/constants.h"
#include "Engine/EngineUtils.h"
#include "Engine/Components/ComponentType.h"


Transform::Transform()
	: m_localPosition(Vector2(0,0))
	, m_localRotation(0)
	, m_localScale(Vector2(1,1))
	, m_worldPosition(Vector2(0, 0))
	, m_worldRotation(0)
	, m_worldScale(Vector2(1, 1))
	, m_parentTransform(nullptr)
{
	type = ComponentType::Transform;
}


Vector2 Transform::getLocalPosition() const
{
	return m_localPosition;
}


Vector2 Transform::getWorldPosition() const
{
	return m_worldPosition;
}


void Transform::setLocalPosition(const Vector2& position)
{
	m_localPosition = position;

	m_worldPosition = localToWorldPosition(position);

	updateChildrenWorldFields();
}


void Transform::setWorldPosition(const Vector2& position)
{
	m_worldPosition = position;

	if (m_parentTransform == nullptr)
	{
		m_localPosition = position;
	}
	else
	{
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		if (parentWorldScale.x == 0 || parentWorldScale.y == 0)
		{
			return;
		}

		m_localPosition = worldToLocalPosition(position);
	}

	updateChildrenWorldFields();
}


double Transform::getLocalRotation() const
{
	return m_localRotation;
}


double Transform::getWorldRotation() const
{
	return m_worldRotation;
}


void Transform::setLocalRotation(double rotation)
{
	// Set Local Rotation
	// Clamp between 0 and 360
	m_localRotation = rotation - 360 * (int)(rotation / 360);
	// Set World Rotation
	m_worldRotation = localToWorldRotation(rotation);

	updateChildrenWorldFields();
}


void Transform::setWorldRotation(double rotation)
{
	// Set World Rotation
	// Clamp between 0 and 360
	m_worldRotation = rotation - 360 * (int)(rotation / 360);
	// Set Local Rotation
	m_localRotation = worldToLocalRotation(rotation);

	updateChildrenWorldFields();
}


Vector2 Transform::getLocalScale() const
{
	return m_localScale;
}


Vector2 Transform::getWorldScale() const
{
	return m_worldScale;
}


void Transform::setLocalScale(const Vector2& scale)
{
	m_localScale = scale;

	m_worldScale = localToWorldScale(scale);

	updateChildrenWorldFields();
}


void Transform::setWorldScale(const Vector2& scale)
{
	m_worldScale = scale;

	m_localScale = worldToLocalScale(scale);

	updateChildrenWorldFields();
}


Vector2 Transform::localToWorldPosition(const Vector2 & localPosition) const
{
	if (m_parentTransform == nullptr)
	{
		return localPosition;
	}
	else
	{
		Vector2 worldPosition;
		//	1. Solve the rotation
		//		1.1 Get polar coordinates for localPosition (r and theta)
		double r = sqrt(localPosition.x * localPosition.x + localPosition.y * localPosition.y);
		double theta = atan2(localPosition.y, localPosition.x);

		//		1.2 use the polar coordinate to recalculate the x and y coordinates
		double parentWorldRotation = m_parentTransform->getWorldRotation();
		worldPosition.x = r * cos(theta + M_PI / 180 * parentWorldRotation);
		worldPosition.y = r * sin(theta + M_PI / 180 * parentWorldRotation);

		//	2. Solve the scale
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		worldPosition.x *= parentWorldScale.x;
		worldPosition.y *= parentWorldScale.y;

		//	3. Solve the position
		Vector2 parentWorldPosition = m_parentTransform->getWorldPosition();
		worldPosition.x += parentWorldPosition.x;
		worldPosition.y += parentWorldPosition.y;

		return (worldPosition);
	}
}


Vector2 Transform::worldToLocalPosition(const Vector2 & worldPosition) const
{
	if (m_parentTransform == nullptr)
	{
		return worldPosition;
	}
	else
	{
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		if (parentWorldScale.x == 0 || parentWorldScale.y == 0)
		{
			return worldPosition;
		}
		
		Vector2 localPosition = Vector2();

		//	1. Solve position
		Vector2 parentWorldPosition = m_parentTransform->getWorldPosition();
		localPosition.x = worldPosition.x - parentWorldPosition.x;
		localPosition.y = worldPosition.y - parentWorldPosition.y;

		//	2. Solve scale
		localPosition.x /= parentWorldScale.x;
		localPosition.y /= parentWorldScale.y;

		//	3. Solve rotation
		//		3.1 Get polar coordinates for the current localPosition (r and theta)
		double r = sqrt(localPosition.x * localPosition.x + localPosition.y * localPosition.y);
		double theta = atan2(localPosition.y, localPosition.x);

		//		3.2 use the polar coordinate to recalculate the x and y coordinates
		double parentWorldRotation = m_parentTransform->getWorldRotation();
		localPosition.x = r * cos(theta - M_PI / 180 * parentWorldRotation);
		localPosition.y = r * sin(theta - M_PI / 180 * parentWorldRotation);

		return localPosition;
	}
}


double Transform::localToWorldRotation(double localRotation) const
{
	double worldRotation = localRotation;
	if (m_parentTransform != nullptr)
	{
		// For rotation, one only needs to add the parent rotation
		worldRotation += m_parentTransform->getWorldRotation();
	}
	// Clamp between 0 and 360
	worldRotation -= 360 * (int)(worldRotation / 360);
	return (worldRotation);
}


double Transform::worldToLocalRotation(double worldRotation) const
{
	if (m_parentTransform == nullptr)
	{
		return worldRotation;
	}
	else
	{
		double localRotation = worldRotation - m_parentTransform->getWorldRotation();
		localRotation -= 360 * (int)(localRotation / 360);
		return localRotation;
	}
}


Vector2 Transform::localToWorldScale(const Vector2 & localScale) const
{
	if (m_parentTransform == nullptr)
	{
		return localScale;
	}
	else
	{
		Vector2 worldScale;
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		worldScale.x = localScale.x * parentWorldScale.x;
		worldScale.y = localScale.y * parentWorldScale.y;
		// For scale, one only needs to multiply the parent scale
		return (worldScale);
	}
}


Vector2 Transform::worldToLocalScale(const Vector2 & worldScale) const
{
	if (m_parentTransform == nullptr)
	{
		return worldScale;
	}
	else
	{
		Vector2 localScale;
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		if (parentWorldScale.x != 0)
		{
			localScale.x = worldScale.x / parentWorldScale.x;
		}
		if (parentWorldScale.y != 0)
		{
			localScale.y = worldScale.y / parentWorldScale.y;
		}
		return localScale;
	}
}


std::weak_ptr<Transform> Transform::getParent()
{
	return m_parentWeakPtr;
}


bool Transform::setParent(std::weak_ptr<Transform> parent)
{
	if (parent.expired())
	{
		removeParent();
	}

	Transform* parentTransform = parent.lock().get();
	// So, if we try to set the current parent as new parent, nothing needs to be done.
	if (m_parentTransform == parentTransform)
	{
		return true;
	}

	// If the parent is a child of this transform, we return false
	if (isTransformInChildrenHierarchy(parentTransform))
	{
		return false;
	}

	// Now, we remove the parent (which in turn removes this transform from the m_parent's children list)
	if (m_parentTransform != nullptr)
	{
		m_parentTransform->removeChild(this);
		m_parentTransform = nullptr;
	}
	// Add this transform to the parentTransform's children
	if (parentTransform->addChild(this))
	{
		// And then set the m_parent variable
		m_parentTransform = parentTransform;
		m_parentWeakPtr = parent;
		updateLocalFields();
		return true;
	}
	else
	{
		updateLocalFields();
		return false;
	}

}


void Transform::removeParent()
{
	if (m_parentTransform != nullptr)
	{
		m_parentTransform->removeChild(this);
		m_parentTransform = nullptr;
		m_parentWeakPtr.reset();
	}
	updateLocalFields();
}


bool Transform::addChild(Transform * childTransform)
{
	int index = EngineUtils::indexOf(m_children, childTransform);
	if (index == -1)
	{
		m_children.push_back(childTransform);
		return true;
	}
	return false;
}


bool Transform::removeChild(Transform * childTransform)
{
	int index = EngineUtils::indexOf(m_children, childTransform);
	if (index != -1)
	{
		m_children.erase(m_children.begin() + index);
		return true;
	}
	return false;
}


bool Transform::isTransformInChildrenHierarchy(Transform* transform)
{
	for (auto childTransform : m_children)
	{
		if (childTransform == transform)
		{
			return true;
		}
		return(childTransform->isTransformInChildrenHierarchy(transform));
	}
	return false;
}


void Transform::updateLocalFields()
{
	m_localPosition = worldToLocalPosition(m_worldPosition);
	m_localRotation = worldToLocalRotation(m_worldRotation);
	m_localScale = worldToLocalScale(m_worldScale);
}


void Transform::updateWorldFields()
{
	m_worldPosition = localToWorldPosition(m_localPosition);
	m_worldRotation = localToWorldRotation(m_localRotation); 
	m_worldScale = localToWorldScale(m_localScale);
}


void Transform::updateChildrenLocalFields()
{
	for (Transform* childTransform : m_children)
	{
		childTransform->updateLocalFields();
		childTransform->updateChildrenLocalFields();
	}
}


void Transform::updateChildrenWorldFields()
{
	for (Transform* childTransform : m_children)
	{
		childTransform->updateWorldFields();
		childTransform->updateChildrenWorldFields();
	}
}
