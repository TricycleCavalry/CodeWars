#ifndef _WRAPPED_MAP_HEADER_
#define _WRAPPED_MAP_HEADER_

#include "GrowingArray.h"
#include <map>
#include "DL_Debug.h"

template<typename Key, typename Type>
class WrappedMap
{
public:
	WrappedMap(int aRecommendedNumberOfItems = 64);
	~WrappedMap();

	void Add(const Type& anItem, const Key& aKey);
	void Add(const Key& aKey);
	void Remove(const Type& anItem);
	void Remove(const Key& aKey);

	inline Type& operator[](const Key& aKey);
	inline const Type& operator[](const Key& aKey) const;

	inline Type& GetWithIndex(const int& aIndex);
	inline const Type& GetWithIndex(const int& aIndex) const;

	inline bool FindKey(const Type& anItem, Key& aKeyToSet);
	inline bool FindItem(Type& anItemToFind, const Key& aKey);

	inline bool HasItem(const Key& aKey) const;
	inline bool HasItem(const Key& aKey);

	inline const GrowingArray<Key>& GetKeys() const;
	inline const GrowingArray<Key>& GetKeys();

	inline void Clear();

	__forceinline int Count() const;
private:

	std::map<Key,Type> myMap;
	GrowingArray<Key> myKeys;
};

template<typename Key,typename Type>
WrappedMap<Key,Type>::WrappedMap(int aRecommendedNumberOfItems)
:	myKeys(aRecommendedNumberOfItems)
{
}

template<typename Key,typename Type>
WrappedMap<Key,Type>::~WrappedMap()
{
}

template<typename Key,typename Type>
void WrappedMap<Key,Type>::Add(const Type& anItem, const Key& aKey)
{
	myMap[aKey] = anItem;
	if(HasItem(aKey) == false)
	{
		myKeys.Add(aKey);
	}
}

template<typename Key,typename Type>
void WrappedMap<Key,Type>::Add(const Key& aKey)
{
	myMap[aKey];
	if(HasItem(aKey) == false)
	{
		myKeys.Add(aKey);
	}
}

template<typename Key,typename Type>
void WrappedMap<Key,Type>::Remove(const Type& anItem)
{
	Key itemKey;
	if(Find(anItem,itemKey) == true)
	{
		myMap.erase(itemKey);
		myKeys.RemoveCyclic(itemKey);
	}
}

template<typename Key,typename Type>
void WrappedMap<Key,Type>::Remove(const Key& aKey)
{
	if(HasItem(aKey) == true)
	{
		myMap.erase(aKey);
		myKeys.RemoveCyclic(aKey);
	}
}

template<typename Key,typename Type>
inline Type& WrappedMap<Key,Type>::operator[](const Key& aKey)
{
#ifndef RETAIL
	if(HasItem(aKey) == false)
	{
		DL_ASSERT("Tried to access WrappedMap with the key: %s, that does not exist!", aKey.c_str());
	}
#endif
	return myMap[aKey];
}

template<typename Key,typename Type>
inline const Type& WrappedMap<Key,Type>::operator[](const Key& aKey) const
{
	if(HasItem(aKey) == false)
	{
		DL_ASSERT("Tried to access WrappedMap with a key that does not exist!");
	}
	return myMap.at(aKey);
}

template<typename Key,typename Type>
inline Type& WrappedMap<Key,Type>::GetWithIndex(const int& aIndex)
{
	return myMap[myKeys[aIndex]];
}

template<typename Key,typename Type>
inline const Type& WrappedMap<Key,Type>::GetWithIndex(const int& aIndex) const
{
	return myMap[myKeys[aIndex]];
}

template<typename Key,typename Type>
inline bool WrappedMap<Key,Type>::FindKey(const Type& anItem, Key& aKeyToSet)
{
	for(std::map<Key,Type>::iterator iter = myMap.begin();iter!=myMap.end();iter++)
	{
		if(iter->second == anItem)
		{
			aKeyToSet = iter->first;
			return true;
		}
	}
	return false;
}

template<typename Key,typename Type>
inline bool WrappedMap<Key,Type>::FindItem(Type& anItemToFind, const Key& aKey)
{
	for(std::map<Key,Type>::iterator iter = myMap.begin();iter!=myMap.end();iter++)
	{
		if(iter->first == aKey)
		{
			anItemToFind = iter->second;
			return true;
		}
	}
	return false;
}

template<typename Key,typename Type>
inline bool WrappedMap<Key,Type>::HasItem(const Key& aKey) const
{
	return myKeys.Find(aKey) != GrowingArray<Key>::FoundNone;
}

template<typename Key,typename Type>
inline bool WrappedMap<Key,Type>::HasItem(const Key& aKey)
{
	return myKeys.Find(aKey) != GrowingArray<Key>::FoundNone;
}

template<typename Key,typename Type>
inline const GrowingArray<Key>& WrappedMap<Key,Type>::GetKeys() const
{
	return myKeys;
}

template<typename Key,typename Type>
inline const GrowingArray<Key>& WrappedMap<Key,Type>::GetKeys()
{
	return myKeys;
}

template<typename Key,typename Type>
inline void WrappedMap<Key,Type>::Clear()
{
	myMap.clear();
	myKeys.RemoveAll();
}

template<typename Key,typename Type>
__forceinline int WrappedMap<Key,Type>::Count() const
{
	return myKeys.Count();
}

#endif