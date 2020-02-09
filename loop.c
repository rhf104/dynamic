#include <string.h>

#include "convec.h"
#include "state.h"

void loop(Convec *cv) {
    State *state = cv->state;
    strncpy(state->msg, "Hello, world!", sizeof(state->msg));
}
