#include "stdafx.h"
#include <time.h>
#include <boost/make_shared.hpp>
#include "WeiboTestCase.h"
#include "WeiboTestCaseHelper.h"
#include <IWeiboMethod.hxx>

#include "ParsingDefine.hxx"
#include "ParsingDataStruct.h"
#include "UNITTestIDBuilderPolicy.h"

using namespace weibo;

static const char gWeiboTestUploadFile[] = "TestImage.jpg";
static const char gWeiboTestUploadURL[] = "http://ww3.sinaimg.cn/bmiddle/4ce0e2b5jw1dmrwb32yyvj.jpg";

static boost::shared_ptr<WeiboTestCaseHelper> gWeiboHelper;

CPPUNIT_TEST_SUITE_REGISTRATION( WeiboTestCase );

WeiboTestCase::WeiboTestCase()
{
	if (!gWeiboHelper)
	{
		gWeiboHelper = boost::make_shared<WeiboTestCaseHelper>();
	}
}

WeiboTestCase::~WeiboTestCase()
{
}

void WeiboTestCase::standardOptionForWaiting(unsigned int id)
{
	while(1)
	{
#if defined(_WIN32)
		Sleep(1000);
#else
        usleep(1000 * 1000);
#endif // _WIN32
        
		WeiboTestCaseResultPtr result = gWeiboHelper->checkoutReqResult(id);

		if (result)
		{
			if (result->resultType_ == WeiboTestCaseResult::ERT_CORRECT)
			{
				CPPUNIT_ASSERT(true);

				char buf[255];
				sprintf(buf, "%d successed!!!!, ", id);
				std::string errMessage = buf;
				errMessage += result->outputString();
				CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE(errMessage,0);
			}
			else if (result->resultType_ == WeiboTestCaseResult::ERT_ERROR)
			{
				char buf[255];
				sprintf(buf, "%d failed, ", id);
				std::string errMessage = buf;
				errMessage += result->outputString();
				CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE(errMessage, 0);
				//CPPUNIT_ASSERT_ASSERTION_FAIL(0);
				CPPUNIT_ASSERT(false);
			}
			else
			{
				continue;
			}
			break;
		}
	}
}

std::string gAccountName;
std::string gPassword;

extern void setAccountInfo(const char* account, const char* password)
{
    gAccountName = account ? account : "";
    gPassword = password ? password : "";
}

void WeiboTestCase::oauth2()
{
    if (gAccountName.empty() || gPassword.empty())
    {
        CPPUNIT_ASSERT_ASSERTION_FAIL(0);
    }
    
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->oauth2(gAccountName.c_str(), gPassword.c_str(), NULL) == WRC_OK);
	standardOptionForWaiting(WBOPT_OAUTH2_ACCESS_TOKEN);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Œ¢≤©∂¡»°

void WeiboTestCase::getStatusesPublicTimeline()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesPublicTimeline() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_PUBLIC_TIMELINE);
}

void WeiboTestCase::getStatusesFriendTimeline()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesFriendTimeline() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_FRIENDS_TIMELINE);
}

void WeiboTestCase::getStatusesHomeTimeline()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesHomeTimeline() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_HOME_TIMELINE);
}

void WeiboTestCase::getStatusesUserTimeline()
{
    weibo::ID id(weibo::ID::IDT_ID, gWeiboHelper->getMYID());
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesUserTimeline(id) == WRC_OK);

	standardOptionForWaiting(WBOPT_GET_STATUSES_USER_TIMELINE);
}

void WeiboTestCase::getStatusesTimelineBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 10);

	ID id = policy.asID();
	id.keyName = "uids";
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesTimelineBatch(id) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_TIMELINE_BATCH);
}

void WeiboTestCase::getStatusesRepostTimeline()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesRepostTimeline(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_REPOST_TIMELINE);
}

void WeiboTestCase::getStatusesRepostByMe()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesRepostByMe() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_REPOST_BYME);
}

void WeiboTestCase::getStatusesMentions()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesMentions() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_PUBLIC_TIMELINE);
}

void WeiboTestCase::getStatusesShow()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesShow(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_SHOW);
}

void WeiboTestCase::getStatusesShowBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS, 0, 25);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesShowBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_SHOW_BATCH);
}

void WeiboTestCase::getStatusesQueryMID()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesQueryMID(policy.asChar(), 1) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_QUERYMID);
}

void WeiboTestCase::getStatusesQueryID()
{
	// TODO(welbon): get mid.

	//CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesQueryID(gMID.c_str(), 1) == WRC_OK);
	//standardOptionForWaiting(WBOPT_GET_STATUSES_QUERYID);
}

void WeiboTestCase::getStatusesRepostDaily()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesRepostDaily() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_REPOST_DAILY);
}

void WeiboTestCase::getStatusesRepostWeekly()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesRepostWeekly() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_REPOST_WEEKLY);
}

void WeiboTestCase::getStatusesHotCommmentsDaily()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesHotCommmentsDaily() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY);
}

void WeiboTestCase::getStatusesHotCommmentsWeekly()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getStatusesHotCommmentsWeekly() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY);
}

// Œ¢≤©–¥»Î
void WeiboTestCase::postStatusesRepost()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postStatusesRepost(policy.asChar(), policy.asWords(), 3) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_STATUSES_REPOST);
}

void WeiboTestCase::postStatusesDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS, WBOPT_GET_STATUSES_REPOST_BYME);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postStatusesDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_STATUSES_DESTROY);
}

void WeiboTestCase::postStatusesUpdate()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postStatusesUpdate(policy.asWords()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_STATUSES_UPDATE);
}

void WeiboTestCase::postStatusesUploadUrlText()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postStatusesUploadUrlText(policy.asWords(), gWeiboTestUploadURL, 1) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_STATUSES_UPLOAD_URL_TEXT);
}

void WeiboTestCase::postStatusesUpload()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);

	std::string appFile = WeiboTestCaseHelper::getAppModulePath();
	appFile += gWeiboTestUploadFile;

	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postStatusesUpload(policy.asWords(), appFile.c_str()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_STATUSES_UPLOAD);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ∆¿¬€∂¡»°
void WeiboTestCase::getCommentsShow()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsShow(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_SHOW);
}

void WeiboTestCase::getCommentsByMe()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsByMe() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_BYME);
}

void WeiboTestCase::getCommentsToMe()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsToMe() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_TOME);
}

void WeiboTestCase::getCommentsTimeline()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsTimeline() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_TIMELINE);
}

void WeiboTestCase::getCommentsMentions()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsMentions() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_MENTIONS);
}

void WeiboTestCase::getCommentsShowBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_COMMENT, WBOPT_GET_COMMENTS_BYME, 50);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getCommentsShowBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_COMMENTS_SHOWBATCH);
}

// ∆¿¬€–¥»Î
void WeiboTestCase::postCommentsCreate()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postCommentsCreate(policy.asChar(), policy.asWords(), 1) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_COMMENTS_CREATE);
}

void WeiboTestCase::postCommentsDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_COMMENT);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postCommentsDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_COMMENTS_DESTROY);
}

void WeiboTestCase::postCommentsDestroyBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_COMMENT, WBOPT_GET_COMMENTS_BYME, 2);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postCommentsDestroyBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_COMMENTS_DESTROY_BATCH);
}

void WeiboTestCase::postCommentsReply()
{
	std::string commentId, statusId;
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_COMMENT);
	policy.getCommentIDAndStatuseID(commentId, statusId);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postCommentsReply(
		commentId.c_str(), policy.asWords(), statusId.c_str(), 0, 0) == WRC_OK);

	standardOptionForWaiting(WBOPT_POST_COMMENTS_REPLY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ÀΩ–≈∂¡»°
void WeiboTestCase::getDirectMessages()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessages() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES);
}

void WeiboTestCase::getDirectMessagesSent()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessagesSent() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES_SENT);
}

void WeiboTestCase::getDirectMessagesUserList()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessagesUserList() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES_USER_LIST);
}

void WeiboTestCase::getDirectMessagesCoversation()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessagesCoversation(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES_CONVERSATION);
}

void WeiboTestCase::getDirectMessagesShowBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_DIRECT_MESSAGE, WBOPT_GET_DIRECTMESSAGES, 50);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessagesShowBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH);
}

void WeiboTestCase::getDirectMessagesIsCapable()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getDirectMessagesIsCapable(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE);
}

// ÀΩ–≈–¥»Î
void WeiboTestCase::postDirectMessagesNew()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postDirectMessagesNew("TEST1234567890@!&#*$)^&*()_+/.,<`~>", policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_DIRECTMESSAGES_NEW);
}

void WeiboTestCase::postDirectMessagesDestory()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_DIRECT_MESSAGE, WBOPT_GET_DIRECTMESSAGES_SENT);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postDirectMessagesDestory(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_DIRECTMESSAGES_DESTORY);
}

void WeiboTestCase::postDirectMessagesDestoryBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_DIRECT_MESSAGE, WBOPT_GET_DIRECTMESSAGES_SENT);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postDirectMessagesDestoryBatch(policy.asChar(), NULL) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ”√ªß∂¡»°
void WeiboTestCase::getUsersShow()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getUsersShow(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_USERS_SHOW);	
}

void WeiboTestCase::getUsersDomainShow()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getUsersDomainShow("welbon") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_USERS_DOMAIN_SHOW);	
}

void WeiboTestCase::getUsersShowBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 20);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getUsersShowBatch(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_USERS_SHOW_BATCH);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// πÿ◊¢∂¡»°
void WeiboTestCase::getFriendshipsFriends()
{
    weibo::ID id(weibo::ID::IDT_ID, gWeiboHelper->getMYID());
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriends(id, 0) == WRC_OK);

	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS);
}

void WeiboTestCase::getFriendshipsInCommon()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsInCommon(policy.asChar(), NULL) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_IN_COMMON);
}

void WeiboTestCase::getFriendshipsBilateral()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsBilateral(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_BILATERAL);
}

void WeiboTestCase::getFriendshipsBilateralIDs()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsBilateralIDs(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS);
}

void WeiboTestCase::getFriendshipsFriendIDs()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendIDs(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS);
}

void WeiboTestCase::getFriendshipsFriendRemarkBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 10);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendRemarkBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH);
}

// ∑€Àø∂¡»°
void WeiboTestCase::getFriendshipsFriendsFollowers()
{	
    weibo::ID id(weibo::ID::IDT_ID, gWeiboHelper->getMYID());
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendsFollowers(id) == WRC_OK);

	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS);
}

void WeiboTestCase::getFriendshipsFriendsFollowersIDs()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendsFollowersIDs(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS);
}

void WeiboTestCase::getFriendshipsFriendsFollowersActive()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendsFollowersActive(policy.asID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE);
}

// πÿœµ¡¥∂¡»°
void WeiboTestCase::getFriendshipsFriendsChainFollowers()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipsFriendsChainFollowers(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS);
}

// πÿœµ◊¥Ã¨
void WeiboTestCase::getFriendshipShow()
{
	using namespace weibo;
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
    ID id(ID::IDT_ID, gWeiboHelper->getMYID());
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFriendshipShow(policy.asID(), id) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FRIENDSHIPS_SHOW);
}

// πÿœµ–¥»Î
void WeiboTestCase::postFriendshipsCreate()
{
	//UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS);
    ID id(ID::IDT_ID,"1645121582");
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFriendshipsCreate(id, 0) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FRIENDSHIPS_CREATE);
}

void WeiboTestCase::postFriendshipsCreateBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS, 10);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFriendshipsCreateBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FRIENDSHIPS_CREATE_BATCH);
}

void WeiboTestCase::postFriendshipsDestroy()
{
	//UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
    ID id(ID::IDT_ID,"1645121582");
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFriendshipsDestroy(id/*policy.asID()*/) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FRIENDSHIPS_DESTROY);
}

void WeiboTestCase::postFriendshipsFollowersDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFriendshipsFollowersDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY);
}

void WeiboTestCase::postFriendshipsRemarkUpdate()
{
	//UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFriendshipsRemarkUpdate("1645121582"/*policy.asChar()*/, "CPPUNIT_Testremark") == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ’ ∫≈∂¡»°
void WeiboTestCase::getAccountProfileBasic()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileBasic(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_BASIC);
}

void WeiboTestCase::getAccountProfileEducation()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileEducation(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION);
}

void WeiboTestCase::getAccountProfileEducationBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 20);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileEducationBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH);
}

void WeiboTestCase::getAccountProfileCareer()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileCareer(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_CAREER);
}

void WeiboTestCase::getAccountProfileCareerBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 20);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileCareerBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH);
}

void WeiboTestCase::getAccountGetPrivacy()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountGetPrivacy() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_GET_PRIVACY);
}

void WeiboTestCase::getAccountProfileSchoolList()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountProfileSchoolList() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST);
}

void WeiboTestCase::getAccountRateLimitStatus()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountRateLimitStatus() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS);
}

void WeiboTestCase::getAccountGetUID()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getAccountGetUID() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_ACCOUNT_GET_UID);
}

// ’ ∫≈–¥»Î
void WeiboTestCase::postAccountProfileBasicUpdate()
{
	weibo::BasicInfo basic;

	// TODO(welbon): to fill basic info
	//CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountProfileBasicUpdate(basic) == WRC_OK);
	//standardOptionForWaiting(WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE);
}

void WeiboTestCase::postAccountProfileEduUpdate()
{
	weibo::EducationInfo edu;
	// TODO(welbon): to fill education info
	//CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountProfileEduUpdate(edu) == WRC_OK);
	//standardOptionForWaiting(WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE);
}

void WeiboTestCase::postAccountProfileEduDestroy()
{
	weibo::EducationInfo edu;
	// TODO(welbon): to fill education info
	// CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountProfileEduDestroy(/*makeRandomID(1, false, RIT_EDUCATION).c_str()*/) == WRC_OK);
	// standardOptionForWaiting(WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY);
}

void WeiboTestCase::postAccountProfileCarUpdate()
{
	weibo::CareerInfo car;
	// TODO(welbon): to fill career info
	//CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountProfileCarUpdate(car) == WRC_OK);
	//standardOptionForWaiting(WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE);
}

void WeiboTestCase::postAccountProfileCarDestroy()
{
	weibo::CareerInfo car;

	// TODO(welbon): to fill career info
	//CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountProfileCarDestroy(makeRandomID(1, false, RIT_CAREER).c_str()) == WRC_OK);
	//standardOptionForWaiting(WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY);
}

void WeiboTestCase::postAccountAvatarUpload()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountAvatarUpload(gWeiboTestUploadFile) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_ACCOUNT_AVATAR_UPLOAD);
}

void WeiboTestCase::postAccountUpdatePrivacy()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postAccountUpdatePrivacy() == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_ACCOUNT_UPDATE_PRIVACY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ’≤ÿ∂¡»°
void WeiboTestCase::getFavorites()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFavorites() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FAVORITES);
}

void WeiboTestCase::getFavoritesShow()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFavoritesShow(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FAVORITES_SHOW);
}

void WeiboTestCase::getFavoritesByTags()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE_TAG);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFavoritesByTags(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FAVORITES_BY_TAGS);
}

void WeiboTestCase::getFavoritesTags()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getFavoritesTags() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FAVORITES_TAGS);
}

//  ’≤ÿ–¥»Î
void WeiboTestCase::postFavoritesCreate()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesCreate(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_CREATE);
}

void WeiboTestCase::postFavoritesDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_STATUS);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_DESTROY);
}

void WeiboTestCase::postFavoritesDestroyBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE, 0, 2);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesDestroyBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_DESTROY_BATCH);
}

void WeiboTestCase::postFavoritesTagUpdate()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesTagUpdate(policy.asChar(), "abdefg") == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_TAGS_UPDATE);
}

void WeiboTestCase::postFavoritesTagsUpdateBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE, 2);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesTagsUpdateBatch(policy.asChar(), "abcdefgcdefg") == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH);
}

void WeiboTestCase::postFavoritesTagsDestroyBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_FAVORITE_TAG);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postFavoritesTagsDestroyBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ª∞Ã‚∂¡»°
void WeiboTestCase::getTrends()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTrends(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TRENDS);
}

void WeiboTestCase::getTrendsStatuses()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTrendsStatuses("NBA", NULL) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TRENDS_STATUSES);
}

void WeiboTestCase::getTrendsHourly()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTrendsHourly() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TRENDS_HOURLY);
}

void WeiboTestCase::getTrendsDaily()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTrendsDaily() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TRENDS_DAILY);
}

void WeiboTestCase::getTrendsWeekly()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTrendsWeekly() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TRENDS_WEEKLY);
}


// ª∞Ã‚–¥»Î
void WeiboTestCase::postTrendsFollow()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_TREND);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postTrendsFollow(policy.getDateString().c_str()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_TRENDS_FOLLOW);
}

void WeiboTestCase::postTrendsDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_TREND);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postTrendsDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_TRENDS_DESTROY);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ±Í«©∂¡»°
void WeiboTestCase::getTags()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTags(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TAGS);
}

void WeiboTestCase::getTagsTagsBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, 0, 20);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTagsTagsBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TAGS_TAGS_BATCH);
}

void WeiboTestCase::getTagsSuggestions()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getTagsSuggestions() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_TAGS_SUGGESTIONS);
}

// ±Í«©–¥»Î
void WeiboTestCase::postTagsCreate()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_TAG);
	std::string created_tag = policy.getDateString();
	created_tag = created_tag.substr(created_tag.length() - 7, created_tag.length() - 1);

	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postTagsCreate(created_tag.c_str()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_TAGS_CREATE);
}

void WeiboTestCase::postTagsDestroy()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_TAG);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postTagsDestroy(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_TAGS_DESTROY);
}

void WeiboTestCase::postTagsDestroyBatch()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_TAG);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postTagsDestroyBatch(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_TAGS_DESTROY_BATCH);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// À—À˜
void WeiboTestCase::getSearchSuggestionsUsers()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsUsers("aa") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_USERS);
}

void WeiboTestCase::getSearchSuggestionsStatues()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsStatues("aa") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES);
}

void WeiboTestCase::getSearchSuggestionsSchool()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsSchool("«Âª™") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS);
}

void WeiboTestCase::getSearchSuggestionsCompanies()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsCompanies("sina") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES);
}

void WeiboTestCase::getSearchSuggestionsApps()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsApps("Œ¢≤©◊¿√Ê") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_APPS);
}

void WeiboTestCase::getSearchSuggestionsAtUsers()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsAtUsers("w", 0) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS);
}

void WeiboTestCase::getSearchSuggestionsIntegrate()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchSuggestionsIntegrate("w") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE);
}

void WeiboTestCase::getSearchStatuses()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchStatuses("w") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_STATUSES);
}

void WeiboTestCase::getSearchGeoStatuses()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchGeoStatuses(-12.34F, 12.34F) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_GEO_STATUSES);
}

void WeiboTestCase::getSearchUsers()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSearchUsers("welbon") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SEARCH_USERS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Õ∆ºˆ∂¡»°
void WeiboTestCase::getSuggestionsFavoritesHot()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSuggestionsFavoritesHot() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SUGGESTIONS_FAVORITES_HOT);
}

void WeiboTestCase::getSuggestionsUsersHot()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSuggestionsUsersHot("default") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SUGGESTIONS_USERS_HOT);
}

void WeiboTestCase::getSuggestionsUsersMayInterested()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSuggestionsUsersMayInterested() == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED);
}

void WeiboTestCase::getSuggestionsUsersByStatus()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getSuggestionsUsersByStatus("ÃÏ∆¯≤ª¥Ì") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Õ∆ºˆ–¥»Î
void WeiboTestCase::postSuggestionsUsersNotInterested()
{
	UNITTestIDBuilderPolicy policy(gWeiboHelper, RIT_USERS, WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED);
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->postSuggestionsUsersNotInterested(policy.asChar()) == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ∂Ã¡¥Ω”ø⁄
void WeiboTestCase::getShortURLShorten()
{
	std::string urls;
	urls += "http://open.weibo.com/wiki/Short_url/shorten";

	urls += ",";
	urls += "http://open.weibo.com/wiki/Short_url/share/counts";

	urls += ",";
	urls += "http://open.weibo.com/wiki/Short_url/share/statuses";

	urls += ",";
	urls += "http://open.weibo.com/wiki/Short_url/comment/counts";

	urls += ",";
	urls += "http://open.weibo.com/wiki/Short_url/comment/comments";

	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLShorten(urls.c_str()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_SHORTEN);
}

void WeiboTestCase::getShortURLExpand()
{
	std::string urls;
	urls += "http://t.cn/amesur";

	urls += ",";
	urls += "http://t.cn/Sz5lzj";

	urls += ",";
	urls += "http://t.cn/arK5HR";

	urls += ",";
	urls += "http://t.cn/Sz5lzY";

	urls += ",";
	urls += "http://t.cn/Sz5lzl";

	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLExpand(urls.c_str()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_EXPAND);
}

void WeiboTestCase::getShortURLShareCounts()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLShareCounts("http://t.cn/Sz5lzl") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_SHARE_COUNTS);
}

void WeiboTestCase::getShortURLShareStatuses()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLShareStatuses("http://t.cn/Sz5lzl") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_SHARE_STATUSES);
}

void WeiboTestCase::getShortURLCommentCounts()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLCommentCounts("http://t.cn/Sz5lzl") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_COMMENT_COUNTS);
}

void WeiboTestCase::getShortURLCommentComments()
{
	CPPUNIT_ASSERT(gWeiboHelper->getWeiboMethod()->getShortURLCommentComments("http://t.cn/Sz5lzl") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SHORT_URL_COMMENT_COUNTS);
}

#if defined(UNITTEST_INTERNAL_INTERFACE)

#include <IWeiboInternalMethod.hxx>

IWeiboInternalMethod* WeiboTestCase::getWeiboInternalMethod()
{
	return dynamic_cast<IWeiboInternalMethod*>(gWeiboHelper->getWeiboMethod());
}

// Suggestion hot
void WeiboTestCase::getSuggestionsStatusesHot()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->getSuggestionsStatusesHot(1, 0) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_SUGGESTIONS_STATUSES_HOT);
}

// Unread
void WeiboTestCase::getRemindUnreadCount()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->getRemindUnreadCount(gWeiboHelper->getMYID()) == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_REMIND_UNREAD_COUNT);
}

//void WeiboTestCase::getRemindUnreadCountSP()
//{
//	CPPUNIT_ASSERT(getWeiboInternalMethod()->getRemindUnreadCountSP(gWeiboHelper->getMYID()) == WRC_OK);
//	standardOptionForWaiting(WBOPT_GET_REMIND_UNREAD_COUNT_SP);
//}
//
//void WeiboTestCase::postRemindAddCount()
//{
//	CPPUNIT_ASSERT(getWeiboInternalMethod()->postRemindAddCount(gWeiboHelper->getMYID(), "status", 10) == WRC_OK);
//	standardOptionForWaiting(WBOPT_POST_REMIND_ADD_COUNT);
//}
//
//void WeiboTestCase::postRemindSetCount()
//{
//	CPPUNIT_ASSERT(getWeiboInternalMethod()->postRemindSetCount(gWeiboHelper->getMYID(), "status", 10) == WRC_OK);
//	standardOptionForWaiting(WBOPT_POST_REMIND_SET_COUNT);
//}
//
//void WeiboTestCase::postRemindClearCount()
//{
//	CPPUNIT_ASSERT(getWeiboInternalMethod()->postRemindClearCount(gWeiboHelper->getMYID()) == WRC_OK);
//	standardOptionForWaiting(WBOPT_POST_REMIND_CLEAR_COUNT);
//}

//File
void WeiboTestCase::getFileAttachmentInfo()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->getFileAttachmentInfo("11111") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FILE_ATTACHMENT_INFO);
}

void WeiboTestCase::getFileAttachmentUploadSign()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->getFileAttachmentUploadSign("11111") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FILE_ATTACHMENT_UPLOAD_SIGN);
}

void WeiboTestCase::getFileAttachmentUploadBack()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->getFileAttachmentUploadBack("11111", "11123") == WRC_OK);
	standardOptionForWaiting(WBOPT_GET_FILE_ATTACHMENT_UPLOAD_BACK);
}

void WeiboTestCase::postFileAttachmentDestroy()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->postFileAttachmentDestroy("11111") == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FILE_ATTACHMENT_DESTROY);
}

void WeiboTestCase::postFileAttachmentRepost()
{
	CPPUNIT_ASSERT(getWeiboInternalMethod()->postFileAttachmentRepost("11111", "11111") == WRC_OK);
	standardOptionForWaiting(WBOPT_POST_FILE_ATTACHMENT_REPOST);
}

#endif //