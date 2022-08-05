#include <iostream>
#include <conio.h>

#include "Source/Game/Game.h"
#include "Source/Util/Types/String.h"

#include "Source/Level/Level.h"
#include "Source/Actor/Actor.h"
#include "Source/Util/Time/TimerManager.h"
#include "Source/Util/Time/Timer.h"
#include "Source/Component/Visible/TextureComponent.h"
#include "Source/Component/Camera/CameraComponent.h"

using namespace snow;

int main()
{
	snow::Game::start();

	std::shared_ptr<Level> level = Game::create_level<Level>();
	std::shared_ptr<Actor> actor = level->spawn_actor<Actor>(Transform(Vector2::ZERO));
	std::shared_ptr<Component> component = actor->create_root_component<Component>(Transform(Vector2::ZERO));
	std::shared_ptr<CameraComponent> camera = component->create_component<CameraComponent>(Transform(Vector2::ZERO));
	std::shared_ptr<TextureComponent> texture = component->create_component<TextureComponent>(Transform(Vector2::ZERO));

	texture->set_texture(L"Hello world!"_s);

	Delegate<void> delegate;
	delegate.bind([&camera, &texture](){ camera->move(Vector2(1.f, 0.f)); texture->rotate(1_deg); });
	Game::timer_manager.create_timer(delegate, .05f, .05f);

	_getch();
	return 0;
}