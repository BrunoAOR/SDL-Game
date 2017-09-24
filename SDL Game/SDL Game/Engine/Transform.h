#pragma once

#include "Component.h"

#include <memory>
#include "Vector2.h"


class Transform final :
	public Component
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

	// Helper methods
	Vector2 localToWorldPosition(const Vector2& localPosition) const;
	Vector2 worldToLocalPosition(const Vector2& worldPosition) const;
	double localToWorldRotation(double localRotation) const;
	double worldToLocalRotation(double worldRotation) const;
	Vector2 localToWorldScale(const Vector2& localScale) const;
	Vector2 worldToLocalScale(const Vector2& worldScale) const;

private:
	Vector2 m_localPosition;
	double m_localRotation;
	Vector2 m_localScale;

	Transform* m_parentTransform;

	void setParent(Transform* parent);

	// These declarations are here just to hide the inheritted members functions from Component
	void setActive(bool activeState);
	bool isActive();
};
