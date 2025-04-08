#pragma once

#include <stdio.h>

template<class Type>

class CQueue
{
public:
	CQueue(void)
	{
		this->m_Begin = NULL;
		this->m_End = NULL;
		this->m_Current = NULL;
		this->m_bEmpty = true;
		this->m_lCount = 0L;
	}


	virtual ~CQueue(void)
	{
		this->Clear();
	}

	void Clear()
	{
		while ( this->m_Begin )
		{
			this->m_Current = this->m_Begin->next;
			delete this->m_Begin;
			this->m_Begin = this->m_Current;
		}
		this->m_Begin = NULL;
		this->m_End = NULL;
		this->m_Current = NULL;
		this->m_lCount = 0L;

		this->m_bEmpty = true;
	}

	inline bool IsEmpty()
	{ 
		return this->m_bEmpty; 
	}

	void Push(const Type& item)
	{
		if(this->IsEmpty())
		{
			this->m_Begin = new Package;
			this->m_Begin->next = NULL;
			this->m_Begin->prev = NULL;
			this->m_Begin->item = item;
			this->m_End = this->m_Begin;
		}
		else
		{
			Package* hlp;
			hlp = new Package;
			hlp->item = item;
			hlp->next = NULL;
			hlp->prev = this->m_End;
			this->m_End->next = hlp;
			this->m_End = hlp;
		}

		this->m_bEmpty = false;
		++this->m_lCount;
	}

	void PopCurrent(void)
	{
		if( !this->IsEmpty() )
		{
			if( this->m_Current )
			{
				Package *left, *right;
				right = this->m_Current->next;
				left = this->m_Current->prev;

				delete this->m_Current;
				--this->m_lCount;
				if( left && right )
				{
					this->m_Current = left;
					left->next = right;
					right->prev = left;
				}
				else if( left )
				{
					this->m_Current = left;
					left->next = NULL;
					this->m_End = left;
				}
				else if( right )
				{
					this->m_Current = right;
					right->prev = NULL;
					this->m_Begin = right;
				}
				else
				{
					this->m_Begin = NULL;
					this->m_Current = NULL;
					this->m_End = NULL;
					this->m_bEmpty = true;
					this->m_lCount = 0L;
				}
			}
		}
	}

	void Pop(void)
	{
		if( !this->IsEmpty() )
		{
			Package *hlp;
			hlp = this->m_Begin->next;

			delete this->m_Begin;
			this->m_Begin = hlp;

			if( !this->m_Begin )
			{
				this->m_End = NULL;
				this->m_bEmpty = true;
			}
			--this->m_lCount;
		}
	}

	inline void SetFirst()
	{
		if(!this->IsEmpty() && this->m_Begin)
			this->m_Current = this->m_Begin;
	}

	inline void SetNext()
	{ 
		if(!this->IsEmpty() && this->m_Current)
			this->m_Current = this->m_Current->next; 
	}

	inline void GetCurrent(Type &item)
	{ 
		if(!this->IsEmpty() && this->m_Current)
		{
			item = this->m_Current->item;
		}
	}

	inline Type GetCurrent()
	{
		if(!this->IsEmpty() && this->m_Current)
			return this->m_Current->item;
		else 
			return NULL;
	}

	inline void SetLast()
	{
		if (!this->IsEmpty() && this->m_End)
			this->m_Current = this->m_End;
	}

	inline long GetCount()
	{
		if (this->IsEmpty())
			return 0;
		else
			return this->m_lCount;
	}

private:
	struct Package
	{
		Package*	next;
		Package*	prev;
		Type		item;
	};

	bool			m_bEmpty;
	Package*		m_Begin;
	Package*		m_End;
	Package*		m_Current;
	long			m_lCount;
};