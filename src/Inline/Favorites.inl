
eWeiboResultCode SDKMethodImpl::getFavorites(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FAVORITES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFavoritesShow(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FAVORITES_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFavoritesByTags(const char* tid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(tid))
	{
		return WRC_TAGID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&tid", tid, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FAVORITES_BY_TAGS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFavoritesTags(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FAVORITES_TAGS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesCreate(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_CREATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesDestroy(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesDestroyBatch(const char* ids, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(ids))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&ids", ids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_DESTROY_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesTagUpdate(const char* id, const char* tags, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&tags", tags, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_TAGS_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesTagsUpdateBatch(const char* id, const char* tag, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&tid", id, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&tag", tag, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFavoritesTagsDestroyBatch(const char* tid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(tid))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&tid", tid, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}