//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Users options V4

//获取用户资料
eWeiboResultCode SDKMethodImpl::getUsersShow(ID& usrId, const char* extend, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::setParam(param, "&has_extend", extend, PARAM_ENCODE_UTF8);	
	SDKHelper::makeVariableParams(param, 255, var);
	
	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_USERS_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

//通过个性域名获取用户信息
eWeiboResultCode SDKMethodImpl::getUsersDomainShow(const char* domain, const char* extend, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	std::string param;
	SDKHelper::setParam(param, "&has_extend", extend, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&domain", domain, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_USERS_DOMAIN_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

//批量获取用户信息
eWeiboResultCode SDKMethodImpl::getUsersShowBatch(ID& usrId, const char* extend, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ );

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Require param
	SDKHelper::setParam(param, "&uids", usrId.id.c_str(), ParamEncodedValue);
	SDKHelper::setParam(param, "&has_extend", Util::StringUtil::getNotNullString(extend), PARAM_ENCODE_UTF8);

	// Variable param
	SDKHelper::makeVariableParams(param, 2048, var);

	//SDKHelper::setParam(param, "&source", mAppKey.c_str(), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_USERS_SHOW_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}