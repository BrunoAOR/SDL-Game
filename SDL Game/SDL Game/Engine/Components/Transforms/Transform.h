#pragma once

#include "Engine/Components/Component.h"

#include <memory>
#include <vector>
#include "Engine/Vector2.h"


class Transform final :
	public Component
{
	friend class GameObjectsManager;
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

	// Hierarchy related
	std::weak_ptr<Transform> getParent();
	bool setParent(std::weak_ptr<Transform> parent);
	void removeParent();

private:
	Vector2 m_localPosition;
	double m_localRotation;
	Vector2 m_localScale;
	
	Vector2 m_worldPosition;
	double m_worldRotation;
	Vector2 m_worldScale;

	// Hierarchy related
	Transform* m_parentTransform;
	std::weak_ptr<Transform> m_parentWeakPtr;
	std::vector<Transform*> m_children;

	bool addChild(Transform* childTransform);
	bool removeChild(Transform* childTransform);
	bool isTransformInChildrenHierarchy(Transform* transform);

	void updateLocalFields();
	void updateWorldFields();
	void updateChildrenLocalFields();
	void updateChildrenWorldFields();

	// Hiding inherited members from Component
	void setActive(bool activeState);
	bool isActive();
};
