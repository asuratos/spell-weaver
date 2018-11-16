class Engine {
public:
	std::vector<std::shared_ptr<Entity>> entL;
	std::unique_ptr<Map> dungeon;
	std::unique_ptr<MovementSystem> Mover;
	std::shared_ptr<Entity> player;

	enum gameState {
		START,
		GAME,
		WIN,
		LOSE
	}gameState;

	int fovRad, sW, sH;

	TCOD_key_t lastKey;

	Engine(int sW, int sH); ~Engine();

	void update(); void render();

private:
	bool computeFov;
};


extern Engine engine;