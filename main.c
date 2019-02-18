#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <assert.h>

__darwin_ino_t fileId(const char *path) {
    struct stat stats;
    stat(path, &stats);
    return stats.st_ino;
}

void unloadLib(void *lib) {
    if (dlclose(lib) == -1) {
        assert(false);
    }
}

void *loadLib(const char *path) {
    void *lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (lib == NULL) {
        assert(false);
    }
    return lib;
}

void *loadSymbol(void *handle, const char *symbol) {
    void *address = dlsym(handle, symbol);
    if (address == NULL) {
        assert(false);
    }
    return address;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    const char *libPath = "libdynamic_share.dylib";
    __darwin_ino_t fId = fileId(libPath);
    void *lib = loadLib(libPath);
    const char *(*secret)(void) = loadSymbol(lib, "secret");
    while (true) {
        __darwin_ino_t maybeNewFileId = fileId(libPath);
        if (fId != maybeNewFileId) {
            unloadLib(lib);
            lib = loadLib(libPath);
            secret = loadSymbol(lib, "secret");
            fId = maybeNewFileId;
            printf("========RELOADED========\n");
        }
        printf("File Id: %d\n", (int) fId);
        printf("Secret: %s\n", secret());

        struct timespec waitTime = {.tv_sec = 1};
        nanosleep(&waitTime, &waitTime);
    }
}

#pragma clang diagnostic pop
