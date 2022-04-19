#include "pch.h"
#include "../MapReduce/FileManagement.h"
#include <boost/log/trivial.hpp>

//Demo Tests
TEST(TemplateTest, TestDemo) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

// unresolved external symbol error?
// FileManagement Tests
//TEST(FileManagementTests, TestSetDirectory) {
//	FileManagement m;
//  ASSERT_EXIT(m.setInputDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
//	ASSERT_EXIT(m.setInputDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
//  ASSERT_EXIT(m.setOutputDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
//	ASSERT_EXIT(m.setOutputDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
//  ASSERT_EXIT(m.seTempDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
//	ASSERT_EXIT(m.seTempDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
//	
//}
