#include "stringtransition.h"


const int StringEvent::TYPE = QEvent::registerEventType();

bool StringTransition::eventTest(QEvent *e) {
    if (e->type() != StringEvent::TYPE)
            return false;
    StringEvent *se = static_cast<StringEvent*>(e);
    return (value_ == se->value);
}
