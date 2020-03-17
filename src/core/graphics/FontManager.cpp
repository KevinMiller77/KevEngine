#include "FontManager.h"

void FontManager::add(const char* ID, const char* location, uint16_t size)
{
    for (FontInfo* font : fonts)
    {
        if (!std::strcmp(font->name, ID))
        {
            LOG_ERR("Font %s already exists. Duplicates are destroyed.\n", ID);
            return;
        }
    }
    LOG_ERR("Font %s doesnt exist. Creating it now.\n", ID);


    FontInfo* newFont = new FontInfo();
    newFont->name = ID;
    newFont->location = location;
    newFont->atlas =  ftgl::texture_atlas_new(1024, 1024, 2);
    newFont->font = ftgl::texture_font_new_from_file(newFont->atlas, size, newFont->location);

    if (!(newFont->font))
    {
        LOG_ERR("Could not load font %s.\n", ID);
        return;
    }
    LOG_INF("Font %s created\n", ID);
    
    fonts.push_back(newFont);
}

FontInfo* FontManager::get(const char* ID)
{
    for (FontInfo* font : fonts)
    {

        if (!std::strcmp(font->name,ID))
        {
            LOG_INF("Found font %s\n", ID);
            return font;
        }
    }

    return nullptr;
}

void FontManager::clearFonts()
{
    for (FontInfo* font : fonts)
    {
        delete font;
    }
    fonts.clear();
}