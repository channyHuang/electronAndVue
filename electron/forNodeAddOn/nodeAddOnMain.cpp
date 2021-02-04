#include <node.h>
#include <nan.h>
#include "managerAddOn.h"

using namespace Nan;

namespace PMonitor {
    using v8::Exception;
    using v8::Context;
    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::FunctionTemplate;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::ObjectTemplate;
    using v8::String;
    using v8::Value;

    void Init(const FunctionCallbackInfo<Value>& args)
    {
        Callback* callback = new Callback(args[0].As<v8::Function>());
        ManagerAddOn* pManager = new ManagerAddOn(callback);
        AsyncQueueWorker(pManager);

        int flag = pManager->init();

        Isolate* isolate = args.GetIsolate();
        Local<Number> num = Number::New(isolate, flag);
        args.GetReturnValue().Set(num);
    }

    void Log(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();
        Local<String> sMsg = Local<String>::Cast(args[0]);
        String::Utf8Value sMessage(isolate, sMsg);

        CInterfaceManager::GetInst()->WriteLog(string(*sMessage).c_str());
    }

    void VerifyFinger(const FunctionCallbackInfo<Value>& args)
    {
        std::string str = "FingerRecog.dll";
        HINSTANCE hDLL = LoadLibrary(str.c_str());
        bool bRes = false;
        if (hDLL != nullptr)
        {
            typedef bool(*TYPE_VerifyFingerPrintMsgDLL)();
            TYPE_VerifyFingerPrintMsgDLL verifyFingerPrintMsgDLL = (TYPE_VerifyFingerPrintMsgDLL)GetProcAddress(hDLL, "verifyFingerPrintMsg");
            bRes = (verifyFingerPrintMsgDLL == nullptr ? false : verifyFingerPrintMsgDLL());
        }
        Isolate* isolate = args.GetIsolate();
        Local<Number> num = Number::New(isolate, bRes);
        args.GetReturnValue().Set(num);
    }
    
    //=========================================================================
    void RegisterModule(Local<Object> exports, Local<Object> module, Local<Context> context) {   //在此注册提供给js调用的接口
        NODE_SET_METHOD(exports, "Init", Init);
        NODE_SET_METHOD(exports, "Log", Log);
        NODE_SET_METHOD(exports, "VerifyFinger", VerifyFinger);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, RegisterModule)     //此处不需分号，它不是一个函数
}  // namespace PMonitor





