#pragma once
#include "gkString.h"

namespace guitk {

class Exception
{
public:
	virtual ~Exception() throw() {;}
	virtual const TCHAR * what() const throw() {return mMsg.c_str();}
	virtual const TCHAR * desc() const throw() {return _T("Error");}

protected:
	Exception(const String &msg) : mMsg(msg) {;}

private:
	String mMsg;
};

class MemoryError : public Exception
{
public:
	MemoryError(const String &msg) : Exception(msg) {;}
	virtual ~MemoryError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Memory Error");}
};

class FatalError : public Exception
{
public:
	FatalError(const String &msg) : Exception(msg) {;}
	virtual ~FatalError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Fatal Error");}
};

class CalculError : public Exception
{
public:
	CalculError(const String &msg) : Exception(msg) {;}
	virtual ~CalculError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Calcul Error");}
};

class DivideByZero : public CalculError
{
public:
	DivideByZero(const String &msg) : CalculError(msg) {;}
	virtual ~DivideByZero() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Divide by Zero");}
};

class ResultInfinity : public CalculError
{
public:
	ResultInfinity(const String &msg) : CalculError(msg) {;}
	virtual ~ResultInfinity() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Infinity As Result");}
};

class MaxIterExceeded : public CalculError
{
public:
	MaxIterExceeded(const String &msg) : CalculError(msg) {;}
	virtual ~MaxIterExceeded() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Max Iteration Excceded");}
};

class IOError : public Exception
{
public:
	IOError(const String &msg) : Exception(msg) {;}
	virtual ~IOError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("IO Error");}
};

class PrintingError : public IOError
{
public:
	PrintingError(const String &msg) : IOError(msg) {;}
	virtual ~PrintingError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Printing Error");}
};

class FileAccessError : public IOError
{
public:
	FileAccessError(const String &msg) : IOError(msg) {;}
	virtual ~FileAccessError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("File Access Error");}
};

class DataFormatError : public IOError
{
public:
	DataFormatError(const String &msg) : IOError(msg) {;}
	virtual ~DataFormatError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Data Format Error");}
};

class ObjectStateError : public Exception {
public:
	ObjectStateError(const String &msg) : Exception(msg) {;}
	virtual ~ObjectStateError() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Object State Error");}
};

class InvalidParam : public Exception
{
public:
	InvalidParam(const String &msg) : Exception(msg) {;}
	virtual ~InvalidParam() throw() {;}
	virtual const TCHAR * desc() const throw() {return _T("Invalid Parameter");}
};

} // namespace guitk
