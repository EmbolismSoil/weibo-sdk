#include "config.h"
#include "SDKHelper.hxx"
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <util/common/StringUtil.hxx>
#include <HttpEngine/IHttpEngineCommon.hxx>

#include "strconv.h"
#include "Urlcode.h"
#include "IWeiboMethod.hxx"

using namespace weibo;

struct tagMethodURLElement
{
	int option;
	const char* url;
};

#if defined(INTERNAL_INTERFACE_USEABLE)
#	include "Internal/SDKInternURL.hxx"
#endif //

static const struct tagMethodURLElement gMethodURLElements[] = 
{
	{ WBOPT_NONE, "" },
	{ WBOPT_GET_STATUSES_PUBLIC_TIMELINE             , "/statuses/public_timeline"  }, //获取最新更新的公共微博消息 
	{ WBOPT_GET_STATUSES_FRIENDS_TIMELINE            , "/statuses/friends_timeline" }, //获取当前用户所关注用户的最新微博信息 (别名: statuses/home_timeline) 
	{ WBOPT_GET_STATUSES_HOME_TIMELINE               , "/statuses/home_timeline" }, //获取当前登录用户及其所关注用户的最新微博消息
	{ WBOPT_GET_STATUSES_USER_TIMELINE               , "/statuses/user_timeline"}, //获取用户发布的微博信息列表 
	{ WBOPT_GET_STATUSES_TIMELINE_BATCH               , "/statuses/timeline_batch" }, //批量获得指定的某一批用户的timeline
	{ WBOPT_GET_STATUSES_REPOST_TIMELINE             , "/statuses/repost_timeline" }, //返回一条微博的最新n条转发微博信息
	{ WBOPT_GET_STATUSES_REPOST_BYME                 , "/statuses/repost_by_me" }, //返回用户转发的最新n条微博信息
	{ WBOPT_GET_STATUSES_MENTIONS                    , "/statuses/mentions" },//获取@当前用户的微博列表 
	{ WBOPT_GET_STATUSES_SHOW                        , "/statuses/show" },//根据ID获取单条微博信息
	{ WBOPT_GET_STATUSES_SHOW_BATCH                  , "/statuses/show_batch" },//批量获取微博信息
	{ WBOPT_GET_STATUSES_QUERYMID                    , "/statuses/querymid" },//通过id获取mid
	{ WBOPT_GET_STATUSES_QUERYID                     , "/statuses/queryid" },//通过mid获取id
	{ WBOPT_GET_STATUSES_REPOST_DAILY                , "/statuses/hot/repost_daily"    },//按天返回热门转发榜
	{ WBOPT_GET_STATUSES_REPOST_WEEKLY               , "/statuses/hot/repost_weekly"   },//按周返回热门转发榜
	{ WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY          , "/statuses/hot/comments_daily"  },//按天返回热门评论榜
	{ WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY         , "/statuses/hot/comments_weekly" },//按周返回热门评论榜

	{ WBOPT_POST_STATUSES_REPOST                , "/statuses/repost"  },//转发一条微博信息
	{ WBOPT_POST_STATUSES_DESTROY               , "/statuses/destroy" },//删除微博评论信息
	{ WBOPT_POST_STATUSES_UPDATE                , "/statuses/update"  },//发布一条微博信息
	{ WBOPT_POST_STATUSES_UPLOAD_URL_TEXT       , "/statuses/upload_url_text" },//发布一条微博，同时指定上传的图片或图片url
	{ WBOPT_POST_STATUSES_UPLOAD                , "/statuses/upload"  },//发布一条微博，上传图片并发布一条微博信息

	{ WBOPT_GET_COMMENTS_SHOW          , "/comments/show" }, //获取某条微博的评论列表
	{ WBOPT_GET_COMMENTS_BYME          , "/comments/by_me" }, //我发出的评论列表
	{ WBOPT_GET_COMMENTS_TOME          , "/comments/to_me" }, //我收到的评论列表
	{ WBOPT_GET_COMMENTS_TIMELINE      , "/comments/timeline" }, //获取当前用户发送及收到的评论列表
	{ WBOPT_GET_COMMENTS_MENTIONS      , "/comments/mentions" }, //@到我的评论
	{ WBOPT_GET_COMMENTS_SHOWBATCH     , "/comments/show_batch" }, //@批量获取评论内容

	{ WBOPT_POST_COMMENTS_CREATE        , "/comments/create" }, //评论一条微博
	{ WBOPT_POST_COMMENTS_DESTROY       , "/comments/destroy" }, //删除一条评论
	{ WBOPT_POST_COMMENTS_DESTROY_BATCH , "/comments/destroy_batch" }, //批量删除评论
	{ WBOPT_POST_COMMENTS_REPLY         , "/comments/reply" }, //回复一条评论

	{ WBOPT_GET_DIRECTMESSAGES,				"/direct_messages"}, //获取当前用户最新私信列表
	{ WBOPT_GET_DIRECTMESSAGES_SENT,			"/direct_messages/sent"}, //获取当前用户发送的最新私信列表
	{ WBOPT_GET_DIRECTMESSAGES_USER_LIST,    "/direct_messages/user_list"}, //获取私信往来用户列表
	{ WBOPT_GET_DIRECTMESSAGES_CONVERSATION, "/direct_messages/conversation"}, //获取与指定用户的往来私信列表
	{ WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH,	"/direct_messages/show_batch"}, //批量获取私信内容
	{ WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE,	"/direct_messages/is_capable"}, //判断是否可以给对方发私信
	{ WBOPT_POST_DIRECTMESSAGES_NEW,			"/direct_messages/new"}, //发送一条私信
	{ WBOPT_POST_DIRECTMESSAGES_DESTORY,		"/direct_messages/destroy"}, //删除一条私信
	{ WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH,"/direct_messages/destroy_batch"},	//批量删除私信

	{ WBOPT_GET_USERS_SHOW,					"/users/show"}, //获取用户资料
	{ WBOPT_GET_USERS_DOMAIN_SHOW,			"/users/domain_show"}, //通过个性域名获取用户信息
	{ WBOPT_GET_USERS_SHOW_BATCH,			"/users/show_batch"}, //批量获取用户信息

	{ WBOPT_GET_ACCOUNT_PROFILE_BASIC, "/account/profile/basic" }, //获取用户基本信息
	{ WBOPT_GET_ACCOUNT_PROFILE_EDUCATION, "/account/profile/education" }, //获取教育信息
	{ WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH, "/account/profile/education_batch" }, //批量获取教育信息
	{ WBOPT_GET_ACCOUNT_PROFILE_CAREER, "/account/profile/career" }, //获取职业信息
	{ WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH, "/account/profile/career_batch" }, //批量获取职业信息
	{ WBOPT_GET_ACCOUNT_GET_PRIVACY, "/account/get_privacy" }, //获取隐私设置信息
	{ WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST, "/account/profile/school_list" }, //获取所有学校列表
	{ WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS, "/account/rate_limit_status" }, //获取当前用户API访问频率限制
	{ WBOPT_GET_ACCOUNT_GET_UID, "/account/get_uid" }, //OAuth授权之后获取用户UID（作用相当于旧版接口的account/verify_credentials）

	{ WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE , "/account/profile/basic_update" }, // 更新用户基本信息
	{ WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE, "/account/profile/edu_update" }, // 更新用户教育信息
	{ WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY , "/account/profile/edu_destroy" }, // 删除用户教育信息
	{ WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE , "/account/profile/car_update" }, // 更新用户职业信息
	{ WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY , "/account/profile/car_destroy" }, // 删除用户职业信息
	{ WBOPT_POST_ACCOUNT_AVATAR_UPLOAD , "/account/avatar/upload" }, // 上传头像
	{ WBOPT_POST_ACCOUNT_UPDATE_PRIVACY , "/account/update_privacy" }, // 更新隐私设置

	{ WBOPT_GET_FRIENDSHIPS_FRIENDS, "/friendships/friends"}, //获取用户的关注列表
	{ WBOPT_GET_FRIENDSHIPS_IN_COMMON, "/friendships/friends/in_common"}, //获取共同关注人列表接口
	{ WBOPT_GET_FRIENDSHIPS_BILATERAL, "/friendships/friends/bilateral"}, //获取双向关注列表
	{ WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS, "/friendships/friends/bilateral/ids"}, //获取双向关注ID列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS, "/friendships/friends/ids"}, //获取用户关注对象uid列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH, "/friendships/friends/remark_batch"},	//批量获取备注
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS, "/friendships/followers"}, //获取用户粉丝列表及每个粉丝的最新一条微博
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS, "/friendships/followers/ids"}, //获取用户粉丝对象uid列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE,"/friendships/followers/active"},		//获取用户优质粉丝列表关系链
	{ WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS, "/friendships/friends_chain/followers"},//获取我的关注人中关注了指定用户的分组
	{ WBOPT_GET_FRIENDSHIPS_SHOW, "/friendships/show"}, //获取两个用户关系的详细情况
	{ WBOPT_POST_FRIENDSHIPS_CREATE, "/friendships/create"}, //关注某用户
	{ WBOPT_POST_FRIENDSHIPS_CREATE_BATCH, "/friendships/create_batch"}, //批量关注用户
	{ WBOPT_POST_FRIENDSHIPS_DESTROY, "/friendships/destroy"}, //取消关注某用户	
	{ WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY,"/friendships/followers/destroy"}, //移除粉丝
	{ WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE, "/friendships/remark/update"}, //更新关注人备注

	{ WBOPT_GET_FAVORITES, "/favorites" }, //获取当前登录用户的收藏列表
	{ WBOPT_GET_FAVORITES_SHOW, "/favorites/show" }, //获取单条收藏信息
	{ WBOPT_GET_FAVORITES_BY_TAGS, "/favorites/by_tags" }, //获取当前用户某个标签下的收藏列表
	{ WBOPT_GET_FAVORITES_TAGS, "/favorites/tags" }, //当前登录用户的收藏标签列表
	{ WBOPT_POST_FAVORITES_CREATE, "/favorites/create" }, //添加收藏
	{ WBOPT_POST_FAVORITES_DESTROY, "/favorites/destroy" }, //删除收藏
	{ WBOPT_POST_FAVORITES_DESTROY_BATCH, "/favorites/destroy_batch" }, //批量删除收藏
	{ WBOPT_POST_FAVORITES_TAGS_UPDATE, "/favorites/tags/update" }, //更新收藏标签
	{ WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH, "/favorites/tags/update_batch" }, //更新当前用户所有收藏下的指定标签
	{ WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH, "/favorites/tags/destroy_batch" }, //删除当前用户所有收藏下的指定标签

	{ WBOPT_GET_TRENDS, "/trends" }, //获取某人话题
	{ WBOPT_GET_TRENDS_STATUSES, "/trends/statuses" }, //获取某一话题下的微博
	{ WBOPT_GET_TRENDS_HOURLY, "/trends/hourly" }, //返回最近一小时内的热门话题
	{ WBOPT_GET_TRENDS_DAILY, "/trends/daily" }, //返回最近一天内的热门话题
	{ WBOPT_GET_TRENDS_WEEKLY, "/trends/weekly" }, //返回最近一周内的热门话题
	{ WBOPT_POST_TRENDS_FOLLOW, "/trends/follow" }, //关注某话题
	{ WBOPT_POST_TRENDS_DESTROY, "/trends/destroy" }, //取消关注的某一个话题

	{ WBOPT_GET_TAGS, "/tags" }, //返回指定用户的标签列表
	{ WBOPT_GET_TAGS_TAGS_BATCH, "/tags/tags_batch" }, //批量获取用户标签
	{ WBOPT_GET_TAGS_SUGGESTIONS, "/tags/suggestions" }, //返回系统推荐的标签列表
	{ WBOPT_POST_TAGS_CREATE, "/tags/create" }, //添加用户标签
	{ WBOPT_POST_TAGS_DESTROY, "/tags/destroy" }, //删除用户标签
	{ WBOPT_POST_TAGS_DESTROY_BATCH, "/tags/destroy_batch" }, //批量删除用户标签

	{ WBOPT_GET_SEARCH_SUGGESTIONS_USERS, "/search/suggestions/users" },//搜用户搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES, "/search/suggestions/statuses" },//搜微博搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS, "/search/suggestions/schools" },//搜学校搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES, "/search/suggestions/companies"},//搜公司搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_APPS, "/search/suggestions/apps" },//搜应用搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS, "/search/suggestions/at_users"},//@联想搜索
	{ WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE, "/search/suggestions/integrate"}, //综合联想搜索
	{ WBOPT_GET_SEARCH_STATUSES, "/search/statuses"}, //微博搜索 
	{ WBOPT_GET_SEARCH_GEO_STATUSES, "/search/geo/statuses"},//搜索指定范围内的微博
	{ WBOPT_GET_SEARCH_USERS, "/search/users"}, //搜索用户

	{ WBOPT_GET_SUGGESTIONS_FAVORITES_HOT, "/suggestions/favorites/hot" }, //热门收藏
	{ WBOPT_GET_SUGGESTIONS_USERS_HOT, "/suggestions/users/hot" }, //获取系统推荐用户
	{ WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED, "/suggestions/users/may_interested" }, //获取用户可能感兴趣的人
	{ WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED, "/suggestions/users/not_interested" }, //不感兴趣的人
	{ WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS, "/suggestions/users/by_status" }, //根据微博内容推荐用户

	{ WBOPT_GET_SHORT_URL_SHORTEN, "/short_url/shorten" }, //将一个或多个长链接转换成短链接
	{ WBOPT_GET_SHORT_URL_EXPAND, "/short_url/expand" }, //将一个或多个短链接还原成原始的长链接
	{ WBOPT_GET_SHORT_URL_SHARE_COUNTS, "/short_url/share/counts" }, //取得一个短链接在微博上的微博分享数（包含原创和转发的微博）
	{ WBOPT_GET_SHORT_URL_SHARE_STATUSES, "/short_url/share/statuses" }, //取得包含指定单个短链接的最新微博内容
	{ WBOPT_GET_SHORT_URL_COMMENT_COUNTS, "/short_url/comment/counts" }, //取得一个短链接在微博上的微博评论数
	{ WBOPT_GET_SHORT_URL_COMMENT_COMMENTS, "/short_url/comment/comments" }, //取得包含指定单个短链接的最新微博评论内容
};

#define IN_BETWEEN(begin, end, optionId) \
	(begin <= methodOption && end >= methodOption)

void SDKHelper::getMethodURLFromOption(unsigned int methodOption, std::string &baseURL)
{
	const int counts = sizeof(gMethodURLElements)/sizeof(gMethodURLElements[0]);

	if (IN_BETWEEN(WBOPT_GET_SHORT_URL_SHORTEN, 
		WBOPT_GET_SHORT_URL_COMMENT_COMMENTS, methodOption))
	{
		baseURL = "https://api.t.sina.com.cn";
	}
	else
	{
		baseURL = "https://api.weibo.com/2";
	}

	bool bFound = false;
	for (int i = 0; i < counts; ++ i)
	{
		if (gMethodURLElements[i].option == methodOption)
		{
			bFound = true;
			baseURL += gMethodURLElements[i].url;
			break;
		}
	}

#if defined(INTERNAL_INTERFACE_USEABLE)

	if (!bFound)
	{
		if (IN_BETWEEN(WBOPT_GET_REMIND_UNREAD_COUNT, 
			WBOPT_POST_REMIND_CLEAR_COUNT, optionId))
		{
			baseURL = "https://api.t.sina.com.cn";
		}

		for (int i = 0; i < counts; ++ i)
		{
			if (gInternalMethodURLElements[i].option == methodOption)
			{
				baseURL += gInternalMethodURLElements[i].url;
				break;
			}
		}
	}

#endif //INTERNAL_INTERFACE_USEABLE
}

int SDKHelper::convertEngineErrorToSDKError(const int code)
{
	if (code == 0)
	{
		return WERR_OK;
	}

	switch(code)
	{
	case httpengine::HE_PROTOCOL_ERROR: return WERR_PROTOCOL;
	case httpengine::HE_CURL_ERROR: return WERR_CURL; 

	default:
		break;
	}
	return WERR_UNKNOW;
}

enum eParamFormat
{
	ParamFMT = 0,
	ParamFMT_UTF8 = 0x01,
	ParamFMT_URLENCODE = 0x02,
};

int getParamnameFormat(int paramformat)
{
	int paramf = 0;

	if (paramformat & ParamEncodedName)
	{
		paramf |= ParamFMT_URLENCODE;
	}

	if (paramformat & ParamUTF8Name) 
	{
		paramf |= ParamFMT_UTF8;
	}
	return paramf;
}

int getParamvalueFormat(int  paramformat)
{
	int paramf = 0;

	if (paramformat & ParamEncodedValue)
	{
		paramf |= ParamFMT_URLENCODE;
	}

	if(paramformat & ParamUTF8Value)
	{
		paramf |= ParamFMT_UTF8;
	}
	return paramf;
}

void setParamFormat(char* param, const char* paramval, int paramformat)
{
#if 0
	int vallen= 0;
	char* outstr = NULL;
	char* urlenc = NULL;

	if (paramformat & ParamFMT_UTF8)
	{
		if (lo_C2Utf8(&outstr, paramval) <= 0)
		{
			outstr = "";
		}
	}
	else
	{
		outstr = (char*)paramval;
	}

	if (paramformat & ParamFMT_URLENCODE)
	{		
		vallen = lo_UrlEncodeA(&urlenc , outstr , -1 );
		if ( vallen <= 0 )
		{
			if ( outstr != (char*)param && outstr ) 
			{
				free( outstr );
			}
			return ;
		}
		if (outstr != (char*)param && outstr)
		{
			free(outstr);
		}
	}
	else
	{
		urlenc = outstr;
	}
	strcat(param, urlenc);
	if (urlenc != (char*)paramval && urlenc)
	{
		free(urlenc);
	}
#else

	if (!paramval || paramval == '\0')
	{
		// Error : param value is null!
		return ;
	}

	char* resultStr = NULL;
	int resultLength = 0;

	// Need utf8 convert.
	if (paramformat & ParamFMT_UTF8)
	{
		resultLength = lo_C2Utf8(&resultStr , paramval);
	}
	else
	{
		resultStr = (char*)paramval;
	}

	if ((paramformat & ParamFMT_URLENCODE) && (resultStr && *resultStr != '\0'))
	{
		char* urlEncodeStr = NULL;
		const int urlEncodeLength = lo_UrlEncodeA(&urlEncodeStr, resultStr, -1);
		if (urlEncodeLength > 0 && urlEncodeStr)
		{
			if (resultLength > 0)
			{
				free(resultStr);	
			}
			resultStr = urlEncodeStr;
			resultLength = urlEncodeLength;
		}
	}

	if (resultStr && *resultStr != '\0')
	{
		strcat(param, resultStr);
		if (resultLength > 0)
		{
			free(resultStr);
		}
	}

#endif //0
}

void SDKHelper::setParam(char* param, const char *paramname, const char *paramval, int paramformat)
{
	if (!paramval || *paramval == '\0')
	{
		return;
	}
	setParamFormat(param, paramname, getParamnameFormat(paramformat));
	strcat(param, "=");
	setParamFormat(param, paramval, getParamvalueFormat(paramformat));
}

void SDKHelper::setIntParam(char * param, const char * paramName, const long long paramval, bool forceAdd)
{
	char val[16] = { 0 };
	if (!forceAdd && paramval <= 0)
	{
		return ;
	}
	sprintf(val, "%lld", paramval);
	setParam(param, paramName, (const char *)val, 0);
}

WeiboRequestPtr SDKHelper::makeRequest(unsigned int methodOption, char *addtionParam, const eWeiboRequestFormat reqformat
									   , const httpengine::HttpMethod method, const char* appkey, const char* accessToken, const UserTaskInfo* pTask)
{
	WeiboRequestPtr requestPtr = boost::make_shared<WeiboRequest>();
	requestPtr->mOptionId = methodOption;
	requestPtr->mHttpMethod = method;

	// base url
	std::string baseURL;
	SDKHelper::getMethodURLFromOption(methodOption, baseURL);

	// format 
	if (WRF_JSON == reqformat)
	{
		baseURL += ".json";
	}
	else if (WRF_XML == reqformat)
	{
		baseURL += ".xml";
	}

	// addtional param 
	if (addtionParam && *addtionParam != '\0')
	{
		if (std::string::npos == baseURL.find_first_of('?'))
		{
			addtionParam[0] = '?';
		}
		baseURL += addtionParam;
	}

	// Build request url and post args, from method.
	makeRequestURL(requestPtr->mURL, requestPtr->mPostArg
		, baseURL.c_str(), (method != httpengine::HM_GET), appkey, accessToken);

	if (pTask)
	{
		memcpy(&(requestPtr->mTaskInfo), pTask, sizeof(UserTaskInfo));
	}
	return requestPtr;
}


void SDKHelper::makeRequestURL(std::string &outURL, std::string &outParam, const char* baseURL
							   , bool isPost, const char* appkey, const char* accessToken)
{
	std::string url = Util::StringUtil::getNotNullString(baseURL);
	if (!url.empty())
	{
		if (isPost)
		{
			std::vector<std::string> vec;
			boost::split(vec, url, boost::is_any_of("?"));
			std::vector<std::string>::iterator it = vec.begin();
			outURL = *it;
			++ it;
			if (it != vec.end())
			{
				outParam = *it;
			}

			outParam += "&access_token=";
			outParam += Util::StringUtil::getNotNullString(accessToken);
		}
		else
		{
			outURL = url;
			outURL += (std::string::npos != outURL.find_first_of('?') ? "&source=" : "?source=" );
			outURL += Util::StringUtil::getNotNullString(appkey);

			outURL += "&access_token=";
			outURL += Util::StringUtil::getNotNullString(accessToken);
		}
	}
}

void SDKHelper::makeVariableParams(char *outParam, const int length, VariableParams* var)
{
	if (!var)
	{
		return ;
	}
	// based variable
	SDKHelper::setIntParam(outParam, "&since_id", var->since_id);
	SDKHelper::setIntParam(outParam, "&max_id", var->max_id);
	SDKHelper::setIntParam(outParam, "&count", var->count);
	SDKHelper::setIntParam(outParam, "&page", var->page);
	SDKHelper::setIntParam(outParam, "&base_app", var->base_app);
	SDKHelper::setIntParam(outParam, "&feature", var->feature);
	SDKHelper::setIntParam(outParam, "&is_encoded", var->is_encoded);
	SDKHelper::setIntParam(outParam, "&cursor", var->cursor);

	// variable for statuses
	SDKHelper::setParam(outParam, "&simplify", var->simplify.c_str(), PARAM_ENCODE_UTF8);
	SDKHelper::setIntParam(outParam, "&filter_by_source", var->filter_by_source);
	SDKHelper::setIntParam(outParam, "&filter_by_type", var->filter_by_type);
	SDKHelper::setIntParam(outParam, "&filter_by_author", var->filter_by_author);
	SDKHelper::setIntParam(outParam, "&trim_user", var->trim_user);
	SDKHelper::setIntParam(outParam, "&trim_status", var->trim_status);
}

void SDKHelper::makeIDParams(char *outParam, const int length, const ID *usrId)
{
	if (!usrId)
	{
		return ;
	}

	if (usrId->keyName.empty())
	{
		if (ID::IDT_ID == usrId->idType)
		{
			SDKHelper::setParam(outParam, "&uid", usrId->id.c_str(), ParamEncodedValue);
		}
		else if (ID::IDT_SCREENNAME == usrId->idType)
		{
			SDKHelper::setParam(outParam, "&screen_name", usrId->id.c_str(), ParamEncodedValue);
		}
	}
	else
	{
		std::string key = "&";
		key += usrId->keyName;
		SDKHelper::setParam(outParam, key.c_str(), usrId->id.c_str(), PARAM_ENCODE_UTF8);
	}
}
