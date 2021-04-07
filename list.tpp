	template <class T>
List<T>::List(const T& i)
{
	first_ = new Node(i);
	last_ = first_;
}

	template <class T>
List<T>::List(const List& L)
{
	first_ = 0;
	last_ = first_;

	const_iterator it = L.begin();
	const_iterator it2 = L.end();

	for (; it != it2; it++)
	{
		push_back(*it);
	}
}

	template <class T>
List<T>& List<T>::operator=(const List<T>& L)
{
	// check for self-assignment
	if (&L != this)
	{
		(*this).clear();

		const_iterator it = L.begin();
		const_iterator it2 = L.end();

		for (; it != it2; it++)
		{
			push_back(*it);
		}

	}
	return *this;

}


	template <class T>
List<T>::~List()
{
	clear();
}

	template <class T>
void List<T>::push_back(const T& i)
{
	if (first_ == 0) // the List is empty
	{
		first_ = new Node(i);
		last_ = first_;
	}
	else
	{
		last_->next = new Node(i);
		last_->next->prev = last_;

		last_ = last_->next;
	}
}

	template <class T>
void List<T>::pop_front()
{

	if (!empty()) // is the List empty?
	{
		Node *nextnode;
	
		if (first_->next == 0)
		{
			delete first_;

			first_ = 0;
			last_ = 0;
		}
		else
		{
			nextnode = first_->next;
			nextnode->prev = 0;

			delete first_;

			first_ = nextnode;
		}
	}
}

	template <class T>
bool List<T>::empty()
{
	if (first_ == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

	template <class T>
void List<T>::clear()
{
	while ( !empty() )
	{
		pop_front();
	}
}

template <class T>
	typename List<T>::iterator& 
List<T>::iterator::operator=(iterator const &it)
{
	iter = it.iter; return *this;
}

template <class T>
	typename List<T>::iterator& 
List<T>::iterator::operator++()
{
	iter = iter->next; return *this;
}

template <class T>
	typename List<T>::iterator
List<T>::iterator::operator++(int)
{
	iterator tmp(*this); iter = iter->next; return tmp;
}

template <class T>
	typename List<T>::iterator& 
List<T>::iterator::operator--()
{
	iter = iter->prev; return *this;
}

template <class T>
	typename List<T>::iterator 
List<T>::iterator::operator--(int)
{
	iterator tmp(*this); iter = iter->prev; return tmp;
}

template <class T>
bool List<T>::iterator::operator==(const iterator &i) const
{
	return iter == i.iter;
}

template <class T>
bool List<T>::iterator::operator!=(const iterator &i) const
{
	return iter != i.iter;
}

template <class T>
T List<T>::iterator::operator*() const
{
	return iter->data;
}

template <class T>
	typename List<T>::const_iterator& 
List<T>::const_iterator::operator=(const_iterator const &it)
{
	iter = it.iter; return *this;
}

template <class T>
	typename List<T>::const_iterator& 
List<T>::const_iterator::operator=(iterator const &it)
{
	iter = it.iter; return *this;
}

template <class T>
	typename List<T>::const_iterator& 
List<T>::const_iterator::operator++()
{
	iter = iter->next; return *this;
}

template <class T>
	typename List<T>::const_iterator
List<T>::const_iterator::operator++(int)
{
	const_iterator tmp(*this); iter = iter->next; return tmp;
}

template <class T>
	typename List<T>::const_iterator& 
List<T>::const_iterator::operator--()
{
	iter = iter->prev; return *this;
}

template <class T>
	typename List<T>::const_iterator 
List<T>::const_iterator::operator--(int)
{
	const_iterator tmp(*this); iter = iter->prev; return tmp;
}

template <class T>
bool List<T>::const_iterator::operator==(const const_iterator &i) const
{
	return iter == i.iter;
}

template <class T>
bool List<T>::const_iterator::operator!=(const const_iterator &i) const
{
	return iter != i.iter;
}

template <class T>
T List<T>::const_iterator::operator*() const
{
	return iter->data;
}
