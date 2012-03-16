//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Friend ships options V4
eWeiboResultCode SDKMethodImpl::getFriendshipsFriends(ID& usrId, const int order/*= 0*/, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	//if (usrId.isEmpty())
	//{
	//	return WRC_USERID_NULL;
	//}

	std::string param;
	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::setIntParam(param, "&order", order);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsInCommon(const char* id, const char* suid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uid", id, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&suid", suid, PARAM_ENCODE_UTF8);

	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_IN_COMMON
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsBilateral(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_BILATERAL
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsBilateralIDs(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendIDs(ID& usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (usrId.isEmpty())
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendRemarkBatch(const char* uids, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uids))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&uids", uids, PARAM_ENCODE_UTF8);

	// Varible params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendsFollowers(ID &usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);
	if (usrId.isEmpty())
	{
		return WRC_WEIBOID_NULL;
	}
	std::string param;

	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendsFollowersIDs(ID &usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);
	if (usrId.isEmpty())
	{
		return WRC_WEIBOID_NULL;
	}
	std::string param;

	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendsFollowersActive(ID &usrIDs, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (usrIDs.isEmpty())
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	SDKHelper::makeIDParams(param, 255, &usrIDs);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipsFriendsChainFollowers(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_WEIBOID_NULL;
	}

	std::string param;

	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getFriendshipShow(ID& sourceId, ID& targetId, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (sourceId.isEmpty())
	{
		return WRC_USERID_NULL;
	}
	if (targetId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Required params
	if (ID::IDT_ID == sourceId.idType)
	{
		SDKHelper::setParam(param, "&source_id", sourceId.id.c_str(), PARAM_ENCODE_UTF8);
	}
	else if (ID::IDT_SCREENNAME == sourceId.idType)
	{
		SDKHelper::setParam(param, "&source_screen_name", sourceId.id.c_str(), PARAM_ENCODE_UTF8);
	}

	if (ID::IDT_ID == targetId.idType)
	{
		SDKHelper::setParam(param, "&target_id", targetId.id.c_str(), PARAM_ENCODE_UTF8);
	}
	else if (ID::IDT_SCREENNAME == targetId.idType)
	{
		SDKHelper::setParam(param, "&target_screen_name", targetId.id.c_str(), PARAM_ENCODE_UTF8);
	}

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_FRIENDSHIPS_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFriendshipsCreate(ID &usrId, const int skipCheck, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::makeIDParams(param, 255, &usrId);
	SDKHelper::setIntParam(param, "&skip_check", skipCheck);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FRIENDSHIPS_CREATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFriendshipsCreateBatch(const char* uids, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uids))
	{
		return WRC_USERID_NULL;
	}
	std::string param;

	// Required params
	SDKHelper::setParam(param, "&uids", uids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FRIENDSHIPS_CREATE_BATCH
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFriendshipsDestroy(ID &usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Id params
	SDKHelper::makeIDParams(param, 255, &usrId);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FRIENDSHIPS_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFriendshipsFollowersDestroy(const char* uid, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postFriendshipsRemarkUpdate(const char* uid, const char* remark, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(uid))
	{
		return WRC_USERID_NULL;
	}

	std::string param;

	// Required params
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&remark", remark, PARAM_ENCODE_UTF8);

	// Variable params
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}
