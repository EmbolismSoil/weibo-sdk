#include "stdafx.h"
#include "WeiboTestCaseHelper.h"

#include <IWeiboDef.hxx>
#include <IWeiboMethod.hxx>

#include "ParsingDefine.hxx"
#include "ParsingDataStruct.h"

#define LOG_SUPPORT

using namespace weibo;

#ifdef LOG_SUPPORT
#	define DEFAULT_SUBSYSTEM "WeiboSDK_UnitTest"
#	include <util/log/Logger.hxx>
#else
#	define CerrLog(args_) std::cout
#	define StackLog(args_) std::cout
#	define DebugLog(args_) std::cout
#	define InfoLog(args_) std::cout
#	define WarningLog(args_) std::cout
#	define ErrLog(args_) std::cout
#	define CritLog(args_) std::cout
#endif


struct IDDebugHelper
{
	unsigned int optionId;
	char *optionIdName;
};

#define HELPER_UNIT(option) { option, #option }

const IDDebugHelper gDebugHelperArray[] = 
{
	HELPER_UNIT(WBOPT_OAUTH2_ACCESS_TOKEN),

	HELPER_UNIT(WBOPT_GET_STATUSES_PUBLIC_TIMELINE),//获取最新更新的公共微博消息 
	HELPER_UNIT(WBOPT_GET_STATUSES_FRIENDS_TIMELINE),//获取当前用户所关注用户的最新微博信息 (别名: statuses/home_timeline) 
	HELPER_UNIT(WBOPT_GET_STATUSES_HOME_TIMELINE),//获取当前登录用户及其所关注用户的最新微博消息
	HELPER_UNIT(WBOPT_GET_STATUSES_USER_TIMELINE),//获取用户发布的微博信息列表 
	HELPER_UNIT(WBOPT_GET_STATUSES_TIMELINE_BATCH),//批量获得指定的某一批用户的timeline
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_TIMELINE),//返回一条微博的最新n条转发微博信息
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_BYME),//返回用户转发的最新n条微博信息
	HELPER_UNIT(WBOPT_GET_STATUSES_MENTIONS),//获取@当前用户的微博列表 
	HELPER_UNIT(WBOPT_GET_STATUSES_SHOW),//根据ID获取单条微博信息
	HELPER_UNIT(WBOPT_GET_STATUSES_SHOW_BATCH),//批量获取微博信息
	HELPER_UNIT(WBOPT_GET_STATUSES_QUERYMID),//通过id获取mid
	HELPER_UNIT(WBOPT_GET_STATUSES_QUERYID),//通过mid获取id
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_DAILY),//按天返回热门转发榜
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_WEEKLY),//按周返回热门转发榜
	HELPER_UNIT(WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY),//按天返回热门评论榜
	HELPER_UNIT(WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY),//按周返回热门评论榜
	HELPER_UNIT(WBOPT_POST_STATUSES_REPOST),//转发一条微博信息
	HELPER_UNIT(WBOPT_POST_STATUSES_DESTROY),//删除微博评论信息
	HELPER_UNIT(WBOPT_POST_STATUSES_UPDATE),//发布一条微博信息
	HELPER_UNIT(WBOPT_POST_STATUSES_UPLOAD_URL_TEXT),//发布一条微博，同时指定上传的图片或图片url
	HELPER_UNIT(WBOPT_POST_STATUSES_UPLOAD),//发布一条微博，上传图片并发布一条微博信息

	HELPER_UNIT(WBOPT_GET_COMMENTS_SHOW),//获取某条微博的评论列表
	HELPER_UNIT(WBOPT_GET_COMMENTS_BYME),//我发出的评论列表
	HELPER_UNIT(WBOPT_GET_COMMENTS_TOME),//我收到的评论列表
	HELPER_UNIT(WBOPT_GET_COMMENTS_TIMELINE),//获取当前用户发送及收到的评论列表
	HELPER_UNIT(WBOPT_GET_COMMENTS_MENTIONS),//@到我的评论
	HELPER_UNIT(WBOPT_GET_COMMENTS_SHOWBATCH),//@批量获取评论内容

	HELPER_UNIT(WBOPT_POST_COMMENTS_CREATE),//评论一条微博
	HELPER_UNIT(WBOPT_POST_COMMENTS_DESTROY),//删除一条评论
	HELPER_UNIT(WBOPT_POST_COMMENTS_DESTROY_BATCH ),//批量删除评论
	HELPER_UNIT(WBOPT_POST_COMMENTS_REPLY),//回复一条评论

	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES),//获取当前用户最新私信列表
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_SENT),//获取当前用户发送的最新私信列表
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_USER_LIST),//获取私信往来用户列表
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_CONVERSATION),//获取与指定用户的往来私信列表
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH),//批量获取私信内容
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE),//判断是否可以给对方发私信
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_NEW),//发送一条私信
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_DESTORY),//删除一条私信
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH),//批量删除私信

	HELPER_UNIT(WBOPT_GET_USERS_SHOW),//获取用户资料
	HELPER_UNIT(WBOPT_GET_USERS_DOMAIN_SHOW),//通过个性域名获取用户信息
	HELPER_UNIT(WBOPT_GET_USERS_SHOW_BATCH),//批量获取用户信息

	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_BASIC), //获取用户基本信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION), //获取教育信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH), //批量获取教育信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_CAREER), //获取职业信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH), //批量获取职业信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_GET_PRIVACY), //获取隐私设置信息
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST), //获取所有学校列表
	HELPER_UNIT(WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS), //获取当前用户API访问频率限制
	HELPER_UNIT(WBOPT_GET_ACCOUNT_GET_UID), //OAuth授权之后获取用户UID（作用相当于旧版接口的account/verify_credentials）
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE), // 更新用户基本信息
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE), // 更新用户教育信息
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY), // 删除用户教育信息
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE), // 更新用户职业信息
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY), // 删除用户职业信息
	HELPER_UNIT(WBOPT_POST_ACCOUNT_AVATAR_UPLOAD), // 上传头像
	HELPER_UNIT(WBOPT_POST_ACCOUNT_UPDATE_PRIVACY), // 更新隐私设置

	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS),//获取用户的关注列表
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_IN_COMMON),//获取共同关注人列表接口
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_BILATERAL),//获取双向关注列表
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS),//获取双向关注ID列表
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS),//获取用户关注对象uid列表
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH),//批量获取备注
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS),//获取用户粉丝列表及每个粉丝的最新一条微博
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS),//获取用户粉丝对象uid列表
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE),//获取用户优质粉丝列表关系链
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS),//获取我的关注人中关注了指定用户的分组
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_SHOW),//获取两个用户关系的详细情况
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_CREATE),//关注某用户
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_CREATE_BATCH),//批量关注用户
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_DESTROY),//取消关注某用户	
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY),//移除粉丝
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE),//更新关注人备注

	HELPER_UNIT(WBOPT_GET_FAVORITES),//获取当前登录用户的收藏列表
	HELPER_UNIT(WBOPT_GET_FAVORITES_SHOW),//获取单条收藏信息
	HELPER_UNIT(WBOPT_GET_FAVORITES_BY_TAGS),//获取当前用户某个标签下的收藏列表
	HELPER_UNIT(WBOPT_GET_FAVORITES_TAGS),//当前登录用户的收藏标签列表
	HELPER_UNIT(WBOPT_POST_FAVORITES_CREATE),//添加收藏
	HELPER_UNIT(WBOPT_POST_FAVORITES_DESTROY),//删除收藏
	HELPER_UNIT(WBOPT_POST_FAVORITES_DESTROY_BATCH),//批量删除收藏
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_UPDATE),//更新收藏标签
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH),//更新当前用户所有收藏下的指定标签
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH),//删除当前用户所有收藏下的指定标签

	HELPER_UNIT(WBOPT_GET_TRENDS),//获取某人话题
	HELPER_UNIT(WBOPT_GET_TRENDS_STATUSES),//获取某一话题下的微博
	HELPER_UNIT(WBOPT_GET_TRENDS_HOURLY),//返回最近一小时内的热门话题
	HELPER_UNIT(WBOPT_GET_TRENDS_DAILY),//返回最近一天内的热门话题
	HELPER_UNIT(WBOPT_GET_TRENDS_WEEKLY),//返回最近一周内的热门话题
	HELPER_UNIT(WBOPT_POST_TRENDS_FOLLOW),//关注某话题
	HELPER_UNIT(WBOPT_POST_TRENDS_DESTROY),//取消关注的某一个话题

	HELPER_UNIT(WBOPT_GET_TAGS),//返回指定用户的标签列表
	HELPER_UNIT(WBOPT_GET_TAGS_TAGS_BATCH),//批量获取用户标签
	HELPER_UNIT(WBOPT_GET_TAGS_SUGGESTIONS),//返回系统推荐的标签列表
	HELPER_UNIT(WBOPT_POST_TAGS_CREATE),//添加用户标签
	HELPER_UNIT(WBOPT_POST_TAGS_DESTROY),//删除用户标签
	HELPER_UNIT(WBOPT_POST_TAGS_DESTROY_BATCH),//批量删除用户标签

	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_USERS),//搜用户搜索建议
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES),//搜微博搜索建议
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS),//搜学校搜索建议
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES), //搜公司搜索建议
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_APPS),//搜应用搜索建议
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS), //@联想搜索
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE),  //综合联想搜索
	HELPER_UNIT(WBOPT_GET_SEARCH_STATUSES),//微博搜索 
	HELPER_UNIT(WBOPT_GET_SEARCH_GEO_STATUSES), //搜索指定范围内的微博
	HELPER_UNIT(WBOPT_GET_SEARCH_USERS),//搜索用户

	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_FAVORITES_HOT),//热门收藏
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_HOT),//获取系统推荐用户
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED),//获取用户可能感兴趣的人
	HELPER_UNIT(WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED),//不感兴趣的人
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS),//根据微博内容推荐用户

	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHORTEN), //将一个或多个长链接转换成短链接
	HELPER_UNIT(WBOPT_GET_SHORT_URL_EXPAND), //将一个或多个短链接还原成原始的长链接
	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHARE_COUNTS), //取得一个短链接在微博上的微博分享数（包含原创和转发的微博）
	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHARE_STATUSES), //取得包含指定单个短链接的最新微博内容
	HELPER_UNIT(WBOPT_GET_SHORT_URL_COMMENT_COUNTS), //取得一个短链接在微博上的微博评论数
	HELPER_UNIT(WBOPT_GET_SHORT_URL_COMMENT_COMMENTS), //取得包含指定单个短链接的最新微博评论内容
};

const char* getOptionName(unsigned int optionId)
{
	const int size = sizeof(gDebugHelperArray)/sizeof(gDebugHelperArray[0]);
	if (optionId >= size)
	{
		assert(false);
		return "";
	}

	for (int i = 0; i < size; ++ i)
	{
		if (optionId == gDebugHelperArray[i].optionId)
		{
			return gDebugHelperArray[i].optionIdName;
		}
	}
	static char buf[10] = { 0 };
	memset(buf, sizeof(char), 10);
    snprintf(buf, 10, "%d", optionId);
	return buf;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 

WeiboTestCaseResult::WeiboTestCaseResult()
: resultType_(ERT_UNKNOW)
, errorCode_(0)
, subErrorCode_(0)
{
}

WeiboTestCaseResult::~WeiboTestCaseResult()
{
}

std::string WeiboTestCaseResult::outputString()
{
	std::string outString;

	return outString;
}

//////////////////////////////////////////////////////////////////////////////
// Case helper

WeiboTestCaseHelper::WeiboTestCaseHelper()
{
	mWeiboPtr = weibo::WeiboFactory::getWeibo();

	mWeiboPtr->startup();
	mWeiboPtr->setOption(weibo::WOPT_CONSUMER, "1016351065", "186ea22b3ea58bfa90923f55fe8b2749");
	mWeiboPtr->OnDelegateComplated += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespComplated);
	mWeiboPtr->OnDelegateErrored += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespErrored);
	mWeiboPtr->OnDelegateWillRelease += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespStoped);

	initializeParsingMap();

#if defined(LOG_SUPPORT) && defined(_WIN32)
	std::wstring logfile = getAppModulePathW();
	logfile += L"UNIT_LOG.log";
	Util::Log::initialize(Util::Log::File | Util::Log::VSDebugWindow, 
		Util::Log::Debug, "WeiboSDK_UnitTest", logfile.c_str());
#endif //LOG_SUPPORT
}

WeiboTestCaseHelper::~WeiboTestCaseHelper()
{
	mResultMap.clear();

	mWeiboPtr->OnDelegateComplated -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespComplated);
	mWeiboPtr->OnDelegateErrored -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespErrored);
	mWeiboPtr->OnDelegateWillRelease -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespStoped);
	mWeiboPtr->shutdown();
}

weibo::IWeiboMethod* WeiboTestCaseHelper::getWeiboMethod()
{
	if (mWeiboPtr)
	{
		return mWeiboPtr->getMethod();
	}
	return NULL;
}

WeiboTestCaseResultPtr WeiboTestCaseHelper::checkoutReqResult(unsigned int optionId)
{
	WeiboTestCaseResultPtr result;
	UnitTestResultMAP::iterator it = mResultMap.find(optionId);
	if (it != mResultMap.end())
	{
		result = it->second;
	}
	return result;
}

const char* WeiboTestCaseHelper::getMYID()
{
	return mMYID.c_str();
}

void WeiboTestCaseHelper::onWeiboRespComplated(unsigned int optionId, const char* httpHeader, ParsingObject* result, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId));

	onResponseProcess(optionId, result, 0, 0, true);
}

void WeiboTestCaseHelper::onWeiboRespErrored(unsigned int optionId, const int errCode, const int errSubCode, ParsingObject* result, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId) << " | error code: "  << errCode << " | sub error Code: " << errSubCode);

	onResponseProcess(optionId, result, errCode, errSubCode, false);
}

void WeiboTestCaseHelper::onWeiboRespStoped(unsigned int optionId, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId));

	// Do noting!
}

using namespace weibo;

#define INSERT_PARSING_OBJECT(id, object)\
	mParsingMap.insert(std::make_pair(id, object))

#define INSERT_PARSING_OBJECT_BATCH(idbegin, idend, object)\
	for (int i = idbegin; i <= idend; ++ i){ mParsingMap.insert(std::make_pair(i, object)); }

void WeiboTestCaseHelper::initializeParsingMap()
{
	// Parsing for statuses
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_PUBLIC_TIMELINE,
		WBOPT_GET_STATUSES_TIMELINE_BATCH, boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_REPOST_TIMELINE,
		WBOPT_GET_STATUSES_REPOST_BYME, boost::make_shared<ParsingStatusesList>("reposts"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_MENTIONS,
		boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_SHOW,
		boost::make_shared<ParsingStatus>());

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_SHOW_BATCH, 
		boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_QUERYMID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "mid")));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_QUERYID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "id")));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_REPOST_DAILY,
		WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY, boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_STATUSES_REPOST,
		WBOPT_POST_STATUSES_UPLOAD, boost::make_shared<ParsingStatus>());

	// Parsing for comment
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_COMMENTS_SHOW,
		WBOPT_GET_COMMENTS_SHOWBATCH, boost::make_shared<ParsingCommentsList>("comments"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_COMMENTS_CREATE,
		WBOPT_POST_COMMENTS_REPLY, boost::make_shared<ParsingComment>());

	// Parsing for direct messages
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_DIRECTMESSAGES,
		WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH, boost::make_shared<ParsingDirectMessagesList>("direct_messages"));

	INSERT_PARSING_OBJECT (WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "result")));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_DIRECTMESSAGES_NEW,
		WBOPT_POST_DIRECTMESSAGES_DESTORY, boost::make_shared<ParsingDirectMessage>());

	INSERT_PARSING_OBJECT (WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH,
		boost::make_shared<ParsingDirectMessagesList>("direct_messages"));

	// Parsing for friendships
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_FRIENDSHIPS_FRIENDS, 
		WBOPT_GET_FRIENDSHIPS_BILATERAL, boost::make_shared<ParsingUsersList>("users"));

	INSERT_PARSING_OBJECT (WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS, 
		boost::make_shared<ParsingUsersList>("users"));

	// Parsing for Accounts
	INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_BASIC,
		boost::make_shared<ParsingAccount>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION,
	//	boost::make_shared<ParsingEducation>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH,
	//	boost::make_shared<ParsingEducationsList>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH,
	//	boost::make_shared<ParsingEducationsList>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_GET_UID,
	//	boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "uid")));

	// Parsing for favorites
	INSERT_PARSING_OBJECT (WBOPT_GET_FAVORITES, 
		boost::make_shared<ParsingFavoritesList>("favorites"));

	INSERT_PARSING_OBJECT (WBOPT_GET_FAVORITES_TAGS, 
		boost::make_shared<ParsingFavoriteTagsList>("tags"));

	INSERT_PARSING_OBJECT (WBOPT_GET_TAGS, 
		boost::make_shared<ParsingTagsList>());

	INSERT_PARSING_OBJECT (WBOPT_GET_TRENDS,
		boost::make_shared<ParsingTrendsList>());


	// parsing for id
	INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_GET_UID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "uid")));
}

void WeiboTestCaseHelper::onResponseProcess(unsigned int optionId, ParsingObject* resultObj, const int errCode, const int errSubCode, bool isComplated)
{
	UnitTestResultMAP::iterator it = mResultMap.find(optionId);
	if (it != mResultMap.end())
	{
		mResultMap.erase(it);
	}

	WeiboTestCaseResultPtr result = boost::make_shared<WeiboTestCaseResult>();
	//result->respBody_ = sc;
	result->errorCode_ = errCode;
	result->subErrorCode_ = errSubCode;
	result->resultType_ = isComplated ? WeiboTestCaseResult::ERT_CORRECT : WeiboTestCaseResult::ERT_ERROR;
	mResultMap.insert(std::make_pair(optionId, result));

	if (isComplated)
	{
		UnitTestParsingMAP::iterator it = mParsingMap.find(optionId);
		if (it != mParsingMap.end())
		{
			result->pasringPtr_ = it->second;
		}
		else
		{
			WarningLog(<< __FUNCTION__ << "| Warning: cannot find parsing object! Option id:" << optionId);
		}
	}
	else
	{
		result->pasringPtr_ = boost::make_shared<ParsingApiError>(false);		
	}

	if (resultObj)
	{
		ParsingObject* tempObject = new ParsingObject(*resultObj);
		ParsingObjectPtr objPtr(tempObject);

		if (result->pasringPtr_ )
		{
			result->pasringPtr_->doParse(objPtr);
		}

		// The special event.
		switch(optionId)
		{
		case WBOPT_OAUTH2_ACCESS_TOKEN:
			{
				ParsingOauthRet ret;
				ret.doParse(objPtr);
				mWeiboPtr->setOption(WOPT_ACCESS_TOKEN, ret.access_token.c_str());
				mMYID = ret.uid;
			}
			break;

		//case WBOPT_GET_ACCOUNT_GET_UID:
		//	{
		//		ParsingResultPtr pret = boost::dynamic_pointer_cast<ParsingResult>(result->pasringPtr_);
		//		if (pret)
		//		{
		//			mMYID = pret->asAString("uid");
		//		}
		//	}
		//	break;

		default:
			break;
		}
	}
}

std::string filePath;
std::wstring filePathW;

#if defined(_WIN32)

const char* WeiboTestCaseHelper::getAppModulePath()
{
	if (filePath.empty())
	{
		char buf[MAX_PATH]={ 0 };
		GetModuleFileNameA(NULL, buf, sizeof(char) * MAX_PATH);
		char* tmp = strrchr(buf, '\\');
		*tmp = '\0';
		filePath = buf;
		filePath += "\\";
	}
	return filePath.c_str();
}

const wchar_t* WeiboTestCaseHelper::getAppModulePathW()
{
	if (filePathW.empty())
	{
		wchar_t buf[MAX_PATH]={ 0 };
		GetModuleFileNameW(NULL, buf, sizeof(wchar_t) * MAX_PATH);
		wchar_t* tmp = wcsrchr (buf, '\\');
		*tmp = '\0';
		filePathW = buf;
		filePathW += L"\\";
	}
	return filePathW.c_str();
}

#else

const char* WeiboTestCaseHelper::getAppModulePath()
{
    /*
	if (filePath.empty())
	{
		char buf[MAX_PATH]={ 0 };
		GetModuleFileNameA(NULL, buf, sizeof(char) * MAX_PATH);
		char* tmp = strrchr(buf, '\\');
		*tmp = '\0';
		filePath = buf;
		filePath += "\\";
	}
     */
	return filePath.c_str();
}

const wchar_t* WeiboTestCaseHelper::getAppModulePathW()
{
    /*
	if (filePathW.empty())
	{
		wchar_t buf[MAX_PATH]={ 0 };
		GetModuleFileNameW(NULL, buf, sizeof(wchar_t) * MAX_PATH);
		wchar_t* tmp = wcsrchr (buf, '\\');
		*tmp = '\0';
		filePathW = buf;
		filePathW += L"\\";
	}
     */
	return filePathW.c_str();
}

#endif //_WIN32
