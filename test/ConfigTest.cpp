#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Config.hpp"
#include <stdexcept>

namespace csl {
namespace csv {

class ConfigTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(ConfigTest);
  CPPUNIT_TEST(testConfig);
  CPPUNIT_TEST(testConfigChar);
  CPPUNIT_TEST(testConfigCharThrowInvalidArgument);
  CPPUNIT_TEST(testConfigCharCharBool);
  CPPUNIT_TEST(testConfigCharCharBoolThrowInvalidArgument);
  CPPUNIT_TEST(testConfigCharCharBoolChar);
  CPPUNIT_TEST(testConfigCharCharBoolCharThrowInvalidArgument);
  CPPUNIT_TEST(testGetDelimitMark);
  CPPUNIT_TEST(testSetDelimitMark);
  CPPUNIT_TEST(testSetDelimitMarkThrowInvalidArgument);
  CPPUNIT_TEST(testGetQuoteEnabled);
  CPPUNIT_TEST(testSetQuoteEnabled);
  CPPUNIT_TEST(testGetQuoteMark);
  CPPUNIT_TEST(testSetQuoteMark);
  CPPUNIT_TEST(testSetQuoteMarkThrowInvalidArgument);
  CPPUNIT_TEST(testGetCommentEnabled);
  CPPUNIT_TEST(testSetCommentEnabled);
  CPPUNIT_TEST(testGetCommentMark);
  CPPUNIT_TEST(testSetCommentMark);
  CPPUNIT_TEST(testSetCommentMarkThrowInvalidArgument);
  CPPUNIT_TEST_SUITE_END();
  
public:
  virtual void setUp(void);
  virtual void tearDown(void);
  
private:
  void testConfig(void);
  void testConfigChar(void);
  void testConfigCharThrowInvalidArgument(void);
  void testConfigCharCharBool(void);
  void testConfigCharCharBoolThrowInvalidArgument(void);
  void testConfigCharCharBoolChar(void);
  void testConfigCharCharBoolCharThrowInvalidArgument(void);
  void testGetDelimitMark(void);
  void testSetDelimitMark(void);
  void testSetDelimitMarkThrowInvalidArgument(void);
  void testGetQuoteEnabled(void);
  void testSetQuoteEnabled(void);
  void testGetQuoteMark(void);
  void testSetQuoteMark(void);
  void testSetQuoteMarkThrowInvalidArgument(void);
  void testGetCommentEnabled(void);
  void testSetCommentEnabled(void);
  void testGetCommentMark(void);
  void testSetCommentMark(void);
  void testSetCommentMarkThrowInvalidArgument(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(ConfigTest);

void ConfigTest::setUp(void)
{
}

void ConfigTest::tearDown(void)
{
}

void ConfigTest::testConfig(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_DELIMIT_MARK, config.getDelimitMark());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_ENABLED, config.getQuoteEnabled());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_MARK, config.getQuoteMark());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_ENABLED, config.getCommentEnabled());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_MARK, config.getCommentMark());
}

void ConfigTest::testConfigChar(void)
{
  Config config('\t');
  CPPUNIT_ASSERT_EQUAL('\t', config.getDelimitMark());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_ENABLED, config.getQuoteEnabled());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_MARK, config.getQuoteMark());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_ENABLED, config.getCommentEnabled());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_MARK, config.getCommentMark());
}

void ConfigTest::testConfigCharThrowInvalidArgument(void)
{
  try {
    Config config('\"');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
}

void ConfigTest::testConfigCharCharBool(void)
{
  Config config('\t', false, '\'');
  CPPUNIT_ASSERT_EQUAL('\t', config.getDelimitMark());
  CPPUNIT_ASSERT_EQUAL(false, config.getQuoteEnabled());
  CPPUNIT_ASSERT_EQUAL('\'', config.getQuoteMark());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_ENABLED, config.getCommentEnabled());
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_MARK, config.getCommentMark());
}

void ConfigTest::testConfigCharCharBoolThrowInvalidArgument(void)
{
  try {
    Config config('\'', false, '\'');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
}

void ConfigTest::testConfigCharCharBoolChar(void)
{
  Config config('\t', false, '\'', true, '\\');
  CPPUNIT_ASSERT_EQUAL('\t', config.getDelimitMark());
  CPPUNIT_ASSERT_EQUAL(false, config.getQuoteEnabled());
  CPPUNIT_ASSERT_EQUAL('\'', config.getQuoteMark());
  CPPUNIT_ASSERT_EQUAL(true, config.getCommentEnabled());
  CPPUNIT_ASSERT_EQUAL('\\', config.getCommentMark());
}

void ConfigTest::testConfigCharCharBoolCharThrowInvalidArgument(void)
{
  try {
    Config config('\'', false, '\'', true, '\\');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
}

void ConfigTest::testGetDelimitMark(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_DELIMIT_MARK, config.getDelimitMark());
}

void ConfigTest::testSetDelimitMark(void)
{
  Config config;
  config.setDelimitMark('\t');
  CPPUNIT_ASSERT_EQUAL('\t', config.getDelimitMark());
}

void ConfigTest::testSetDelimitMarkThrowInvalidArgument(void)
{
  Config config;
  try {
    config.setDelimitMark('"');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
}

void ConfigTest::testGetQuoteEnabled(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_ENABLED, config.getQuoteEnabled());
}

void ConfigTest::testSetQuoteEnabled(void)
{
  Config config;
  config.setQuoteEnabled(false);
  CPPUNIT_ASSERT_EQUAL(false, config.getQuoteEnabled());
}

void ConfigTest::testGetQuoteMark(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_QUOTE_MARK, config.getQuoteMark());
}

void ConfigTest::testSetQuoteMark(void)
{
  Config config;
  config.setQuoteMark('\'');
  CPPUNIT_ASSERT_EQUAL('\'', config.getQuoteMark());
}

void ConfigTest::testSetQuoteMarkThrowInvalidArgument(void)
{
  Config config;
  try {
    config.setQuoteMark(',');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
}

void ConfigTest::testGetCommentEnabled(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_ENABLED, config.getCommentEnabled());
}

void ConfigTest::testSetCommentEnabled(void)
{
  Config config;
  config.setCommentEnabled(true);
  CPPUNIT_ASSERT_EQUAL(true, config.getCommentEnabled());
}

void ConfigTest::testGetCommentMark(void)
{
  Config config;
  CPPUNIT_ASSERT_EQUAL(DEFAULT_COMMENT_MARK, config.getCommentMark());
}

void ConfigTest::testSetCommentMark(void)
{
  Config config;
  config.setCommentMark('\\');
  CPPUNIT_ASSERT_EQUAL('\\', config.getCommentMark());
}

void ConfigTest::testSetCommentMarkThrowInvalidArgument(void)
{
  Config config;
  try {
    config.setCommentMark('"');
    CPPUNIT_FAIL("std::invalid_argument must be throw.");
  } catch (std::invalid_argument&) {
    CPPUNIT_ASSERT(true);
  }
} 

} // namespace csv
} // namespace csl
