
eWeiboResultCode SDKMethodImpl::getSearchSuggestionsUsers(const char* q, const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_USERS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsStatues(const char* q, const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsSchool(const char* q, const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsCompanies(const char* q, const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsApps(const char* q, const int count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_APPS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsAtUsers(const char* q, const int type, const int count, const int range, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	char ctype[10] = { 0 };
	snprintf(ctype, 10, "%d", type);

	SDKHelper::setParam(param, "&type", ctype, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);
	SDKHelper::setIntParam(param, "&range", range);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchSuggestionsIntegrate(const char* query, const int sort_user, const int sort_app, const int sort_grp,
															  const int user_count, const int app_count, const int grp_count, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&query", query, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&sort_user", sort_user);
	SDKHelper::setIntParam(param, "&sort_app", sort_app);
	SDKHelper::setIntParam(param, "&sort_grp", sort_grp);
	SDKHelper::setIntParam(param, "&user_count", user_count);
	SDKHelper::setIntParam(param, "&app_count", app_count);
	SDKHelper::setIntParam(param, "&grp_count", grp_count);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchStatuses(const char* q, const int filter_ori, const int filter_pic, const char* fuid, 
												  const int province, const int city, const char* starttime, const char* endtime, const int count, 
												  const int page, const bool needcount, const int base_app, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[1024] = { 0 };

	// Required params
	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&filter_ori", filter_ori);
	SDKHelper::setIntParam(param, "&filter_pic", filter_pic);
	SDKHelper::setParam(param, "&fuid", fuid, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&province", province);
	SDKHelper::setIntParam(param, "&city", city);
	SDKHelper::setParam(param, "&starttime", starttime, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&endtime", endtime, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&count", count);
	SDKHelper::setIntParam(param, "&page", page);
	SDKHelper::setParam(param, "&page", needcount ? "true" : "", PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&base_app", base_app);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_STATUSES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchGeoStatuses(const float longitude, const float latitudeconst, const int range, const int time,
													 const int sort_type, const int page, const int count, const int base_app, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[255] = { 0 };

	// Required params
	char clo[16] = { 0 };
	sprintf(clo, "%fd", longitude);

	char cla[16] = { 0 };
	sprintf(clo, "%fd", latitudeconst);

	SDKHelper::setParam(param, "&longitude", clo, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&latitudeconst", cla, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&range", range);
	SDKHelper::setIntParam(param, "&time", time);
	SDKHelper::setIntParam(param, "&sort_type", sort_type);
	SDKHelper::setIntParam(param, "&page", page);
	SDKHelper::setIntParam(param, "&count", count);
	SDKHelper::setIntParam(param, "&base_app", base_app);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_GEO_STATUSES
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getSearchUsers(const char* q, const int snick, const int sdomain, const int sintro, const int stag, 
											   const int province, const int city, const char* gender, const char* comorsch, const int sort,
											   const int count, const int page, const int base_app, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	char param[1024] = { 0 };

	SDKHelper::setParam(param, "&q", q, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&snick", snick);
	SDKHelper::setIntParam(param, "&sdomain", sdomain);
	SDKHelper::setIntParam(param, "&sintro", sintro);
	SDKHelper::setIntParam(param, "&province", province);
	SDKHelper::setIntParam(param, "&city", city);
	SDKHelper::setIntParam(param, "&city", city);
	SDKHelper::setParam(param, "&gender", gender, PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&comorsch", comorsch, PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(param, "&sort", sort);
	SDKHelper::setIntParam(param, "&count", count);
	SDKHelper::setIntParam(param, "&page", page);
	SDKHelper::setIntParam(param, "&base_app", base_app);


	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_SEARCH_USERS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

