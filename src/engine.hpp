class Engine {
public:
	std::vector<std::shared_ptr<Ent>> entL;
	std::vector<std::shared_ptr<Element>> magicL;
	std::unique_ptr<Map> dungeon;

	enum gameState {
		START,
		IDLE,
		SPELL,
		TURN,
		WIN,
		LOSE
	}gameState;

	int fovRad;

	Ent *player;

	Engine(); ~Engine();

	void update(); void render();

private:
	bool computeFov;
};


extern Engine engine;