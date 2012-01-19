#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

eWeiboResultCode SDKMethodImpl::getShortURLShorten(const char* url_long, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_long))
	{
		return WRC_INVALIDE_PARAM;
	}

	char param[2048] = {0};
	std::vector<std::string> vec;
	boost::split(vec, url_long, boost::is_any_of(","));
	std::vector<std::string>::iterator it = vec.begin();
	while (it != vec.end())
	{
		SDKHelper::setParam(param, "&url_long", 
			Util::StringUtil::getNotNullString(it->c_str()), PARAM_ENCODE_UTF8);

		++ it;
	}

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_SHORTEN
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortURLExpand(const char* url_short, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_short))
	{
		return WRC_INVALIDE_PARAM;
	}

	char param[2048] = {0};
	std::vector<std::string> vec;
	boost::split(vec, url_short, boost::is_any_of(","));
	std::vector<std::string>::iterator it = vec.begin();
	while (it != vec.end())
	{
		SDKHelper::setParam(param, "&url_short",
			Util::StringUtil::getNotNullString(it->c_str()), PARAM_ENCODE_UTF8);
		++ it;
	}

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_EXPAND
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortURLShareCounts(const char* url_short, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_short))
	{
		return WRC_INVALIDE_PARAM;
	}

	char param[255] = {0};
	SDKHelper::setParam(param, "&url_short",
		Util::StringUtil::getNotNullString(url_short), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_SHARE_COUNTS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortURLShareStatuses(const char* url_short, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_short))
	{
		return WRC_INVALIDE_PARAM;
	}

	// Required params
	char param[255] = {0};
	SDKHelper::setParam(param, "&url_short",
		Util::StringUtil::getNotNullString(url_short), PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_SHARE_STATUSES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortURLCommentCounts(const char* url_short, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_short))
	{
		return WRC_INVALIDE_PARAM;
	}

	// Required params
	char param[255] = {0};
	SDKHelper::setParam(param, "&url_short",
		Util::StringUtil::getNotNullString(url_short), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_COMMENT_COUNTS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortURLCommentComments(const char* url_short, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(url_short))
	{
		return WRC_INVALIDE_PARAM;
	}

	// Required params
	char param[255] = {0};
	SDKHelper::setParam(param, "&url_short",
		Util::StringUtil::getNotNullString(url_short), PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_COMMENT_COMMENTS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getShortUrlInfo(const char* shortUrlIDs, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(shortUrlIDs))
	{
		return WRC_INVALIDE_PARAM;
	}

	// Required params
	char param[1024] = {0};
	SDKHelper::setParam(param, "&url_short", 
		Util::StringUtil::getNotNullString(shortUrlIDs), PARAM_ENCODE_UTF8);

	// Request
	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SHORT_URL_INFO, 
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}
