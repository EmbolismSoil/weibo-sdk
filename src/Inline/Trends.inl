//下行接口
//trends 获取某人话题
//trends/statuses 获取某一话题下的微博
//trends/is_follow 是否关注某话题【待上线】
//trends/hourly 返回最近一小时内的热门话题
//trends/daily 返回最近一天内的热门话题
//trends/weekly 返回最近一周内的热门话题
//trends/hot_sp 首页右侧热门话题(主站专用,带推荐位)
//上行接口
//trends/follow 关注某话题
//trends/destroy 取消关注的某一个话题

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Trends options V4
eWeiboResultCode SDKMethodImpl::getTrends(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TRENDS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getTrendsStatuses(const char* trendWords, const char* provinceId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(trendWords))
	{
		return WRC_TEXT_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&trend", trendWords, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&province", provinceId, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TRENDS_STATUSES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getTrendsHourly(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TRENDS_HOURLY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getTrendsDaily(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TRENDS_DAILY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getTrendsWeekly(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TRENDS_WEEKLY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postTrendsFollow(const char* trendName, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&trend_name", trendName, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_TRENDS_FOLLOW
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postTrendsDestroy(const char* trendId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&trend_id", trendId, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_TRENDS_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}