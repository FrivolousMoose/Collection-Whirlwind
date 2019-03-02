#include "ObjectPool.h"

template<typename T>
T* ObjectPool<T>::AllocateObject()
{
	if (m_activeCount < m_size)
	{
		return m_data + (m_activeCount++);
	}
}

template<typename T>
void ObjectPool<T>::DeallocateObject(T* index)
{
	index = m_data[--m_activeCount];
		//T[m_activeCount - 1] = T[index]
		//m_activeCount -= 1;
}

template<typename T>
int ObjectPool<T>::ReturnItems()
{
	return m_activeCount;
}

template<typename T>
int ObjectPool<T>::ReturnSize()
{
	return m_size;
}
