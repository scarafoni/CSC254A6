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
};

template <class T>
class Pointer {
private:
	T* entity;
	bool isNull;
	int referenceCount;
public:
	//tombstone<T> ts;
	tombstone<T>* tsp;
	bool getIsNull()
	{return isNull;}

	friend void setIsNull(Pointer<T> &pointer)
	{pointer.isNull = true;}

	void printInfo(string name)
	{
		cout<<"printing info on "<<name<< "\n";
		printf("\t location- %p\n",this);
		printf("\t entity (loc, data)- %p, %d\n",tsp->entity,*(tsp->entity));
		printf("\t null %d\n",(tsp->isNull));
		printf("\t refcount- %d\n",tsp->referenceCount);
	}
	Pointer<T>() // default constructor
	{
		cout << "default " << this << "\n";
		//tsp = &ts;
		tsp = new tombstone<T>;
		tsp->entity = 0;
		tsp->isNull = true;
		tsp->referenceCount = 0;
	}
	Pointer<T>(Pointer<T>& otherP)
	{
		cout << "copy constructor " << this << "\n";
		if(otherP.tsp->isNull)
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
			tsp->isNull = false;

		tsp->entity = otherEntity;
		tsp->referenceCount = 1;
	}// bootstrapping constructor
			// argument should always be a call to new

	~Pointer<T>()
	{
		cout << "refs left (before delete) "<<tsp->referenceCount<<"\n";
		tsp->referenceCount--;
		cout << "deconstructor. " << this << tsp << " refs left- " << tsp->referenceCount << " freed? "<< (tsp->isNull) << " \n";
		if(tsp->referenceCount == 0 && !tsp->isNull)
			throw mlExp;
	}// destructor

	T& operator*() const
	{
		printf("* on %p\n",this);
		if(!tsp->isNull)
		{
			//printf("not null\n");
			//if (entity)
				//printf("value in *: %p %d\n", this->entity, *(this->entity));
			//else
				//printf("value in *: %p\n", this->entity);
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
		if(tsp->entity)
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
		printf("= to pointer %p = %p\n", this, &other);
		if(tsp != other.tsp)
		{
			tsp = other.tsp;
			other.tsp->referenceCount++;
		}
		/*referenceCount++;
		tsp->entity = other.tsp->entity;
		isNull = false;
		return *this;	
		*/
	}// assignment

	friend void free(Pointer<T>& pointer)
	{
		if(pointer.tsp->isNull)
			throw drExp;
		pointer.printInfo("free");
		free(&*pointer);
		pointer.tsp->isNull = true;
	/*
		printf("freeing %p\n",&*pointer);
		if(pointer.getIsNull())
		{
			cout << "this is null\n";
			throw drExp;
		}
		free(&*pointer);
		setIsNull(pointer);
		*/
	}// delete pointed-at object
			// This is essentially the inverse of the new inside the call to
			// the bootstrapping constructor.
	// equality comparisons:
	bool operator==(const Pointer<T>& other) const
	{
		printf("== on %p and %p\n",entity,&*other);
		if(!isNull)
		{
			return entity == &*other;
		}
		else
			throw drExp;
	}
	bool operator!=(const Pointer<T>& other) const
	{
		printf("!= on %p and %p\n",entity,&*other);
		if(!tsp->isNull)
			return tsp->entity != other.tsp->entity;
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
