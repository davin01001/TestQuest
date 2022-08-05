#pragma once

template<typename T>
class CArrayAutoPtr : public CAutoPtr<T>
{
public:
    CArrayAutoPtr<T>(void) throw() : CAutoPtr<T>() {}
    CArrayAutoPtr<T>(T * p) throw() : CAutoPtr<T>(p) {}

	virtual ~CArrayAutoPtr<T>(void) throw()
	{
		free();
	}

	inline void free(void) throw()
	{
		delete [] m_p;
		m_p = 0;
	}

	T * get(void) const throw()
	{	 
		return m_p;
	}
};
