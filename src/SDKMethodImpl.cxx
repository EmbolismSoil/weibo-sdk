#include "config.h"
#include <stdio.h>
//#include <boost/make_shared.hpp>
#include "SDKMethodImpl.hxx"
#include "SDKHelper.hxx"
#include "SDKManager.hxx"

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

SDKMethodImpl::SDKMethodImpl(SDKManager *manager)
: mManager(manager)
, mUnfiedFormat(WRF_JSON)
{

}

eWeiboResultCode SDKMethodImpl::oauth2(const char* userName, const char* password, UserTaskInfo* pTask)
{
	std::string param;

	if (Util::StringUtil::NullOrEmpty(userName))
	{
		return WRC_USERID_NULL;
	}
	if (Util::StringUtil::NullOrEmpty(password))
	{
		return WRC_PASSWORD_NULL;
	}

	SDKHelper::setParam(param, "&username", userName, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&password", password, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&client_id", mConsumerkey.c_str(), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&client_secret", mConsumersecret.c_str(), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&grant_type", "password", PARAM_ENCODE_UTF8);

	WeiboRequestPtr requestPtr;
    requestPtr.reset(new WeiboRequest());
    
	if (requestPtr)
	{
		requestPtr->mHttpMethod = httpengine::HM_POST;
		requestPtr->mOptionId   = WBOPT_OAUTH2_ACCESS_TOKEN;

		requestPtr->mURL = "https://api.weibo.com/oauth2/access_token";
		requestPtr->mPostArg = param;

		if (pTask)
		{
			memcpy(&(requestPtr->mTaskInfo), pTask, sizeof(UserTaskInfo));
		}
		return internalEnqueue(requestPtr);
	}

	return WRC_INTERNAL_ERROR;
}


weibo::eWeiboResultCode SDKMethodImpl::oauth2Authorize(const char* userName, const char* password, UserTaskInfo* pTask)
{
	std::string open =
		"https://api.t.sina.com.cn/oauth2/authorize?client_id=";
	open += mConsumerkey;
	open += "&redirect_uri=http://www.example.com/response&response_type=code";

	ShellExecuteA(NULL, "open", open.c_str(), NULL, NULL, SW_SHOWNORMAL);
	return WRC_INTERNAL_ERROR;
}

eWeiboResultCode SDKMethodImpl::endSession()
{
	std::string param;

	SDKHelper::setParam(param, "&source", mConsumerkey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr requestPtr;
    requestPtr.reset(new WeiboRequest());
	
    if (requestPtr)
	{
		requestPtr->mHttpMethod = httpengine::HM_POST;
		requestPtr->mOptionId = WBOPT_END_SESSION;

		requestPtr->mURL = "http://api.weibo.com/account/end_session";
		requestPtr->mPostArg = param;

		return internalEnqueue(requestPtr);
	}
	return WRC_INTERNAL_ERROR;
}

WeiboRequestPtr SDKMethodImpl::internalMakeWeiboRequest(unsigned int methodOption, std::string& addtionParam, const eWeiboRequestFormat reqformat,
														const httpengine::HttpMethod method, const UserTaskInfo* pTask)
{
	return SDKHelper::makeRequest(methodOption, addtionParam, reqformat,
		method, mConsumerkey.c_str(), mAccesstoken.c_str(), pTask);
}

eWeiboResultCode SDKMethodImpl::internalEnqueue(WeiboRequestPtr requestPtr)
{
	if (mManager && requestPtr)
	{
		return mManager->enqueueRequest(requestPtr);
	}
	return WRC_INTERNAL_ERROR;
}

void SDKMethodImpl::setUnifiedFormat(const eWeiboRequestFormat format)
{
	mUnfiedFormat = format;
}

eWeiboRequestFormat SDKMethodImpl::getUnifiedFormat() const
{
	return mUnfiedFormat;
}

void SDKMethodImpl::setConsumer(std::string &key, std::string& secret)
{
	mConsumerkey = key;
	mConsumersecret = secret;
}

void SDKMethodImpl::setAccesstoken(std::string &token)
{
	mAccesstoken = token;
}

#include "Inline/Statuses.inl"
#include "Inline/Comment.inl"
#include "Inline/DirectMessage.inl"
#include "Inline/FriendShip.inl"
#include "Inline/Users.inl"
#include "Inline/Favorites.inl"
#include "Inline/Trends.inl"
#include "Inline/Tags.inl"
#include "Inline/Suggestions.inl"
#include "Inline/Account.inl"
#include "Inline/Search.inl"
#include "Inline/ShortURL.inl"
#include "Inline/Unread.inl"
#include "Inline/Groups.inl"
