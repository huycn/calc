#pragma once

#if defined(NB_NO_LOG)

	#define LOGV(...)
	#define LOGD(...)
	#define LOGW(...)
	#define LOGE(...)

#else
	#if defined(GK_LOG_TAG)
		#define GK_GET_LOG_TAG #GK_LOG_TAG ": "
	#else
		#define GK_GET_LOG_TAG
	#endif

	namespace guitk
	{
		typedef void (*PrintLogFunc)(const char* fmt, ...);

	#if defined(GK_CUSTOM_LOGGER)
		void SetLogVHandler(PrintLogFunc f);	// f should be thread-safe
		void SetLogDHandler(PrintLogFunc f);	// f should be thread-safe
		void SetLogWHandler(PrintLogFunc f);	// f should be thread-safe
		void SetLogEHandler(PrintLogFunc f);	// f should be thread-safe
	#endif
	}

	#if !defined(NB_CUSTOM_LOGGER) && defined(NB_HAVE_QT)

		#include <qlogging.h>

		#define LOGV(...) qDebug(GK_GET_LOG_TAG __VA_ARGS__)
		#define LOGD(...) qDebug(GK_GET_LOG_TAG __VA_ARGS__)
		#define LOGW(...) qWarning(GK_GET_LOG_TAG __VA_ARGS__)
		#define LOGE(...) qCritical(GK_GET_LOG_TAG __VA_ARGS__)

	#else // NB_CUSTOM_LOGGER || !NB_HAVE_QT

		namespace guitk {
			namespace details {
				extern PrintLogFunc sLogVHandler;
				extern PrintLogFunc sLogDHandler;
				extern PrintLogFunc sLogWHandler;
				extern PrintLogFunc sLogEHandler;
			}
		}

		#define LOGV(...) (*guitk::details::sLogVHandler)(GK_GET_LOG_TAG __VA_ARGS__);
		#define LOGD(...) (*guitk::details::sLogDHandler)(GK_GET_LOG_TAG __VA_ARGS__);
		#define LOGW(...) (*guitk::details::sLogWHandler)(GK_GET_LOG_TAG __VA_ARGS__);
		#define LOGE(...) (*guitk::details::sLogEHandler)(GK_GET_LOG_TAG __VA_ARGS__);

	#endif

#endif // !NB_NO_LOG
