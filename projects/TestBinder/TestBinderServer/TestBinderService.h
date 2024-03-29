#ifndef ANDROID_TESTBINDERSERVICE_H_
#define ANDROID_TESTBINDERSERVICE_H_

#include <utils/KeyedVector.h>
#include "../Interface/ITestBinderService.h"

namespace android {

class TestBinderService: public BnTestBinderService {
public:
	static void instantiate();
	int add(int a,int b);
    sp<IAddTest> BeginAddTest();
private:
	TestBinderService();
	virtual ~TestBinderService();
};

}

#endif /* ANDROID_TESTBINDERSERVICE_H_ */
