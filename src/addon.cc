#include <napi.h>
#include "SharedMemory.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return SharedMemory::Init(env, exports);
}

NODE_API_MODULE(SharedMemory, InitAll)