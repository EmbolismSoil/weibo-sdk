//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Statuses options V4

eWeiboResultCode SDKMethodImpl::getStatusesPublicTimeline(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_PUBLIC_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesFriendTimeline(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_FRIENDS_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesHomeTimeline(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_HOME_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesUserTimeline(ID& usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	char param[1024] = { 0 };
	SDKHelper::makeIDParams(param, 1024, &usrId);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_USER_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesTimelineBatch(ID &usrId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (usrId.isEmpty())
	{
		return WRC_USERID_NULL;
	}

	char param[1024] = { 0 };
	SDKHelper::makeIDParams(param, 1024, &usrId);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_TIMELINE_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesRepostTimeline(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[1024] = { 0 };
	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_USERID_NULL;
	}

	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_REPOST_TIMELINE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesRepostByMe(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_REPOST_BYME
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesMentions(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_MENTIONS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesShow(const char* id, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[1024] = { 0 };

	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_SHOW
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesShowBatch(const char* inputIDs, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(inputIDs))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[1024] = { 0 };

	SDKHelper::setParam(param, "&ids", inputIDs, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_SHOW_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesQueryMID(const char *weiboId, const int type, const int is_batch, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(weiboId))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[1024] = { 0 };

	SDKHelper::setParam(param, "&id", weiboId , PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&type"     , type);
	SDKHelper::setIntParam(param, "&is_batch" , is_batch);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_QUERYMID
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesQueryID(const char *mId, const int type, const int is_batch, const int inbox, const int isBase62, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	if (Util::StringUtil::NullOrEmpty(mId))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[1024] = { 0 };

	SDKHelper::setParam(param, "&mid", mId , PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&type"     , type);
	SDKHelper::setIntParam(param, "&is_batch" , is_batch);
	SDKHelper::setIntParam(param, "&inbox"    , inbox);
	SDKHelper::setIntParam(param, "&isBase62" , isBase62);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_QUERYID
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesRepostDaily(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_REPOST_DAILY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesRepostWeekly(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_REPOST_WEEKLY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesHotCommmentsDaily(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getStatusesHotCommmentsWeekly(VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	char param[255] = { 0 };
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Option for post

eWeiboResultCode SDKMethodImpl::postStatusesRepost(const char* weiboId, const char* statusText, const int isComment, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(weiboId))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[2048] = { 0 };
	SDKHelper::setParam(param, "&id", weiboId, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&status", statusText , 0);
	SDKHelper::setIntParam(param, "&is_comment", isComment);

	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_STATUSES_REPOST
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}


eWeiboResultCode SDKMethodImpl::postStatusesDestroy(const char *weiboId, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(weiboId))
	{
		return WRC_WEIBOID_NULL;
	}

	char param[255] = { 0 };
	SDKHelper::setParam(param, "&id", weiboId , PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_STATUSES_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}


eWeiboResultCode SDKMethodImpl::postStatusesUpdate(const char* statusText, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(statusText))
	{
		return WRC_TEXT_NULL;
	}

	char param[2048] = { 0 };
	SDKHelper::setParam(param, "&status", statusText, 0);
	SDKHelper::makeVariableParams(param, 255, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_STATUSES_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postStatusesUploadUrlText(const char* statusText, const char *picInfo, bool isPicUrl, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(statusText))
	{
		return WRC_TEXT_NULL;
	}

	char param[1024] = { 0 };
	SDKHelper::setParam(param, "&status", statusText, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, isPicUrl ? "&url":"&pic_id", picInfo, PARAM_ENCODE_UTF8);
	SDKHelper::makeVariableParams(param, 1024, var);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_STATUSES_UPLOAD_URL_TEXT
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::postStatusesUpload(const char* statusText, const char* filePath, VariableParams* var, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| var: " << var);

	if (Util::StringUtil::NullOrEmpty(statusText))
	{
		return WRC_TEXT_NULL;
	}

	if (Util::StringUtil::NullOrEmpty(filePath))
	{
		return WRC_FILEPATH_NULL;
	}

	char param[2048] = { 0 };
	SDKHelper::setParam(param, "&status", statusText, 0);
	SDKHelper::makeVariableParams(param, 255, var);

	//Note: Set with post form
	WeiboRequestPtr requestPtr = internalMakeWeiboRequest(WBOPT_POST_STATUSES_UPLOAD
		, param, getUnifiedFormat(), httpengine::HM_POSTFORM, pTask);

	requestPtr->mPostFileField = "pic";	
	requestPtr->makeUploadTaskDetail(Util::StringUtil::getNotNullString(filePath));

	return internalEnqueue(requestPtr); 
}