#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <string>
#include <vector>
#include <map>
#include "../math/math.h"
#include "../utils/Logging.h"

#ifdef BUILD_STATIC_LIB
#include <freetype-gl/freetype-gl.h>
#else
#include <../ext/freetype-gl/freetype-gl.h>
#endif

struct FontInfo 
{
    const char* name;
    const char* location;
    ftgl::texture_atlas_t* atlas;
	ftgl::texture_font_t* font;

};

class FontManager
{
private:

    std::vector<FontInfo*> fonts;

public:
    FontManager() = default;
    ~FontManager()
    {
        for (FontInfo* font : fonts)
        {
            delete font;
        }

        fonts.clear();
    }

    void add(const char* ID, const char* location, uint16_t size);
    FontInfo* get(const char* ID);

    void clearFonts();
    
};

#endif