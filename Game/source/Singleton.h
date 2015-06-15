#ifndef __SINGLETON_H__
#define __SINGLETON_H__

// Singleton
template <class T> class Singleton
{
protected:
	static T*     s_instance;
public:
	Singleton(){}
	virtual ~Singleton(){}

	static T*     GetInstance()
	{
		if(!s_instance)
			s_instance = new T();
		return s_instance;
	}
};

template <class T>
T* Singleton<T>::s_instance = NULL;

#endif