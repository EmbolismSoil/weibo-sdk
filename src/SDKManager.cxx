#include "config.h"
#include "SDKManager.hxx"
#include <stdio.h>
#include <stdarg.h>
//#include <boost/make_shared.hpp>
#include "Urlcode.h"
#include "SDKHelper.hxx"
#include "ParsingObject.hxx"
#include "strconv.h"

#if defined(INTERNAL_INTERFACE_USEABLE)
#	include "Internal/SDKInternalMethod.hxx"
#else
#	include "SDKMethodImpl.hxx"
#endif //

using namespace weibo;

#ifdef LOG_SUPPORT
#	define DEFAULT_SUBSYSTEM "WeiboSDKV4"
#	include <util/log/Logger.hxx>
#else
#	define CerrLog(args_)
#	define StackLog(args_)
#	define DebugLog(args_)
#	define InfoLog(args_)
#	define WarningLog(args_)
#	define ErrLog(args_)
#	define CritLog(args_)
#endif

namespace weibo
{
	struct UploadTaskDetail
	{
		typedef boost::shared_ptr<httpengine::PostFormStreamData> PostFormDataPtr;

		UploadTaskDetail(const char* fileName)
			: fileName_(Util::StringUtil::getNotNullString(fileName))
			, fileSize_(0)
			, fileSeek_(0)
		{
#ifdef WIN32
			FILE* file = _wfopen(CUTF82W(fileName_.c_str()).c_str(), L"rb");
#else
			FILE* file = fopen(fileName_.c_str(), "rb");
#endif
			if (file)
			{
				fseek(file, 0, SEEK_END);
				fileSize_ = ftell(file);
				fseek(file, 0, SEEK_SET);
				fclose(file);
			}
		}

		size_t doReadFile(void* uploadBuffer, size_t bufSize)
		{
			if (fileSeek_ >= fileSize_)
			{
				return 0;
			}

#ifdef WIN32
			FILE* file = _wfopen(CUTF82W(fileName_.c_str()).c_str(), L"rb");
#else
			FILE* file = fopen(fileName_.c_str(), "rb");
#endif
			if (file)
			{
				if (fileSize_ > bufSize)
				{
					fseek(file, fileSeek_, SEEK_SET);

					size_t fileSurplusSize = (fileSize_ - fileSeek_);
					if (fileSurplusSize < bufSize)
					{
						bufSize = fileSurplusSize;
					}
				}
				else
				{
					bufSize = fileSize_;
				}

				fileSeek_ += fread(uploadBuffer, sizeof(char), bufSize, file);
				fclose(file);

				return bufSize;
			}
			return 0;
		}

		PostFormDataPtr getPostFormData(unsigned requestId, httpengine::IHttpEngine* engine)
		{
			if (!postFormDataPtr_)
			{
				postFormDataPtr_.reset(new httpengine::PostFormStreamData(requestId, engine, NULL));
			}
			return postFormDataPtr_;
		}

		size_t fileSeek_;
		size_t fileSize_;
		std::string fileName_;
		PostFormDataPtr postFormDataPtr_;
	};

	WeiboRequest::WeiboRequest()
		: mTaskId(0)
		, mOptionId(WBOPT_NONE)
		, mHttpMethod(httpengine::HM_GET)
	{
		memset(&mTaskInfo, 0, sizeof(UserTaskInfo));
	}

	void WeiboRequest::makeUploadTaskDetail(const char* file)
	{
		mUploadTaskDetail.reset();
		if (file)
		{
			mUploadTaskDetail.reset(new UploadTaskDetail(file));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// manager implements

SDKManager::SDKManager()
: mRequestFormat(WRF_JSON)
, mMaxActiveCounts(10)
{
	DebugLog(<< __FUNCTION__ << "| cotr");

#if defined(INTERNAL_INTERFACE_USEABLE)
	mMethodPtr.reset(new SDKInternalMethod(this));
#else
	mMethodPtr.reset(new SDKMethodImpl(this));
#endif //INTERNAL_INTERFACE_USEABLE
}

SDKManager::~SDKManager()
{
	DebugLog(<< __FUNCTION__ << "| detr");
}

int SDKManager::startup()
{
	DebugLog(<< __FUNCTION__);

	if (!mHttpEnginePtr)
	{
		mHttpEnginePtr = httpengine::HttpEngineFactory::createHttpEngine();
	}

	if (mHttpEnginePtr)
	{
		mHttpEnginePtr->initialize();

		mHttpEnginePtr->OnRequestWriteEvent += std::make_pair(this, &SDKManager::onRequestWriteAction);
		mHttpEnginePtr->OnRequestReadEvent += std::make_pair(this, &SDKManager::onRequestReadAction);
		mHttpEnginePtr->OnRequestHeaderEvent += std::make_pair(this, &SDKManager::onRequestHeaderAction);

		mHttpEnginePtr->OnRequestStartedNotify += std::make_pair(this, &SDKManager::onRequestStarted);
		mHttpEnginePtr->OnRequestStopedNotify += std::make_pair(this, &SDKManager::onRequestStoped);
		mHttpEnginePtr->OnRequestErroredNotify += std::make_pair(this, &SDKManager::onRequestErrored);
		mHttpEnginePtr->OnRequestComplatedNotify += std::make_pair(this, &SDKManager::onRequestComplated);
		mHttpEnginePtr->OnRequestReleaseNotify += std::make_pair(this, &SDKManager::onRequestWillRelease);

		//mHttpEnginePtr->OnRequestProgressNotify += std::make_pair(this, &SDKManager::onRequestProgress);// Not used now!
	}
	return 0;
}

int SDKManager::shutdown()
{
	DebugLog(<< __FUNCTION__);

	if (mHttpEnginePtr)
	{
		mHttpEnginePtr->OnRequestReadEvent -= std::make_pair(this, &SDKManager::onRequestWriteAction);
		mHttpEnginePtr->OnRequestWriteEvent -= std::make_pair(this, &SDKManager::onRequestReadAction);
		mHttpEnginePtr->OnRequestHeaderEvent -= std::make_pair(this, &SDKManager::onRequestHeaderAction);

		mHttpEnginePtr->OnRequestStartedNotify -= std::make_pair(this, &SDKManager::onRequestStarted);
		mHttpEnginePtr->OnRequestStopedNotify -= std::make_pair(this, &SDKManager::onRequestStoped);
		mHttpEnginePtr->OnRequestErroredNotify -= std::make_pair(this, &SDKManager::onRequestErrored);
		mHttpEnginePtr->OnRequestComplatedNotify -= std::make_pair(this, &SDKManager::onRequestComplated);
		mHttpEnginePtr->OnRequestReleaseNotify -= std::make_pair(this, &SDKManager::onRequestWillRelease);

		//mHttpEnginePtr->OnRequestProgressNotify -= std::make_pair(this, &SDKManager::onRequestProgress);// Not used now.

		mHttpEnginePtr->unInitialize();
		mHttpEnginePtr.reset();
	}
	return 0;
}

void SDKManager::stopAll()
{
	//TODO(welbon): To stop all.
}

void SDKManager::setOption(const eWeiboOption option, ...)
{
	va_list arg ;
	va_start(arg, option);

	switch(option)
	{
	case WOPT_CONSUMER:///< char *appkey, const char *appsecret
		{
			if (mMethodPtr)
			{
				std::string key = Util::StringUtil::getNotNullString(va_arg(arg, const char *));
				std::string secret = Util::StringUtil::getNotNullString(va_arg(arg, const char *));

				mMethodPtr->setConsumer(key, secret);
			}
		}
		break;

	case WOPT_PROXY: ///< eWeiboProxyType type, char *host, int port, char *proxyuser, char *password
		{
			if (mHttpEnginePtr)
			{
				httpengine::ProxyInfo proxy;
				proxy.mProxyType = (httpengine::ProxyInfo::eProxyType)va_arg(arg, const int);
				proxy.mServer = Util::StringUtil::getNotNullString(va_arg(arg, const char*));
				proxy.mPort = va_arg(arg, const int);
				proxy.mUsername = Util::StringUtil::getNotNullString(va_arg(arg, const char*));
				proxy.mPassword = Util::StringUtil::getNotNullString(va_arg(arg, const char*));

				mHttpEnginePtr->setOption(httpengine::EOT_PROXY, 
					&proxy, sizeof(httpengine::ProxyInfo), false);
			}
		}
		break;

	case WOPT_RESPONSE_FORMAT:
		{
			if (mMethodPtr)
			{
				const eWeiboRequestFormat format = (const eWeiboRequestFormat)va_arg(arg, int);
				mMethodPtr->setUnifiedFormat(format);
			}
		}
		break;

	case WOPT_ACCESS_TOKEN:
		{
			if (mMethodPtr)
			{
				std::string token = Util::StringUtil::getNotNullString(va_arg(arg, const char*));
				mMethodPtr->setAccesstoken(token);
			}
		}
		break;

	case WOPT_LOG_FILE:
		{
#if defined(LOG_SUPPORT)

			const char* file = Util::StringUtil::getNotNullString(va_arg(arg, const char*));

#	if defined(WIN32)

			if (file && file[0] != '\0')
			{
				CC2W cv(file);
				Util::Log::initialize(Util::Log::File | Util::Log::VSDebugWindow, 
					Util::Log::Debug, "WeiboSDK", cv.c_str());
			}
#	else

			if (file && file[0] != '\0')
			{
				Util::Log::initialize(Util::Log::File | Util::Log::VSDebugWindow, 
					Util::Log::Debug, "WeiboDesktop", file);
			}

#	endif //WIN32
#endif //LOG_SUPPORT
		}
		break;

	default:
		break;
	}
	va_end(arg);
}

void SDKManager::getOption(const eWeiboOption option, ...)
{
}

IWeiboMethod *SDKManager::getMethod()
{
	return mMethodPtr.get();
}

unsigned int SDKManager::onRequestReadAction(unsigned int requestId, void* data, unsigned int dataSize, const int dataCounts
											 , unsigned int errorCode, const int subErrorCode, void* userData)
{
	WeiboRequestPtr requestPtr = 
		internalFindRequestFromActiveMap(requestId);

	if (requestPtr && requestPtr->mUploadTaskDetail)
	{
		return requestPtr->mUploadTaskDetail->doReadFile(data, dataCounts);
	}
	else
	{
		ErrLog(<< __FUNCTION__ << " | Read file errored.");
	}
	return 0;
}

unsigned int SDKManager::onRequestWriteAction(unsigned int requestId, void* data, unsigned int dataSize, const int dataCounts
											  , unsigned int errorCode, const int subErrorCode, void* userData)
{
	WeiboRequestPtr requestPtr = 
		internalFindRequestFromActiveMap(requestId);

	if (requestPtr && data)
	{
		StackLog(<< __FUNCTION__ << "| Write body event, dataCount " << dataCounts);
		requestPtr->mResponseBody += Util::StringUtil::getNotNullString((const char*)data);
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map, or data == NULL!");
	}
	return dataSize * dataCounts;
}

unsigned int SDKManager::onRequestHeaderAction(unsigned int requestId, void* data, unsigned int dataSize, const int dataCounts
											   , unsigned int errorCode, const int subErrorCode, void* userData)
{
	WeiboRequestPtr requestPtr = 
		internalFindRequestFromActiveMap(requestId);

	if (requestPtr && data)
	{
		StackLog(<< __FUNCTION__ << "| Write header event, dataCount " << dataCounts);
		requestPtr->mResponseHeader += Util::StringUtil::getNotNullString((const char*)data);
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map, or data == NULL!");
	}
	return dataSize * dataCounts;
}

void SDKManager::onRequestStarted(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData)
{
	DebugLog(<< __FUNCTION__ << " | request id: " << requestId << " | error code :" << errorCode << " | sub error code :" << subErrorCode);

	if (requestId <= 0)
	{
		return ;
	}

	WeiboRequestPtr requestPtr = internalFindRequestFromActiveMap(requestId);
	if (requestPtr)
	{
		// If we have postform method, append the post filed.
		if (requestPtr->mHttpMethod == httpengine::HM_POSTFORM && requestPtr->mUploadTaskDetail)
		{
			// Get the file name.
			std::string &filePath = requestPtr->mUploadTaskDetail->fileName_;
			if (!filePath.empty())
			{
				std::string file;
#ifdef WIN32
				const int pos = filePath.find_last_of('\\');
#else
				const int pos = filePath.find_last_of('/');
#endif
				if (pos != std::string::npos)
				{
					file = filePath.substr(pos + 1, filePath.length());
				}
				else
				{
					file = filePath;
				}

#if 0
				// Convert the file name to utf8
				CC2UTF8 cvUTF8(file.c_str());
				std::string saveFileUTF8 = cvUTF8.c_str();
#else
				std::string saveFileUTF8 = file;
#endif

				UploadTaskDetail::PostFormDataPtr formDataPtr 
					= requestPtr->mUploadTaskDetail->getPostFormData(requestId, mHttpEnginePtr.get());

				mHttpEnginePtr->setRequestOption(requestId, httpengine::TOT_POST_FORM
					, httpengine::HTTP_FORMTYPE_COPYNAME, requestPtr->mPostFileField.c_str()
					, httpengine::HTTP_FORMTYPE_FILENAME, saveFileUTF8.c_str()
					, httpengine::HTTP_FORMTYPE_STREAM, formDataPtr ? formDataPtr.get() : NULL
					, httpengine::HTTP_FORMTYPE_CONTENTSLENGTH, requestPtr->mUploadTaskDetail->fileSize_
					, httpengine::HTTP_FORMTYPE_CONTENTTYPE, "image/jpeg"
					, httpengine::HTTP_FORMTYPE_END);
			}
		}

		// Append all http headers.
		if (!requestPtr->mReqHeader.empty())
		{
			WeiboRequest::ReqHeaderMap::iterator it = requestPtr->mReqHeader.begin();
			while (it != requestPtr->mReqHeader.end())
			{
				mHttpEnginePtr->setRequestOption(requestId, 
					httpengine::TOT_CUSTOM_HEADER, it->first.c_str(), it->second.c_str(), NULL);

				++ it;
			}
		}
	}
}

void SDKManager::onRequestStoped(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData)
{
	DebugLog(<< __FUNCTION__ << " | request id: " << requestId 
		<< " | error code :" << errorCode << " | sub error code :" << subErrorCode);

	if (requestId <= 0)
	{
		return ;
	}

	WeiboRequestPtr requestPtr;

	{
		// lock
		Util::Lock lock(mActiveMutex);
		requestPtr = internalFindRequestFromActiveMap(requestId);
	}

	if (requestPtr)
	{
		//StackLog(<< __FUNCTION__ << "| fire OnResponseStoped");
		//OnDelegateWillRelease(requestPtr->mOptionId, &requestPtr->mTaskInfo);
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map.");
	}
}

void SDKManager::onRequestErrored(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData)
{
	DebugLog(<< __FUNCTION__ << " | request id: " << requestId 
		<< " | error code :" << errorCode << " | sub error code :" << subErrorCode);

	if (requestId <= 0)
	{
		return ;
	}

	WeiboRequestPtr requestPtr;

	{
		// lock
		Util::Lock lock(mActiveMutex);
		requestPtr = internalFindRequestFromActiveMap(requestId);
	}

	if (requestPtr)
	{
		const int outErrorCode = SDKHelper::convertEngineErrorToSDKError(errorCode);
		ParsingObject result(requestPtr->mResponseBody.c_str());
		OnDelegateErrored(requestPtr->mOptionId, outErrorCode, subErrorCode, &result, &requestPtr->mTaskInfo);

		DebugLog(<< __FUNCTION__ << "| Source :" << requestPtr->mResponseBody.c_str());
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map.");
	}
}

void SDKManager::onRequestProgress(unsigned int requestId, const double total, const double complated, const double speed)
{
	StackLog(<< __FUNCTION__ << " | request id: " << requestId << " | error code :" 
		<< total << " | sub error code :" << complated << "| speed: " << speed);
}

void SDKManager::onRequestComplated(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData)
{
	DebugLog(<< __FUNCTION__ << " | request id: " << requestId 
		<< " | error code :" << errorCode << " | sub error code :" << subErrorCode);

	if (requestId <= 0)
	{
		return ;
	}

	WeiboRequestPtr requestPtr;

	{
		// lock
		Util::Lock lock(mActiveMutex);
		requestPtr = internalFindRequestFromActiveMap(requestId);
	}

	if (requestPtr)
	{
		ParsingObject result(requestPtr->mResponseBody.c_str());
		OnDelegateComplated(requestPtr->mOptionId, requestPtr->mResponseHeader.c_str(), &result, &requestPtr->mTaskInfo);

		DebugLog(<< __FUNCTION__ << " | Option Id : " << requestPtr->mOptionId
			<<"| Source :" << requestPtr->mResponseBody.c_str());
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map.");
	}
}

void SDKManager::onRequestWillRelease(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData)
{
	DebugLog(<< __FUNCTION__ << " | request id: " << requestId 
		<< " | error code :" << errorCode << " | sub error code :" << subErrorCode);

	if (requestId <= 0)
	{
		return ;
	}

	WeiboRequestMap::iterator iter = mRequestActivedMap.find(requestId);
	if (iter != mRequestActivedMap.end())
	{
		DebugLog(<< __FUNCTION__ << "| Task ID : " << requestId << "| fire OnDelegateWillRelease");
		OnDelegateWillRelease(iter->second->mOptionId, &(iter->second->mTaskInfo));
		mRequestActivedMap.erase(iter);
	}
	else
	{
		ErrLog(<< __FUNCTION__ << "| Request ptr is not at actived map.");
	}

	{
		Util::Lock lock(mActiveMutex);
		internalLoadNewActiveTask();
	}
}

eWeiboResultCode SDKManager::enqueueRequest(WeiboRequestPtr ptr)
{
	// lock
	Util::Lock lock(mActiveMutex);

	mRequestPersistent.push_back(ptr);
	return internalLoadNewActiveTask();
}

eWeiboResultCode SDKManager::internalLoadNewActiveTask()
{
	if (((int)mRequestActivedMap.size() < mMaxActiveCounts) 
		&& (!mRequestPersistent.empty()))
	{
		WeiboRequestPersistent::iterator it = mRequestPersistent.begin();
		eWeiboResultCode retCode = internalStartTask(*it);
		mRequestPersistent.erase(it);
		return retCode;
	}
	return WRC_OK;
}

eWeiboResultCode SDKManager::internalStartTask(WeiboRequestPtr reqPtr)
{
	if (mHttpEnginePtr && reqPtr)
	{
		if (reqPtr->mOptionId == WBOPT_OAUTH2_ACCESS_TOKEN)
		{
			DebugLog(<< __FUNCTION__ << "| Option id : " << reqPtr->mOptionId << " | url : " << reqPtr->mURL.c_str());
		}
		else
		{
			DebugLog(<< __FUNCTION__ << "| Option id : " << reqPtr->mOptionId << " | url : " << reqPtr->mURL.c_str() 
				<< " | post arguments: " << reqPtr->mPostArg.c_str() << " | Http method : " << reqPtr->mHttpMethod);
		}

		mHttpEnginePtr->startUrlRequest(reqPtr->mTaskId, reqPtr->mURL.c_str()
			, reqPtr->mPostArg.c_str(), reqPtr->mHttpMethod);

		// Check has same request.
		WeiboRequestMap::iterator it = mRequestActivedMap.find(reqPtr->mTaskId);
		if (it != mRequestActivedMap.end())
		{
			// Already has this task.
			WarningLog(<< __FUNCTION__ << "| Task is exist : " << reqPtr->mTaskId);

			return WRC_TASK_EXIST;
		}
		mRequestActivedMap.insert(std::make_pair(reqPtr->mTaskId, reqPtr));
		return WRC_OK;
	}
	return WRC_INTERNAL_ERROR;
}

WeiboRequestPtr SDKManager::internalFindRequestFromActiveMap(unsigned int taskId)
{
	WeiboRequestPtr request ;
	WeiboRequestMap::iterator iter = mRequestActivedMap.find(taskId);
	if (iter != mRequestActivedMap.end())
	{
		request = iter->second;
	}
	return request;
}

////////////////////////////////////////////////////////////////////////////////
// weibo function

boost::weak_ptr<IWeibo> WeiboFactory::mWeiboPtr;
boost::shared_ptr<IWeibo> WeiboFactory::getWeibo()
{
	boost::shared_ptr<IWeibo> weiboPtr;
	if (mWeiboPtr.expired())
	{
		weiboPtr.reset(new SDKManager());
		mWeiboPtr = weiboPtr;
	}
	else
	{
		weiboPtr = mWeiboPtr.lock();
	}
	return weiboPtr;
}
