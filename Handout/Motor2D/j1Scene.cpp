#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Minimap.h"

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	map1 = config.child("map1").attribute("path").as_string();
	map2 = config.child("map2").attribute("path").as_string();
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load(map1.c_str());

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (App->minimap->display == true)
			App->minimap->display = false;
		else
			App->minimap->display = true;
	}

	App->map->Draw();

		
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		changeMap();

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::changeMap() {
	App->map->CleanUp();
	App->minimap->CleanUp();
	if (App->map->data.type==MAPTYPE_ISOMETRIC) {
		App->map->Load(map2.c_str());
		App->minimap->Start();
	}
	else if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
		App->map->Load(map1.c_str());
		App->minimap->Start();
	}
}
