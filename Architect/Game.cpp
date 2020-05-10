#include "Game.hpp"

//keeps game loop running
static bool running = true;
//handler for quit event
void QuitHandler(Event &event) { running = false; }

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

	//register components with coordinator
	this->registerComponents();

	//register systems with coordinator
	this->registerSystems();

	this->Run();
}

Game::~Game()
{
	SDL_DestroyTexture(testTexture);
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

	staticRenderSystem = _coordinator.RegisterSystem<StaticRenderSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<StaticComp>());

		_coordinator.SetSystemSignature<StaticRenderSystem>(signature);
	}
	staticRenderSystem->Init(&_coordinator, &worldCamera, _window.getRenderer());

	playerInputSystem = _coordinator.RegisterSystem<PlayerInputSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerInputSystem>(signature);
	}
	playerInputSystem->Init(&_coordinator);

	playerRenderSystem = _coordinator.RegisterSystem<PlayerRenderSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());
		signature.set(_coordinator.GetComponentType<Renderable>());

		_coordinator.SetSystemSignature<PlayerRenderSystem>(signature);
	}
	playerRenderSystem->Init(&_coordinator, &worldCamera, _window.getRenderer());

	playerMoveSystem = _coordinator.RegisterSystem<PlayerMoveSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerMoveSystem>(signature);
	}
	playerMoveSystem->Init(&_coordinator);
}

void Game::HandleInput()
{
	//input updates
	_inputManager.Update();
	playerInputSystem->Update();
}

void Game::Update()
{
	//logic updates
	playerMoveSystem->Update();

	//update camera after logic
	cameraController->Update();
}

void Game::Render()
{
	//render updates
	_window.clear(0, 0, 200, 255);

	staticRenderSystem->Update();
	playerRenderSystem->Update();

	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 62 * 3;
	rect.h = 104 * 3;
	SDL_RenderCopy(_window.getRenderer(), testTexture, nullptr, &rect);

	_window.present();
}

void Game::Run()
{
	//create entities
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

	//test texture stuff
	SDL_Surface* surface = IMG_Load("Resources/Scarecrow.png");
	if (surface == nullptr) std::cerr << "Failed to create surface\n";
	testTexture = SDL_CreateTextureFromSurface(_window.getRenderer(), surface);
	if (testTexture == nullptr) std::cerr << "Failed to create texture\n";
	SDL_FreeSurface(surface);

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