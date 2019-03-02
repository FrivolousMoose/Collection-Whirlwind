template <typename T>
class ObjectPool {
public:
	ObjectPool(unsigned int size)
	{
		m_activeCount = 0;
		m_size = size;
		m_data = new T[size];
	}
	~ObjectPool() { delete[] m_data; }
	T* AllocateObject()
	{
		if (m_activeCount < m_size)
		{
			return m_data + (m_activeCount++);
		}
	}
	void DeallocateObject(T* index)
	{
		*index = m_data[--m_activeCount];
		//T[m_activeCount - 1] = T[index]
		//m_activeCount -= 1;
	}
	int ReturnItems()
	{
		return m_activeCount;
	}
	int ReturnSize()
	{
		return m_size;
	}
private:
	unsigned int m_activeCount = 0; // also refers to next inactive index
	unsigned int m_size = 0;
	T* m_data = nullptr;
};


