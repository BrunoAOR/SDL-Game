#pragma once

#include "Vector2.h"


class Transform
{
public:	
	Transform();

	// Position
	Vector2 getWorldPosition() const;
	Vector2 getLocalPosition() const;
	void setWorldPosition(const Vector2& position);
	void setLocalPosition(const Vector2& position);

	// Rotation
	double getWorldRotation() const;
	double getLocalRotation() const;
	void setWorldRotation(double rotation);
	void setLocalRotation(double rotation);

	// Scale
	Vector2 getWorldScale() const;
	Vector2 getLocalScale() const;
	void setWorldScale(const Vector2& scale);
	void setLocalScale(const Vector2& scale);

	// Pivots
	Vector2 getPositionPivot() const;
	void setPositionPivot(const Vector2& positionPivot, bool adjustScalePivot = true);

	Vector2 getRotationPivot() const;
	void setRotationPivot(const Vector2& rotationPivot);

	Vector2 getScalePivot() const;
	void setScalePivot(const Vector2& scalePivot);

	void setAllPivots(const Vector2& pivot);

private:	
	Vector2 m_worldPosition;
	Vector2 m_localPosition;
	double m_worldRotation;
	double m_localRotation;
	Vector2 m_worldScale;
	Vector2 m_localScale;

	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;
};
