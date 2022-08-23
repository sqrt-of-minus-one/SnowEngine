    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleSpriteAnimation.h     //
////////////////////////////////////////

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Vector/Point2.h"

namespace snow
{

class Timer;

class SimpleSpriteAnimation : public Object, public ISpriteAnimation
{
public:
			/* CONSTRUCTORS */

	SimpleSpriteAnimation(const SimpleSpriteAnimation& animation);
	SimpleSpriteAnimation(const Point2& sprite_size, const Point2& origin, const Point2& grid_size, float frequency_sec);
	~SimpleSpriteAnimation();

			/* METHODS FROM Object */

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

			/* METHODS FROM ISpriteAnimation */

	virtual IntRect get_sprite_rect() const override;

private:
	Point2 sprite_size_;
	Point2 origin_;
	Point2 grid_size_;
	float frequency_sec_;

	Point2 current_position_;

	std::shared_ptr<Timer> timer_;

	void next_frame_();
};

}
