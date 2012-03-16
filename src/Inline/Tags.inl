//下行接口
//tags 返回指定用户的标签列表
//tags/tags_batch 批量获取用户标签
//tags/suggestions 返回系统推荐的标签列表
//上行接口
//tags/create 添加用户标签
//tags/destroy 删除用户标签
//tags/destroy_batch 批量删除用户标签


eWeiboResultCode SDKMethodImpl::getTags(const char* uid, VariableParams* var, UserTaskInfo* pTask)
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

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TAGS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getTagsTagsBatch(const char* uids, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uids))
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&uids", uids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TAGS_TAGS_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getTagsSuggestions(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_TAGS_SUGGESTIONS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::postTagsCreate(const char* tags, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(tags))
	{
		return WRC_TEXT_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&tags", tags, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_TAGS_CREATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postTagsDestroy(const char* tagId, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(tagId))
	{
		return WRC_TEXT_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&tag_id", tagId, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_TAGS_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postTagsDestroyBatch(const char* tagIds, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(tagIds))
	{
		return WRC_TEXT_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&ids", tagIds, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_TAGS_DESTROY_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}