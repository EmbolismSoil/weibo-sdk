////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comments .

eWeiboResultCode SDKMethodImpl::getCommentsShow(const char *weiboId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(weiboId))
	{
		return WRC_USERID_NULL;
	}

	char param[1024] = { 0 };
	SDKHelper::setParam(param, "&id", weiboId, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getCommentsByMe(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_BYME
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getCommentsToMe(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_TOME
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getCommentsTimeline(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getCommentsMentions(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_MENTIONS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::getCommentsShowBatch(const char* cids, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[1024] = { 0 };
	SDKHelper::makeVariableParams(param, 1024, var);
	SDKHelper::setParam(param, "&cids", cids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_COMMENTS_SHOWBATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);  
}

eWeiboResultCode SDKMethodImpl::postCommentsCreate(const char* id, const char* comment, const int comment_ori, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[1024] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	SDKHelper::setParam(param, "&id", id, ParamEncodedValue);
	SDKHelper::setParam(param, "&comment", comment, ParamEncodedValue);
	SDKHelper::setIntParam(param, "&comment_ori", comment_ori);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_COMMENTS_CREATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postCommentsDestroy(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);
	SDKHelper::setParam(param, "&cid", id, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_COMMENTS_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postCommentsDestroyBatch(const char* cids, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);
	SDKHelper::setParam(param, "&cids", cids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_COMMENTS_DESTROY_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postCommentsReply(const char* commentId
											  , const char* comment
											  , const char* weiboId
											  , const int withoutMention
											  , const int commentOri
											  , VariableParams* var
											  , UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);
	SDKHelper::setParam(param, "&cid", commentId, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&id", weiboId, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&comment", comment, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&comment_ori", commentOri);
	SDKHelper::setIntParam(param, "&without_mention", withoutMention);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_COMMENTS_REPLY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}