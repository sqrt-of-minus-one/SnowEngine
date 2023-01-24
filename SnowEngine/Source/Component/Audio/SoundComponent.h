    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SoundComponent.h            //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `SoundComponent` class
 *
 *	This file contains the definition of the `SoundComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `SoundComponent`
 *
 *	Этот файл содержит определение класса `SoundComponent`.
 */

#include "../Component.h"

#include <SFML/Audio/Sound.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class SoundBuffer;
}

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The component that can create sound
 *	
 *	This component creates sound. Use it for short sounds such as shots or footsteps. For long
 *	sounds use the `MusicComponent` class.
 *	
 *	\~russian
 *	\brief Компонент, который может создавать звук
 *	
 *	Этот компонент создаёт звук. Используйте его для короких звуков, таких как шаги. Для длинных
 *	звуков используйте класс `MusicComponent`.
 */
class SoundComponent : public Component
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new sound component.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create a component use the `create_component` method or the `create_root_component` method
	 *	of the `Actor` class.
	 *	\param actor The actor that the component will be attached to.
	 *	\param parent The parent component or the null pointer if the component will be root.
	 *	\param transform The transform of the component relative to the actor.
	 *	
	 *	\~russian
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый звуковой компонент.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать компонент, воспользуйтесь методом `create_component` или методом
	 *	`create_root_component` класса `Actor`.
	 *	\param actor Актёр, к которому будет прикреплён компонент.
	 *	\param parent Родительский компонент  или нулевой указатель, если компонент будет корневым.
	 *	\param transform Преобразование компонента относительно актёра.
	 */
	SoundComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the sound of the component
	 *	
	 *	Sets the sound that the component will be ready to play.
	 *	\param sound The name of the sound resource.
	 *	\return `true` if the sounds is successfully set, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Установить звук для компонента
	 *	
	 *	Устанавливает звук, который компонент будет готов проиграть.
	 *	\param sound Название звукового ресурса.
	 *	\return `true`, если звук успешно установлен, иначе `false`.
	 */
	bool set_sound(const String& sound);

	/**
	 *	\~english
	 *	\brief Play the sound
	 *	
	 *	Starts the sound playback.
	 *	
	 *	\~russian
	 *	\brief Воспроизвести звук
	 *	
	 *	Начинает воспроизведение звука.
	 */
	void play();

	/**
	 *	\~english
	 *	\brief Pause the sound
	 *
	 *	Pauses the sound playback.
	 *
	 *	\~russian
	 *	\brief Приостанавливает звук
	 *
	 *	Приостанавливает воспроизведение звука.
	 */
	void pause();

	/**
	 *	\~english
	 *	\brief Stop the sound
	 *
	 *	Stops the sound playback.
	 *
	 *	\~russian
	 *	\brief Останавливает звук
	 *
	 *	Останавливает воспроизведение звука.
	 */
	void stop();

protected:
			/* EVENT METHODS FROM Component */

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the level
	 *
	 *	This event is called when the component is transformed relative to the level, i. e. when
	 *	its level position, angle of rotation or scale is changed. If you override this method,
	 *	don't forget to call parent's `when_transformed`.
	 *	\param new_level_transform The new level transform of the component.
	 *
	 *	\~russian
	 *	\brief Компонент преобразован относительно уровня
	 *
	 *	Это событие вызывается, когда компонент преобразовывается относительно уровня, то есть
	 *	изменяется его положение, угол поворота или масштаб на уровне. Если вы переопределяете
	 *	этот метод, не забудьте вызвать родительский `when_transformed`.
	 *	\param new_level_transform Новое преобразование компонента на уровне.
	 */
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	sf::Sound sound_;
	std::shared_ptr<sf::SoundBuffer> buffer_;
	String sound_name_;
};

}
