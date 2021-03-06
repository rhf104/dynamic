#include <stdio.h>

#include "convec.h"
#include "state.h"

int main() {
    State state = {};
    Convec cv = ConvecInit("libtest_loop.dylib", "loop", &state,
                           1000000);
    do {
        ConvecRunAndUpdate(&cv);
        printf("%s\n", state.msg);
    } while (!state.quit);
    return 0;
}