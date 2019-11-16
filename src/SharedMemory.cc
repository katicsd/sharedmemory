#include <napi.h>
#include <windows.h>
#include <string.h>

#include "SharedMemory.h"

Napi::FunctionReference SharedMemory::constructor;

Napi::Object SharedMemory::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func =
        DefineClass(env,
                    "SharedMemory",{
                        InstanceMethod("open", &SharedMemory::open),
                        InstanceMethod("close", &SharedMemory::close),
                        InstanceMethod("readFloat", &SharedMemory::readFloat),
                        InstanceMethod("readDouble", &SharedMemory::readDouble),
                        InstanceMethod("readInt8", &SharedMemory::readInt8),
                        InstanceMethod("readInt16", &SharedMemory::readInt16),
                        InstanceMethod("readInt32", &SharedMemory::readInt32),
                        InstanceMethod("readUInt8", &SharedMemory::readUInt8),
                        InstanceMethod("readUInt16", &SharedMemory::readUInt16),
                        InstanceMethod("readUInt32", &SharedMemory::readUInt32),
                        InstanceMethod("writeFloat", &SharedMemory::writeFloat),
                        InstanceMethod("writeDouble", &SharedMemory::writeDouble),
                        InstanceMethod("writeInt8", &SharedMemory::writeInt8),
                        InstanceMethod("writeInt16", &SharedMemory::writeInt16),
                        InstanceMethod("writeInt32", &SharedMemory::writeInt32),
                        InstanceMethod("writeUInt8", &SharedMemory::writeUInt8),
                        InstanceMethod("writeUInt16", &SharedMemory::writeUInt16),
                        InstanceMethod("writeUInt32", &SharedMemory::writeUInt32)                        
                    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("SharedMemory", func);
    return exports;
}

SharedMemory::SharedMemory(const Napi::CallbackInfo &info): Napi::ObjectWrap<SharedMemory>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length < 2 || !info[0].IsString() || !info[1].IsNumber()){
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }

    Napi::String name = info[0].As<Napi::String>();
    std::string s = name;
    this->MemName = (char *)malloc(s.length() + 1);
    std::strcpy(this->MemName, s.c_str());
    Napi::Number site = info[1].As<Napi::Number>();
    this->MemSize = site.Uint32Value();
    this->MapFile = NULL;
    this->Buffer = NULL;
}

Napi::Value SharedMemory::open(const Napi::CallbackInfo &info){
    int num = 0;
    this->MapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, this->MemName);
    if (!this->MapFile){
        return Napi::Number::New(info.Env(), 1);
    }
    else{
        this->Buffer = (LPTSTR)MapViewOfFile(this->MapFile, FILE_MAP_ALL_ACCESS, 0, 0, this->MemSize);
        if (!this->Buffer){
            return Napi::Number::New(info.Env(), 2);
        }
    }
    return Napi::Number::New(info.Env(), 0);
}

Napi::Value SharedMemory::close(const Napi::CallbackInfo &info){
    int r=1;
    r &= UnmapViewOfFile(this->Buffer);
    r &= CloseHandle(this->MapFile);
    return Napi::Number::New(info.Env(), r);
}

//***********************
//*** READ functions ***
//***********************

Napi::Value SharedMemory::readFloat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    float value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 4);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readDouble(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    double value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 8);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readInt8(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    signed char value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 1);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readInt16(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    short value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 2);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readInt32(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    long value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 4);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readUInt8(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned char value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 1);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readUInt16(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned short value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 2);
    return Napi::Number::New(env, value);
}

Napi::Value SharedMemory::readUInt32(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned long value;
    memcpy(&value, this->Buffer + info[0].As<Napi::Number>().Uint32Value(), 4);
    return Napi::Number::New(env, value);
}

//***********************
//*** WRITE functions ***
//***********************

Napi::Value SharedMemory::writeFloat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    float value = info[1].As<Napi::Number>().FloatValue();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 4);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeDouble(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    double value = info[1].As<Napi::Number>().DoubleValue();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 8);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeInt8(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    char value = info[1].As<Napi::Number>().Int32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 1);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeInt16(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    short value = info[1].As<Napi::Number>().Int32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 2);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeInt32(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    long value = info[1].As<Napi::Number>().Int32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 4);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeUInt8(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned char value = info[1].As<Napi::Number>().Uint32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 1);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeUInt16(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned short value = info[1].As<Napi::Number>().Uint32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 2);
    return Napi::Number::New(info.Env(), 1);
}

Napi::Value SharedMemory::writeUInt32(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!this->Buffer)
    {
        Napi::TypeError::New(env, "Not initialized shared memory!").ThrowAsJavaScriptException();
    }
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong attributes!").ThrowAsJavaScriptException();
    }
    unsigned long value = info[1].As<Napi::Number>().Uint32Value();
    memcpy(this->Buffer + info[0].As<Napi::Number>().Uint32Value(), &value, 4);
    return Napi::Number::New(info.Env(), 1);
}