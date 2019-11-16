#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <napi.h>
#include <windows.h>

class SharedMemory : public Napi::ObjectWrap<SharedMemory>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  SharedMemory(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;

  Napi::Value open(const Napi::CallbackInfo &info);
  Napi::Value close(const Napi::CallbackInfo &info);

  Napi::Value readFloat(const Napi::CallbackInfo &info);
  Napi::Value readDouble(const Napi::CallbackInfo &info);
  Napi::Value readInt8(const Napi::CallbackInfo &info);
  Napi::Value readInt16(const Napi::CallbackInfo &info);
  Napi::Value readInt32(const Napi::CallbackInfo &info);
  Napi::Value readUInt8(const Napi::CallbackInfo &info);
  Napi::Value readUInt16(const Napi::CallbackInfo &info);
  Napi::Value readUInt32(const Napi::CallbackInfo &info);

  Napi::Value writeFloat(const Napi::CallbackInfo &info);
  Napi::Value writeDouble(const Napi::CallbackInfo &info);
  Napi::Value writeInt8(const Napi::CallbackInfo &info);
  Napi::Value writeInt16(const Napi::CallbackInfo &info);
  Napi::Value writeInt32(const Napi::CallbackInfo &info);
  Napi::Value writeUInt8(const Napi::CallbackInfo &info);
  Napi::Value writeUInt16(const Napi::CallbackInfo &info);
  Napi::Value writeUInt32(const Napi::CallbackInfo &info);

  char *MemName;
  unsigned long MemSize;
  HANDLE MapFile;
  LPTSTR Buffer;
};

#endif