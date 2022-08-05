#pragma once

#include <stdexcept>
#include <atltrace.h>
                                                                                                                
class SLSException : public std::runtime_error
{
public:
	/** 
	* All the BCP based error codes. 
	* The range used is between 100 - 199.
	*/
	enum SLSExceptionErrorCode
	{
		/** Success. */
		NoError = 0,
		/** DO initialisation error. */
		DOInitError = -100,					// All data object errors mapped from -100 to -199
		/** BO initialisation error. */
		BOInitError = -200,					// All business object errors mapped from -200 to -299
		/** UO error. */
		UOUIError = -300,					// All user object errors mapped from -300 to -399
		/** XML error. */
		XMLError = -400,					// All XML errors mapped from -400 to -499
		/** Security error. */
		SecError = -500,					// All Security manage errors from -500 to -599
		/** Comm Error. */				
		ComError = -600						//All COM errors
	};

public: 

    /**
    * Constructor from message and error code.
    * @param msg [in] Exception message.
    * @param code [in] Exception code.
    * @param file [in] File where exception occurred.
    * @param line [in] Line where exception occurred.
	*/
    SLSException(
                  const char *msg,    
                  SLSExceptionErrorCode code, 
                  const char file[], 
                  int line           
                 ) throw ()
	:	m_code(code),
		m_file(file),
		m_line(line),
		runtime_error(msg)	
	{
		ATLTRACE2(L"SLSException::SLSException\tmessage: %S, code: %d, thrown at: %S, line: %d\n", 
								msg, code, file, line);
	}
	   
	/**
    * Constructor from message and error code (UNICODE).
    * @param msg [in] Exception message.
    * @param code [in] Exception code.
    * @param file [in] File where exception occurred.
    * @param line [in] Line where exception occurred.
	*/
    SLSException(const std::wstring & msg, SLSExceptionErrorCode code, const char file[], int line) throw ()
		: m_code(code), m_file(file), m_line(line), runtime_error(std::string(msg.begin(), msg.end()))
	{
		ATLTRACE2(L"SLSException::SLSException\tmessage: %s, code: %d, thrown at: %s, line: %d\n", msg, code, file, line);
	}
	
public:

	/**
    * Returns exception error code.
    * @return BCPManagerErrorCode - exception error code.
    */
	inline SLSExceptionErrorCode     GetCode() const throw()
	{ 
		return m_code;	
	}
	
	/**
    * Returns filename where exception occurred.
    * @return const char * - filename where exception occurred.
    */
	inline const char *const GetFile() const throw()
	{ 
		return m_file;	
	}


    /**
    * Returns line where exception occurred.
    * @return int - line where exception occurred.
    */
	inline int GetLine() const throw()
	{ 
		return m_line;	
	}

private:
	/** Error code. */
	const	SLSExceptionErrorCode	m_code;            
	/** file name. */
	const char	*const m_file;                     
	/** line number. */
	const int m_line;     
};
