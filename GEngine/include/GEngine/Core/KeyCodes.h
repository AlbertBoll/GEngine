#pragma once
#include <cstdint>

namespace GEngine::Input
{
	using KeyCode = uint16_t;
	

	namespace Key
	{
		typedef enum : KeyCode
		{
            GENGINE_KEY_UNKNOWN = 0,
            GENGINE_KEY_A = 4,
            GENGINE_KEY_B = 5,
            GENGINE_KEY_C = 6,
            GENGINE_KEY_D = 7,
            GENGINE_KEY_E = 8,
            GENGINE_KEY_F = 9,
            GENGINE_KEY_G = 10,
            GENGINE_KEY_H = 11,
            GENGINE_KEY_I = 12,
            GENGINE_KEY_J = 13,
            GENGINE_KEY_K = 14,
            GENGINE_KEY_L = 15,
            GENGINE_KEY_M = 16,
            GENGINE_KEY_N = 17,
            GENGINE_KEY_O = 18,
            GENGINE_KEY_P = 19,
            GENGINE_KEY_Q = 20,
            GENGINE_KEY_R = 21,
            GENGINE_KEY_S = 22,
            GENGINE_KEY_T = 23,
            GENGINE_KEY_U = 24,
            GENGINE_KEY_V = 25,
            GENGINE_KEY_W = 26,
            GENGINE_KEY_X = 27,
            GENGINE_KEY_Y = 28,
            GENGINE_KEY_Z = 29,

            GENGINE_KEY_1 = 30,
            GENGINE_KEY_2 = 31,
            GENGINE_KEY_3 = 32,
            GENGINE_KEY_4 = 33,
            GENGINE_KEY_5 = 34,
            GENGINE_KEY_6 = 35,
            GENGINE_KEY_7 = 36,
            GENGINE_KEY_8 = 37,
            GENGINE_KEY_9 = 38,
            GENGINE_KEY_0 = 39,

            GENGINE_KEY_RETURN = 40,
            GENGINE_KEY_ESCAPE = 41,
            GENGINE_KEY_BACKSPACE = 42,
            GENGINE_KEY_TAB = 43,
            GENGINE_KEY_SPACE = 44,

            GENGINE_KEY_MINUS = 45,
            GENGINE_KEY_EQUALS = 46,
            GENGINE_KEY_LEFTBRACKET = 47,
            GENGINE_KEY_RIGHTBRACKET = 48,
            GENGINE_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                          *   key on ISO keyboards and at the right end
                                          *   of the QWERTY row on ANSI keyboards.
                                          *   Produces REVERSE SOLIDUS (backslash) and
                                          *   VERTICAL LINE in a US layout, REVERSE
                                          *   SOLIDUS and VERTICAL LINE in a UK Mac
                                          *   layout, NUMBER SIGN and TILDE in a UK
                                          *   Windows layout, DOLLAR SIGN and POUND SIGN
                                          *   in a Swiss German layout, NUMBER SIGN and
                                          *   APOSTROPHE in a German layout, GRAVE
                                          *   ACCENT and POUND SIGN in a French Mac
                                          *   layout, and ASTERISK and MICRO SIGN in a
                                          *   French Windows layout.
                                          */
            GENGINE_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                          *   instead of 49 for the same key, but all
                                          *   OSes I've seen treat the two codes
                                          *   identically. So, as an implementor, unless
                                          *   your keyboard generates both of those
                                          *   codes and your OS treats them differently,
                                          *   you should generate GENGINE_KEY_BACKSLASH
                                          *   instead of this code. As a user, you
                                          *   should not rely on this code because SDL
                                          *   will never generate it with most (all?)
                                          *   keyboards.
                                          */
            GENGINE_KEY_SEMICOLON = 51,
            GENGINE_KEY_APOSTROPHE = 52,
            GENGINE_KEY_GRAVE = 53,     /**< Located in the top left corner (on both ANSI
                                          *   and ISO keyboards). Produces GRAVE ACCENT and
                                          *   TILDE in a US Windows layout and in US and UK
                                          *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                                          *   and NOT SIGN in a UK Windows layout, SECTION
                                          *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                          *   layouts on ISO keyboards, SECTION SIGN and
                                          *   DEGREE SIGN in a Swiss German layout (Mac:
                                          *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                                          *   DEGREE SIGN in a German layout (Mac: only on
                                          *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                          *   French Windows layout, COMMERCIAL AT and
                                          *   NUMBER SIGN in a French Mac layout on ISO
                                          *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                          *   SIGN in a Swiss German, German, or French Mac
                                          *   layout on ANSI keyboards.
                                          */
            GENGINE_KEY_COMMA = 54,
            GENGINE_KEY_PERIOD = 55,
            GENGINE_KEY_SLASH = 56,
            
            GENGINE_KEY_CAPSLOCK = 57,
            
            GENGINE_KEY_F1 = 58,
            GENGINE_KEY_F2 = 59,
            GENGINE_KEY_F3 = 60,
            GENGINE_KEY_F4 = 61,
            GENGINE_KEY_F5 = 62,
            GENGINE_KEY_F6 = 63,
            GENGINE_KEY_F7 = 64,
            GENGINE_KEY_F8 = 65,
            GENGINE_KEY_F9 = 66,
            GENGINE_KEY_F10 = 67,
            GENGINE_KEY_F11 = 68,
            GENGINE_KEY_F12 = 69,
            
            GENGINE_KEY_PRINTSCREEN = 70,
            GENGINE_KEY_SCROLLLOCK = 71,
            GENGINE_KEY_PAUSE = 72,
            GENGINE_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                                                     does send code 73, not 117) */
            GENGINE_KEY_HOME = 74,
            GENGINE_KEY_PAGEUP = 75,
            GENGINE_KEY_DELETE = 76,
            GENGINE_KEY_END = 77,
            GENGINE_KEY_PAGEDOWN = 78,
            GENGINE_KEY_RIGHT = 79,
            GENGINE_KEY_LEFT = 80,
            GENGINE_KEY_DOWN = 81,
            GENGINE_KEY_UP = 82,
            
            GENGINE_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                                                                                      */
            GENGINE_KEY_KP_DIVIDE = 84,
            GENGINE_KEY_KP_MULTIPLY = 85,
            GENGINE_KEY_KP_MINUS = 86,
            GENGINE_KEY_KP_PLUS = 87,
            GENGINE_KEY_KP_ENTER = 88,
            GENGINE_KEY_KP_1 = 89,
            GENGINE_KEY_KP_2 = 90,
            GENGINE_KEY_KP_3 = 91,
            GENGINE_KEY_KP_4 = 92,
            GENGINE_KEY_KP_5 = 93,
            GENGINE_KEY_KP_6 = 94,
            GENGINE_KEY_KP_7 = 95,
            GENGINE_KEY_KP_8 = 96,
            GENGINE_KEY_KP_9 = 97,
            GENGINE_KEY_KP_0 = 98,
            GENGINE_KEY_KP_PERIOD = 99,
            
            GENGINE_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                               *   keyboards have over ANSI ones,
                                               *   located between left shift and Y.
                                               *   Produces GRAVE ACCENT and TILDE in a
                                               *   US or UK Mac layout, REVERSE SOLIDUS
                                               *   (backslash) and VERTICAL LINE in a
                                               *   US or UK Windows layout, and
                                               *   LESS-THAN SIGN and GREATER-THAN SIGN
                                               *   in a Swiss German, German, or French
                                               *   layout. */
            GENGINE_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
            GENGINE_KEY_POWER = 102,       /**< The USB document says this is a status flag,
                                            *   not a physical key - but some Mac keyboards
                                            *   do have a power key. */
            GENGINE_KEY_KP_EQUALS = 103,
            GENGINE_KEY_F13 = 104,
            GENGINE_KEY_F14 = 105,
            GENGINE_KEY_F15 = 106,
            GENGINE_KEY_F16 = 107,
            GENGINE_KEY_F17 = 108,
            GENGINE_KEY_F18 = 109,
            GENGINE_KEY_F19 = 110,
            GENGINE_KEY_F20 = 111,
            GENGINE_KEY_F21 = 112,
            GENGINE_KEY_F22 = 113,
            GENGINE_KEY_F23 = 114,
            GENGINE_KEY_F24 = 115,
            GENGINE_KEY_EXECUTE = 116,
            GENGINE_KEY_HELP = 117,
            GENGINE_KEY_MENU = 118,
            GENGINE_KEY_SELECT = 119,
            GENGINE_KEY_STOP = 120,
            GENGINE_KEY_AGAIN = 121,   /**< redo */
            GENGINE_KEY_UNDO = 122,
            GENGINE_KEY_CUT = 123,
            GENGINE_KEY_COPY = 124,
            GENGINE_KEY_PASTE = 125,
            GENGINE_KEY_FIND = 126,
            GENGINE_KEY_MUTE = 127,
            GENGINE_KEY_VOLUMEUP = 128,
            GENGINE_KEY_VOLUMEDOWN = 129,
            
            GENGINE_KEY_LOCKINGCAPSLOCK = 130,
            GENGINE_KEY_LOCKINGNUMLOCK = 131,
            GENGINE_KEY_LOCKINGSCROLLLOCK = 132,
            GENGINE_KEY_KP_COMMA = 133,
            GENGINE_KEY_KP_EQUALSAS400 = 134,
            
            GENGINE_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
            footnotes in USB doc */
            GENGINE_KEY_INTERNATIONAL2 = 136,
            GENGINE_KEY_INTERNATIONAL3 = 137, /**< Yen */
            GENGINE_KEY_INTERNATIONAL4 = 138,
            GENGINE_KEY_INTERNATIONAL5 = 139,
            GENGINE_KEY_INTERNATIONAL6 = 140,
            GENGINE_KEY_INTERNATIONAL7 = 141, 
            GENGINE_KEY_INTERNATIONAL8 = 142,
            GENGINE_KEY_INTERNATIONAL9 = 143,
            GENGINE_KEY_LANG1 = 144, /**< Hangul/English toggle */
            GENGINE_KEY_LANG2 = 145, /**< Hanja conversion */
            GENGINE_KEY_LANG3 = 146, /**< Katakana */
            GENGINE_KEY_LANG4 = 147, /**< Hiragana */
            GENGINE_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
            GENGINE_KEY_LANG6 = 149, /**< reserved */
            GENGINE_KEY_LANG7 = 150, /**< reserved */
            GENGINE_KEY_LANG8 = 151, /**< reserved */
            GENGINE_KEY_LANG9 = 152, /**< reserved */
            GENGINE_KEY_ALTERASE = 153, /**< Erase-Eaze */
            GENGINE_KEY_SYSREQ = 154,
            GENGINE_KEY_CANCEL = 155,
            GENGINE_KEY_CLEAR = 156,
            GENGINE_KEY_PRIOR = 157,
            GENGINE_KEY_RETURN2 = 158,
            GENGINE_KEY_SEPARATOR = 159,
            GENGINE_KEY_OUT = 160,
            GENGINE_KEY_OPER = 161,
            GENGINE_KEY_CLEARAGAIN = 162,
            GENGINE_KEY_CRSEL = 163,
            GENGINE_KEY_EXSEL = 164,
            GENGINE_KEY_KP_00 = 176,
            GENGINE_KEY_KP_000 = 177,
            GENGINE_KEY_THOUSANDSSEPARATOR = 178,
            GENGINE_KEY_DECIMALSEPARATOR = 179,
            GENGINE_KEY_CURRENCYUNIT = 180,
            GENGINE_KEY_CURRENCYSUBUNIT = 181,
            GENGINE_KEY_KP_LEFTPAREN = 182,
            GENGINE_KEY_KP_RIGHTPAREN = 183,
            GENGINE_KEY_KP_LEFTBRACE = 184,
            GENGINE_KEY_KP_RIGHTBRACE = 185,
            GENGINE_KEY_KP_TAB = 186,
            GENGINE_KEY_KP_BACKSPACE = 187,
            GENGINE_KEY_KP_A = 188,
            GENGINE_KEY_KP_B = 189,
            GENGINE_KEY_KP_C = 190,
            GENGINE_KEY_KP_D = 191,
            GENGINE_KEY_KP_E = 192,
            GENGINE_KEY_KP_F = 193,
            GENGINE_KEY_KP_XOR = 194,
            GENGINE_KEY_KP_POWER = 195,
            GENGINE_KEY_KP_PERCENT = 196,
            GENGINE_KEY_KP_LESS = 197,
            GENGINE_KEY_KP_GREATER = 198,
            GENGINE_KEY_KP_AMPERSAND = 199,
            GENGINE_KEY_KP_DBLAMPERSAND = 200,
            GENGINE_KEY_KP_VERTICALBAR = 201,
            GENGINE_KEY_KP_DBLVERTICALBAR = 202,
            GENGINE_KEY_KP_COLON = 203,
            GENGINE_KEY_KP_HASH = 204,
            GENGINE_KEY_KP_SPACE = 205,
            GENGINE_KEY_KP_AT = 206,
            GENGINE_KEY_KP_EXCLAM = 207,
            GENGINE_KEY_KP_MEMSTORE = 208,
            GENGINE_KEY_KP_MEMRECALL = 209,
            GENGINE_KEY_KP_MEMCLEAR = 210,
            GENGINE_KEY_KP_MEMADD = 211,
            GENGINE_KEY_KP_MEMSUBTRACT = 212,
            GENGINE_KEY_KP_MEMMULTIPLY = 213,
            GENGINE_KEY_KP_MEMDIVIDE = 214,
            GENGINE_KEY_KP_PLUSMINUS = 215,
            GENGINE_KEY_KP_CLEAR = 216,
            GENGINE_KEY_KP_CLEARENTRY = 217,
            GENGINE_KEY_KP_BINARY = 218,
            GENGINE_KEY_KP_OCTAL = 219,
            GENGINE_KEY_KP_DECIMAL = 220,
            GENGINE_KEY_KP_HEXADECIMAL = 221,
            GENGINE_KEY_LCTRL = 224,
            GENGINE_KEY_LSHIFT = 225,
            GENGINE_KEY_LALT = 226, /**< alt, option */
            GENGINE_KEY_LGUI = 227, /**< windows, command (apple), meta */
            GENGINE_KEY_RCTRL = 228,
            GENGINE_KEY_RSHIFT = 229,
            GENGINE_KEY_RALT = 230, /**< alt gr, option */
            GENGINE_KEY_RGUI = 231, /**< windows, command (apple), meta */
            GENGINE_KEY_MODE = 257,
            GENGINE_KEY_AUDIONEXT = 258,
            GENGINE_KEY_AUDIOPREV = 259,
            GENGINE_KEY_AUDIOSTOP = 260,
            GENGINE_KEY_AUDIOPLAY = 261,
            GENGINE_KEY_AUDIOMUTE = 262,
            GENGINE_KEY_MEDIASELECT = 263,
            GENGINE_KEY_WWW = 264,
            GENGINE_KEY_MAIL = 265,
            GENGINE_KEY_CALCULATOR = 266,
            GENGINE_KEY_COMPUTER = 267,
            GENGINE_KEY_AC_SEARCH = 268,
            GENGINE_KEY_AC_HOME = 269,
            GENGINE_KEY_AC_BACK = 270,
            GENGINE_KEY_AC_FORWARD = 271,
            GENGINE_KEY_AC_STOP = 272,
            GENGINE_KEY_AC_REFRESH = 273,
            GENGINE_KEY_AC_BOOKMARKS = 274,
            GENGINE_KEY_BRIGHTNESSDOWN = 275,
            GENGINE_KEY_BRIGHTNESSUP = 276,
            GENGINE_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display                                     switch, video mode switch */
            GENGINE_KEY_KBDILLUMTOGGLE = 278,
            GENGINE_KEY_KBDILLUMDOWN = 279,
            GENGINE_KEY_KBDILLUMUP = 280,
            GENGINE_KEY_EJECT = 281,
            GENGINE_KEY_SLEEP = 282,
            GENGINE_KEY_APP1 = 283,
            GENGINE_KEY_APP2 = 284,
            GENGINE_KEY_AUDIOREWIND = 285,
            GENGINE_KEY_AUDIOFASTFORWARD = 286,
            GENGINE_NUM_SCANCODES = 512  //Set Key upper board
            
        } GEngineKeyCode;
    }

}
            
    