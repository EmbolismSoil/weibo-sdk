#ifndef WEIBOSDK_SDKMANAGER_HXX
#define WEIBOSDK_SDKMANAGER_HXX

#include <map>
#include <boost/shared_ptr.hpp>
#include <Util/threading/Lock.hxx>
#include <HttpEngine/IHttpEngine.hxx>
#include "IWeibo.hxx"
#include "SDKRequest.hxx"

namespace weibo
{
	class SDKMethodImpl;

	/** Weibo sdk implements
	* 
	* @author welbon
	*
	* @date 2011-08-22
	*/
	class SDKManager : public IWeibo
	{
	public:
		SDKManager();
		virtual ~SDKManager();

		////////////////////////////////////////////////////////////
		// IWeibo implements
		virtual int startup();
		virtual int shutdown();
		virtual void stopAll();
		
		virtual void getOption(const eWeiboOption option, ...);
		virtual void setOption(const eWeiboOption option, ...);

		virtual IWeiboMethod *getMethod();

		////////////////////////////////////////////////////////////
		// Internal public function.
		eWeiboResultCode enqueueRequest(WeiboRequestPtr ptr);

	protected:
		unsigned int onRequestReadAction(unsigned int requestId, void* data, unsigned int dataSize
			, const int dataCounts, unsigned int errorCode, const int subErrorCode, void* userData);

		unsigned int onRequestWriteAction(unsigned int requestId, void* data, unsigned int dataSize
			, const int dataCounts, unsigned int errorCode, const int subErrorCode, void* userData);

		unsigned int onRequestHeaderAction(unsigned int requestId, void* data, unsigned int dataSize
			, const int dataCounts, unsigned int errorCode, const int subErrorCode, void* userData);

		void onRequestStarted(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData);
		void onRequestStoped(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData);
		void onRequestErrored(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData);
		void onRequestComplated(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData);
		void onRequestWillRelease(unsigned int requestId, const int errorCode, const int subErrorCode, void* userData);
		void onRequestProgress(unsigned int requestId, const double total, const double complated, const double speed);

		eWeiboResultCode internalStartTask(WeiboRequestPtr ptr);
		eWeiboResultCode internalLoadNewActiveTask();

		WeiboRequestPtr internalFindRequestFromActiveMap(unsigned int taskId);
		void internalProcessGrant(WeiboRequestPtr requestPtr);

	protected:
		typedef std::map<unsigned int, WeiboRequestPtr> WeiboRequestMap;
		typedef std::vector<WeiboRequestPtr> WeiboRequestPersistent;

		int mMaxActiveCounts;
		eWeiboRequestFormat mRequestFormat;
		httpengine::HttpEnginePtr mHttpEnginePtr;

		WeiboRequestMap mRequestActivedMap;
		WeiboRequestPersistent mRequestPersistent;

		boost::shared_ptr<SDKMethodImpl> mMethodPtr;
		Util::Mutex mActiveMutex;

		std::string mConsumerkey;
		std::string mConsumersecret;
		std::string mAccesstoken;
	};
}

#endif //WEIBOSDK_SDKMANAGER_HXX