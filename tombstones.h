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
	{return "dangling reference error";}
}drExp;

class memoryLeakException : public exception
{
	virtual const char* what() const throw()
	{return "memory leak error";}
}memLeakExp;


template <class T>
class Pointer {
private:
	bool isNull;
	T* entity;
	int referenceCount;
public:

	Pointer<T>() // default constructor
	{
		printf("");
		cout << "default " << this << "\n";
		isNull = true;
		entity = 0;
		referenceCount = 0;
	}
	Pointer<T>(Pointer<T>& otherP)
	{
		cout << "copy constructor " << this << "\n";
		entity = &*otherP;
		referenceCount = 0;
		referenceCount++;
	}// copy constructor


	Pointer<T>(T* otherEntity)
	{
		cout << "bootstrap " << this << "\n";
		entity = otherEntity;
		referenceCount = 0;
		//referenceCount++;
		isNull = true;
	}// bootstrapping constructor
			// argument should always be a call to new

	~Pointer<T>()
	{
		referenceCount--;
		cout << "deconstructor. " << this << " refs left- " << referenceCount << " freed? "<< (entity==0) << " \n";
		if(referenceCount >= 0 && entity != 0)
			throw memLeakExp;
		//delete(entity);
	}// destructor

	T& operator*() const
	{
		if(!isNull)
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
		if(!(entity == 0))// || !hasVal))
		{
			printf("->\n");
			return entity;	
		}
		else
		{
			throw drExp;
		}	
	}// field dereferencing

	Pointer<T>& operator=(const Pointer<T>& other)
	{
		printf("= to pointer %p = %p\n", this, &other);
		referenceCount++;
		entity = other.entity;
		return *this;	
	}// assignment

	friend void free(Pointer<T>& pointer)
	{
		printf("freeing %p\n",&*pointer);
		if(pointer.entity == 0)
			throw drExp;
		free(&*pointer);
		pointer.entity = 0;
	}// delete pointed-at object
			// This is essentially the inverse of the new inside the call to
			// the bootstrapping constructor.
	// equality comparisons:
	bool operator==(const Pointer<T>& other) const
	{
		if(entity == 0)
		{
			return entity == &*other;
		}
		else
			throw drExp;
	}
	bool operator!=(const Pointer<T>& other) const
	{
		cout << "!=\n";
		//cout << "!= " << *entity << " " << *other << "\n";
		if(entity != 0)//hasVal)
			return entity != other.entity;
		else
			throw drExp;
	}
	bool operator==(const int num) const
	{
		// true iff Pointer is null and int is zero
		return num == 0 && entity == 0;
	}
	bool operator!=(const int num) const
	{
		// false iff Pointer is null and int is zero
		return !(num == 0); 
	}
};


#endif // __TOMBSTONES_H__
