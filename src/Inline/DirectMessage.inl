//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Statuses options V4
eWeiboResultCode SDKMethodImpl::getDirectMessages(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getDirectMessagesSent(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES_SENT
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getDirectMessagesUserList(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	std::string param;
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES_USER_LIST
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getDirectMessagesCoversation(ID &usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );


	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&user_id", usrId.id.c_str(), PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES_CONVERSATION
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getDirectMessagesShowBatch(const char* dmids, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (Util::StringUtil::NullOrEmpty(dmids))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&dmids", dmids, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getDirectMessagesIsCapable(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postDirectMessagesNew(const char* text, const ID& uid, const char* fields, const char* weiboId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(text))
	{
		return WRC_TEXT_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::makeIDParams(param, 1024, &uid);
	SDKHelper::setParam(param, "&text", text, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&fields", fields, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&id", weiboId, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_DIRECTMESSAGES_NEW
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postDirectMessagesDestory(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_USERID_NULL;
	}

	// Required params
	std::string param;
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_DIRECTMESSAGES_DESTORY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postDirectMessagesDestoryBatch(const char* ids, const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	// Required params
	std::string param;
	if (ids && *ids != '\0')
	{
		SDKHelper::setParam(param, "&ids", ids, PARAM_ENCODE_UTF8);
	}
	else
	{
		SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	}

	// Variable params
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}
