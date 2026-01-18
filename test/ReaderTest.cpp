#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Reader.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

class ReaderTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(ReaderTest);
  CPPUNIT_TEST(testReaderIstream);
  CPPUNIT_TEST(testReaderIstreamConfig);
  CPPUNIT_TEST(testReadQuoteEnabled);
  CPPUNIT_TEST(testReadQuoteDisabled);
  CPPUNIT_TEST(testReadCommentEnabled);
  CPPUNIT_TEST(testReadCommentDisabled);
  CPPUNIT_TEST(testReadUnmatchedQuote);
  CPPUNIT_TEST(testReadThrowFailure);
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp(void);
  virtual void tearDown(void);

private:
  void testReaderIstream(void);
  void testReaderIstreamConfig(void);
  void testHasNext(void);
  void testReadQuoteEnabled(void);
  void testReadQuoteDisabled(void);
  void testReadCommentEnabled(void);
  void testReadCommentDisabled(void);
  void testReadUnmatchedQuote(void);
  void testReadThrowFailure(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(ReaderTest);

void ReaderTest::setUp(void)
{
}

void ReaderTest::tearDown(void)
{
}

void ReaderTest::testReaderIstream(void)
{
  std::stringstream stream("");
  Reader reader(stream);
}

void ReaderTest::testReaderIstreamConfig(void)
{
  std::stringstream stream("");
  Config config;
  Reader reader(stream, config);
}

void ReaderTest::testHasNext(void)
{
  std::stringstream stream("a");
  Reader reader(stream);
  std::vector<std::string> record;

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT_EQUAL(false, reader.hasNext());
}

void ReaderTest::testReadQuoteEnabled(void)
{
  std::stringstream stream("aaa,bbb,ccc\r\n"
			   "\"aaa\",\"bbb,bbb\",\"ccc\"\"\",\"\r\n\"\r\n"
			   "\"\"\r,\"\"aaa,\r,\r\"\",\rbbb,\r\r");
  Reader reader(stream);
  std::vector<std::string> record;

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "aaa");
  CPPUNIT_ASSERT(record[1] == "bbb");
  CPPUNIT_ASSERT(record[2] == "ccc");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 4);
  CPPUNIT_ASSERT(record[0] == "aaa");
  CPPUNIT_ASSERT(record[1] == "bbb,bbb");
  CPPUNIT_ASSERT(record[2] == "ccc\"");
  CPPUNIT_ASSERT(record[3] == "\r\n");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 6);
  CPPUNIT_ASSERT(record[0] == "\r");
  CPPUNIT_ASSERT(record[1] == "aaa");
  CPPUNIT_ASSERT(record[2] == "\r");
  CPPUNIT_ASSERT(record[3] == "\r");
  CPPUNIT_ASSERT(record[4] == "\rbbb");
  CPPUNIT_ASSERT(record[5] == "\r\r");

  CPPUNIT_ASSERT_EQUAL(false, reader.hasNext());
}

void ReaderTest::testReadQuoteDisabled(void)
{
  std::stringstream stream("aaa,bbb,ccc\r\n"
			   "\"aaa\",\"bbb,bbb\",\"ccc\"\"\",\"\r\n\"\r\n"
			   "\"\"\r,\"\"aaa,\r,\r\"\",\rbbb,\r\r");
  Config config;
  config.setQuoteEnabled(false);
  Reader reader(stream, config);
  std::vector<std::string> record;

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "aaa");
  CPPUNIT_ASSERT(record[1] == "bbb");
  CPPUNIT_ASSERT(record[2] == "ccc");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 5);
  CPPUNIT_ASSERT(record[0] == "\"aaa\"");
  CPPUNIT_ASSERT(record[1] == "\"bbb");
  CPPUNIT_ASSERT(record[2] == "bbb\"");
  CPPUNIT_ASSERT(record[3] == "\"ccc\"\"\"");
  CPPUNIT_ASSERT(record[4] == "\"");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 1);
  CPPUNIT_ASSERT(record[0] == "\"");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 6);
  CPPUNIT_ASSERT(record[0] == "\"\"\r");
  CPPUNIT_ASSERT(record[1] == "\"\"aaa");
  CPPUNIT_ASSERT(record[2] == "\r");
  CPPUNIT_ASSERT(record[3] == "\r\"\"");
  CPPUNIT_ASSERT(record[4] == "\rbbb");
  CPPUNIT_ASSERT(record[5] == "\r\r");

  CPPUNIT_ASSERT_EQUAL(false, reader.hasNext());
}

void ReaderTest::testReadCommentEnabled(void)
{
  std::stringstream stream("#comment line1\r\n"
			   "aaa,bbb,ccc\r\n"
			   "#comment line2\r\n"
			   "ddd,eee,fff\r\n"
			   "#comment line3\r\n");
  Config config;
  config.setCommentEnabled(true);
  Reader reader(stream, config);
  std::vector<std::string> record;

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "aaa");
  CPPUNIT_ASSERT(record[1] == "bbb");
  CPPUNIT_ASSERT(record[2] == "ccc");
  
  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "ddd");
  CPPUNIT_ASSERT(record[1] == "eee");
  CPPUNIT_ASSERT(record[2] == "fff");
  
  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 0);
  
  CPPUNIT_ASSERT_EQUAL(false, reader.hasNext());
}

void ReaderTest::testReadCommentDisabled(void)
{
  std::stringstream stream("#comment line1\r\n"
			   "aaa,bbb,ccc\r\n"
			   "#comment line2\r\n"
			   "ddd,eee,fff\r\n"
			   "#comment line3\r\n");
  Reader reader(stream);
  std::vector<std::string> record;
  
  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 1);
  CPPUNIT_ASSERT(record[0] == "#comment line1");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "aaa");
  CPPUNIT_ASSERT(record[1] == "bbb");
  CPPUNIT_ASSERT(record[2] == "ccc");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 1);
  CPPUNIT_ASSERT(record[0] == "#comment line2");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 3);
  CPPUNIT_ASSERT(record[0] == "ddd");
  CPPUNIT_ASSERT(record[1] == "eee");
  CPPUNIT_ASSERT(record[2] == "fff");

  CPPUNIT_ASSERT_EQUAL(true, reader.hasNext());
  reader.read(record);
  CPPUNIT_ASSERT(record.size() == 1);
  CPPUNIT_ASSERT(record[0] == "#comment line3");

  CPPUNIT_ASSERT_EQUAL(false, reader.hasNext());
}

void ReaderTest::testReadUnmatchedQuote(void)
{
  std::stringstream stream("\"aaa,bbb\r\n");  // 終了引用符なし
  Reader reader(stream);
  std::vector<std::string> record;

  try {
    reader.read(record);
    CPPUNIT_FAIL("std::runtime_error must be throw.");
  } catch (std::runtime_error& e) {
    // 期待される例外
    std::string msg = e.what();
    CPPUNIT_ASSERT(msg.find("Unmatched quote") != std::string::npos);
  }
}

void ReaderTest::testReadThrowFailure(void)
{
  std::ifstream stream("");
  Reader reader(stream);
  std::vector<std::string> record;

  try {
    reader.read(record);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

} // namespace csv
} // namespace csl
