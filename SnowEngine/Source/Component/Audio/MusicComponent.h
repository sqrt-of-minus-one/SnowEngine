    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MusicComponent.h            //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `MusicComponent` class
 *
 *	This file contains the definition of the `MusicComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `MusicComponent`
 *
 *	Этот файл содержит определение класса `MusicComponent`.
 */

#include "../Component.h"

#include <SFML/Audio/Music.hpp>

#include "../../Util/Types/String.h"

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The component that can create music
 *
 *	This component creates sound. Use it for music and other long sounds. For short sounds you can
 *	use the `SoundComponent` class.
 *
 *	\~russian
 *	\brief Компонент, который может создавать музыку
 *
 *	Этот компонент создаёт звук. Используйте его для музыки и других длинных звуков. Для коротких
 *	звуков вы можете использовать класс `SoundComponent`.
 */
class MusicComponent : public Component
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new sound component.
	 *	\warningThe constructo r is designed for internal use only, don't use it directly. To
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
	MusicComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the music of the component
	 *	
	 *	Sets the music that the component will be ready to play.
	 *	\param music The name of the music resource.
	 *	\return `true` if the music is successfully set, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Установить музыку для компонента
	 *	
	 *	Устанавливает музыку, которую компонент будет готов проиграть.
	 *	\param music Название музыкального ресурса.
	 *	\return `true`, если музыка успешно установлен; иначе `false`.
	 */
	bool set_music(const String& music);

	/**
	 *	\~english
	 *	\brief Play the music
	 *
	 *	Starts the music playback.
	 *
	 *	\~russian
	 *	\brief Воспроизвести музыку
	 *
	 *	Начинает воспроизведение музыки.
	 */
	void play();

	/**
	 *	\~english
	 *	\brief Pause the music
	 *
	 *	Pauses the music playback.
	 *
	 *	\~russian
	 *	\brief Приостанавливает музыку
	 *
	 *	Приостанавливает воспроизведение музыки.
	 */
	void pause();

	/**
	 *	\~english
	 *	\brief Stop the music
	 *
	 *	Stops the music playback.
	 *
	 *	\~russian
	 *	\brief Останавливает музыку
	 *
	 *	Останавливает воспроизведение музыки.
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
	sf::Music music_;
	String music_name_;
};

}
