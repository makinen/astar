#ifndef HEAP_H
#define HEAP_H

#include <memory>

template<class T> 
class Heap
{
	public:
		Heap(): data(0), avail(0), limit(0), nodes(0) {}
		Heap(std::size_t n);
		~Heap();
		std::size_t size() { return nodes; }
		void push(const T& val, int key);
		void decKey(T data, int newkey);
		T min();
		T delMin();
		bool delNodeX(const T& nodedata);

	private:
		struct HeapNode
		{
			HeapNode(const T x, int key): data(x), key(key) {}
			T data;
			int key;
		};

		std::allocator<HeapNode> alloc;


		HeapNode *data;   // pointer to the first node in the heap array
		HeapNode *avail;  // pointer to (one past) the last constructed node
		HeapNode *limit;  // points to the last available node
		size_t nodes;     // the amount of nodes

		
		void grow();    // grow the heap size when it's full
		void uncreate();
		void swap(HeapNode *i, HeapNode *j);
		void heapify(HeapNode *i);

		int parent(HeapNode *child);
		int left(HeapNode *parent);
		int right(HeapNode *parent);
};

#include "heap.tpp"

#endif
