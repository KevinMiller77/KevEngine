#ifndef INPUT_CODES
#define INPUT_CODES

#include <windows.h>

enum class MouseCode
{
	Button0                = 0,
	Button1                = 1,
	Button2                = 2,
	Button3                = 3,
	Button4                = 4,
	Button5                = 5,
	Button16               = 16,
	Button17               = 17,
	ButtonNext			   = Button17,
	ButtonLast             = Button16,
	ButtonLeft             = Button0,
	ButtonRight            = Button1,
	ButtonMiddle           = Button4
} Mouse;

enum class KeyCode
{
	//From windows
	Space               = VK_SPACE,
	Apostrophe          = 0xDE, /* ' */
	Comma               = 0xBC, /* , */
	Minus               = 0xBD, /* - */
	Period              = 0xBE, /* . */
	Slash               = 0xBF, /* / */
	D0                  = 48, /* 0 */
	D1                  = 49, /* 1 */
	D2                  = 50, /* 2 */
	D3                  = 51, /* 3 */
	D4                  = 52, /* 4 */
	D5                  = 53, /* 5 */
	D6                  = 54, /* 6 */
	D7                  = 55, /* 7 */
	D8                  = 56, /* 8 */
	D9                  = 57, /* 9 */
	Semicolon           = 0xBA, /* ; */
	Equal               = 100 + 61, /* = */
	A                   = 65,
	B                   = 66,
	C                   = 67,
	D                   = 68,
	E                   = 69,
	F                   = 70,
	G                   = 71,
	H                   = 72,
	I                   = 73,
	J                   = 74,
	K                   = 75,
	L                   = 76,
	M                   = 77,
	N                   = 78,
	O                   = 79,
	P                   = 80,
	Q                   = 81,
	R                   = 82,
	S                   = 83,
	T                   = 84,
	U                   = 85,
	V                   = 86,
	W                   = 87,
	X                   = 88,
	Y                   = 89,
	Z                   = 90,
	LeftBracket         = 0xDB,  /* [ */
	Backslash           = 0xDC,  /* \ */
	RightBracket        = 0xDD,  /* ] */
	GraveAccent         = 0xC0,  /* ` */
	/* Function keys */
	Escape              = 0x1B,
	Enter               = 0x0D,
	Tab                 = 0x09,
	Backspace           = 0x08,
	Insert              = 0x2D,
	Delete              = 0x2E,
	Right               = 0x27,
	Left                = 0x25,
	Down                = WM_KEYDOWN,
	Up                  = WM_KEYUP,
	PageUp              = 0x21,
	PageDown            = 0x22,
	Home                = 0x24,
	End                 = 0x23,
	CapsLock            = 0x14,
	ScrollLock          = 281,
	NumLock             = 0x90,
	PrintScreen         = 283,
	Pause               = 284,
	F1                  = 0x70,
	F2                  = 0x71,
	F3                  = 0x72,
	F4                  = 0x73,
	F5                  = 0x74,
	F6                  = 0x75,
	F7                  = 0x76,
	F8                  = 0x77,
	F9                  = 0x78,
	F10                 = 0x79,
	F11                 = 0x7A,
	F12                 = 0x7B,
	F13                 = 0x7C,
	F14                 = 0x7D,
	F15                 = 0x7E,
	F16                 = 0x7F,
	F17                 = 0x80,
	F18                 = 0x81,
	F19                 = 0x82,
	F20                 = 0x83,
	F21                 = 0x84,
	F22                 = 0x85,
	F23                 = 0x86,
	F24                 = 0x87,
	/* Keypad */
	KP0                 = 0x60,
	KP1                 = 0x61,
	KP2                 = 0x62,
	KP3                 = 0x63,
	KP4                 = 0x64,
	KP5                 = 0x65,
	KP6                 = 0x66,
	KP7                 = 0x67,
	KP8                 = 0x68,
	KP9                 = 0x69,
	KPDecimal           = VK_DECIMAL,
	KPDivide            = VK_DIVIDE,
	KPMultiply          = VK_MULTIPLY,
	KPSubtract          = VK_SUBTRACT,
	KPAdd               = VK_ADD,
	KPEnter             = 0xD,
	KPEqual             = 336,
	LeftShift           = 0x10,
	LeftControl         = 0x11,
	LeftAlt             = 0x12,
	LeftSuper           = 0x14,
} Key;

// From Windows
// All of these must be defined for each platform
#define KEV_KEY_SPACE           Key::Space
#define KEV_KEY_APOSTROPHE      Key::Apostrophe    /* ' */
#define KEV_KEY_COMMA           Key::Comma         /* , */
#define KEV_KEY_MINUS           Key::Minus         /* - */
#define KEV_KEY_PERIOD          Key::Period        /* . */
#define KEV_KEY_SLASH           Key::Slash         /* / */
#define KEV_KEY_0               Key::D0
#define KEV_KEY_1               Key::D1
#define KEV_KEY_2               Key::D2
#define KEV_KEY_3               Key::D3
#define KEV_KEY_4               Key::D4
#define KEV_KEY_5               Key::D5
#define KEV_KEY_6               Key::D6
#define KEV_KEY_7               Key::D7
#define KEV_KEY_8               Key::D8
#define KEV_KEY_9               Key::D9
#define KEV_KEY_SEMICOLON       Key::Semicolon     /* ; */
#define KEV_KEY_EQUAL           Key::Equal         /* = */
#define KEV_KEY_A               Key::A
#define KEV_KEY_B               Key::B
#define KEV_KEY_C               Key::C
#define KEV_KEY_D               Key::D
#define KEV_KEY_E               Key::E
#define KEV_KEY_F               Key::F
#define KEV_KEY_G               Key::G
#define KEV_KEY_H               Key::H
#define KEV_KEY_I               Key::I
#define KEV_KEY_J               Key::J
#define KEV_KEY_K               Key::K
#define KEV_KEY_L               Key::L
#define KEV_KEY_M               Key::M
#define KEV_KEY_N               Key::N
#define KEV_KEY_O               Key::O
#define KEV_KEY_P               Key::P
#define KEV_KEY_Q               Key::Q
#define KEV_KEY_R               Key::R
#define KEV_KEY_S               Key::S
#define KEV_KEY_T               Key::T
#define KEV_KEY_U               Key::U
#define KEV_KEY_V               Key::V
#define KEV_KEY_W               Key::W
#define KEV_KEY_X               Key::X
#define KEV_KEY_Y               Key::Y
#define KEV_KEY_Z               Key::Z
#define KEV_KEY_LEFT_BRACKET    Key::LeftBracket   /* [ */
#define KEV_KEY_BACKSLASH       Key::Backslash     /* \ */
#define KEV_KEY_RIGHT_BRACKET   Key::RightBracket  /* ] */
#define KEV_KEY_GRAVE_ACCENT    Key::GraveAccent   /* ` */
#define KEV_KEY_WORLD_1         Key::World1        /* non-US #1 */
#define KEV_KEY_WORLD_2         Key::World2        /* non-US #2 */

/* Function keys */
#define KEV_KEY_ESCAPE          Key::Escape
#define KEV_KEY_ENTER           Key::Enter
#define KEV_KEY_TAB             Key::Tab
#define KEV_KEY_BACKSPACE       Key::Backspace
#define KEV_KEY_INSERT          Key::Insert
#define KEV_KEY_DELETE          Key::Delete
#define KEV_KEY_RIGHT           Key::Right
#define KEV_KEY_LEFT            Key::Left
#define KEV_KEY_DOWN            Key::Down
#define KEV_KEY_UP              Key::Up
#define KEV_KEY_PAGE_UP         Key::PageUp
#define KEV_KEY_PAGE_DOWN       Key::PageDown
#define KEV_KEY_HOME            Key::Home
#define KEV_KEY_END             Key::End
#define KEV_KEY_CAPS_LOCK       Key::CapsLock
#define KEV_KEY_SCROLL_LOCK     Key::ScrollLock
#define KEV_KEY_NUM_LOCK        Key::NumLock
#define KEV_KEY_PRINT_SCREEN    Key::PrintScreen
#define KEV_KEY_PAUSE           Key::Pause
#define KEV_KEY_F1              Key::F1
#define KEV_KEY_F2              Key::F2
#define KEV_KEY_F3              Key::F3
#define KEV_KEY_F4              Key::F4
#define KEV_KEY_F5              Key::F5
#define KEV_KEY_F6              Key::F6
#define KEV_KEY_F7              Key::F7
#define KEV_KEY_F8              Key::F8
#define KEV_KEY_F9              Key::F9
#define KEV_KEY_F10             Key::F10
#define KEV_KEY_F11             Key::F11
#define KEV_KEY_F12             Key::F12
#define KEV_KEY_F13             Key::F13
#define KEV_KEY_F14             Key::F14
#define KEV_KEY_F15             Key::F15
#define KEV_KEY_F16             Key::F16
#define KEV_KEY_F17             Key::F17
#define KEV_KEY_F18             Key::F18
#define KEV_KEY_F19             Key::F19
#define KEV_KEY_F20             Key::F20
#define KEV_KEY_F21             Key::F21
#define KEV_KEY_F22             Key::F22
#define KEV_KEY_F23             Key::F23
#define KEV_KEY_F24             Key::F24
#define KEV_KEY_F25             Key::F25

/* Keypad */
#define KEV_KEY_KP_0            Key::KP0
#define KEV_KEY_KP_1            Key::KP1
#define KEV_KEY_KP_2            Key::KP2
#define KEV_KEY_KP_3            Key::KP3
#define KEV_KEY_KP_4            Key::KP4
#define KEV_KEY_KP_5            Key::KP5
#define KEV_KEY_KP_6            Key::KP6
#define KEV_KEY_KP_7            Key::KP7
#define KEV_KEY_KP_8            Key::KP8
#define KEV_KEY_KP_9            Key::KP9
#define KEV_KEY_KP_DECIMAL      Key::KPDecimal
#define KEV_KEY_KP_DIVIDE       Key::KPDivide
#define KEV_KEY_KP_MULTIPLY     Key::KPMultiply
#define KEV_KEY_KP_SUBTRACT     Key::KPSubtract
#define KEV_KEY_KP_ADD          Key::KPAdd
#define KEV_KEY_KP_ENTER        Key::KPEnter
#define KEV_KEY_KP_EQUAL        Key::KPEqual

#define KEV_KEY_LEFT_SHIFT      Key::LeftShift
#define KEV_KEY_LEFT_CONTROL    Key::LeftControl
#define KEV_KEY_LEFT_ALT        Key::LeftAlt
#define KEV_KEY_LEFT_SUPER      Key::LeftSuper

#define KEV_MOUSE_BUTTON_0      Mouse::Button0
#define KEV_MOUSE_BUTTON_1      Mouse::Button1
#define KEV_MOUSE_BUTTON_2      Mouse::Button2
#define KEV_MOUSE_BUTTON_3      Mouse::Button3
#define KEV_MOUSE_BUTTON_4      Mouse::Button4
#define KEV_MOUSE_BUTTON_5      Mouse::Button5
#define KEV_MOUSE_BUTTON_16     Mouse::Button16
#define KEV_MOUSE_BUTTON_17     Mouse::Button17
#define KEV_MOUSE_BUTTON_NEXT	Mouse::ButtonNext
#define KEV_MOUSE_BUTTON_LAST   Mouse::ButtonLast
#define KEV_MOUSE_BUTTON_LEFT   Mouse::ButtonLeft
#define KEV_MOUSE_BUTTON_RIGHT  Mouse::ButtonRight
#define KEV_MOUSE_BUTTON_MIDDLE Mouse::ButtonMiddle

#endif