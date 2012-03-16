#include "config.h"
#include "SDKHelper.hxx"
#include <stdio.h>

#include <util/common/StringUtil.hxx>
#include <HttpEngine/IHttpEngineCommon.hxx>

#include "Urlcode.h"
#include "IWeiboMethod.hxx"

using namespace weibo;

#ifdef _DEBUG
static bool IsUTF8(const char *str)
{
	int count = 0;
	unsigned char chr;
	while (chr = *str++)
	{
		if (count == 0)
		{
			if (chr >= 0x80)
			{
				do
				{
					chr <<= 1;
					count++;
				} while ((chr & 0x80) != 0);
				count--;                
				if (count != 2)
				{
					return false;
				}
			}
		}
		else
		{
			if ((chr & 0xC0) != 0x80)
			{
				return false;
			}
			count--;
		}
	}
	return count == 0;
}
#endif

enum enHostType
{
	EHT_V3,
	EHT_V4,
};

struct tagMethodURLElement
{
	int option;
	const char* url;
	enHostType type;
};

#if defined(INTERNAL_INTERFACE_USEABLE)
#	include "Internal/SDKInternURL.hxx"
#endif //

static const struct tagMethodURLElement gMethodURLElements[] = 
{
	{ WBOPT_NONE, "" },
	{ WBOPT_GET_STATUSES_PUBLIC_TIMELINE, "/statuses/public_timeline", EHT_V4 }, //获取最新更新的公共微博消息 
	{ WBOPT_GET_STATUSES_FRIENDS_TIMELINE, "/statuses/friends_timeline", EHT_V4 }, //获取当前用户所关注用户的最新微博信息 (别名: statuses/home_timeline) 
	{ WBOPT_GET_STATUSES_HOME_TIMELINE, "/statuses/home_timeline", EHT_V4 }, //获取当前登录用户及其所关注用户的最新微博消息
	{ WBOPT_GET_STATUSES_USER_TIMELINE, "/statuses/user_timeline", EHT_V4 }, //获取用户发布的微博信息列表 
	{ WBOPT_GET_STATUSES_TIMELINE_BATCH, "/statuses/timeline_batch", EHT_V4 }, //批量获得指定的某一批用户的timeline
	{ WBOPT_GET_STATUSES_REPOST_TIMELINE, "/statuses/repost_timeline", EHT_V4 }, //返回一条微博的最新n条转发微博信息
	{ WBOPT_GET_STATUSES_REPOST_BYME, "/statuses/repost_by_me", EHT_V4 }, //返回用户转发的最新n条微博信息
	{ WBOPT_GET_STATUSES_MENTIONS, "/statuses/mentions", EHT_V4 },//获取@当前用户的微博列表 
	{ WBOPT_GET_STATUSES_SHOW, "/statuses/show", EHT_V4 },//根据ID获取单条微博信息
	{ WBOPT_GET_STATUSES_SHOW_BATCH, "/statuses/show_batch", EHT_V4 },//批量获取微博信息
	{ WBOPT_GET_STATUSES_QUERYMID, "/statuses/querymid", EHT_V4 },//通过id获取mid
	{ WBOPT_GET_STATUSES_QUERYID, "/statuses/queryid", EHT_V4 },//通过mid获取id
	{ WBOPT_GET_STATUSES_REPOST_DAILY, "/statuses/hot/repost_daily", EHT_V4 },//按天返回热门转发榜
	{ WBOPT_GET_STATUSES_REPOST_WEEKLY, "/statuses/hot/repost_weekly", EHT_V4 },//按周返回热门转发榜
	{ WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY, "/statuses/hot/comments_daily", EHT_V4 },//按天返回热门评论榜
	{ WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY, "/statuses/hot/comments_weekly", EHT_V4 },//按周返回热门评论榜

	{ WBOPT_POST_STATUSES_REPOST, "/statuses/repost", EHT_V4 },//转发一条微博信息
	{ WBOPT_POST_STATUSES_DESTROY, "/statuses/destroy", EHT_V4 },//删除微博评论信息
	{ WBOPT_POST_STATUSES_UPDATE, "/statuses/update", EHT_V4 },//发布一条微博信息
	{ WBOPT_POST_STATUSES_UPLOAD_URL_TEXT, "/statuses/upload_url_text", EHT_V4 },//发布一条微博，同时指定上传的图片或图片url
	{ WBOPT_POST_STATUSES_UPLOAD, "/statuses/upload" },//发布一条微博，上传图片并发布一条微博信息

	{ WBOPT_GET_COMMENTS_SHOW, "/comments/show", EHT_V4 }, //获取某条微博的评论列表
	{ WBOPT_GET_COMMENTS_BYME, "/comments/by_me", EHT_V4 }, //我发出的评论列表
	{ WBOPT_GET_COMMENTS_TOME, "/comments/to_me", EHT_V4 }, //我收到的评论列表
	{ WBOPT_GET_COMMENTS_TIMELINE, "/comments/timeline", EHT_V4 }, //获取当前用户发送及收到的评论列表
	{ WBOPT_GET_COMMENTS_MENTIONS, "/comments/mentions", EHT_V4 }, //@到我的评论
	{ WBOPT_GET_COMMENTS_SHOWBATCH, "/comments/show_batch", EHT_V4 }, //@批量获取评论内容

	{ WBOPT_POST_COMMENTS_CREATE, "/comments/create", EHT_V4 }, //评论一条微博
	{ WBOPT_POST_COMMENTS_DESTROY, "/comments/destroy", EHT_V4 }, //删除一条评论
	{ WBOPT_POST_COMMENTS_DESTROY_BATCH , "/comments/destroy_batch", EHT_V4 }, //批量删除评论
	{ WBOPT_POST_COMMENTS_REPLY, "/comments/reply", EHT_V4 }, //回复一条评论

	{ WBOPT_GET_DIRECTMESSAGES, "/direct_messages", EHT_V4 }, //获取当前用户最新私信列表
	{ WBOPT_GET_DIRECTMESSAGES_SENT, "/direct_messages/sent", EHT_V4 }, //获取当前用户发送的最新私信列表
	{ WBOPT_GET_DIRECTMESSAGES_USER_LIST, "/direct_messages/user_list", EHT_V4 }, //获取私信往来用户列表
	{ WBOPT_GET_DIRECTMESSAGES_CONVERSATION, "/direct_messages/conversation", EHT_V4 }, //获取与指定用户的往来私信列表
	{ WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH,	"/direct_messages/show_batch", EHT_V4 }, //批量获取私信内容
	{ WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE,	"/direct_messages/is_capable", EHT_V4 }, //判断是否可以给对方发私信
	{ WBOPT_POST_DIRECTMESSAGES_NEW, "/direct_messages/new", EHT_V4 }, //发送一条私信
	{ WBOPT_POST_DIRECTMESSAGES_DESTORY, "/direct_messages/destroy", EHT_V4 }, //删除一条私信
	{ WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH,"/direct_messages/destroy_batch", EHT_V4 },	//批量删除私信

	{ WBOPT_GET_USERS_SHOW, "/users/show", EHT_V4 }, //获取用户资料
	{ WBOPT_GET_USERS_DOMAIN_SHOW, "/users/domain_show", EHT_V4 }, //通过个性域名获取用户信息
	{ WBOPT_GET_USERS_SHOW_BATCH, "/users/show_batch", EHT_V4 }, //批量获取用户信息

	{ WBOPT_GET_ACCOUNT_PROFILE_BASIC, "/account/profile/basic", EHT_V4 }, //获取用户基本信息
	{ WBOPT_GET_ACCOUNT_PROFILE_EDUCATION, "/account/profile/education", EHT_V4 }, //获取教育信息
	{ WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH, "/account/profile/education_batch", EHT_V4 }, //批量获取教育信息
	{ WBOPT_GET_ACCOUNT_PROFILE_CAREER, "/account/profile/career", EHT_V4 }, //获取职业信息
	{ WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH, "/account/profile/career_batch", EHT_V4 }, //批量获取职业信息
	{ WBOPT_GET_ACCOUNT_GET_PRIVACY, "/account/get_privacy", EHT_V4 }, //获取隐私设置信息
	{ WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST, "/account/profile/school_list", EHT_V4 }, //获取所有学校列表
	{ WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS, "/account/rate_limit_status", EHT_V4 }, //获取当前用户API访问频率限制
	{ WBOPT_GET_ACCOUNT_GET_UID, "/account/get_uid", EHT_V4 }, //OAuth授权之后获取用户UID（作用相当于旧版接口的account/verify_credentials）

	{ WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE , "/account/profile/basic_update", EHT_V4 }, // 更新用户基本信息
	{ WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE, "/account/profile/edu_update", EHT_V4 }, // 更新用户教育信息
	{ WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY , "/account/profile/edu_destroy", EHT_V4 }, // 删除用户教育信息
	{ WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE , "/account/profile/car_update", EHT_V4 }, // 更新用户职业信息
	{ WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY , "/account/profile/car_destroy", EHT_V4 }, // 删除用户职业信息
	{ WBOPT_POST_ACCOUNT_AVATAR_UPLOAD , "/account/avatar/upload", EHT_V4 }, // 上传头像
	{ WBOPT_POST_ACCOUNT_UPDATE_PRIVACY , "/account/update_privacy", EHT_V4 }, // 更新隐私设置

	{ WBOPT_GET_FRIENDSHIPS_FRIENDS, "/friendships/friends", EHT_V4 }, //获取用户的关注列表
	{ WBOPT_GET_FRIENDSHIPS_IN_COMMON, "/friendships/friends/in_common", EHT_V4 }, //获取共同关注人列表接口
	{ WBOPT_GET_FRIENDSHIPS_BILATERAL, "/friendships/friends/bilateral", EHT_V4 }, //获取双向关注列表
	{ WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS, "/friendships/friends/bilateral/ids", EHT_V4 }, //获取双向关注ID列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS, "/friendships/friends/ids", EHT_V4 }, //获取用户关注对象uid列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH, "/friendships/friends/remark_batch"},	//批量获取备注
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS, "/friendships/followers", EHT_V4 }, //获取用户粉丝列表及每个粉丝的最新一条微博
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS, "/friendships/followers/ids", EHT_V4 }, //获取用户粉丝对象uid列表
	{ WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE,"/friendships/followers/active", EHT_V4 },		//获取用户优质粉丝列表关系链
	{ WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS, "/friendships/friends_chain/followers", EHT_V4 }, //获取我的关注人中关注了指定用户的分组
	{ WBOPT_GET_FRIENDSHIPS_SHOW, "/friendships/show", EHT_V4 }, //获取两个用户关系的详细情况
	{ WBOPT_POST_FRIENDSHIPS_CREATE, "/friendships/create", EHT_V4 }, //关注某用户
	{ WBOPT_POST_FRIENDSHIPS_CREATE_BATCH, "/friendships/create_batch", EHT_V4 }, //批量关注用户
	{ WBOPT_POST_FRIENDSHIPS_DESTROY, "/friendships/destroy", EHT_V4 }, //取消关注某用户	
	{ WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY,"/friendships/followers/destroy"}, //移除粉丝
	{ WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE, "/friendships/remark/update", EHT_V4 }, //更新关注人备注

	{ WBOPT_GET_FAVORITES, "/favorites", EHT_V4 }, //获取当前登录用户的收藏列表
	{ WBOPT_GET_FAVORITES_SHOW, "/favorites/show", EHT_V4 }, //获取单条收藏信息
	{ WBOPT_GET_FAVORITES_BY_TAGS, "/favorites/by_tags", EHT_V4 }, //获取当前用户某个标签下的收藏列表
	{ WBOPT_GET_FAVORITES_TAGS, "/favorites/tags", EHT_V4 }, //当前登录用户的收藏标签列表
	{ WBOPT_POST_FAVORITES_CREATE, "/favorites/create", EHT_V4 }, //添加收藏
	{ WBOPT_POST_FAVORITES_DESTROY, "/favorites/destroy", EHT_V4 }, //删除收藏
	{ WBOPT_POST_FAVORITES_DESTROY_BATCH, "/favorites/destroy_batch", EHT_V4 }, //批量删除收藏
	{ WBOPT_POST_FAVORITES_TAGS_UPDATE, "/favorites/tags/update", EHT_V4 }, //更新收藏标签
	{ WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH, "/favorites/tags/update_batch", EHT_V4 }, //更新当前用户所有收藏下的指定标签
	{ WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH, "/favorites/tags/destroy_batch", EHT_V4 }, //删除当前用户所有收藏下的指定标签

	{ WBOPT_GET_TRENDS, "/trends", EHT_V4 }, //获取某人话题
	{ WBOPT_GET_TRENDS_STATUSES, "/trends/statuses", EHT_V4 }, //获取某一话题下的微博
	{ WBOPT_GET_TRENDS_HOURLY, "/trends/hourly", EHT_V4 }, //返回最近一小时内的热门话题
	{ WBOPT_GET_TRENDS_DAILY, "/trends/daily", EHT_V4 }, //返回最近一天内的热门话题
	{ WBOPT_GET_TRENDS_WEEKLY, "/trends/weekly", EHT_V4 }, //返回最近一周内的热门话题
	{ WBOPT_POST_TRENDS_FOLLOW, "/trends/follow", EHT_V4 }, //关注某话题
	{ WBOPT_POST_TRENDS_DESTROY, "/trends/destroy", EHT_V4 }, //取消关注的某一个话题

	{ WBOPT_GET_TAGS, "/tags", EHT_V4 }, //返回指定用户的标签列表
	{ WBOPT_GET_TAGS_TAGS_BATCH, "/tags/tags_batch", EHT_V4 }, //批量获取用户标签
	{ WBOPT_GET_TAGS_SUGGESTIONS, "/tags/suggestions", EHT_V4 }, //返回系统推荐的标签列表
	{ WBOPT_POST_TAGS_CREATE, "/tags/create", EHT_V4 }, //添加用户标签
	{ WBOPT_POST_TAGS_DESTROY, "/tags/destroy", EHT_V4 }, //删除用户标签
	{ WBOPT_POST_TAGS_DESTROY_BATCH, "/tags/destroy_batch", EHT_V4 }, //批量删除用户标签

	{ WBOPT_GET_SEARCH_SUGGESTIONS_USERS, "/search/suggestions/users", EHT_V4 }, //搜用户搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES, "/search/suggestions/statuses", EHT_V4 }, //搜微博搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS, "/search/suggestions/schools", EHT_V4 }, //搜学校搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES, "/search/suggestions/companies", EHT_V4 }, //搜公司搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_APPS, "/search/suggestions/apps" },//搜应用搜索建议
	{ WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS, "/search/suggestions/at_users", EHT_V4 }, //@联想搜索
	{ WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE, "/search/suggestions/integrate", EHT_V4 }, //综合联想搜索
	{ WBOPT_GET_SEARCH_STATUSES, "/search/statuses", EHT_V4 }, //微博搜索 
	{ WBOPT_GET_SEARCH_GEO_STATUSES, "/search/geo/statuses", EHT_V4 }, //搜索指定范围内的微博
	{ WBOPT_GET_SEARCH_USERS, "/search/users", EHT_V4 }, //搜索用户

	{ WBOPT_GET_SUGGESTIONS_FAVORITES_HOT, "/suggestions/favorites/hot", EHT_V4 }, //热门收藏
	{ WBOPT_GET_SUGGESTIONS_USERS_HOT, "/suggestions/users/hot", EHT_V4 }, //获取系统推荐用户
	{ WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED, "/suggestions/users/may_interested", EHT_V4 }, //获取用户可能感兴趣的人
	{ WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED, "/suggestions/users/not_interested", EHT_V4 }, //不感兴趣的人
	{ WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS, "/suggestions/users/by_status", EHT_V4 }, //根据微博内容推荐用户

	{ WBOPT_GET_SHORT_URL_SHORTEN, "/short_url/shorten", EHT_V3 }, //将一个或多个长链接转换成短链接
	{ WBOPT_GET_SHORT_URL_EXPAND, "/short_url/expand", EHT_V3 }, //将一个或多个短链接还原成原始的长链接
	{ WBOPT_GET_SHORT_URL_SHARE_COUNTS, "/short_url/share/counts", EHT_V3 }, //取得一个短链接在微博上的微博分享数（包含原创和转发的微博）
	{ WBOPT_GET_SHORT_URL_SHARE_STATUSES, "/short_url/share/statuses", EHT_V3 }, //取得包含指定单个短链接的最新微博内容
	{ WBOPT_GET_SHORT_URL_COMMENT_COUNTS, "/short_url/comment/counts", EHT_V3 }, //取得一个短链接在微博上的微博评论数
	{ WBOPT_GET_SHORT_URL_COMMENT_COMMENTS, "/short_url/comment/comments", EHT_V3 }, //取得包含指定单个短链接的最新微博评论内容
	{ WBOPT_GET_SHORT_URL_INFO, "/short_url/batch_info", EHT_V3 },

	// Unread
	{ WBOPT_GET_REMIND_UNREAD_COUNT, "/remind/unread_count", EHT_V4}, //获取某个用户的各种消息未读数
	{ WBOPT_POST_STATUSES_RESET_COUNT, "/statuses/reset_count", EHT_V3}, //type: 1.comments, 2. @me, 3.Direct Message 4. follower

	// Groups
	{ WBOPT_GET_GROUPS_JOINED, "/groups/joined", EHT_V4 },
	{ WBOPT_GET_GROUPS_SHOW_BATCH, "/groups/show_batch", EHT_V4 },
	{ WBOPT_GET_GROUPS_GET_ANNOUNCEMENT, "/groups/get_announcement", EHT_V4 },
	{ WBOPT_GET_GROUPS_ADMIN, "/groups/%s/admin", EHT_V3},
	{ WBOPT_GET_GROUPS_USERS, "/groups/%s/users", EHT_V3 },
	{ WBOPT_GET_GROUPS_SUGGESTION_MAY_INTERESTED, "/groups/suggestions/may_interested", EHT_V3 },
	{ WBOPT_GET_GROUPS_CHAT_BLOCK, "/groups/chat/block", EHT_V4 },
	{ WBOPT_GET_GROUPS_CHAT_UNBLOCK, "/groups/chat/unblock", EHT_V4 },
	{ WBOPT_GET_GROUPS_CHAT_IS_BLOCKED, "/groups/chat/is_blocked", EHT_V4 },
	{ WBOPT_GET_GROUP_USERS_JOINED_STATUSES, "/groups/statuses/joined_timeline", EHT_V4},
};

//#define IN_BETWEEN(begin, end, optionId) \
//	(begin <= methodOption && end >= methodOption)
//
//#define IS_METHOD_USEOLD(option)\
//	IN_BETWEEN(WBOPT_GET_SHORT_URL_SHORTEN, WBOPT_GET_SHORT_URL_INFO, option)\
//	|| (WBOPT_POST_STATUSES_RESET_COUNT == option)

const char* getMethodBaseURL(const enHostType type)
{
	switch(type)
	{
	case EHT_V3:
		return "https://api.t.sina.com.cn";

	case EHT_V4: 
		return "https://api.weibo.com/2";

	default:
		{
			// Error: Undefined type!
			assert(false);
		}
		break;
	}
	return "";
}

void SDKHelper::getMethodURLFromOption(unsigned int methodOption, std::string &baseURL)
{
	const int counts = sizeof(gMethodURLElements)/sizeof(gMethodURLElements[0]);

	for (int i = 0; i < counts; ++ i)
	{
		const tagMethodURLElement& tempElem = gMethodURLElements[i];
		if (tempElem.option == methodOption)
		{
			baseURL = getMethodBaseURL(tempElem.type);
			baseURL += tempElem.url;
			return ;
		}
	}

#if defined(INTERNAL_INTERFACE_USEABLE)

	for (int i = 0; i < counts; ++ i)
	{
		const tagMethodURLElement& tempElem = gInternalMethodURLElements[i];
		if (tempElem.option == methodOption)
		{
			baseURL = getMethodBaseURL(tempElem.type);
			baseURL += tempElem.url;
			return ;
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

void setParamFormat(std::string& param, const char* paramval, int paramformat)
{
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
#ifdef	_DEBUG
		if (!IsUTF8(paramval))
		{
			assert(0 && "the paramval is not utf-8 ???");
		}
#endif
		resultStr = (char*)paramval;
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
		param += resultStr;
		if (resultLength > 0)
		{
			free(resultStr);
		}
	}
}

void SDKHelper::setParam(std::string& param, const char *paramname, const char *paramval, int paramformat)
{
	if (!paramval || *paramval == '\0')
	{
		return;
	}
	setParamFormat(param, paramname, getParamnameFormat(paramformat));
	param += '=';
	setParamFormat(param, paramval, getParamvalueFormat(paramformat));
}

void SDKHelper::setIntParam(std::string& param, const char * paramName, const long long paramval, bool forceAdd)
{
	char val[64] = { 0 };
	if (!forceAdd && paramval <= 0)
	{
		return ;
	}
	sprintf(val, "%lld", paramval);
	setParam(param, paramName, (const char *)val, 0);
}

WeiboRequestPtr SDKHelper::makeRequest(unsigned int methodOption, std::string& addtionParam, const eWeiboRequestFormat reqformat
									   , const httpengine::HttpMethod method, const char* appkey, const char* accessToken, const UserTaskInfo* pTask)
{
	WeiboRequestPtr requestPtr;
	requestPtr.reset(new WeiboRequest());
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

	// additional param 
	if (addtionParam.length() > 0)
	{
		if (std::string::npos == baseURL.find_first_of('?'))
		{
			baseURL += '?';
			baseURL += addtionParam.length() > 1 ? addtionParam.substr(1) : addtionParam;
		}
		else
		{
			baseURL += addtionParam;
		}
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

void SDKHelper::split(std::vector<std::string>& outVector, const char* string, const char splite)
{
	std::string inString = Util::StringUtil::getNotNullString(string);
	if (inString.empty()) 
	{
		return ;
	}

	int counter = 0;
	int start = 0;
	std::string::iterator it = inString.begin();
	while (it != inString.end())
	{
		if ((*it) == splite)
		{
			outVector.push_back(inString.substr(start, counter - start));
			start = counter + 1;
		}
		++ it;
		++ counter;
		if (it == inString.end())
		{
			outVector.push_back(inString.substr(start));
		}
	}
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
			split(vec, url.c_str(), '?');

			if (!vec.empty())
			{
				// URL
				std::vector<std::string>::iterator it = vec.begin();
				outURL = *it;

				// Post params
				++ it;
				if (it != vec.end())
				{
					outParam = *it;
				}
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

void SDKHelper::makeVariableParams(std::string& outParam, const int length, VariableParams* var)
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

void SDKHelper::makeIDParams(std::string& outParam, const int length, const ID *usrId)
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
