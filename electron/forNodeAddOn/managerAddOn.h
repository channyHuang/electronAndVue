#ifndef MANAGERADDON_H
#define MANAGERADDON_H

#include <node.h>
#include <nan.h>
#include <v8.h>
#include <uv.h>

using namespace v8;
using namespace Nan;

class ManagerAddOn
{
public:
	ManagerAddOn();
	virtual ~ManagerAddOn();

	bool init();
private:

};
#endif

