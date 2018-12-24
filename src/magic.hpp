#pragma once

class Spell : public Entity{
public:
	void update();
	void render();
};

class MagicSystem {
	//AEFSW
	enum spellName { A, E, F, S, W,
					//two element spells
					AA, AE, AF, AS, AW,
					EE, EF, ES, EW,
					FF, FS, FW,
					SS, SW,
					WW,
					
					//three element spells
					//XXY, XXX type
					AAA, AAE, AAF, AAS, AAW,
					AEE, EEE, EEF, EES, EEW,
					AFF, EFF, FFF, FFS, FFW,
					AWW, EWW, FWW, SWW, WWW,
					
					//XYZ type
					AEF, AES, AEW, AFS, AFW,
					ASW, EFS, EFW, ESW, FSW};

public:

	MagicSystem(); ~MagicSystem();

	void castSpell(const std::shared_ptr<Entity> &ent);

	spellName lookup(std::string spellstring);
};