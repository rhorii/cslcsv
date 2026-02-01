#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Writer.hpp"
#include "csl/csv/Reader.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

class WriterTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(WriterTest);
  CPPUNIT_TEST(testWriterOstream);
  CPPUNIT_TEST(testWriterOstreamConfig);
  CPPUNIT_TEST(testWriteQuoteEnabled);
  CPPUNIT_TEST(testWriteQuoteDisabled);
  CPPUNIT_TEST(testWriteQuoteEscape);
  CPPUNIT_TEST(testWriteRoundTrip);
  CPPUNIT_TEST(testWriteThrowFailure);
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp(void);
  virtual void tearDown(void);

private:
  void testWriterOstream(void);
  void testWriterOstreamConfig(void);
  void testWriteQuoteEnabled(void);
  void testWriteQuoteDisabled(void);
  void testWriteQuoteEscape(void);
  void testWriteRoundTrip(void);
  void testWriteThrowFailure(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(WriterTest);

void WriterTest::setUp(void)
{
}

void WriterTest::tearDown(void)
{
}

void WriterTest::testWriterOstream(void)
{
  std::stringstream stream("");
  Writer writer(stream);
}

void WriterTest::testWriterOstreamConfig(void)
{
  std::stringstream stream("");
  Config config;
  Writer writer(stream, config);
}

void WriterTest::testWriteQuoteEnabled(void)
{
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");
  
  std::stringstream stream("");
  Writer writer(stream);

  writer.write(record);

  CPPUNIT_ASSERT(stream.str() == "\"aaa\",\"bbb\",\"ccc\"\r\n");
}

void WriterTest::testWriteQuoteDisabled(void)
{
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");

  std::stringstream stream("");
  Config config;
  config.setQuoteEnabled(false);
  Writer writer(stream, config);

  writer.write(record);

  CPPUNIT_ASSERT(stream.str() == "aaa,bbb,ccc\r\n");
}

void WriterTest::testWriteQuoteEscape(void)
{
  std::stringstream stream("");
  Writer writer(stream);

  std::vector<std::string> record;
  record.push_back("hello\"world");  // 引用符を含む
  record.push_back("test");

  writer.write(record);

  // 期待: "hello""world","test"\r\n
  std::string expected = "\"hello\"\"world\",\"test\"\r\n";
  CPPUNIT_ASSERT(stream.str() == expected);
}

void WriterTest::testWriteRoundTrip(void)
{
  // Writer → Reader のラウンドトリップテスト
  std::stringstream ostream("");
  Writer writer(ostream);

  std::vector<std::string> originalRecord;
  originalRecord.push_back("aaa");
  originalRecord.push_back("b\"b\"b");
  originalRecord.push_back("ccc\"");

  writer.write(originalRecord);

  std::stringstream istream(ostream.str());
  Reader reader(istream);

  std::vector<std::string> readRecord;
  reader.read(readRecord);

  CPPUNIT_ASSERT(readRecord.size() == originalRecord.size());
  for (size_t i = 0; i < originalRecord.size(); i++) {
    CPPUNIT_ASSERT(readRecord[i] == originalRecord[i]);
  }
}

void WriterTest::testWriteThrowFailure(void)
{
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");

  std::ofstream stream("");
  Writer writer(stream);

  try {
    writer.write(record);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

} // namespace csv
} // namespace csl
