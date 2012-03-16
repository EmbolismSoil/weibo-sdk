
eWeiboResultCode SDKMethodImpl::getAccountProfileBasic(const char *uid, UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__);

	std::string param;
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_BASIC
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr); 
}

eWeiboResultCode SDKMethodImpl::getAccountProfileEducation(const char* uid, UserTaskInfo* pTask)
{
	std::string param;
	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountProfileEducationBatch(const char* uids, UserTaskInfo* pTask)
{
	if (Util::StringUtil::NullOrEmpty(uids))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uids", uids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountProfileCareer(const char* uid, UserTaskInfo* pTask)
{
	std::string param;

	SDKHelper::setParam(param, "&uid", uid, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_CAREER
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountProfileCareerBatch(const char* uids, UserTaskInfo* pTask)
{
	if (Util::StringUtil::NullOrEmpty(uids))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&uids", uids, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountGetPrivacy(UserTaskInfo* pTask)
{
	std::string param;

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_GET_PRIVACY
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountProfileSchoolList(const int province, const int city, const int area, const int type, 
													 const char* capital, const char* keyword, const int counts, UserTaskInfo* pTask)
{
	std::string param;
	SDKHelper::setIntParam(param, "&province", province);
	SDKHelper::setIntParam(param, "&city", city);
	SDKHelper::setIntParam(param, "&type", type);
	SDKHelper::setIntParam(param, "&counts", counts);
	SDKHelper::setParam(param, "&capital", Util::StringUtil::getNotNullString(capital), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&keyword", Util::StringUtil::getNotNullString(keyword), PARAM_ENCODE_UTF8);	

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountRateLimitStatus(UserTaskInfo* pTask)
{
	std::string param;

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::getAccountGetUID(UserTaskInfo* pTask)
{
	std::string param;

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_GET_ACCOUNT_GET_UID
		, param, getUnifiedFormat(), httpengine::HM_GET, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountProfileBasicUpdate(const BasicInfo& basic, UserTaskInfo* pTask)
{
	std::string param;

	SDKHelper::setParam(param, "&screen_name", Util::StringUtil::getNotNullString(basic.screen_name.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&real_name", Util::StringUtil::getNotNullString(basic.real_name.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&real_name_visible", Util::StringUtil::getNotNullString(basic.real_name_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&province", Util::StringUtil::getNotNullString(basic.province.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&city", Util::StringUtil::getNotNullString(basic.city.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&birthday", Util::StringUtil::getNotNullString(basic.birthday.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&birthday_visible", Util::StringUtil::getNotNullString(basic.birthday_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&qq	false", Util::StringUtil::getNotNullString(basic.qq.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&qq_visible", Util::StringUtil::getNotNullString(basic.qq_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&msn", Util::StringUtil::getNotNullString(basic.msn.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&msn_visible", Util::StringUtil::getNotNullString(basic.msn_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&url_string", Util::StringUtil::getNotNullString(basic.url_string.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&url_visible", Util::StringUtil::getNotNullString(basic.url_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&gender", Util::StringUtil::getNotNullString(basic.gender.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&credentials_type", Util::StringUtil::getNotNullString(basic.credentials_type.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&credentials_num", Util::StringUtil::getNotNullString(basic.credentials_num.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&emai", Util::StringUtil::getNotNullString(basic.email.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&email_visible", Util::StringUtil::getNotNullString(basic.email_visible.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&lang", Util::StringUtil::getNotNullString(basic.lang.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&description", Util::StringUtil::getNotNullString(basic.description.c_str()), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountProfileEduUpdate(const EducationInfo& edu, UserTaskInfo* pTask)
{
	std::string param;

	SDKHelper::setParam(param, "&id", Util::StringUtil::getNotNullString(edu.id.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&type", Util::StringUtil::getNotNullString(edu.type.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&school", Util::StringUtil::getNotNullString(edu.school.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&department", Util::StringUtil::getNotNullString(edu.department.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&year", Util::StringUtil::getNotNullString(edu.year.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&visible", Util::StringUtil::getNotNullString(edu.visible.c_str()), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountProfileEduDestroy(const char* id, UserTaskInfo* pTask)
{
	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "&id", id, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountProfileCarUpdate(const CareerInfo& career, UserTaskInfo* pTask)
{
	std::string param;

	SDKHelper::setParam(param, "&id", Util::StringUtil::getNotNullString(career.id.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&city", Util::StringUtil::getNotNullString(career.city.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&province", Util::StringUtil::getNotNullString(career.province.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&start", Util::StringUtil::getNotNullString(career.start.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&end", Util::StringUtil::getNotNullString(career.end.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&company", Util::StringUtil::getNotNullString(career.company.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&department", Util::StringUtil::getNotNullString(career.department.c_str()), PARAM_ENCODE_UTF8);
	SDKHelper::setParam(param, "&visible", Util::StringUtil::getNotNullString(career.visible.c_str()), PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountProfileCarDestroy(const char* id, UserTaskInfo* pTask)
{
	if (Util::StringUtil::NullOrEmpty(id))
	{
		return WRC_USERID_NULL;
	}

	std::string param;
	SDKHelper::setParam(param, "id", id, PARAM_ENCODE_UTF8);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountAvatarUpload(const char* filePath, UserTaskInfo* pTask)
{
	if (Util::StringUtil::NullOrEmpty(filePath))
	{
		return WRC_FILEPATH_NULL;
	}

	std::string param;
	//
	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_AVATAR_UPLOAD
		, param, getUnifiedFormat(), httpengine::HM_POSTFORM, pTask);

	ptr->mPostFileField = "image";
	ptr->makeUploadTaskDetail(Util::StringUtil::getNotNullString(filePath));

	return internalEnqueue(ptr);
}

eWeiboResultCode SDKMethodImpl::postAccountUpdatePrivacy(const int comment, const int geo, const int message, const int realname, 
														 const int badge, const int mobile, UserTaskInfo* pTask)
{
	std::string param;

	SDKHelper::setIntParam(param, "&comment", comment);
	SDKHelper::setIntParam(param, "&geo", geo);
	SDKHelper::setIntParam(param, "&message", message);
	SDKHelper::setIntParam(param, "&realname", realname);
	SDKHelper::setIntParam(param, "&badge", badge);
	SDKHelper::setIntParam(param, "&mobile", mobile);

	WeiboRequestPtr ptr = internalMakeWeiboRequest(WBOPT_POST_ACCOUNT_UPDATE_PRIVACY
		, param, getUnifiedFormat(), httpengine::HM_POST, pTask);

	return internalEnqueue(ptr);
}