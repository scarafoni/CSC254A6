/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include <exception>
using namespace std;

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

class danglingReferenceException : public exception
{
	virtual const char* what() const throw()
	{
		return "dangling reference error";
	}
}drExp;


template <class T>
class Pointer {
private:
	bool hasVal;
	T* entity;
	int referenceCount;
public:
	Pointer<T>() // default constructor
	{
		hasVal = false;
		referenceCount = 0;
	}
	Pointer<T>(Pointer<T>& otherP)
	{
		entity = &*otherP;
		referenceCount = 0;
		referenceCount++;
		hasVal = true;		
	}// copy constructor


	Pointer<T>(T* entity)
	{
		this->entity = entity;
		referenceCount = 0;
		referenceCount++;
		hasVal = true;
	}// bootstrapping constructor
			// argument should always be a call to new

	~Pointer<T>()
	{
		referenceCount--;
		hasVal = false;
		delete(entity);
	}// destructor

	T& operator*() const
	{
		if(hasVal)
			return *entity;	
		else
			throw drExp;
	}// deferencing

	T* operator->() const
	{
		if(!(entity == 0 || !hasVal))
			return *entity;	
		else
		{
			throw drExp;
		}	
	}// field dereferencing

	Pointer<T>& operator=(const Pointer<T>& other)
	{
		//other.incRefCount();
		//referenceCount--;
		//Pointer<T>& temp = new Pointer<T>(&*other);
		entity = &*other;
		return *this;	
	}// assignment

	friend void free(Pointer<T>& pointer)
	{
		free(&*pointer);
	}// delete pointed-at object
			// This is essentially the inverse of the new inside the call to
			// the bootstrapping constructor.
	// equality comparisons:
	bool operator==(const Pointer<T>& other) const
	{
		if(hasVal)
		{
			return entity == &*other;
		}
		else
			throw drExp;
	}
	bool operator!=(const Pointer<T>& other) const
	{
		return !(this == &*other);
	}
	bool operator==(const int num) const
	{
		// true iff Pointer is null and int is zero
		return num == 0 && entity == NULL;
	}
	bool operator!=(const int num) const
	{
		// false iff Pointer is null and int is zero
		return !(num == 0); 
	}
};


#endif // __TOMBSTONES_H__
