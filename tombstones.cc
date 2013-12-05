#include "tombstones.h"

template <class T>
class Pointer {
private:
	bool hasVal;
	T& entity;
	referenceCount;
public:
    Pointer<T>() // default constructor
		{
			hasVal = false;
			referenceCount = 0;
		}
    Pointer<T>(Pointer<T>& otherP)
		{
			entity = *otherP;
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
			return entity;	
		}// deferencing

    T* operator->() const
		{
			if(!(entity == NULL || !hasVal))
				return *entity;	
			else
			{
				throw new std::exception("dangling reference");
			}	
		}// field dereferencing

    Pointer<T>& operator=(const Pointer<T>& other)
		{
			other->referenceCount++;
			referenceCount--;
			return other;	
		}// assignment

    friend void free(Pointer<T>& pointer)
		{
			delete(pointer->entity);
			hasVal = false;
		}// delete pointed-at object
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    // equality comparisons:
    bool operator==(const Pointer<T>& other) const
		{
			if(hasVal && other->hasVal)
			{
				return entity == other->entity;
			}
			else
			{
				if(!other->hasVal)
					throw new std::exception("argument has no data");
				if(!hasVal)
					throw new std::exception("current pointer has no data");
			}
		}
    bool operator!=(const Pointer<T>& other) const
		{
			return !(this == other);
		}
    bool operator==(const int num) const
		{
			// true iff Pointer is null and int is zero
			return num == 0 && entity == NULL;
		}
    bool operator!=(const int num) const
		{
			// false iff Pointer is null and int is zero
			return !(this == 0); 
		}
}
