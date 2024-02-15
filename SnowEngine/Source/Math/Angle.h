    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

namespace snow
{

class Point2;
class Point3;

/**
 *	\addtogroup Math
 *	\{
 */

/**
 *	\~english
 *	\brief The class for angles
 *	
 *	SnowEngine angle class. Supports degrees, radians and gradians. You can use literals to create
 *	an angle:
 *	\code
 *		Angle angle1 = 90_deg;
 *		Angle angle2 = angle1 - 50.5_grad;
 *		Angle angle3(90_deg + 3.1415_rad);
 *	\endcode
 *	You can also use the constants `Angle::ZERO`, `Angle::RIGHT`, and `Angle::STRAIGHT`.
 *	
 *	\~russian
 *	\brief Класс угла
 *
 *	Класс угла, используемый SnowEngine. Поддерживает задание в градусах, радианах и градах. Чтобы
 *	создать угол, можно использовать литералы `_deg` для градусов, `_rad` для радиан и `_grad`
 *	для градов:
 *	\code
 *		Angle angle1 = 90_deg;
 *		Angle angle2 = angle1 - 50.5_grad;
 *		Angle angle3(90_deg + 3.1415_rad);
 *	\endcode
 *	Вы также можете использовать константы `Angle::ZERO`, `Angle::RIGHT` и `Angle::STRAIGHT`.
 */
class Angle : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a zero angle.
	 *
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *
	 *	Создаёт нулевой угол.
	 */
	Angle();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the angle.
	 *	\param angle The angle that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует угол.
	 *	\param angle Угол, который будет скопирован.
	 */
	Angle(const Angle& angle);

	/**
	 *	\~english
	 *	\brief Creates an angle with the specified value in degrees
	 *	
	 *	The constructor that creates an angle with the specified value in degrees.
	 *	\warning This constructor is not recommended to be used. The better way to create an angle
	 *	is using literals or setters. They help you not to get confused in units of measurement:
	 *	\code
	 *		Angle angle1 = 90_deg;
	 *		
	 *		double radians_value = 3.1415;
	 *		Angle angle2;
	 *		angle2.set_radians(radians_value);
	 *		
	 *		Angle angle3;
	 *		angle3.set_radians(math::PI);
	 *		
	 *		Angle angle4(1.2); // Degrees? Radians? Gradians?
	 *	\endcode
	 *	\param degrees A value of a new angle in degrees
	 *
	 *	\~russian
	 *	\brief Создаёт угол с заданным в градусах значением
	 *
	 *	Конструктор, создающий угол с заданным в градусах значением.
	 *	\warning Не рекомендуется использовать этот конструктор. Лучше создавать угол с
	 *	использованием литералов или функций-сеттеров. Они помогут вам не запутаться с единицами
	 *	измерения:
	 *	\code
	 *		Angle angle1 = 90_deg;
	 *
	 *		double radians_value = 3.1415;
	 *		Angle angle2;
	 *		angle2.set_radians(radians_value);
	 *
	 *		Angle angle3;
	 *		angle3.set_radians(math::PI);
	 *		
	 *		Angle angle4(1.2); // Градусы? Радианы? Грады?
	 *	\endcode
	 *	\param degrees Значение нового угла в градусах.
	 */
	Angle(double degrees);

	/**
	 *	\~english
	 *	\brief Creates a new angle from the JSON element
	 *
	 *	Creates an angle using a value contained in the passed JSON element. It must be either a
	 *	double or integer value (the angle in degrees) or the object containing a single field. Its
	 *	key must be `deg`, `rad` or `grad`, its value must be a double or integer value
	 *	representing the angle value in degrees, radians or gradians respectively.
	 *	\code
	 *		Angle first(json::Element::from_string(L"45")); // 45°
	 *		Angle second(json::Element::from_string(L"{ \"deg\": 30 }")); // 30°
	 *		Angle third(json::Element::from_string(L"{ \"rad\": 3.1415 }")); // 360°
	 *		Angle fourth(json::Element::from_string(L"{ \"grad\": 100 }")); // 90°
	 *	\endcode
	 *	\param json The JSON element with the value of a new angle.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *
	 *	\~russian
	 *	\breif Создаёт новый угол из элемента JSON
	 *
	 *	Создаёт угол, используя значение, содержащееся в переданном элементе JSON. Этот элемент
	 *	должен быть либо вещественным или целочисленным значением (угол в градусах), либо объектом,
	 *	содержащим единственное поле. Его ключом должно быть `deg`, `rad` или `grad`, а значением —
	 *	вещественное или целочисленное значение, представляющее собой значение угла в градусах,
	 *	радианах или градианах соответственно.
	 *	\code
	 *		Angle first(json::Element::from_string(L"45")); // 45°
	 *		Angle second(json::Element::from_string(L"{ \"deg\": 30 }")); // 30°
	 *		Angle third(json::Element::from_string(L"{ \"rad\": 3.1415 }")); // 360°
	 *		Angle fourth(json::Element::from_string(L"{ \"grad\": 100 }")); // 90°
	 *	\endcode
	 *	\param json Элемент JSON со значением нового угла.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	Angle(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief Creates an angle formed by three 2D-points
	 *	
	 *	Creates a new angle by connecting three 2D-points. The angle is between 0° and 180°.
	 *	\param vertex The vertex of the angle.
	 *	\param a The first point.
	 *	\param b The second point.
	 *	\throw std::domain_error a or b coinsides with the vertex.
	 *	
	 *	\~russian
	 *	\brief Создаёт угол, образованный тремя двумерными точками
	 *	
	 *	Создаёт новый угол, соединяя три двумерные точки. Угол лежит между 0° и 180°.
	 *	\param vertex Вершина угла.
	 *	\param a Первая точка.
	 *	\param b Вторая точка.
	 *	\throw std::domain_error a или b совпадает с вершиной.
	 */
	Angle(Point2 vertex, Point2 a, Point2 b);

	/**
	 *	\~english
	 *	\brief Creates an angle formed by three 3D-points
	 *	
	 *	Creates a new angle by connecting three 3D-points. The angle is between 0° and 180°.
	 *	\param vertex The vertex of the angle.
	 *	\param a The first point.
	 *	\param b The second point.
	 *	\throw std::domain_error a or b coinsides with the vertex.
	 *	
	 *	\~russian
	 *	\brief Создаёт угол, образованный тремя трёхмерными точками
	 *	
	 *	Создаёт новый угол, соединяя три трёхмерные точки. Угол лежит между 0° и 180°.
	 *	\param vertex Вершина угла.
	 *	\param a Первая точка.
	 *	\param b Вторая точка.
	 *	\throw std::domain_error a или b совпадает с вершиной.
	 */
	Angle(Point3 vertex, Point3 a, Point3 b);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the angle into a string
	 *
	 *	Creates a string with the angle value in degrees.
	 *	\return A string with the angle value.
	 *
	 *	\~russian
	 *	\brief Конвертирует угол в строку
	 *
	 *	Создаёт строку с величиной угла в градусах.
	 *	\return Строка, содержащая величину угла.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the angle into a JSON element
	 *
	 *	Creates a JSON object with a single field. Its key is `deg`, its value is the angle value
	 *	in degrees.
	 *	\return The JSON object with the angle value.
	 *
	 *	\~russian
	 *	\brief Конвертирует угол в элемент JSON
	 *
	 *	Создаёт объект JSON с единственным полем. Его ключ — `deg`, а значение — значение угла в
	 *	градусах.
	 *	\return Объект JSON со значением угла.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The angle value in degrees
	 *	
	 *	Allows to get the angle value in degrees.
	 *	\return The angle value in degrees.
	 *
	 *	\~russian
	 *	\brief Величина угла в градусах
	 *
	 *	Позволяет получить значение угла в градусах.
	 *	\return Значение угла в градусах.
	 */
	double get_degrees() const noexcept;

	/**
	 *	\~english
	 *	\brief The angle value in radians
	 *
	 *	Allows to get the angle value in radians.
	 *	\return The angle value in radians.
	 *
	 *	\~russian
	 *	\brief Величина угла в радианах
	 *
	 *	Позволяет получить значение угла в радианах.
	 *	\return Величина угла в радианах.
	 */
	double get_radians() const noexcept;

	/**
	 *	\~english
	 *	\brief The angle value in gradians
	 *
	 *	Allows to get the angle value in gradians.
	 *	\return The angle value in gradians.
	 *	
	 *	\~russian
	 *	\brief Величина угла в градах
	 *
	 *	Позволяет получить значение угла в градах.
	 *	\return Величина угла в градах.
	 */
	double get_gradians() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the angle value in degrees
	 *	
	 *	Allows to change the angle value.
	 *	\param degrees The new angle value in degrees.
	 *	
	 *	\~russian
	 *	\brief Устанавливает величину угла в градусах
	 *
	 *	Позволяет изменить величину угла.
	 *	\param degrees Новая величина угла в градусах.
	 */
	void set_degrees(double degrees) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the angle value in radians
	 *
	 *	Allows to change the angle value.
	 *	\param radians The new angle value in radians.
	 *
	 *	\~russian
	 *	\brief Устанавливает величину угла в радианах
	 *
	 *	Позволяет изменить величину угла.
	 *	\param radians Новая величина угла в радианах.
	 */
	void set_radians(double radians) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the angle value in gradians
	 *
	 *	Allows to change the angle value.
	 *	\param gradians The new angle value in gradians.
	 *
	 *	\~russian
	 *	\brief Устанавливает величину угла в градах
	 *
	 *	Позволяет изменить величину угла.
	 *	\param gradians Новая величина угла в градах.
	 */
	void set_gradians(double gradians) noexcept;

	/**
	 *	\~english
	 *	\brief Normalizes an angle value so that it is inside \f$[0°, 360°)\f$
	 *
	 *	Changes an angle value to the equivalent that it is inside the interval \f$[0°, 360°)\f$.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_360(); // Now angle1 == 30_deg;
	 *		
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_360(); // Now angle2 == 270_deg;
	 *		
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_360(); // Now angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_360(); // Now angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_360(); // Now angle5 == 270_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_360(); // Now angle6 == 90_deg;
	 *	\endcode
	 *	\return A reference to itself.
	 *	\sa
	 *	- `normalize_180()`
	 *	- `normalize_90()`
	 *	- `get_normalized_360()`
	 *
	 *	\~russian
	 *	\brief Нормализует величину угла, чтобы она попадала в полуинтервал \f$[0°; 360°)\f$
	 *
	 *	Изменяет величину угла на эквивалентную, лежащую в полуинтервале \f$[0°; 360°)\f$.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_360(); // Теперь angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_360(); // Теперь angle2 == 270_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_360(); // Теперь angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_360(); // Теперь angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_360(); // Теперь angle5 == 270_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_360(); // Теперь angle6 == 90_deg;
	 *	\endcode
	 *	\return Ссылка на себя.
	 *	\sa
	 *	- `normalize_180()`
	 *	- `normalize_90()`
	 *	- `get_normalized_360()`
	 */
	Angle& normalize_360();

	/**
	 *	\~english
	 *	\brief Normalizes an angle value so that it is inside \f$(-180°, 180°]\f$
	 *
	 *	Changes an angle value to the equivalien that it is inside the interval
	 *	\f$(-180°, 180°]\f$.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_180(); // Now angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_180(); // Now angle2 == -90_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_180(); // Now angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_180(); // Now angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_180(); // Now angle5 == -90_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_180(); // Now angle6 == 90_deg;
	 *	\endcode
	 *	\return A reference to itself.
	 *	\sa
	 *	- `normalize_360()`
	 *	- `normalize_90()`
	 *	- `get_normalized_180()`

	 *	\~russian
	 *	\brief Нормализует величину угла, чтобы она попадала в полуинтервал \f$(-180°; 180°]\f$
	 *
	 *	Изменяет величину угла на эквивалентную, лежащую в полуинтервале \f$(-180°; 180°]\f$.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_180(); // Теперь angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_180(); // Теперь angle2 == -90_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_180(); // Теперь angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_180(); // Теперь angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_180(); // Теперь angle5 == -90_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_180(); // Теперь angle6 == 90_deg;
	 *	\endcode
	 *	\return Ссылка на себя.
	 *	\sa
	 *	- `normalize_360()`
	 *	- `normalize_90()`
	 *	- `get_normalized_180()`
	 */
	Angle& normalize_180();

	/**
	 *	\~english
	 *	\brief Normalizes an angle value so that it is inside \f$(-90°, 90°]\f$
	 *
	 *	Changes an angle value to a value inside the interval \f$(-90°, 90°]\f$ so that the tangent
	 *	of the angle doesn't change.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_90(); // Now angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_90(); // Now angle2 == 90_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_90(); // Now angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_90(); // Now angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_90(); // Now angle5 == 90_deg;
	 *
	 *		Angle angle6(100_deg);
	 *		angle6.normalize_90(); // Now angle6 == -80_deg;
	 *		
	 *		Angle angle7(-135_deg);
	 *		angle7.normalize_90(); // Now angle7 == 45_deg;
	 *	\endcode
	 *	\return A reference to itself.
	 *	\sa
	 *	- `normalize_360()`
	 *	- `normalize_180()`
	 *	- `get_normalized_90()`

	 *	\~russian
	 *	\brief Нормализует величину угла, чтобы она попадала в полуинтервал \f$(-90°; 90°]\f$
	 *
	 *	Изменяет величину угла на лежащую в полуинтервале \f$(-90°; 90°]\f$ так, чтобы танегс угла
	 *	при этом не изменился.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_90(); // Теперь angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_90(); // Теперь angle2 == 90_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_90(); // Теперь angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_90(); // Теперь angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_90(); // Теперь angle5 == 90_deg;
	 *
	 *		Angle angle6(100_deg);
	 *		angle6.normalize_90(); // Теперь angle6 == -80_deg;
	 *		
	 *		Angle angle7(-135_deg);
	 *		angle7.normalize_90(); // Теперь angle7 == 45_deg;
	 *	\endcode
	 *	\return Ссылка на себя.
	 *	\sa
	 *	- `normalize_360()`
	 *	- `normalize_180()`
	 *	- `get_normalized_90()`
	 */
	Angle& normalize_90();

	/**
	 *	\~english
	 *	\brief A normalized angle with value inside \f$[0°, 360°)\f$
	 *
	 *	Allows to get an angle that is equivalent to this one, but with a value inside
	 *	\f$[0°, 360°)\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_360() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_360() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_360() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_360() == 90_deg;
	 *	\endcode
	 *	\return A normalized angle.
	 *	\sa
	 *	- `get_normalized_180()`
	 *	- `get_normalized_90()`
	 *	- `normalize_360()`
	 *
	 *	\~russian
	 *	\brief Нормализованный угол со значением в полуинтервале \f$[0°; 360°)\f$
	 *	
	 *	Позволяет получить угол, эквивалентный данному, но со значением в полуинтервале
	 *	\f$[0°; 360°)\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_360() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_360() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_360() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_360() == 90_deg;
	 *	\endcode
	 *	\return Нормализованный угол.
	 *	\sa
	 *	- `get_normalized_180()`
	 *	- `get_normalized_90()`
	 *	- `normalize_360()`
	 */
	const Angle get_normalized_360() const;

	/**
	 *	\~english
	 *	\brief A normalized angle with value inside \f$(-180°, 180°]\f$
	 *
	 *	Allows to get an angle that is equivalent to this one, but with a value inside
	 *	\f$(-180°, 180°]\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_180() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_180() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_180() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_180() == 90_deg;
	 *	\endcode
	 *	\return A normalized angle.
	 *	\sa
	 *	- `get_normalized_360()`
	 *	- `get_normalized_90()`
	 *	- `normalize_180()`
	 *
	 *	\~russian
	 *	\brief Нормализованный угол со значением в полуинтервале \f$(-180°, 180°]\f$
	 *
	 *	Позволяет получить угол, эквивалентный данному, но со значением в полуинтервале
	 *	\f$(-180°, 180°]\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_180() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_180() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_180() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_180() == 90_deg;
	 *	\endcode
	 *	\return Нормализованный угол.
	 *	\sa
	 *	- `get_normalized_360()`
	 *	- `get_normalized_90()`
	 *	- `normalize_180()`
	 */
	const Angle get_normalized_180() const;

	/**
	 *	\~english
	 *	\brief A normalized angle with value inside \f$(-90°, 90°]\f$
	 *
	 *	Allows to get an angle with the same tangent whose value is inside \f$(-90°, 90°]\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_90() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_90() == 90_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_90() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_90() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_90() == 90_deg;
	 *
	 *		Angle angle6(100_deg);
	 *		angle6.get_normalized_90() == -80_deg;
	 *		
	 *		Angle angle7(-135_deg);
	 *		angle7.get_normalized_90() == 45_deg;
	 *	\endcode
	 *	\return A normalized angle.
	 *	\sa
	 *	- `get_normalized_360()`
	 *	- `get_normalized_180()`
	 *	- `normalize_90()`
	 *
	 *	\~russian
	 *	\brief Нормализованный угол со значением в полуинтервале \f$(-90°, 90°]\f$
	 *
	 *	Позволяет получить угол с таким же тангенсом, чьё значение лежит в полуинтервале
	 *	\f$(-90°, 90°]\f$.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_90() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_90() == -90_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_90() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_90() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_90() == -90_deg;
	 *
	 *		Angle angle6(100_deg);
	 *		angle6.get_normalized_90() == -80_deg;
	 *		
	 *		Angle angle7(-135_deg);
	 *		angle7.get_normalized_90() == 45_deg;
	 *	\endcode
	 *	\return Нормализованный угол.
	 *	\sa
	 *	- `get_normalized_360()`
	 *	- `get_normalized_90()`
	 *	- `normalize_90()`
	 */
	const Angle get_normalized_90() const;

	/**
	 *	\~english
	 *	\brief An absolute value of the angle
	 *	
	 *	Allows to get the angle whose value is an absolute value of this angle.
	 *	\return An absolute value of the angle.
	 *
	 *	\~russian
	 *	\brief Модуль угла
	 *
	 *	Позволяет получить угол, значение которого равно модулю значения данного угла.
	 *	\return Модуль угла.
	 */
	const Angle abs() const ;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief Copies an angle
	 *
	 *	Assigns a passed value to the angle.
	 *	\param angle The angle that will be copied.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Копирует угол
	 *
	 *	Присваивает переданное значение углу.
	 *	\param angle Угол, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	Angle& operator=(const Angle& angle) noexcept;
	
	/**
	 *	\~english
	 *	\brief Returns itself
	 *
	 *	Does nothing. I don't know why C++ has a unary plus.
	 *	\code
	 *		angle == +angle;
	 *		30_deg == +30_deg;
	 *	\endcode
	 *	`angle` is l-value, but `+angle` is r-value. Maybe you can think up what to do with this
	 *	information.
	 *	\return A copy of itself.
	 *	
	 *	\~russian
	 *	\brief Возвращает себя
	 *
	 *	Не делает ничего. Я не знаю, зачем в C++ есть унарный плюс.
	 *	\code
	 *		angle == +angle;
	 *		30_deg == +30_deg;
	 *	\endcode
	 *	`angle` — l-value, но `+angle` — r-value. Может, вы сможете придумать, что делать с этой
	 *	информацией.
	 *	\return Копия себя.
	 */
	const Angle operator+() const;

	/**
	 *	\~english
	 *	\brief An angle with an opposite sign
	 *
	 *	Allows to get an angle with an opposite sign:
	 *	\code
	 *		Angle angle(90_deg);
	 *		-angle == -90_deg;
	 *	\endcode
	 *	\return An angle with an opposite sign.
	 *
	 *	\~russian
	 *	\brief Угол с противоположным знаком
	 *
	 *	Позволяет получить угол с противоположным знаком:
	 *	\code
	 *		Angle angle(90_deg);
	 *		-angle == -90_deg;
	 *	\endcode
	 *	\return Угол с противоположным знаком.
	 */
	const Angle operator-() const;

	/**
	 *	\~english
	 *	\brief Adds angles
	 *
	 *	Allows to get the sum of two angles.
	 *	\param angle The second summand.
	 *	\return The sum of two angles.
	 *	
	 *	\~russian
	 *	\brief Складывает углы
	 *
	 *	Позволяет получить сумму двух углов.
	 *	\param angle Второе слагаемое.
	 *	\return Сумма двух углов.
	 */
	const Angle operator+(const Angle& angle) const;

	/**
	 *	\~english
	 *	\brief Subtracts angles
	 *
	 *	Allows to get the difference of two angles.
	 *	\param angle The subtrahend.
	 *	\return The difference of two angles.
	 *
	 *	\~russian
	 *	\brief Вычитает углы
	 *
	 *	Позволяет получить разность двух углов.
	 *	\param angle Вычитаемое.
	 *	\return Разность двух углов.
	 */
	const Angle operator-(const Angle& angle) const;

	/**
	 *	\~english
	 *	\brief Multiplies the angle and a number
	 *
	 *	Allows to get the production of the angle and the number.
	 *	\param value The multiplier.
	 *	\return The product of the angle and the number.
	 *
	 *	\~russian
	 *	\brief Умножает угол на число
	 *
	 *	Позволяет получить произведение угла и числа.
	 *	\param value Множитель.
	 *	\return Произведение угла и числа.
	 */
	const Angle operator*(double value) const;

	/**
	 *	\~english
	 *	\brief Multiplies a number and an angle
	 *
	 *	Allows to get the production of the angle and the number.
	 *	\param value The multiplier.
	 *	\param angle The angle.
	 *	\return The product of the number and the angle.
	 *
	 *	\~russian
	 *	\brief Умножает число на угол
	 *
	 *	Позволяет получить произведение числа и угла.
	 *	\param value Множитель.
	 *	\param angle Угол.
	 *	\return Произведение числа и угла.
	 */
	friend const Angle operator*(double value, const Angle& angle);

	/**
	 *	\~english
	 *	\brief Divides the angle by a number
	 *
	 *	Allows to get the quotient of the angle and the number.
	 *	\param value The divisor.
	 *	\return The quotient of the angle and the number.
	 *	\throw std::domain_error The divisor is equal to zero.
	 *
	 *	\~russian
	 *	\brief Делит угол на число
	 *
	 *	Позволяет получить частное угла и числа.
	 *	\param value Делитель.
	 *	\return Частное угла и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const Angle operator/(double value) const;

	/**
	 *	\~english
	 *	\brief Adds a passed angle to itself
	 *	
	 *	Finds the sum of two angles and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle1 += angle2;
	 *		angle1 = angle1 + angle2;
	 *	\endcode
	 *	\param angle The summand.
	 *	\return A reference to itself.

	 *	\~russian
	 *	\brief Прибавляет к себе переданный угол
	 *	
	 *	Находит сумму двух углов и присаивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		angle1 += angle2;
	 *		angle1 = angle1 + angle2;
	 *	\endcode
	 *	\param angle Слагаемое.
	 *	\return Ссылка на себя.
	 */
	Angle& operator+=(const Angle& angle) noexcept;

	/**
	 *	\~english
	 *	\brief Subtracts a passed angle from itself
	 *
	 *	Finds the difference of two angles and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle1 -= angle2;
	 *		angle1 = angle1 - angle2;
	 *	\endcode
	 *	\param angle The subtrahend.
	 *	\return A reference to itself.

	 *	\~russian
	 *	\brief Вычитает из себя переданный угол
	 *
	 *	Находит разность двух углов и присаивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		angle1 -= angle2;
	 *		angle1 = angle1 - angle2;
	 *	\endcode
	 *	\param angle Вычитаемое.
	 *	\return Ссылка на себя.
	 */
	Angle& operator-=(const Angle& angle) noexcept;
	
	/**
	 *	\~english
	 *	\brief Multiplies itself by a passed number
	 *	
	 *	Finds the product of the angle and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle *= num;
	 *		angle = angle * num;
	 *	\endcode
	 *	\param value The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Умножает себя на переданное число
	 *
	 *	Находит произведение угла на число и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		angle *= num;
	 *		angle = angle * num;
	 *	\endcode
	 *	\param value Множитель.
	 *	\return Ссылка на себя.
	 */
	Angle& operator*=(double value) noexcept;

	/**
	 *	\~english
	 *	\brief Divides itself by a passed number
	 *
	 *	Finds the quotient of the angle and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle /= num;
	 *		angle = angle / num;
	 *	\endcode
	 *	\param value The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error Value is equal to zero.
	 *
	 *	\~russian
	 *	\brief Делит себя на переданное число
	 *
	 *	Находит частное угла и числа и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		angle /= num;
	 *		angle = angle / num;
	 *	\endcode
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	Angle& operator/=(double value);

	/**
	 *	\~english
	 *	\brief Checks whether two angles are equal
	 *
	 *	Checks whether two angles are equal. Note that 0° is not equal to 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 360_deg;
	 *		
	 *		angle1 == angle2; // false
	 *		
	 *		angle1.get_normalized_360() == angle2.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if angles are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два угла
	 *
	 *	Проверяет равны ли два угла. Учтите, что 0° не равно 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle1 == angle2; // false
	 *
	 *		angle1.get_normalized_360() == angle2.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если углы равны, иначе `false`.
	 */
	bool operator==(const Angle& angle) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two angles are different
	 *
	 *	Checks whether two angles are different. Note that 0° is not equal to 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle1 != angle2; // true
	 *		
	 *		angle1 != angle3; // true
	 *
	 *		angle1.get_normalized_360() != angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if angles are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два угла
	 *
	 *	Проверяет различаются ли два угла. Учтите, что 0° не равно 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle1 != angle2; // true
	 *
	 *		angle1 != angle3; // true
	 *
	 *		angle1.get_normalized_360() != angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если углы не равны, иначе `false`.
	 */
	bool operator!=(const Angle& angle) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the angle is less than a passed one
	 *
	 *	Checks whether the angle is less than a passed one. Note that 270° is less than 450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 < angle1; // false
	 *
	 *		angle2 < angle3; // true
	 *
	 *		angle2.get_normalized_360() < angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is less than a passed one, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, меньше ли значение данного угла, чем значение переданного.
	 *
	 *	Проверяет, меньше ли значение данного угла, чем значение переданного. Учтите, что 270°
	 *	меньше, чем 450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 < angle1; // false
	 *
	 *		angle2 < angle3; // true
	 *
	 *		angle2.get_normalized_360() < angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если данный угол меньше, чем переданный, иначе `false`.
	 */
	bool operator<(const Angle& angle) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the angle is greater than a passed one
	 *
	 *	Checks whether the angle is greater than a passed one. Note that 270° is less than 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 > angle1; // true
	 *
	 *		angle2 > angle3; // false
	 *
	 *		angle2.get_normalized_360() > angle3.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is greater than a passed one, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, больше ли значение данного угла, чем значение переданного.
	 *
	 *	Проверяет, больше ли значение данного угла, чем значение переданного. Учтите, что 270°
	 *	меньше, чем 360°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 > angle1; // true
	 *
	 *		angle2 > angle3; // false
	 *
	 *		angle2.get_normalized_360() > angle3.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если данный угол больше, чем переданный, иначе `false`.
	 */
	bool operator>(const Angle& angle) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the angle is less than or equal to a passed one
	 *
	 *	Checks whether the angle is less than or equal to a passed one. Note that 270° is less than
	 *	450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 <= angle1; // false
	 *
	 *		angle2 <= angle3; // true
	 *
	 *		angle2.get_normalized_360() <= angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is less than or equal to a passed one, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, меньше или равно ли значение данного угла значению переданного.
	 *
	 *	Проверяет, меньше или равно ли значение данного угла значению переданного. Учтите, что
	 *	270° меньше, чем 450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 <= angle1; // false
	 *
	 *		angle2 <= angle3; // true
	 *
	 *		angle2.get_normalized_360() <= angle3.get_normalized_360(); // false
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если данный угол меньше или равен переданному, иначе `false`.
	 */
	bool operator<=(const Angle& angle) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the angle is greater than or equal to a passed one
	 *
	 *	Checks whether the angle is greater than or equal to a passed one. Note that 270° is less
	 *	than 450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 >= angle1; // true
	 *
	 *		angle2 >= angle3; // false
	 *
	 *		angle2.get_normalized_360() >= angle3.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is greater than or equal to a passed one, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, больше или равно ли значение данного угла значению переданного.
	 *
	 *	Проверяет, больше или равно ли значение данного угла значению переданного. Учтите, что
	 *	270° меньше, чем 450°.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		angle2 >= angle1; // true
	 *
	 *		angle2 >= angle3; // false
	 *
	 *		angle2.get_normalized_360() >= angle3.get_normalized_360(); // true
	 *	\endcode
	 *	\param angle Угол для сравнения.
	 *	\return `true`, если данный угол больше или равен переданному, иначе `false`.
	 */
	bool operator>=(const Angle& angle) const noexcept;
		
			/* LITERALS */

	/**
	 *	\~english
	 *	\brief Literal for degrees
	 *	
	 *	Can be used for create an angle with a value specified in degrees.
	 *	\code
	 *		Angle angle1 = 2.5_deg;
	 *		Angle angle2(-5.5_deg);
	 *		if (angle1 <= 2.5_deg)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param degrees A value in degrees.
	 *	\return An angle with a specified value.
	 *	
	 *	\~russian
	 *	\brief Литерал для градусов
	 *
	 *	Может быть использован для создания угла со значением, указанным в градусах.
	 *	\code
	 *		Angle angle1 = 2.5_deg;
	 *		Angle angle2(-5.5_deg);
	 *		if (angle1 <= 2.5_deg)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param degrees Значение в градусах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_deg(long double degrees);

	/**
	 *	\~english
	 *	\brief Literal for degrees
	 *	
	 *	Can be used for create an angle with a value specified in degrees.
	 *	\code
	 *		Angle angle1 = 30_deg;
	 *		Angle angle2(-90_deg);
	 *		if (angle1 <= 30_deg)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param degrees A value in degrees.
	 *	\return An angle with a specified value.
	 *	
	 *	\~russian
	 *	\brief Литерал для градусов
	 *
	 *	Может быть использован для создания угла со значением, указанным в градусах.
	 *	\code
	 *		Angle angle1 = 30_deg;
	 *		Angle angle2(-90_deg);
	 *		if (angle1 <= 30_deg)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param degrees Значение в градусах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_deg(unsigned long long degrees);

	/**
	 *	\~english
	 *	\brief Literal for radians
	 *
	 *	Can be used for create an angle with a value specified in radians.
	 *	\code
	 *		Angle angle1 = 3.1415_rad;
	 *		Angle angle2(-3.5_rad);
	 *		if (angle1 <= 3.1415_rad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param radians A value in radians.
	 *	\return An angle with a specified value.
	 *	
	 *	\~russian
	 *	\brief Литерал для радиан
	 *
	 *	Может быть использован для создания угла со значением, указанным в радианах.
	 *	\code
	 *		Angle angle1 = 3.1415_rad;
	 *		Angle angle2(-3.5_rad);
	 *		if (angle1 <= 3.1415_rad)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param radians Значение в радианах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_rad(long double radians);

	/**
	 *	\~english
	 *	\brief Literal for radians
	 *
	 *	Can be used for create an angle with a value specified in radians.
	 *	\code
	 *		Angle angle1 = 3_rad;
	 *		Angle angle2(-1_rad);
	 *		if (angle1 <= 3_rad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param radians A value in radians.
	 *	\return An angle with a specified value.
	 *	
	 *	\~russian
	 *	\brief Литерал для радиан
	 *
	 *	Может быть использован для создания угла со значением, указанным в радианах.
	 *	\code
	 *		Angle angle1 = 3_rad;
	 *		Angle angle2(-1_rad);
	 *		if (angle1 <= 3_rad)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param radians Значение в радианах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_rad(unsigned long long radians);

	/**
	 *	\~english
	 *	\brief Literal for gradians
	 *
	 *	Can be used for create an angle with a value specified in gradians.
	 *	\code
	 *		Angle angle1 = 12.5_grad;
	 *		Angle angle2(-33.3_grad);
	 *		if (angle1 <= 12.5_grad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param gradians A value in gradians.
	 *	\return An angle with a specified value.
	 *	
	 *	\~russian
	 *	\brief Литерал для градов
	 *
	 *	Может быть использован для создания угла со значением, указанным в градах.
	 *	\code
	 *		Angle angle1 = 12.5_grad;
	 *		Angle angle2(-33.3_grad);
	 *		if (angle1 <= 12.5_grad)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param gradians Значение в градах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_grad(long double gradians);

	/**
	 *	\~english
	 *	\brief Literal for gradians
	 *
	 *	Can be used for create an angle with a value specified in gradians.
	 *	\code
	 *		Angle angle1 = 50_grad;
	 *		Angle angle2(-100_grad);
	 *		if (angle1 <= 50_grad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param gradians A value in gradians.
	 *	\return An angle with a specified value.
	 *
	 *	\~russian
	 *	\brief Литерал для градов
	 *
	 *	Может быть использован для создания угла со значением, указанным в градах.
	 *	\code
	 *		Angle angle1 = 50_grad;
	 *		Angle angle2(-100_grad);
	 *		if (angle1 <= 50_grad)
	 *		{
	 *			// Какой-то код
	 *		}
	 *	\endcode
	 *	\param gradians Значение в градах.
	 *	\return Угол с указанным значением.
	 */
	friend Angle operator""_grad(unsigned long long gradians);

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The zero angle
	 *	
	 *	This angle is equal to 0°.
	 *
	 *	\~russian
	 *	\brief Нулевой угол
	 *
	 *	Этот угол равен 0°.
	 */
	static const Angle ZERO;

	/**
	 *	\~english
	 *	\brief The right angle
	 *	
	 *	This angle is equal to 90°.
	 *
	 *	\~russian
	 *	\brief Прямой угол
	 *
	 *	Этот угол равен 90°.
	 */
	static const Angle RIGHT;

	/**
	 *	\~english
	 *	\brief The straight angle
	 *	
	 *	This angle is equal to 180°.
	 *
	 *	\~russian
	 *	\brief Развёрнутый угол угол
	 *
	 *	Этот угол равен 180°.
	 */
	static const Angle STRAIGHT;

private:
	double value_deg_;
};

Angle operator""_deg(long double degrees);
Angle operator""_deg(unsigned long long degrees);
Angle operator""_rad(long double radians);
Angle operator""_rad(unsigned long long radians);
Angle operator""_grad(long double gradians);
Angle operator""_grad(unsigned long long gradians);

/**
 *	\}
 */

}

using snow::operator""_deg;
using snow::operator""_rad;
using snow::operator""_grad;
