/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include <exception>
#include <stdio.h>
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


	Pointer<T>(T* otherEntity)
	{
		entity = otherEntity;
		referenceCount = 0;
		referenceCount++;
		hasVal = true;
	}// bootstrapping constructor
			// argument should always be a call to new

	~Pointer<T>()
	{
		printf("deconstructor \n");
		referenceCount--;
		hasVal = false;
		printf("entity %d\n",entity);
		//delete(entity);
	}// destructor

	T& operator*() const
	{
		if(hasVal)
		{
			//printf("not null\n");
			//if (entity)
				//printf("value in *: %p %d\n", this->entity, *(this->entity));
			//else
				//printf("value in *: %p\n", this->entity);
			return *entity;	
		}
		else
		{
			printf("error- null\n");
			throw drExp;
		}
	}// deferencing

	T* operator->() const
	{
		if(!(entity == 0 || !hasVal))
		{
			//printf("->\n");
			return *entity;	
		}
		else
		{
			throw drExp;
		}	
	}// field dereferencing

	Pointer<T>& operator=(const Pointer<T>& other)
	{
		//printf("other: %p %d, \n",other.entity, *other);
		T* holder = new T(*other);
		//other.incRefCount();
		referenceCount++;
		entity = holder;
		//entity = other.entity;
		//printf("this (after change): %p %d\n", this->entity, *(this->entity));
		return *this;	
	}// assignment

	friend void free(Pointer<T>& pointer)
	{
		printf("freeing %p\n",&*pointer);
		if(referenceCount == 0)
			throw drExp;
		referenceCount--;
		if(referenceCount == 0)
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
		if(hasVal)
			return entity != &*other;
		else
			throw drExp;
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
