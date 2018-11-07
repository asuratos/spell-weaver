class Engine {
public:
	std::vector<std::shared_ptr<Ent>> entL;
	//std::vector<std::shared_ptr<Element>> magicL;
	std::unique_ptr<Map> dungeon;

	enum gameState {
		START,
		GAME,
		WIN,
		LOSE
	}gameState;

	int fovRad, sW, sH;

	TCOD_key_t lastKey;

	std::shared_ptr<Actor> player;

	Engine(int sW, int sH); ~Engine();

	void update(); void render();

private:
	bool computeFov;
};


extern Engine engine;