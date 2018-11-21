#pragma once

class Spell : public Entity{
public:
	void update();
	void render();
};

class MagicSystem {
	enum spellName { F, W, E, A, S };

public:

	MagicSystem(); ~MagicSystem();

	void castSpell(const std::shared_ptr<Entity> &ent);

	spellName lookup(std::string spellstring);
};