#include <memory>
#include <iostream>

	template <class T>
T Heap<T>::min()
{
	return data->data;
}

// The function removes the smallest T from the heap
	template <class T>
T Heap<T>::delMin()
{
	avail--;
	nodes--;
	HeapNode *min = data;
	HeapNode *last = avail;

	swap(min, last);

	heapify(min);

	T foo = avail->data;

	alloc.destroy(avail);

	return foo;
}

// This function removes any existing node from the heap.
// It returns true if the removing successed or false
// if the node didn't exist. 
template <class T>
bool Heap<T>::delNodeX(const T& nodedata)
{
	HeapNode *iter = data;

	// try to find the right node
	while ( (iter != avail) && (iter->data != nodedata))
	{
		iter++;
	}

	// the node was not found
	if (iter == avail)
	{
		return false;
	}
	else
	{
		avail--;
		nodes--;

		swap(iter, avail);
		heapify(iter);

		alloc.destroy(avail);

		return true;
	}
}

	template <class T>
int Heap<T>::parent(HeapNode *node)
{
	return ((node - data) / 2);
}

	template <class T>
int Heap<T>::left(HeapNode *node)
{
	return ((node-data) * 2 +1);
}

	template <class T>
int Heap<T>::right(HeapNode *node)
{
	return ((node-data) * 2 + 2);
}


	template <class T>
void Heap<T>::heapify(HeapNode *node)
{
	HeapNode *smallest = 0;
	int l = left(node);
	int r = right(node);


	if ( r <= (avail - data -1) ) // If both children exist
	{
		if ( (data +l)->key < (data +r)->key ) smallest = data + l; 
		else smallest = data + r;

		if (node->key > smallest->key )
		{
			swap(node, smallest);
			heapify(smallest);
		}
	}
	// if only the left child exists
	else
	{
		// swap if the left child is smaller than the node
		if ( (l == (avail - data -1)) && (node->key > (data+l)->key))
		{
			swap(node, (data + l));
		}
	}
}


	template <class T>
void Heap<T>::decKey(T nodedata, int newkey)
{
	HeapNode *iter = data;
	HeapNode *pnode = 0;

	// first find the right node which key will be decreased
	while ( (iter != avail) && (iter->data != nodedata))
	{
		iter++;
	}

	// if the node was found and its key is bigger than the new key
	if ( (iter != avail) && (iter->key > newkey) )
	{
		iter->key = newkey;
		pnode = data+parent(iter);

		while ( iter->key < pnode->key )
		{ 
			swap(iter, pnode);
			iter = pnode;
			pnode = data+parent(iter);
		}
	}
}

	template <class T>
Heap<T>::Heap(std::size_t n)
{
	if (n != 0)
	{
		data = alloc.allocate(n);
	}
	limit = data + n;
	avail = data;
	nodes = 0;
}

	template<class T>
void Heap<T>::push(const T& t, int key)
{
	HeapNode *i= 0;
	HeapNode *pnode = 0;

	if (avail == limit)
	{
		grow();
	}
	i = avail;

	alloc.construct(avail, HeapNode(t, key));

	avail += 1;
	nodes += 1;
	// the parent node of the last constructed HeapNode
	pnode = (data + parent(i));

	while ( (i != data) && (pnode->key > key) )
	{
		// swap the values
		swap(i, pnode);

		i = pnode;

		// the parent node of i
		pnode = (data + parent(i));
	}
}

	template <class T>
void Heap<T>::swap(HeapNode *i, HeapNode *j)
{
	T tempData = i->data;
	int tempKey = i->key;

	i->data = j->data;
	i->key = j->key;

	j->data = tempData;
	j->key = tempKey;

}

	template<class T>
void Heap<T>::grow()
{
	std::size_t new_size = (2* (limit-data) + 1);

	// Allocate new space and copy existing elements to the new space
	HeapNode *new_data = alloc.allocate(new_size);
	HeapNode *new_avail = std::uninitialized_copy(data, avail, new_data);

	uncreate();

	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

	template<class T>
Heap<T>::~Heap()
{
	uncreate();
}

	template <class T>
void Heap<T>::uncreate()
{
	if (data)
	{
		for (HeapNode *it = data; it != avail; it++)
		{
			alloc.destroy(it);
		}

		alloc.deallocate(data, limit - data);
	}

	data = limit = avail = 0;
}
