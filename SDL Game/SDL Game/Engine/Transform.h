#pragma once

#include "Vector2.h"


class Transform
{

	friend class GameObject;
public:	
	Transform();

	// Position
	Vector2 getLocalPosition() const;
	Vector2 getWorldPosition() const;
	void setLocalPosition(const Vector2& position);
	void setWorldPosition(const Vector2& position);

	// Rotation
	double getLocalRotation() const;
	double getWorldRotation() const;
	void setLocalRotation(double rotation);
	void setWorldRotation(double rotation);

	// Scale
	Vector2 getLocalScale() const;
	Vector2 getWorldScale() const;
	void setLocalScale(const Vector2& scale);
	void setWorldScale(const Vector2& scale);

	// Pivots
	Vector2 getPositionPivot() const;
	void setPositionPivot(const Vector2& positionPivot, bool adjustScalePivot = true);

	Vector2 getRotationPivot() const;
	void setRotationPivot(const Vector2& rotationPivot);

	Vector2 getScalePivot() const;
	void setScalePivot(const Vector2& scalePivot);

	void setAllPivots(const Vector2& pivot);

private:	
	Vector2 m_localPosition;
	double m_localRotation;
	Vector2 m_localScale;

	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;

	Transform* m_parentTransform;
	void setParent(Transform* parent);

};
