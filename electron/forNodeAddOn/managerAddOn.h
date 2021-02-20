#ifndef MANAGERADDON_H
#define MANAGERADDON_H

#include <string>
#include <fstream>
#include <queue>
#include <mutex>
#include "windows.h"

typedef void(__stdcall* CBFun_NetworkCallback)(std::string sMsg, int nSeq, void* pUser);
typedef void(__stdcall* TYPE_FunParamVoidReturnVoid)();
typedef int(*TYPE_FunParamValidReturnVoid)(const char* pString, int nNumber);
typedef char* (*TYPE_FunParamVoidReturnValid)();
typedef int(*TYPE_FuncParamValidReturnValid)(const char* pString, int nNumber);
typedef int (__stdcall* TYPE_FuncSetCallback)(CBFun_NetworkCallback pFunc, void* pUser);
typedef void(*TYPE_FunRequestNetworkAndCallback)(std::string sUserName, std::string sPassword);


class ManagerAddOn
{
public:
	
	static ManagerAddOn* getInstance() {
		if (m_instance == nullptr) {
			m_instance = new ManagerAddOn();
		}
		return m_instance;
	}
	virtual ~ManagerAddOn();

public:
	ManagerAddOn();
	bool init();
	bool isLoadingSuccess() {
		return m_bLoad;
	}

	void funParamVoidReturnVoid();
	void funParamValidReturnVoid(const char* pString, int nNumber);
	char* funParamVoidReturnValid();
	int funParamValidReturnValid(const char* pString, int nNumber);
	void setCallback(CBFun_NetworkCallback pFunc, void* pUser);
	void requestNetworkAndCallback(std::string sUserName, std::string sPassword);

	void writeManagerLog(std::string sMsg);
private:
	

	static ManagerAddOn* m_instance;
	TYPE_FunParamVoidReturnVoid FunParamVoidReturnVoidDLL = nullptr;
	TYPE_FunParamValidReturnVoid FunParamValidReturnVoidDLL = nullptr;
	TYPE_FunParamVoidReturnValid FunParamVoidReturnValidDLL = nullptr;
	TYPE_FuncParamValidReturnValid FunParamValidReturnValidDLL = nullptr;
	TYPE_FuncSetCallback FunSetCallbackDLL = nullptr;
	TYPE_FunRequestNetworkAndCallback FunRequestNetworkAndCallbackDLL = nullptr;

	bool m_bLoad = false;
	HINSTANCE hDLL = nullptr;
};

#endif

