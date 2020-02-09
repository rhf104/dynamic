#include <stdio.h>

#include "convec.h"
#include "state.h"

int main() {
    State state;
    Convec cv = ConvecInit("libloop.dylib", "loop", &state,
                           1000000);
    do {
        ConvecRunAndUpdate(&cv);
        printf("%s\n", state.msg);
    } while (ConvecIsRunning(&cv));
    return 0;
}