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
}mlExp;

template <typename T>
struct tombstone 
{
	T* entity;
	int referenceCount;
	bool isNull;
	bool isFree;
};

template <class T>
class Pointer {
public:
	tombstone<T>* tsp;

	void printInfo(string name)
	{
		cout<<"printing info on "<<name<< "\n";
		printf("\t location- %p\n",this);
		printf("\t tombstone- %p\n",tsp);
		printf("\t entity (loc, data)- %p, %d\n",tsp->entity,*(tsp->entity));
		printf("\t null %d\n",(tsp->isNull));
		printf("\t free %d\n",(tsp->isFree));
		printf("\t refcount- %d\n",tsp->referenceCount);
	}
	Pointer<T>() // default constructor
	{
		cout << "default " << this << "\n";
		//tsp = &ts;
		tsp = new tombstone<T>;
		tsp->entity = 0;
		tsp->isNull = true;
		tsp->isFree = false;
		tsp->referenceCount = 0;
	}
	Pointer<T>(Pointer<T>& otherP)
	{
		cout << "copy constructor " << this << "\n";
		if(otherP.tsp->isFree)
			throw drExp;
		tsp = otherP.tsp;
		tsp->referenceCount++;
	}// copy constructor


	Pointer<T>(T* otherEntity)
	{
		cout << "bootstrap " << this << "\n";
		tsp = new tombstone<T>;
		if(!(otherEntity == 0))
			tsp->isNull = false;
		else
			tsp->isNull = true;

		tsp->entity = otherEntity;
		tsp->referenceCount = 1;
		tsp->isFree = false;
	}// bootstrapping constructor
			// argument should always be a call to new

	~Pointer<T>()
	{
		cout << "refs left (before delete) "<<tsp->referenceCount<<"\n";
		tsp->referenceCount--;
		cout << "deconstructor. " << this <<" tsp-  "<< tsp << " refs left- " << tsp->referenceCount << " freed? "<< (tsp->isFree) << " \n";
		if(tsp->referenceCount == 0 && !tsp->isFree && !tsp->isNull)
			throw mlExp;
		if(tsp->referenceCount == 0 && tsp->isFree)
			delete(tsp);
	}// destructor

	T& operator*() const
	{
		printf("* on %p\n",this);
		if(tsp->entity && !tsp->isFree && !tsp->isNull)
		{
			return *tsp->entity;	
		}
		else
		{
			printf("error- null\n");
			throw drExp;
		}
	}// deferencing
	
	T* operator->() const
	{
		if(tsp->entity && !tsp->isFree && !tsp->isNull)
		{
			printf("->\n");
			return tsp->entity;	
		}
		else
		{
			throw drExp;
		}	
	}// field dereferencing
	
	Pointer<T>& operator=(const Pointer<T>& other)
	{
		printf("= to pointer %p = %p, %d refs left\n", this, &*other,tsp->referenceCount);
		printInfo("=");
		if(other.tsp == tsp)
			return *this;
		tsp->referenceCount--;
		if(!tsp->isNull && !tsp->isFree && tsp->referenceCount == 0)
			throw mlExp;
		tsp = other.tsp;
		tsp->referenceCount++;
	}// assignment

	friend void free(Pointer<T>& pointer)
	{
		if(pointer.tsp->isNull || pointer.tsp->isFree)
			throw drExp;
		pointer.printInfo("free");
		free(&*pointer);
		pointer.tsp->isFree = true;
	}// delete pointed-at object
			// This is essentially the inverse of the new inside the call to
			// the bootstrapping constructor.
	// equality comparisons:
	bool operator==(const Pointer<T>& other) const
	{
		printf("== on %p and %p\n",tsp->entity,&*other);
		if(!tsp->isNull && !tsp->isFree)
		{
			return tsp->entity == &*other;
		}
		else
			throw drExp;
	}
	bool operator!=(const Pointer<T>& other) const
	{
		printf("!= on %p and %p\n",tsp->entity,&*other);
		if(!tsp->isNull)
			return tsp->entity != other.tsp->entity;
		else
			throw drExp;
	}
	bool operator==(const int num) const
	{
		// true iff Pointer is null and int is zero
		return num == 0 && tsp->isNull;
	}
	bool operator!=(const int num) const
	{
		// false iff Pointer is null and int is zero
		return !(num == 0); 
	}
};


#endif // __TOMBSTONES_H__
