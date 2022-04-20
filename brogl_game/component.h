/// Base component for gameobject to derive from
/// And main derived components
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

namespace bro
{
	class transformation;
	class _rendermanager;
	class _objectmanager;

	class component
	{
	protected:
		transformation& transform;

	public:
		virtual void Update() {};

	public:
		component(transformation& _transform) : transform{ _transform } {};
	};

	class rendercomponent : public component
	{
	protected:
		_rendermanager& Render;
		_objectmanager& Objects;

	public:
		rendercomponent(transformation& _transform, _rendermanager& _render, _objectmanager& _objects) : 
			component{ _transform }, Render{ _render }, Objects{ _objects } {};

	};

	class physicscomponent : public component
	{
	public:
		physicscomponent(transformation& _transform) : component{ _transform } {};
	};

	class collisioncomponent : public component
	{
	public:
		collisioncomponent(transformation& _transform) : component{ _transform } {};

	};

}

#endif // !_COMPONENT_H_
