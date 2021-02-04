#ifndef MANAGERADDON_H
#define MANAGERADDON_H

#include <node.h>
#include <nan.h>
#include <v8.h>
#include <uv.h>

using namespace v8;
using namespace Nan;

#include <string>
#include <fstream>

class ManagerAddOn : public AsyncProgressWorker
{
public:
	ManagerAddOn(Callback* callback) : AsyncProgressWorker(callback);
	virtual ~ManagerAddOn();

	bool init();
	void writeLog(std::string str);
private:
	Callback* m_callback;
};
#endif

