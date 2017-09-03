#include "Transform.h"


Transform::Transform()
{
	m_worldPosition = { 0, 0 };
	m_localPosition = { 0, 0 };
	m_worldRotation = 0;
	m_localRotation = 0;
	m_worldScale = { 1, 1 };
	m_localScale = { 1, 1 };
	
	m_positionPivot = { 0.5 , 0 };
	m_rotationPivot = { 0.5, 0.5 };
	m_scalePivot = { 0.5 , 0 };
}


Vector2 Transform::getWorldPosition() const
{
	return m_worldPosition;
}


Vector2 Transform::getLocalPosition() const
{
	return m_localPosition;
}


void Transform::setWorldPosition(const Vector2& position)
{
	// Set Global Position
	m_worldPosition = position;

	// Adjust Local Position
	// TEMPORARY!
	m_localPosition = m_worldPosition;
}


void Transform::setLocalPosition(const Vector2& position)
{
	// Set Local Position
	m_localPosition = position;

	// Adjust Global Position
	// TEMPORARY!
	m_worldPosition = m_localPosition;
}


double Transform::getWorldRotation() const
{
	return m_worldRotation;
}


double Transform::getLocalRotation() const
{
	return m_localRotation;
}


void Transform::setWorldRotation(double rotation)
{
	// Set Global Rotation
	m_worldRotation = rotation - 360 * (int)(rotation / 360);

	// Adjust Local Rotation
	// TEMPORARY!
	m_localRotation = m_worldRotation;
}


void Transform::setLocalRotation(double rotation)
{
	// Set Local Rotation
	m_localRotation = rotation - 360 * (int)(rotation / 360);

	// Adjust Global Rotation
	// TEMPORARY!
	m_worldRotation = m_localRotation;
}


Vector2 Transform::getWorldScale() const
{
	return m_worldScale;
}


Vector2 Transform::getLocalScale() const
{
	return m_localScale;
}


void Transform::setWorldScale(const Vector2& scale)
{
	// Set Global Scale
	m_worldScale.x = scale.x;// >= 0 ? scale.x : 0;
	m_worldScale.y = scale.y;// >= 0 ? scale.y : 0;

	// Adjust Local Scale
	// TEMPORARY!
	m_localScale = m_worldScale;
}


void Transform::setLocalScale(const Vector2& scale)
{
	// Set Local Scale
	m_localScale.x = scale.x;// >= 0 ? scale.x : 0;
	m_localScale.y = scale.y;// >= 0 ? scale.y : 0;

	// Adjust Global Scale
	// TEMPORARY!
	m_worldScale = m_localScale;
}


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

