#ifndef LIST_H
#define LIST_H

// iterator classes derive from this for stdlib algorithm compatibily
#include <iterator> 

template <class T>
class List 
{
	private:
		struct Node
		{
			Node(const T x, Node* y = 0):data(x),next(y),prev(y) {}
			T data;
			Node *next;
			Node *prev;
		};

		// pointers to the begin and the end of the list
		Node *first_;
		Node *last_;

	public:
		class iterator;

		class const_iterator: public std::iterator<std::bidirectional_iterator_tag, const T>
		{
			private:
				const Node* iter;

				friend class iterator;

			public:
				const_iterator(const Node *x = 0):iter(x) {}
				const_iterator(const const_iterator &it):iter(it.iter) {}
				const_iterator(const iterator &it):iter(it.iter) {}
				const_iterator& operator=(const_iterator const &it);
				const_iterator& operator=(iterator const &it);

				const_iterator& operator++(); // ++it   
				const_iterator operator++(int); // it++
				const_iterator& operator--(); // --it   
				const_iterator operator--(int); // it--
				bool operator== (const const_iterator &i) const;
				bool operator!=(const const_iterator &i) const;
				T operator* () const; 
		};

		class iterator: public std::iterator<std::bidirectional_iterator_tag, T>
		{
			private:
				Node *iter;

				friend class const_iterator;

			public:
				iterator(Node *x = 0):iter(x) {}
				iterator(const iterator &it):iter(it.iter) {}
				iterator& operator=(iterator const &it);

				iterator& operator++(); // ++it   
				iterator operator++(int); // it++
				iterator& operator--(); // --it   
				iterator operator--(int); // it--

				bool operator== (const iterator &i) const;
				bool operator!= (const iterator &i) const;
				T operator* () const;
		};


		List(): first_(0), last_(0) {}
		List(const T& i);
		List(const List& L);
		List<T>& operator=(const List& L);
		~List();
		void push_back(const T& i);
		void pop_front();
		bool empty();
		void clear();

		

		int size() { int i = 0; const_iterator b = begin(); 
			for (; b != end(); b++) { i++; }
			return i;
		}
			
		iterator begin() { return iterator(first_); };
		iterator end() { return iterator(0); };

		const_iterator begin() const { return const_iterator(first_); };
		const_iterator end() const { return const_iterator(0); };
};

#include "list.tpp"

#endif
