#include "managerAddOn.h"

ManagerAddOn* ManagerAddOn::m_instance;

ManagerAddOn::ManagerAddOn()
{
};

ManagerAddOn::~ManagerAddOn() {}

void __stdcall ManagerCPlusCallback(std::string sMsg, int nSeq, void* pUser)
{
    if (pUser == nullptr) {
        return;
    }
    ManagerAddOn* manager = static_cast<ManagerAddOn*>(pUser);
    //to do
    //manager->callBackFunc(sMsg);
}

void ManagerAddOn::writeManagerLog(std::string sMsg)
{
    std::ofstream ofs("log.txt", std::ios::app);
    ofs << sMsg << std::endl;
    ofs.close();
}

bool ManagerAddOn::init()
{
    std::string str = "demoDll.dll";
    hDLL = LoadLibrary(str.c_str());

    if (hDLL != nullptr)
    {
        FunParamVoidReturnVoidDLL = (TYPE_FunParamVoidReturnVoid)GetProcAddress(hDLL, "funParamVoidReturnVoid");
        FunParamValidReturnVoidDLL = (TYPE_FunParamValidReturnVoid)GetProcAddress(hDLL, "funParamValidReturnVoid");
        FunParamVoidReturnValidDLL = (TYPE_FunParamVoidReturnValid)GetProcAddress(hDLL, "funParamVoidReturnValid");
        FunParamValidReturnValidDLL = (TYPE_FuncParamValidReturnValid)GetProcAddress(hDLL, "funParamValidReturnValid");
        FunSetCallbackDLL = (TYPE_FuncSetCallback)GetProcAddress(hDLL, "funSetNetworkCallback");
        FunRequestNetworkAndCallbackDLL = (TYPE_FunRequestNetworkAndCallback)GetProcAddress(hDLL, "funRequestNetworkAndCallback");

        m_bLoad = true;
        if (FunParamVoidReturnVoidDLL == nullptr) {
            writeManagerLog("FunParamVoidReturnVoidDLL null");
            m_bLoad = false;
        }
        if (FunParamValidReturnVoidDLL == nullptr) {
            writeManagerLog("FunParamValidReturnVoidDLL null");
            m_bLoad = false;
        }
        if (FunParamVoidReturnValidDLL == nullptr) {
            writeManagerLog("FunParamVoidReturnValidDLL null");
            m_bLoad = false;
        }
        if (FunParamValidReturnValidDLL == nullptr) {
            writeManagerLog("FunParamValidReturnValidDLL null");
            m_bLoad = false;
        }
        if (FunSetCallbackDLL == nullptr) {
            writeManagerLog("FunSetCallbackDLL null");
            m_bLoad = false;
        }
        if (FunRequestNetworkAndCallbackDLL == nullptr) {
            writeManagerLog("FunRequestNetworkAndCallbackDLL null");
            m_bLoad = false;
        }
        writeManagerLog("load dll");
    }
    else {
        writeManagerLog("load dll failed");
    }

    return m_bLoad;
}

void ManagerAddOn::funParamVoidReturnVoid()
{
    if (FunParamVoidReturnVoidDLL != nullptr) {
        FunParamVoidReturnVoidDLL();
    }
}

void ManagerAddOn::funParamValidReturnVoid(const char* pString, int nNumber)
{
    if (FunParamValidReturnVoidDLL != nullptr) {
        FunParamValidReturnVoidDLL(pString, nNumber);
    }
}

char* ManagerAddOn::funParamVoidReturnValid()
{
    if (FunParamVoidReturnValidDLL != nullptr) {
        return FunParamVoidReturnValidDLL();
    }
    return nullptr;
}

int ManagerAddOn::funParamValidReturnValid(const char* pString, int nNumber)
{
    if (FunParamValidReturnValidDLL) {
        return FunParamValidReturnValidDLL(pString, nNumber);
    }
    return -1;
}

void ManagerAddOn::setCallback(CBFun_NetworkCallback pFunc, void* pUser)
{
    if (FunSetCallbackDLL != nullptr) {
        FunSetCallbackDLL(pFunc, pUser);
    }
}
void ManagerAddOn::requestNetworkAndCallback(std::string sUserName, std::string sPassword)
{
    if (FunRequestNetworkAndCallbackDLL != nullptr) {
        FunRequestNetworkAndCallbackDLL(sUserName, sPassword);
    }
}