#include "DummyEnemy.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"

DummyEnemy::DummyEnemy() : j2Entity(ENTITY_TYPE::ENEMY)
{
}

DummyEnemy::~DummyEnemy()
{
}

bool DummyEnemy::Start()
{
	entity_rect = {62,4,32,57};
	entity_tex = App->tex->Load("textures/entities_sprites.png");

	return true;
}

bool DummyEnemy::Update(float dt, bool do_logic)
{
	return true;
}

bool DummyEnemy::CleanUp()
{
	App->tex->UnLoad(entity_tex);
	return true;
}

void DummyEnemy::Draw()
{
	if (App->map->data.type == MAPTYPE_ORTHOGONAL)
		App->render->Blit(entity_tex, position.x, position.y, &entity_rect);
	else if (App->map->data.type==MAPTYPE_ISOMETRIC)
		App->render->Blit(entity_tex, position.x -16, position.y, &entity_rect);
}
