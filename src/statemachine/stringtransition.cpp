#include "stringtransition.h"
#include "stringevent.h"


bool StringTransition::eventTest(QEvent *e) {
    if (e->type() != StringEvent::TYPE)
            return false;
    StringEvent *se = static_cast<StringEvent*>(e);
    return (value_ == se->value);
}
