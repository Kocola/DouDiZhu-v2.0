#ifndef					__SINGLETON_H__
#define					__SINGLETON_H__

template<typename T>
class Singleton
{
public:
	static T& getIns();

	static T* getInstance();

//在VS2013里，private可以正常运行，但是NDK编译时会出错
//这里应该使用protected，不然继承该类的类无法调用该父类的
//默认构造函数
protected:
	Singleton() = default;

	~Singleton() = default;

private:
	Singleton(const Singleton&) = delete;

	Singleton& operator=(const Singleton&) = delete;
};

template<typename T>
T& Singleton<T>::getIns()
{
	static T s_instance;
	return s_instance;
}

template<typename T>
T* Singleton<T>::getInstance()
{
	return &getIns();
}

#endif