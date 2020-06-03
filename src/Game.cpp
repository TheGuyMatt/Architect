#include "Game.hpp"

#include "Core/Rendering/TextureManager.hpp"
#include "Core/Util/Log.hpp"
#include "Core/Rendering/TileSet.hpp"

//keeps game loop running
static bool running = true;
//handler for quit event
void QuitHandler(Event &event)
{
	running = false;
	Log("Shutting down game...");
}

TileSet tempTileSet;

Game::Game(const std::string &title, int width, int height)
{
	//initialize coordinator
	_coordinator.Init();

	//register quit event with coordinator
	_coordinator.AddEventListener(FUNCTION_LISTENER(Events::Window::QUIT, QuitHandler));

	//create window
	_window.create(title, width, height, &_coordinator);

	//initialize inputManager
	_inputManager.Init(&_coordinator);

	//initialize textureManager
	TextureManager::Init(_window.getRenderer());
  tempTileSet.load(TextureManager::get("TempTileSet"), Math::Vector2i(32, 32));

	//register components with coordinator
	this->registerComponents();

	//register systems with coordinator
	this->registerSystems();

	this->Run();
}

void Game::registerComponents()
{
	_coordinator.RegisterComponent<Transform>();
	_coordinator.RegisterComponent<RigidBody>();
	_coordinator.RegisterComponent<Renderable>();
	_coordinator.RegisterComponent<Player>();
	_coordinator.RegisterComponent<PhysicsBody>();
	_coordinator.RegisterComponent<StaticComp>();
}

void Game::registerSystems()
{
	cameraController = _coordinator.RegisterSystem<CameraController>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Player>());
		signature.set(_coordinator.GetComponentType<Transform>());

		_coordinator.SetSystemSignature<CameraController>(signature);
	}
	cameraController->Init(&_coordinator, &worldCamera);

	staticRender = _coordinator.RegisterSystem<StaticRender>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<StaticComp>());

		_coordinator.SetSystemSignature<StaticRender>(signature);
	}
	staticRender->Init(&_coordinator, &worldCamera, _window.getRenderer());

	playerInput = _coordinator.RegisterSystem<PlayerInput>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerInput>(signature);
	}
	playerInput->Init(&_coordinator);

	playerRender = _coordinator.RegisterSystem<PlayerRender>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());
		signature.set(_coordinator.GetComponentType<Renderable>());

		_coordinator.SetSystemSignature<PlayerRender>(signature);
	}
	playerRender->Init(&_coordinator, &worldCamera, _window.getRenderer());

	playerMove = _coordinator.RegisterSystem<PlayerMove>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerMove>(signature);
	}
	playerMove->Init(&_coordinator);
}

void Game::HandleInput()
{
	//input updates
	_inputManager.Update();
	playerInput->Update();
}

void Game::Update()
{
	//logic updates
	playerMove->Update();

	//update camera after logic
	cameraController->Update();
}

void Game::Render()
{
	//render updates
	_window.clear(0, 0, 0, 255);

	TextureManager::get("sky")->render(0, 0, 800, 600);
  tempTileSet.render(1, 1, 200, 50, 128, 128);

	staticRender->Update();
	playerRender->Update();

	_window.present();
}

void Game::Run()
{
	//create static green squares
	for (float i = 0; i < 2; i++)
	{
		for (float j = 0; j < 2; j++)
		{
			Entity entity = _coordinator.CreateEntity();
			_coordinator.AddComponent<Transform>(entity, { Math::Vector2f(i * 700, j * 500) });
			_coordinator.AddComponent<RigidBody>(entity, { Math::Vector2i(100, 100) });
			_coordinator.AddComponent<Renderable>(entity, { Math::Vector4i(0, 255, 0, 255) });
			_coordinator.AddComponent<StaticComp>(entity, {});
		}
	}

	//create player
	Entity player = _coordinator.CreateEntity();
	_coordinator.AddComponent<Transform>(player, { Math::Vector2f(350.0f, 250.0f) });
	_coordinator.AddComponent<RigidBody>(player, { Math::Vector2i(100, 100) });
	_coordinator.AddComponent<PhysicsBody>(player, { Math::Vector2f() });
	_coordinator.AddComponent<Renderable>(player, { Math::Vector4i(200, 0, 200, 255) });
	_coordinator.AddComponent<Player>(player, {});

	const float FPS = 60;
	const float frameDelay = 1000 / FPS;
	float frameStart;
	float frameTime;

	while (running)
	{
		frameStart = (float)SDL_GetTicks();

		this->HandleInput();
		this->Update();
		this->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay((Uint32)(frameDelay - frameTime));
		}
	}
	
	_window.close();
}
