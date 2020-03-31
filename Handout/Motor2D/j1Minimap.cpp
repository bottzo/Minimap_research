#include "j1Minimap.h"

#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"

#include "j1Map.h"
#include "j2Entity.h"
#include "j2EntityManager.h"

#include "p2Log.h"

#include <list>

j1Minimap::j1Minimap()
{
	name = "minimap";
}

j1Minimap::~j1Minimap() {}

bool j1Minimap::Awake(pugi::xml_node & config)
{
	//TODO 1: Get the size of the minimap and its position from the config file
	//You can change the values on the file to adapt the minimap to the one you want
	//The size must be an integer and it ranges from 1 to tile_height
	//Both are alredy declared on the minimap class

	return true;
}

bool j1Minimap::Start()
{
	display = true;
	Load();

	return true;
}


bool j1Minimap::Update(float dt)
{	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int map_x, map_y;
		
		//If we are clicking on the minimap translate the minimap coordinates to map coordinates
		if (MinimapCoords(map_x, map_y))
		{
			//TODO 9: Assign the the center of the camera to the translated map coordinates
			//Remember the camera parameters are negative
			//App->render->camera.x = ;
			//App->render->camera.y = ;
		}
	}

	return true;
}

bool j1Minimap::PostUpdate()
{	
	if (display) {
		App->render->Blit(minimap_tex, position.x, position.y, NULL, false);
		MinimapBorders();
		DrawEntities();
		DrawCamera();
	}
	
	return true;
}

bool j1Minimap::CleanUp()
{
	SDL_DestroyTexture(minimap_tex);

	return true;
}

void j1Minimap::Load() {
	if (App->map->active)
	{

		//TODO 2: Calculate the minimap scale
		//The scale must always be a divider of the tile_height. 
		//If not, we will get floats when drawing the map that will get approximated to integers when creating the SDL_Rect to blit each tile and the minimap will not be blited correctly
		//The minimap_scale variable is already initialized on the minimap class

		//TODO 2: Once we obtained the minimap scale we can calculate the minimap width and height


		//TODO 3: Create a new texture for the minimap and make it the render target
		//Make sure the texture accses is the corret one to make the texture accsesible for the renderer
		//The texture size should be the minimap width and height
		//The minimap_tex variable is already initialized on the minimap class

	}
	DrawMinimap();

	//TODO 5: Return the render target to the renderer to stop bliting on the texture
	//TODO 5: Change the texture blendmode in order to get the unused backgorund of the texture transparent
	//After this TODO we should have succesfully blited the minimap


}

bool j1Minimap::MinimapCoords(int& map_x, int& map_y)
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);

	//if we click inside the minimap
	if (mouse_x >= position.x && mouse_x <= minimap_width +position.x	&&	mouse_y >= position.y && mouse_y <= minimap_height+position.y) 
	{
		// TODO 8: Translate the minimap click coordinates to map coordinates
		// Remember that we multiply for the scale to translate from map to minimap so to translate backwards we should do the opposite
		// Take into account that in the isometric map the position x=0 starts at the center of the map
		// Remember to remove the offset of the position of the minimap on the screen
		
		if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
			//map_x = ;
			//map_y = ;
		}
		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
			//map_x = ;
			//map_y = ;
		}

	}

	else
		return false;

	return true;
}

void j1Minimap::DrawMinimap()
{
	std::list<MapLayer*>::const_iterator item = App->map->data.layers.cbegin();

	for (; item != App->map->data.layers.end(); item = next(item))
	{
		MapLayer* layer = *item;

		for (int y = 0; y < App->map->data.height; ++y)
		{
			for (int x = 0; x < App->map->data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					TileSet* tileset = App->map->GetTilesetFromTileId(tile_id);

					SDL_Rect r = tileset->GetTileRect(tile_id);
					iPoint pos = App->map->MapToWorld(x, y);
					
					//TODO 4: Blit the minimap on the texture
					//As you can see to draw the minimap we can use the same draw function as the map but with 2 changes
					//One change is that the position where we blit the map must be scaled to the minimap one
					pos.x *= minimap_scale;
					pos.y *= minimap_scale;

					// TODO 4: Blit each tile of the minimap
					//The change is that we won't be using the camera
					//Remember that the pos.x=0 on the x axis for an isometric map is on the center of the map and not at the left
					//We need to include the minimap_scale also on the blit function
					/*
					if (App->map->data.type == MAPTYPE_ORTHOGONAL) 
						App->render->Blit();
					else if (App->map->data.type == MAPTYPE_ISOMETRIC)
						App->render->Blit();
					*/
				}
			}
		}
	}
}

void j1Minimap::DrawCamera()
{
	// TODO 7: Draw a representation of the camera on the minimap
	// Scale the camera parameters and move the minicamera to the map position
	// Reminder: The camera position values are negative
	// Take into account that in the isometric map the x position starts (x=0) on the center of the map
	if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
		//SDL_Rect map_camera = {};
		//App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
	}
	else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
		//SDL_Rect map_camera = {};
		//App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
	}
}

void j1Minimap::MinimapBorders()
{
	int isotile_x_offset = App->map->data.tile_width / 2 * minimap_scale;
	int isotile_y_offset = App->map->data.tile_height / 2 * minimap_scale;
	
	if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
		App->render->DrawLine(position.x , position.y, position.x + minimap_width, position.y, 0, 0, 255, 255, false);
		App->render->DrawLine(position.x + minimap_width, position.y, minimap_width + position.x, minimap_height + position.y, 0, 0, 255, 255, false);
		App->render->DrawLine(position.x,minimap_height + position.y, minimap_width + position.x, minimap_height + position.y, 0, 0, 255, 255, false);
		App->render->DrawLine(position.x, position.y, position.x, position.y + minimap_height, 0, 0, 255, 255, false);
	}
	else if (App->map->data.type == MAPTYPE_ISOMETRIC){
		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + position.y + isotile_y_offset, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
	}

}

void j1Minimap::DrawEntities()
{
	// TODO 6: Represent entities on the minimap
	// To do so you just need to draw a square with the scaled proportions of the entity
	// Remember that if we have moved the minimap position we also need to move the entities accordingly
	int pos_x, pos_y, width, height;

	for (std::list<j2Entity*>::iterator item = App->entity_manager->entities.begin(); item != App->entity_manager->entities.end(); ++item) 
	{
		if(App->map->data.type==MAPTYPE_ORTHOGONAL){
			/*
			pos_x = ;
			pos_y = ;
			width = ;
			height = ;
			*/
		}
		//TODO 6: If the map is isometric remember to add the needed offsets on the x position
		//(from the map and from the entity!!! Check the blit of the entities to know the offset that will also need to be scaled to the minimap size)
		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
			/*
			pos_x = ;
			pos_y = ;
			width = ;
			height = ;
			*/
		}
		//Uncomment when finished the TODO 6
		/*
		SDL_Rect entity_rect = { pos_x,pos_y,width,height };


		if ((*item)->type == ENTITY_TYPE::ENEMY)
			App->render->DrawQuad(entity_rect, 255, 0, 0, 255, true, false);
		
		else if ((*item)->type == ENTITY_TYPE::PLAYER)
			App->render->DrawQuad(entity_rect, 0, 255, 0, 255, true, false);
		*/
	}
}


