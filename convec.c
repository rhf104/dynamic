#include <stdio.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <assert.h>

#include "convec.h"

static __darwin_ino_t fileId(const char *path) {
    struct stat stats;
    stat(path, &stats);
    return stats.st_ino;
}

static void unloadLib(void *lib) {
    if (dlclose(lib) == -1) {
        assert(false);
    }
}

static void *loadLib(const char *path) {
    void *lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (lib == NULL) {
        assert(false);
    }
    return lib;
}

static void *loadSymbol(void *handle, const char *symbol) {
    void *address = dlsym(handle, symbol);
    if (address == NULL) {
        assert(false);
    }
    return address;
}

Convec ConvecInit(const char *libPath, const char *funcName, void *state,
                  int waitCycles) {
    void *lib = loadLib(libPath);
    return (Convec) {
            .quit = false,
            .libPath = libPath,
            .fileId = fileId(libPath),
            .lib = lib,
            .funcName = funcName,
            .callback = loadSymbol(lib, funcName),
            .state = state,
            .waitCycles = waitCycles,
    };
}

void ConvecRunAndUpdate(Convec *cv) {
    cv->callback(cv);
    cv->cycles += 1;

    if (cv->cycles >= cv->waitCycles) {
        cv->cycles = 0;

        __darwin_ino_t maybeNewFileId = fileId(cv->libPath);
        if (cv->fileId != maybeNewFileId) {
            cv->fileId = maybeNewFileId;
            unloadLib(cv->lib);
            cv->lib = loadLib(cv->libPath);
            cv->callback = loadSymbol(cv->lib, cv->funcName);
        }
    }
}

bool ConvecIsRunning(Convec *cv) {
    return !cv->quit;
}

