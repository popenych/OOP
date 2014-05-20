#ifndef XLIST_OOP
#define XLIST_OOP

#include <exception>

template < class T > class XList 
{
	private:
		struct Node
	{
		Node ( T const & data )
			:m_data ( data ) { next = nullptr; prev = nullptr; }

		~Node() {}

		T m_data;
		Node * next;
		Node * prev;
	};

public:

	class ListIsEmpty: public std::exception
	{
		virtual char const * what() const throw() { return "List is empty! Can not find first or last element."; };
	};
	
	class XIterator
	{
		
	public:
		
		XIterator( Node * pointer ) {	m_element = pointer; }
		XIterator( XIterator const & other ) { m_element = other.m_element; }
		
		XIterator & operator = ( XIterator const & input )
		{
			m_element = input.m_element;
			return *this;
		}
		
		bool operator == ( XIterator const & other ) { return m_element == other.m_element; }
		bool operator != ( XIterator const & other ) { return m_element != other.m_element; }
		
		T operator * () const { return m_element->m_data(); }

		T & operator * () { return m_element->m_data; }

		T operator -> () { return m_element->m_data; }
		
		XIterator & operator++()
		{
			m_element = m_element->next;
			return *this;
		}

		XIterator operator++( int )
		{
			XIterator temp = *this;
			++(*this);
			return temp;
		}

		XIterator & operator--()
		{
			m_element = m_element->prev;
			return *this;
		}

		XIterator operator--( int )
		{
			XIterator temp = *this;
			--*this;
			return temp;
		}

	private:

		Node * m_element;
	};

	XList()
		:m_head( nullptr )
		,m_tail ( nullptr )
		,m_size( 0 ) {}
	
	XList ( const XList & orig )
	{
		m_head = orig.m_head;
		m_tail = orig.m_tail;
		m_size = orig.m_size;
	}
	
	~XList () { remove(); }

	XIterator begin() const { return XIterator(m_head); }

	XIterator end() const { return XIterator(m_tail); }

	void push_front ( T const & data )
	{
		if ( nullptr == m_head)
		{
			m_head = new Node( data );
			m_tail = m_head;	
		}
		else
		{
			Node * element = new Node( data );			
			element->next = m_head;

			m_head->prev = element;
			m_head = element;
		}
		++m_size;
	}

	void pop_front()
	{
		if ( m_head != nullptr )
		{
			Node * element = m_head->next;
			delete m_head;
			m_head = element;
			m_head->prev = nullptr;
			--m_size;
		}
		else
		{
			throw ListIsEmpty();
		}
	}
	
	void push_back ( T const & data )
	{
		if ( nullptr == m_tail )
		{
			m_tail = new Node ( data );
			m_head = m_tail;
		}
		else
		{
			Node * element = new Node ( data );			
			element->prev = m_tail;

			m_tail->next = element;
			m_tail = element;
		}
		++m_size;
	}
	
	void pop_back()
	{
		if ( m_tail != nullptr )
		{
			Node * element = m_tail->prev;
			delete m_tail;
			m_tail = element;
			m_tail->next = nullptr;
			--m_size;
		}
		else
		{
			throw ListIsEmpty();
		}
	}

	T get_first() const
	{
		if ( m_head != nullptr )
		{
			return m_head->m_data;
		}
		else
		{
			throw ListIsEmpty();
		}		
	}

	T get_last() const
	{
		if ( m_tail != nullptr )
		{
			return m_tail->m_data;		
		}
		else
		{
			throw ListIsEmpty();	
		}
	}

	void remove()
	{
		Node * pointer = m_head;
		while( pointer != nullptr )
		{
			Node* temp_pointer = pointer;
			pointer = pointer->next;
			delete temp_pointer;
		}
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	
	}

	size_t get_size() const { return m_size; }

	bool is_empty() const { return ( nullptr == m_head ); }

	
	private:

		Node * m_head;
		Node * m_tail;
		size_t m_size;

	};

#endif