
eWeiboResultCode SDKMethodImpl::getGroupsJoined(const char* uid, const int page, const int count, 
												const int type, const int filter, const int sort, 
												const int member_limit, const int simplify, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&page", page);
	SDKHelper::setIntParam(param, "&count", count);
	SDKHelper::setIntParam(param, "&type", type);
	SDKHelper::setIntParam(param, "&filter", filter);
	SDKHelper::setIntParam(param, "&sort", sort);
	SDKHelper::setIntParam(param, "&member_limit", member_limit);
	SDKHelper::setIntParam(param, "&simplify", simplify);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_JOINED,
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsShowBatch(const char* gids, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&gids", gids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_SHOW_BATCH,
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsGetAnnouncement(const char* gid, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&gid", gid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_GET_ANNOUNCEMENT,
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsAdmin(const char* gid, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_ADMIN,
		NULL, getUnifiedFormat(), httpengine::HM_GET, pTask);

	char finalURL[256] = { 0 };
	sprintf(finalURL, ptr->mURL.c_str(), gid);
	ptr->mURL = finalURL;

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsUsers(const char* gid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_USERS,
		NULL, getUnifiedFormat(), httpengine::HM_GET, pTask);


	char finalURL[256] = { 0 };
	sprintf(finalURL, ptr->mURL.c_str(), gid);
	ptr->mURL = finalURL;

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsSuggestionMayInterested(const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_SUGGESTION_MAY_INTERESTED,
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getGroupsChatIsBlocked(const char* gids, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&gids", gids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_CHAT_IS_BLOCKED,
		param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::postGroupsChatBlock(const char* gid, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&gid", gid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_CHAT_BLOCK,
		param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::postGroupsChatUnblock(const char* gid, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&gid", gid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_GROUPS_CHAT_UNBLOCK,
		param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr); 
}