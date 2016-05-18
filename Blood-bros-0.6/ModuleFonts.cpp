#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

#include<string.h>


int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
	if (fonts[id].graphic == nullptr)
		break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}


	fonts[id].graphic = tex;
	strcpy_s(fonts[id].table, characters);

	fonts[id].rows = rows;
	fonts[id].len = strlen(fonts[id].table);
	fonts[id].row_chars = (strlen(fonts[id].table) / rows);
	fonts[id].char_w = 32;
	fonts[id].char_h = 35;

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}


void ModuleFonts::Blit(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	for (uint i = 0; i < len; ++i)
	{
		for (uint j = 0; j < font->len; j++)
		{
			if (text[i] == font->table[j]){
				rect = { font->char_w * j, (font->char_h * (j / font->row_chars)), font->char_w, font->char_h };
				App->render->Blit(font->graphic, x, y, &rect, 0);
				x += font->char_w;
			}
		}

	}
}