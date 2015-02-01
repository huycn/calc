#include "gkLogger.h"

#if !defined(NB_NO_LOG)

	#if !defined(NB_CUSTOM_LOGGER) && defined(NB_HAVE_QT)

	namespace Nubook
	{
		void SetLogVHandler(PrintLogFunc f)
		{
		}

		void SetLogDHandler(PrintLogFunc f)
		{
		}

		void SetLogWHandler(PrintLogFunc f)
		{
		}

		void SetLogEHandler(PrintLogFunc f)
		{
		}
	}

	#else // !NB_HAVE_QT

	#include <cstdarg>
	#include <cstdio>
	#include <mutex>

	namespace guitk
	{
		static std::mutex sDefaultLogMutex;

		static const char* kPrefixes[] = {"** ", "++ ", "-- ", "I: "};

		template <int prefixIndex>
		static void DefaultLogWE(const char* fmt, ...)
		{
			std::lock_guard<std::mutex> lock(sDefaultLogMutex);
			fprintf(stderr, kPrefixes[prefixIndex]);
			va_list argp;
			va_start(argp, fmt);
			vfprintf(stderr, fmt, argp);
			fprintf(stderr, "\n");
			va_end(argp);
		}

		static void NoopLog(const char*, ...)
		{
		}

		namespace details
		{
		#ifdef _DEBUG
			PrintLogFunc sLogVHandler = &DefaultLogWE<3>;
			PrintLogFunc sLogDHandler = &DefaultLogWE<2>;
		#else
			PrintLogFunc sLogVHandler = &NoopLog;
			PrintLogFunc sLogDHandler = &NoopLog;
		#endif
			PrintLogFunc sLogWHandler = &DefaultLogWE<1>;
			PrintLogFunc sLogEHandler = &DefaultLogWE<0>;
		}

	#if defined(NB_CUSTOM_LOGGER)

		void SetLogVHandler(PrintLogFunc f)
		{
			details::sLogVHandler = f;
		}

		void SetLogDHandler(PrintLogFunc f)
		{
			details::sLogDHandler = f;
		}

		void SetLogWHandler(PrintLogFunc f)
		{
			details::sLogWHandler = f;
		}

		void SetLogEHandler(PrintLogFunc f)
		{
			details::sLogEHandler = f;
		}

	#endif

	}

	#endif

#endif //!NB_NO_LOG

