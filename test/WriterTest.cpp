#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Writer.hpp"
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
