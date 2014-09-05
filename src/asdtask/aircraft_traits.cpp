#include "aircraft_traits.h"

#include "aircraft.h"


void asd::Aircraft::Traits::attach(const asd::Aircraft::Sprite *sprite) { sprite_ = sprite; }

qreal asd::Aircraft::Traits::current_velocity() { return sprite_->state_->vel; }
qreal asd::Aircraft::Traits::cleared_velocity() { return sprite_->state_->cvl; }
qreal asd::Aircraft::Traits::current_altitude() { return sprite_->state_->alt; }
qreal asd::Aircraft::Traits::cleared_altitude() { return sprite_->state_->cfl; }
