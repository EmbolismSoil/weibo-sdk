// WeiboUnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>

#include "WeiboTestCase.h"

#if defined(_WIN32)
#   define TEST_MAIN _tmain(int argc, __TCHAR* argv[])
#else
#   define TEST_MAIN main(int argc, char* argv[])
#endif

int TEST_MAIN
{
    char userName[255] = { 0 };
    char password[255] = { 0 };
    
    printf("Please enter user name: ");
    gets(userName);
    
    printf("Please enter password: ");
    gets(password);

    // Account info
    setAccountInfo(userName, password);
    
	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );

	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	// Print test in a compiler compatible format.
	//CPPUNIT_NS::CompilerOutputter outputter(&controller, CPPUNIT_NS::stdCOut() );
	//outputter.write(); 

	std::ofstream outputFile("WeiboUnitTestResults.xml");
	CppUnit::XmlOutputter outputter(&result, outputFile);
	outputter.write();
	outputFile.close();

	int ret = result.wasSuccessful() ? 0 : 1;

	system("pause");

	return ret;
}