    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Keys.h                      //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\///
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\///
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\///
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |///
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\____,__\\__\\__\\//\| system     |//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace snow
{

/**
 *	\~english
 *	\brief Keyboard keys
 *	
 *	The enumeration of keyboard keys.
 *	
 *	\~russian
 *	\brief Клавиши клавиатуры
 *	
 *	Перечисление клавиш клавиатуры.
 */
enum class EKey
{
	UNKNOWN = -1,	///< \~english Unknown key \~russian Неизвестная клавиша
	A = 0,			///< \~english A key \~russian Клавиша A (Ф на русской раскладке)
	B,				///< \~english B key \~russian Клавиша B (И на русской раскладке)
	C,				///< \~english C key \~russian Клавиша C (С на русской раскладке)
	D,				///< \~english D key \~russian Клавиша D (В на русской раскладке)
	E,				///< \~english E key \~russian Клавиша E (У на русской раскладке)
	F,				///< \~english F key \~russian Клавиша F (А на русской раскладке)
	G,				///< \~english G key \~russian Клавиша G (П на русской раскладке)
	H,				///< \~english H key \~russian Клавиша H (Р на русской раскладке)
	I,				///< \~english I key \~russian Клавиша I (Ш на русской раскладке)
	J,				///< \~english J key \~russian Клавиша J (О на русской раскладке)
	K,				///< \~english K key \~russian Клавиша K (Л на русской раскладке)
	L,				///< \~english L key \~russian Клавиша L (Д на русской раскладке)
	M,				///< \~english M key \~russian Клавиша M (М на русской раскладке)
	N,				///< \~english N key \~russian Клавиша N (Т на русской раскладке)
	O,				///< \~english O key \~russian Клавиша O (Щ на русской раскладке)
	P,				///< \~english P key \~russian Клавиша P (З на русской раскладке)
	Q,				///< \~english Q key \~russian Клавиша Q (Й на русской раскладке)
	R,				///< \~english R key \~russian Клавиша R (К на русской раскладке)
	S,				///< \~english S key \~russian Клавиша S (Ы на русской раскладке)
	T,				///< \~english T key \~russian Клавиша T (Е на русской раскладке)
	U,				///< \~english U key \~russian Клавиша U (Г на русской раскладке)
	V,				///< \~english V key \~russian Клавиша V (М на русской раскладке)
	W,				///< \~english W key \~russian Клавиша W (Ц на русской раскладке)
	X,				///< \~english X key \~russian Клавиша X (Ч на русской раскладке)
	Y,				///< \~english Y key \~russian Клавиша Y (Н на русской раскладке)
	Z,				///< \~english Z key \~russian Клавиша Z (Я на русской раскладке)
	SPACE,			///< \~english Space key \~russian Клавиша пробела
	BACKSPACE,		///< \~english Backspace key \~russian Клавиша Backspace
	ONE,			///< \~english 1 key \~russian Клавиша 1
	TWO,			///< \~english 2 key \~russian Клавиша 2
	THREE,			///< \~english 3 key \~russian Клавиша 3
	FOUR,			///< \~english 4 key \~russian Клавиша 4
	FIVE,			///< \~english 5 key \~russian Клавиша 5
	SIX,			///< \~english 6 key \~russian Клавиша 6
	SEVEN,			///< \~english 7 key \~russian Клавиша 7
	EIGHT,			///< \~english 8 key \~russian Клавиша 8
	NINE,			///< \~english 9 key \~russian Клавиша 9
	ZERO,			///< \~english 0 key \~russian Клавиша 0
	MINUS,			///< \~english - key \~russian Клавиша -
	EQUAL,			///< \~english = key \~russian Клавиша =
	F1,				///< \~english F1 key \~russian Клавиша F1
	F2,				///< \~english F2 key \~russian Клавиша F2
	F3,				///< \~english F3 key \~russian Клавиша F3
	F4,				///< \~english F4 key \~russian Клавиша F4
	F5,				///< \~english F5 key \~russian Клавиша F5
	F6,				///< \~english F6 key \~russian Клавиша F6
	F7,				///< \~english F7 key \~russian Клавиша F7
	F8,				///< \~english F8 key \~russian Клавиша F8
	F9,				///< \~english F9 key \~russian Клавиша F9
	F10,			///< \~english F10 key \~russian Клавиша F10
	F11,			///< \~english F11 key \~russian Клавиша F11
	F12,			///< \~english F12 key \~russian Клавиша F12
	TILDE,			///< \~english ~ key \~russian Клавиша ~ (Ё на русской раскладке)
	ESC,			///< \~english Escape key \~russian Клавиша Escape
	TAB,			///< \~english Tabulation key \~russian Клавиша табуляции
	L_SHIFT,		///< \~english Left shift key \~russian Клавиша левый Shift
	R_SHIFT,		///< \~english Right shift key \~russian Клавиша правый Shift
	L_CTRL,			///< \~english Left control key \~russian Клавиша левый Ctrl
	R_CTRL,			///< \~english Right control key \~russian Клавиша правый Ctrl
	L_ALT,			///< \~english Left alt key \~russian Клавиша левый Alt
	R_ALT,			///< \~english Right alt key \~russian Клавиша правый Alt
	WIN,			///< \~english Windows key \~russian Клавиша Windows
	ENTER,			///< \~english Enter (Return) key \~russian Клавиша Enter (Return)
	LEFT,			///< \~english Left arrow \~russian Cтрелка влево
	RIGHT,			///< \~english Right arrow \~russian Cтрелка право
	UP,				///< \~english Up arrow \~russian Cтрелка вверх
	DOWN,			///< \~english Down arrow \~russian Cтрелка вниз
	L_BRACKET,		///< \~english [ key \~russian Клавиша [ (Х на русской раскладке)
	R_BRACKET,		///< \~english ] key \~russian Клавиша ] (Ъ на русской раскладке)
	SEMICOLON,		///< \~english ; key \~russian Клавиша ; (Ж на русской раскладке)
	QUOTE,			///< \~english ' key \~russian Клавиша ' (Э на русской раскладке)
	BACKSLASH,		///< \~english \\ key (backslash) \~russian Клавиша \\ (обратный слеш)
	COMMA,			///< \~english , key \~russian Клавиша , (Б на русской раскладке)
	PERIOD,			///< \~english . key \~russian Клавиша . (Ю на русской раскладке)
	SLASH,			///< \~english / key \~russian Клавиша / (. на русской раскладке)
	HOME,			///< \~english Home key \~russian Клавиша Home
	END,			///< \~english End key \~russian Клавиша End
	PAGE_UP,		///< \~english Page Up key \~russian Клавиша Page Up 
	PAGE_DOWN,		///< \~english Page Down key \~russian Клавиша Page Down
	DELETE,			///< \~english Delete key \~russian Клавиша Delete
	INSERT,			///< \~english Insert key \~russian Клавиша Insert
	PAUSE,			///< \~english Pause key \~russian Клавиша Pause
	MENU,			///< \~english Menu key \~russian Клавиша Menu
	NUM_ADD,		///< \~english + numpad key \~russian Клавиша + на цифровой клавиатуре
	NUM_SUBTRACT,	///< \~english - numpad key \~russian Клавиша - на цифровой клавиатуре
	NUM_MULTIPLY,	///< \~english * numpad key \~russian Клавиша * на цифровой клавиатуре
	NUM_DIVIDE,		///< \~english / numpad key \~russian Клавиша / на цифровой клавиатуре
	NUM_0,			///< \~english 0 numpad key \~russian Клавиша 0 на цифровой клавиатуре
	NUM_1,			///< \~english 1 numpad key \~russian Клавиша 1 на цифровой клавиатуре
	NUM_2,			///< \~english 2 numpad key \~russian Клавиша 2 на цифровой клавиатуре
	NUM_3,			///< \~english 3 numpad key \~russian Клавиша 3 на цифровой клавиатуре
	NUM_4,			///< \~english 4 numpad key \~russian Клавиша 4 на цифровой клавиатуре
	NUM_5,			///< \~english 5 numpad key \~russian Клавиша 5 на цифровой клавиатуре
	NUM_6,			///< \~english 6 numpad key \~russian Клавиша 6 на цифровой клавиатуре
	NUM_7,			///< \~english 7 numpad key \~russian Клавиша 7 на цифровой клавиатуре
	NUM_8,			///< \~english 8 numpad key \~russian Клавиша 8 на цифровой клавиатуре
	NUM_9 			///< \~english 9 numpad key \~russian Клавиша 9 на цифровой клавиатуре
};

/**
 *	\~english
 *	\brief System keys
 *	
 *	The structure with the information about which system keys are pressed.
 *	
 *	\~russian
 *	\brief Системные клавиши
 *	
 *	Структура с информацией о том, какие системы клавиши нажаты.
 */
struct SystemKeys
{
	bool LeftShift : 1;		///< \~english Left Shift \~russian Левый Shift
	bool LeftCtrl : 1;		///< \~english Left Control \~russian Левый Ctrl
	bool LeftAlt : 1;		///< \~english Left Alt \~russian Левый Alt
	bool RightShift : 1;	///< \~english Right Shift \~russian Правый Shift
	bool RightCtrl : 1;		///< \~english Right Control \~russian Правый Ctrl
	bool RightAlt : 1;		///< \~english Right Alt \~russian Правый Alt
	bool Win : 1;			///< \~english Windows \~russian Windows
};

/**
 *	\~english
 *	\brief Mouse button
 *	
 *	The enumeration with mouse buttons.
 *	
 *	\~russian
 *	\brief Кнопки мыши
 *	
 *	Перечисление с кнопками мыши.
 */
enum class EButton
{
	LEFT = 0,	///< \~english Left mouse button \~russian Левая кнопка мыши
	RIGHT,		///< \~english Right mouse button \~russian Правая кнопка мыши
	MIDDLE,		///< \~english Middle mouse button \~russian Средняя кнопка мыши
	EXTRA_1,	///< \~english The first extra mouse button \~russian Первая дополнительная кнопка мыши
	EXTRA_2		///< \~english The second extra mouse button \~russian Вторая дополнительная кнопка мыши
};

sf::Keyboard::Key key_snow_to_sfml(EKey key) noexcept;
EKey key_sfml_to_snow(sf::Keyboard::Key key) noexcept;
sf::Mouse::Button button_snow_to_sfml(EButton button) noexcept;
EButton button_sfml_to_snow(sf::Mouse::Button button) noexcept;

}
