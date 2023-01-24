    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: VisibleComponent.h          //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `VisibleComponent` class
 *
 *	This file contains the definition of the `VisibleComponent` class.
 *
 *	\~russian
 *	\brief ���� � ������� `VisibleComponent`
 *
 *	���� ���� �������� ����������� ������ `VisibleComponent`.
 */

#include "../Component.h"

#include <map>
#include <list>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The visible component
 *	
 *	The component that is rendered on the level and can be seen by the player.
 *	
 *	\~russian
 *	\brief ������� ���������
 *	
 *	���������, ������� ������������ �� ������ � ����� ���� ����� ������.
 */
class VisibleComponent : public Component
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new component.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create a component use the `create_component` method or the `create_root_component` method
	 *	of the `Actor` class.
	 *	\param actor The actor that the component will be attached to.
	 *	\param parent The parent component or the null pointer if the component will be root.
	 *	\param transform The transform of the component relative to the actor.
	 *	
	 *	\~russian
	 *	\brief ����������
	 *	
	 *	������ ����� ���������.
	 *	\warning ����������� ������������ ������ ��� ����������� �������������, �� ����������� ���
	 *	��������. ����� ������� ���������, �������������� ������� `create_component` ��� �������
	 *	`create_root_component` ������ `Actor`.
	 *	\param actor ����, � �������� ����� ��������� ���������.
	 *	\param parent ������������ ���������  ��� ������� ���������, ���� ��������� ����� ��������.
	 *	\param transform �������������� ���������� ������������ �����.
	 */
	VisibleComponent(Actor& actor, Component* parent, const Transform& transform);

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	Removes the component.
	 *	
	 *	\~russian
	 *	\brief ����������
	 *	
	 *	������� ���������.
	 */
	~VisibleComponent();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Render the component on the level
	 *	
	 *	This method draws the component on the passed window. It is called by the engine, you
	 *	shouldn't call it directly.
	 *	\param window The SFML window where the component will be drawn.
	 *	
	 *	\~russian
	 *	\brief ���������� ��������� �� ������
	 *	
	 *	���� ����� ������������ ��������� �� ���������� ����. �� ���������� �������; �� �� ������
	 *	�������� ��� ���������������.
	 *	\param window ���� SFML, ��� ��������� ����� ���������.
	 */
	virtual void draw(sf::RenderWindow& window) = 0;

	/**
	 *	\~english
	 *	\brief Get all visible components
	 *
	 *	Allows to get the map with all visible components. Keys of the map are the levels where
	 *	components are.
	 *	\return The map with all visible components.
	 *
	 *	\~russian
	 *	\brief �������� ��� ������� ����������
	 *
	 *	��������� �������� ������� �� ����� �������� ������������. ������� ������� ��������
	 *	������, �� ������� ��������� ����������.
	 *	\return ������� �� ����� �������� ������������.
	 */
	static const std::map<Level*, std::list<VisibleComponent*>>& get_visible_components();

private:
	static std::map<Level*, std::list<VisibleComponent*>> visible_components_;
};

}
