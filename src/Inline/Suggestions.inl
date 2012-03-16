//suggestions/favorites/hot 热门收藏【待上线】
//suggestions/events/may_interested 可能感兴趣的活动推荐
//suggestions/events/may_interested_sp 可能感兴趣的活动推荐(带广告，主站专用)【待上线】
//suggestions/all_in_one 推荐的微群、活动、和应用( 主站右侧推荐模块)
//微博类推荐
//suggestions/statuses/hot 微博精选【待上线】
//suggestions/statuses/reorder Feed根据兴趣重排
//suggestions/statuses/reorder/ids Feed根据兴趣重排（仅返回ID）
//用户类推荐
//suggestions/users/hot 获取系统推荐用户
//suggestions/users/recommend 获取人气用户
//suggestions/users/may_interested 获取用户可能感兴趣的人
//suggestions/users/not_interested 不感兴趣的人
//suggestions/users/by_status 根据微博内容推荐用户
//suggestions/users/worth_follow 推荐关注
//suggestions/users/worth_follow/ids 推荐关注(只返回id)【待上线】

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Suggestion options for V4
eWeiboResultCode SDKMethodImpl::getSuggestionsFavoritesHot(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SUGGESTIONS_FAVORITES_HOT
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}


eWeiboResultCode SDKMethodImpl::getSuggestionsUsersHot(const char* category, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	SDKHelper::setParam(param, "&category", category, PARAM_ENCODE_UTF8);
	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SUGGESTIONS_USERS_HOT
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSuggestionsUsersMayInterested(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postSuggestionsUsersNotInterested(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSuggestionsUsersByStatus(const char* content, const int num, const char* url, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	SDKHelper::setParam(param, "&content", Util::StringUtil::getNotNullString(content), PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&num", num);
	SDKHelper::setParam(param, "&url", Util::StringUtil::getNotNullString(url), PARAM_ENCODE_UTF8);
	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}