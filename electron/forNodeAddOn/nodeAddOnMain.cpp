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

    struct StCallbackData {
        Nan::Callback* callback;    //回调函数
        int nSeq;                 //需要回调到js层的数据
        std::string sMsg;
        uv_async_t handle;          //异步句柄
    };

    StCallbackData* on_start_session_data = new StCallbackData();

    static void CallJSCallback(const std::string sMsg, const int nSeq) {
        on_start_session_data->nSeq = nSeq;
        on_start_session_data->sMsg = sMsg;
        on_start_session_data->handle.data = (void*)on_start_session_data; //数据类型的一些转换
        uv_async_send(&on_start_session_data->handle);                      //唤醒事件循环中的事件  
    }

    void OnStartSessionEvent(uv_async_t* handle) {                  //具体执行的事件
        Nan::HandleScope scope;
        StCallbackData* data = (StCallbackData*)handle->data;
        v8::Local<v8::Value> argv[2] = { Nan::New(data->sMsg).ToLocalChecked(), Nan::New((int)data->nSeq) };//数据类型的一些转换
        data->callback->Call(2, argv);                               //数据回调到js层
    }

    void __stdcall FunCPlusCallback(std::string sMsg, int nSeq, void* pUser)
    {
        if (pUser == nullptr) {
            return;
        }
        CallJSCallback(sMsg, nSeq);
    }

    void Init(const FunctionCallbackInfo<Value>& args)
    {
        ManagerAddOn::getInstance()->init();
    }

    void FunParamVoidReturnVoid(const FunctionCallbackInfo<Value>& args)
    {
        ManagerAddOn::getInstance()->funParamVoidReturnVoid();
        bool bRes = true;

        Isolate* isolate = args.GetIsolate();
        Local<Number> num = Number::New(isolate, bRes);
        args.GetReturnValue().Set(num);
    }

    void FunParamValidReturnVoid(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();
        Local<String> lParamString = Local<String>::Cast(args[0]);
        String::Utf8Value sParamString(isolate, lParamString);

        ManagerAddOn::getInstance()->funParamValidReturnVoid(std::string(*sParamString).c_str(), 8);
        bool bRes = true;

        Local<Number> num = Number::New(isolate, bRes);
        args.GetReturnValue().Set(num);
    }

    void FunParamVoidReturnValid(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();

        char *pMessage = ManagerAddOn::getInstance()->funParamVoidReturnValid();
        int nRes = 1;

        Local<Object> resObj = Object::New(isolate);
        resObj->Set(resObj->CreationContext(),
            Local<Value>(String::NewFromUtf8(isolate, "nResult").ToLocalChecked()),
            Local<Value>(String::NewFromUtf8(isolate, std::to_string(nRes).c_str()).ToLocalChecked())
        );
        resObj->Set(resObj->CreationContext(),
            Local<Value>(String::NewFromUtf8(isolate, "sResult").ToLocalChecked()),
            Local<Value>(String::NewFromUtf8(isolate, std::string("message~").c_str()).ToLocalChecked())
        );

        args.GetReturnValue().Set(resObj);
    }

    void FuncParamValidReturnValid(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();
        Local<String> lParamString = Local<String>::Cast(args[0]);
        String::Utf8Value sParamString(isolate, lParamString);

        int nRes = ManagerAddOn::getInstance()->funParamValidReturnValid(std::string(*sParamString).c_str(), 9);

        Local<Number> num = Number::New(isolate, nRes);
        args.GetReturnValue().Set(num);
    }

    void FuncSetCallback(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();

        Nan::Callback* start_session_callback = new Nan::Callback(args[0].As<Function>());

        on_start_session_data->callback = start_session_callback;  //获取回调函数 
        uv_async_init(uv_default_loop(), &on_start_session_data->handle, OnStartSessionEvent);  //加入事件循环中，等待唤醒，uv_default_loop()获取libuv默认创建的事件循环句柄

        int value = 0;
        Local<Value> argv[1] = { Nan::New((int)value) };
        args.GetReturnValue().Set(Nan::New((int)value));

        //Local<Number> num = Number::New(isolate, nRes);
        //args.GetReturnValue().Set(num);
    }

    void FunRequestNetworkAndCallback(const FunctionCallbackInfo<Value>& args)
    {
        Isolate* isolate = args.GetIsolate();
        Local<String> lsUserName = Local<String>::Cast(args[0]);
        String::Utf8Value svUserName(isolate, lsUserName);
        std::string sUserName = std::string(*svUserName);
        Local<String> lsPassword = Local<String>::Cast(args[1]);
        String::Utf8Value svPassword(isolate, lsPassword);
        std::string sPassword = std::string(*svPassword);

        ManagerAddOn::getInstance()->setCallback(FunCPlusCallback, nullptr);
        ManagerAddOn::getInstance()->requestNetworkAndCallback(sUserName, sPassword);
    }

    //=========================================================================
    void RegisterModule(Local<Object> exports, Local<Object> module, Local<Context> context) {
        NODE_SET_METHOD(exports, "Init", Init);
        NODE_SET_METHOD(exports, "FunParamVoidReturnVoid", FunParamVoidReturnVoid);
        NODE_SET_METHOD(exports, "FunParamValidReturnVoid", FunParamValidReturnVoid);
        NODE_SET_METHOD(exports, "FunParamVoidReturnValid", FunParamVoidReturnValid);
        NODE_SET_METHOD(exports, "FuncParamValidReturnValid", FuncParamValidReturnValid);
        NODE_SET_METHOD(exports, "FunRequestNetworkAndCallback", FunRequestNetworkAndCallback);
        NODE_SET_METHOD(exports, "FuncSetCallback", FuncSetCallback);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, RegisterModule)
}  // namespace PMonitor
