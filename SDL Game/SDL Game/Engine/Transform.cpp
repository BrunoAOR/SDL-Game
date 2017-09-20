#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "constants.h"


Transform::Transform()
{
	m_localPosition = Vector2(0, 0);
	m_localRotation = 0;
	m_localScale = Vector2(1, 1);
	
	m_positionPivot = Vector2(0.5, 0.5);
	m_rotationPivot = Vector2(0.5, 0.5);
	m_scalePivot = Vector2(0.5, 0.5);

	m_parentTransform = nullptr;
}


Vector2 Transform::getLocalPosition() const
{
	return m_localPosition;
}


Vector2 Transform::getWorldPosition() const
{
	return (localToWorldPosition(m_localPosition));
}


void Transform::setLocalPosition(const Vector2& position)
{
	m_localPosition = position;
}


void Transform::setWorldPosition(const Vector2& position)
{
	if (m_parentTransform == nullptr)
	{
		setLocalPosition(position);
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
}


double Transform::getLocalRotation() const
{
	return m_localRotation;
}


double Transform::getWorldRotation() const
{
	if (m_parentTransform == nullptr)
	{
		return getLocalRotation();
	}
	else
	{
		// For rotation, one only needs to add the parent rotation
		double worldRotation = m_localRotation + m_parentTransform->getWorldRotation();
		// Clamp between 0 and 360
		worldRotation -= 360 * (int)(worldRotation / 360);
		return (worldRotation);
	}
}


void Transform::setLocalRotation(double rotation)
{
	// Set Local Rotation
	// Clamp between 0 and 360
	m_localRotation = rotation - 360 * (int)(rotation / 360);
}


void Transform::setWorldRotation(double rotation)
{
	if (m_parentTransform == nullptr)
	{
		setLocalRotation(rotation);
	}
	else
	{
		m_localRotation = rotation - m_parentTransform->getWorldRotation();
		m_localRotation -= 360 * (int)(m_localRotation / 360);
	}
}


Vector2 Transform::getLocalScale() const
{
	return m_localScale;
}


Vector2 Transform::getWorldScale() const
{
	if (m_parentTransform == nullptr)
	{
		return getLocalScale();
	}
	else
	{
		Vector2 worldScale;
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		worldScale.x = m_localScale.x * parentWorldScale.x;
		worldScale.y = m_localScale.y * parentWorldScale.y;
		// For scale, one only needs to multiply the parent scale
		return (worldScale);
	}
}


void Transform::setLocalScale(const Vector2& scale)
{
	m_localScale = scale;
}


void Transform::setWorldScale(const Vector2& scale)
{
	if (m_parentTransform == nullptr)
	{
		setLocalScale(scale);
	}
	else
	{
		Vector2 parentWorldScale = m_parentTransform->getWorldScale();
		if (parentWorldScale.x == 0 || parentWorldScale.y == 0)
		{
			return;
		}
		m_localScale.x = scale.x / parentWorldScale.x;
		m_localScale.y = scale.y / parentWorldScale.y;
	}
}


// PIVOTS


Vector2 Transform::getPositionPivot() const
{
	return m_positionPivot;
}


void Transform::setPositionPivot(const Vector2& positionPivot, bool adjustScalePivot)
{
	m_positionPivot = positionPivot;

	if (adjustScalePivot)
	{
		setScalePivot(m_positionPivot);
	}
}


Vector2 Transform::getRotationPivot() const
{
	return m_rotationPivot;
}


void Transform::setRotationPivot(const Vector2& rotationPivot)
{
	m_rotationPivot = rotationPivot;
}


Vector2 Transform::getScalePivot() const
{
	return m_scalePivot;
}


void Transform::setScalePivot(const Vector2& scalePivot)
{
	m_scalePivot = scalePivot;
}


void Transform::setAllPivots(const Vector2& pivot)
{
	setPositionPivot(pivot);
	setRotationPivot(pivot);
	setScalePivot(pivot);
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
		//		1.1 Get polar coordinates for m_localPosition (r and theta)
		double r = sqrt(m_localPosition.x * m_localPosition.x + m_localPosition.y * m_localPosition.y);
		double theta = atan2(m_localPosition.y, m_localPosition.x);

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
		//		3.1 Get polar coordinates for the current m_localPosition (r and theta)
		double r = sqrt(m_localPosition.x * m_localPosition.x + m_localPosition.y * m_localPosition.y);
		double theta = atan2(m_localPosition.y, m_localPosition.x);

		//		3.2 use the polar coordinate to recalculate the x and y coordinates
		double parentWorldRotation = m_parentTransform->getWorldRotation();
		localPosition.x = r * cos(theta - parentWorldRotation);
		localPosition.y = r * sin(theta - parentWorldRotation);

		return localPosition;
	}
}

void Transform::setParent(Transform * parent)
{
	if (parent == nullptr)
	{
		// Set parent to world
		m_parentTransform = nullptr;
	}
	else
	{
		// Set parent to the supplied transform
		m_parentTransform = parent;
	}
}

