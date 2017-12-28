#pragma once
#include <cassert>

template<typename T>
class Service {
public:
	static void setService(T* givenService){
		myService = givenService;
	};
	static T* getService(){
		assert(myService != nullptr);
		return myService;
	};
private:
	static T* myService;
};

template<typename T>
T* Service<T>::myService = nullptr;