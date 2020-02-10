#include <stdio.h>
#include <stdbool.h>

typedef struct Convec Convec;
struct Convec {
    void *lib;
    const char *libPath;
    __darwin_ino_t fileId;
    void (*callback)(Convec*);
    void *state;
    int waitCycles;
    int cycles;
    const char *funcName;
};

Convec ConvecInit(const char *libPath, const char *funcName, void *state,
                  int waitCycles);
void ConvecRunAndUpdate(Convec *cv);
