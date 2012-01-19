#ifndef WEIBOSDK_SDKREQUEST_HXX
#define WEIBOSDK_SDKREQUEST_HXX

#include <map>
#include <boost/shared_ptr.hpp>
#include <HttpEngine/IHttpEngineCommon.hxx>
#include "IWeiboDef.hxx"

/** SDK Request information, this struct used internal
* 
* @author welbon
*
* @Email libo.weng@gmail.com
*
* @date 2011-10-26
*
*/
namespace weibo
{
	struct UploadTaskDetail;

	class WeiboRequest
	{
	public:
		WeiboRequest();

		void makeUploadTaskDetail(const char* file);

		unsigned int mOptionId;
		unsigned int mTaskId;
		UserTaskInfo mTaskInfo;
		typedef std::map<std::string, std::string> ReqHeaderMap;
		
		httpengine::HttpMethod mHttpMethod;

		std::string mURL;
		std::string mPostArg;
		std::string mResponseBody;
		std::string mResponseHeader;
		ReqHeaderMap mReqHeader;

		std::string mPostFileField;
		boost::shared_ptr<UploadTaskDetail> mUploadTaskDetail;
	};
	typedef boost::shared_ptr<WeiboRequest> WeiboRequestPtr;
}

#endif //WEIBOSDK_SDKREQUEST_HXX