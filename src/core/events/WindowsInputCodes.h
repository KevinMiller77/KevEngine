#ifndef __INPUT_CODES__
#define __INPUT_CODES__

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
};

enum class KeyCode
{
	MouseLeft			= 0x01,
	MouseRight			= 0x02,
	MouseMiddle			= 0x04,
	MouseX1				= 0x05,
	MouseX2				= 0x06,
	
	//From windows
	Space               = 0x20,
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
	Equal               = 61, /* = */
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
	Down                = 0x28,
	Up                  = 0x26,
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
	KPDecimal           = 0x6E,
	KPDivide            = 0x6F,
	KPMultiply          = 0x6A,
	KPSubtract          = 0x6D,
	KPAdd               = 0x6B,
	KPEnter             = 0xD,
	KPEqual             = 336,
	LeftShift           = 0x10,
	LeftControl         = 0x11,
	LeftAlt             = 0x12,
	LeftSuper           = 0x14,
};

// From Windows
// All of these must be defined for each platform
#define KEV_KEY_SPACE           KeyCode::Space
#define KEV_KEY_APOSTROPHE      KeyCode::Apostrophe    /* ' */
#define KEV_KEY_COMMA           KeyCode::Comma         /* , */
#define KEV_KEY_MINUS           KeyCode::Minus         /* - */
#define KEV_KEY_PERIOD          KeyCode::Period        /* . */
#define KEV_KEY_SLASH           KeyCode::Slash         /* / */
#define KEV_KEY_0               KeyCode::D0
#define KEV_KEY_1               KeyCode::D1
#define KEV_KEY_2               KeyCode::D2
#define KEV_KEY_3               KeyCode::D3
#define KEV_KEY_4               KeyCode::D4
#define KEV_KEY_5               KeyCode::D5
#define KEV_KEY_6               KeyCode::D6
#define KEV_KEY_7               KeyCode::D7
#define KEV_KEY_8               KeyCode::D8
#define KEV_KEY_9               KeyCode::D9
#define KEV_KEY_SEMICOLON       KeyCode::Semicolon     /* ; */
#define KEV_KEY_EQUAL           KeyCode::Equal         /* = */
#define KEV_KEY_A               KeyCode::A
#define KEV_KEY_B               KeyCode::B
#define KEV_KEY_C               KeyCode::C
#define KEV_KEY_D               KeyCode::D
#define KEV_KEY_E               KeyCode::E
#define KEV_KEY_F               KeyCode::F
#define KEV_KEY_G               KeyCode::G
#define KEV_KEY_H               KeyCode::H
#define KEV_KEY_I               KeyCode::I
#define KEV_KEY_J               KeyCode::J
#define KEV_KEY_K               KeyCode::K
#define KEV_KEY_L               KeyCode::L
#define KEV_KEY_M               KeyCode::M
#define KEV_KEY_N               KeyCode::N
#define KEV_KEY_O               KeyCode::O
#define KEV_KEY_P               KeyCode::P
#define KEV_KEY_Q               KeyCode::Q
#define KEV_KEY_R               KeyCode::R
#define KEV_KEY_S               KeyCode::S
#define KEV_KEY_T               KeyCode::T
#define KEV_KEY_U               KeyCode::U
#define KEV_KEY_V               KeyCode::V
#define KEV_KEY_W               KeyCode::W
#define KEV_KEY_X               KeyCode::X
#define KEV_KEY_Y               KeyCode::Y
#define KEV_KEY_Z               KeyCode::Z
#define KEV_KEY_LEFT_BRACKET    KeyCode::LeftBracket   /* [ */
#define KEV_KEY_BACKSLASH       KeyCode::Backslash     /* \ */
#define KEV_KEY_RIGHT_BRACKET   KeyCode::RightBracket  /* ] */
#define KEV_KEY_GRAVE_ACCENT    KeyCode::GraveAccent   /* ` */

/* Function keys */
#define KEV_KEY_ESCAPE          KeyCode::Escape
#define KEV_KEY_ENTER           KeyCode::Enter
#define KEV_KEY_TAB             KeyCode::Tab
#define KEV_KEY_BACKSPACE       KeyCode::Backspace
#define KEV_KEY_INSERT          KeyCode::Insert
#define KEV_KEY_DELETE          KeyCode::Delete
#define KEV_KEY_RIGHT           KeyCode::Right
#define KEV_KEY_LEFT            KeyCode::Left
#define KEV_KEY_DOWN            KeyCode::Down
#define KEV_KEY_UP              KeyCode::Up
#define KEV_KEY_PAGE_UP         KeyCode::PageUp
#define KEV_KEY_PAGE_DOWN       KeyCode::PageDown
#define KEV_KEY_HOME            KeyCode::Home
#define KEV_KEY_END             KeyCode::End
#define KEV_KEY_CAPS_LOCK       KeyCode::CapsLock
#define KEV_KEY_SCROLL_LOCK     KeyCode::ScrollLock
#define KEV_KEY_NUM_LOCK        KeyCode::NumLock
#define KEV_KEY_PRINT_SCREEN    KeyCode::PrintScreen
#define KEV_KEY_PAUSE           KeyCode::Pause
#define KEV_KEY_F1              KeyCode::F1
#define KEV_KEY_F2              KeyCode::F2
#define KEV_KEY_F3              KeyCode::F3
#define KEV_KEY_F4              KeyCode::F4
#define KEV_KEY_F5              KeyCode::F5
#define KEV_KEY_F6              KeyCode::F6
#define KEV_KEY_F7              KeyCode::F7
#define KEV_KEY_F8              KeyCode::F8
#define KEV_KEY_F9              KeyCode::F9
#define KEV_KEY_F10             KeyCode::F10
#define KEV_KEY_F11             KeyCode::F11
#define KEV_KEY_F12             KeyCode::F12
#define KEV_KEY_F13             KeyCode::F13
#define KEV_KEY_F14             KeyCode::F14
#define KEV_KEY_F15             KeyCode::F15
#define KEV_KEY_F16             KeyCode::F16
#define KEV_KEY_F17             KeyCode::F17
#define KEV_KEY_F18             KeyCode::F18
#define KEV_KEY_F19             KeyCode::F19
#define KEV_KEY_F20             KeyCode::F20
#define KEV_KEY_F21             KeyCode::F21
#define KEV_KEY_F22             KeyCode::F22
#define KEV_KEY_F23             KeyCode::F23
#define KEV_KEY_F24             KeyCode::F24
#define KEV_KEY_F25             KeyCode::F25

/* Keypad */
#define KEV_KEY_KP_0            KeyCode::KP0
#define KEV_KEY_KP_1            KeyCode::KP1
#define KEV_KEY_KP_2            KeyCode::KP2
#define KEV_KEY_KP_3            KeyCode::KP3
#define KEV_KEY_KP_4            KeyCode::KP4
#define KEV_KEY_KP_5            KeyCode::KP5
#define KEV_KEY_KP_6            KeyCode::KP6
#define KEV_KEY_KP_7            KeyCode::KP7
#define KEV_KEY_KP_8            KeyCode::KP8
#define KEV_KEY_KP_9            KeyCode::KP9
#define KEV_KEY_KP_DECIMAL      KeyCode::KPDecimal
#define KEV_KEY_KP_DIVIDE       KeyCode::KPDivide
#define KEV_KEY_KP_MULTIPLY     KeyCode::KPMultiply
#define KEV_KEY_KP_SUBTRACT     KeyCode::KPSubtract
#define KEV_KEY_KP_ADD          KeyCode::KPAdd
#define KEV_KEY_KP_ENTER        KeyCode::KPEnter
#define KEV_KEY_KP_EQUAL        KeyCode::KPEqual

#define KEV_KEY_LEFT_SHIFT      KeyCode::LeftShift
#define KEV_KEY_LEFT_CONTROL    KeyCode::LeftControl
#define KEV_KEY_LEFT_ALT        KeyCode::LeftAlt
#define KEV_KEY_LEFT_SUPER      KeyCode::LeftSuper

#define KEV_MOUSE_BUTTON_0      KeyCode::MouseLeft
#define KEV_MOUSE_BUTTON_1      KeyCode::MouseRight
#define KEV_MOUSE_BUTTON_2      MouseCode::Button2
#define KEV_MOUSE_BUTTON_3      MouseCode::Button3
#define KEV_MOUSE_BUTTON_4      KeyCode::MouseMiddle
#define KEV_MOUSE_BUTTON_5      MouseCode::Button5
#define KEV_MOUSE_BUTTON_16     KeyCode::MouseX1
#define KEV_MOUSE_BUTTON_17     KeyCode::MouseX2
#define KEV_MOUSE_BUTTON_NEXT	KeyCode::MouseX2
#define KEV_MOUSE_BUTTON_LAST   KeyCode::MouseX1
#define KEV_MOUSE_BUTTON_LEFT   KeyCode::MouseLeft
#define KEV_MOUSE_BUTTON_RIGHT  KeyCode::MouseRight
#define KEV_MOUSE_BUTTON_MIDDLE KeyCode::MouseMiddle

#endif