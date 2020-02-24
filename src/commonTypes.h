#ifndef __TLETC_TYPES__
#define __TLETC_TYPES__

<<<<<<< HEAD
=======
#include <windows.h>
#include <wingdi.h>

#include "graphics/GL2DRenderer.h"
#include "graphics/ShaderProgram.h"

void OnGameStart();
void Draw(HDC windowHDC);
void Update(); 

>>>>>>> 9385a6cb1b46d988773c0c175ebbdd2b460a3a3a
#define local static
#define global static

//Common type defs
typedef char                i8_t;
typedef short               i16_t;
typedef int                 i32_t;
typedef long long           i64_t;
typedef unsigned char       u8_t;
typedef unsigned short int  u16_t;
typedef unsigned int        u32_t;
typedef unsigned long long  u64_t;
typedef float               f32_t;
typedef double              f64_t;
typedef long double         f96_t;

typedef unsigned char byte;


#endif