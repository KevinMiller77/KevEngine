#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <string>
#include <vector>
#include <map>

#include <math/math.h>
#include <utils/Logging.h>

//#include <../ext/freetype-gl/freetype-gl.h>

struct KevFontInfo 
{
    const char* name;
    const char* location;
//    ftgl::texture_atlas_t* atlas;
//	ftgl::texture_font_t* font;

};

class FontManager
{
private:

    std::vector<KevFontInfo*> fonts;

public:
    FontManager() = default;
    ~FontManager()
    {
        for (KevFontInfo* font : fonts)
        {
            delete font;
        }

        fonts.clear();
    }

    void Add(const char* ID, const char* location, uint16_t size);
    KevFontInfo* Get(const char* ID);

    void ClearFonts();
    
};

#endif
