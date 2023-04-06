#include <iostream>
#include <conio.h>

#include "Source/Game/Game.h"
#include "Source/Util/Types/String.h"
#include "Source/Math/Vector/Point2.h"
#include "Source/Level/Level.h"
#include "Source/Actor/Actor.h"
#include "Source/Util/Time/TimerManager.h"
#include "Source/Util/Time/Timer.h"
#include "Source/Component/Visible/AnimationComponent.h"
#include "Source/Component/Camera/CameraComponent.h"
#include "Source/Component/Visible/TextComponent.h"
#include "Source/Component/Audio/SoundComponent.h"
#include "Source/Util/Animation/AdvancedSpriteAnimation.h"
#include "Source/Util/Input/Input.h"
#include "Source/Component/Clickable/RectClickableComponent.h"
#include "Source/Util/SaveLoad/SaveLoad.h"

using namespace snow;

int main()
{
	snow::Game::start();

	std::shared_ptr<Level> level = Game::create_level<Level>();
	std::shared_ptr<Actor> actor = level->spawn_actor<Actor>(Transform(Vector2::ZERO));
	std::shared_ptr<Component> component = actor->create_root_component<Component>(Transform(Vector2::ZERO));

	std::shared_ptr<CameraComponent> camera = component->create_component<CameraComponent>(Transform(Vector2::ZERO));
	std::shared_ptr<AnimationComponent> texture = component->create_component<AnimationComponent>(Transform(Vector2::ZERO));
	std::shared_ptr<TextComponent> text = component->create_component<TextComponent>(Transform(Vector2::ZERO));
	std::shared_ptr<SoundComponent> sound = component->create_component<SoundComponent>(Transform(Vector2::ZERO));
	std::shared_ptr<RectClickableComponent> clickable = component->create_component<RectClickableComponent>(Transform(Vector2::ZERO));

	clickable->on_pressed.bind([](EButton button) { std::wcout << "Hello!\n"; });

	texture->set_texture(L"selection.png"_s);

	std::list<Frame> frames;
	frames.push_back({ IntRect(Point2(0, 0), Point2(32, 32)), .5f });
	frames.push_back({ IntRect(Point2(32, 32), Point2(64, 64)), 1.5f });

	std::shared_ptr<AdvancedSpriteAnimation> animation = std::make_shared<AdvancedSpriteAnimation>(std::move(frames));
	texture->set_sprite_animation(animation);

	text->set_font(L"cambriab.ttf"_s);
	text->set_text(L"Hello world!"_s);

	sound->set_sound(L"cow_passive_0.wav");

	//Delegate<void> delegate;
	//delegate.bind([&camera, &texture, &actor](){ camera->move(Vector2(.5f, 0.f)); texture->rotate(.1_deg); actor->scale(Vector2(.999f, .999f)); });
	//TimerManager::get_instance().create_timer(delegate, .05f, .05f);

	Delegate<void> sound_delegate;
	sound_delegate.bind([&sound]() { sound->play(); });
	TimerManager::get_instance().create_timer(sound_delegate, 0.f, 5.f);

	Input::get_instance().on_mouse_released(EButton::RIGHT).bind([]() { std::wcout << L"Pressed! (" << Input::get_instance().get_window_mouse_position().to_string() << L")" << std::endl; Input::get_instance().set_screen_mouse_position(Point2(100, 100)); });

	std::wcout << util::to_string(-5.f) << std::endl <<
		util::to_string(-5.67f, 0) << std::endl <<
		util::to_string(-5.f, 4) << std::endl <<
		util::to_string(-5.f, -4) << std::endl <<
		util::to_string(5.67899f, 4) << std::endl;

	_getch();
	return 0;
}