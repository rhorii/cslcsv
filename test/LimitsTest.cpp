#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Reader.hpp"
#include "csl/csv/Util.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

class LimitsTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(LimitsTest);
  CPPUNIT_TEST(testFieldSizeLimit);
  CPPUNIT_TEST(testRecordSizeLimit);
  CPPUNIT_TEST(testMaxRecordsLimit);
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp(void);
  virtual void tearDown(void);

private:
  void testFieldSizeLimit(void);
  void testRecordSizeLimit(void);
  void testMaxRecordsLimit(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(LimitsTest);

void LimitsTest::setUp(void)
{
}

void LimitsTest::tearDown(void)
{
}

void LimitsTest::testFieldSizeLimit(void)
{
  // Test field size limit
  std::stringstream stream("aaaaaaaaaa,bbb\r\n");
  Config config;
  config.setMaxFieldSize(5);
  Reader reader(stream, config);
  std::vector<std::string> record;

  try {
    reader.read(record);
    CPPUNIT_FAIL("std::length_error must be thrown.");
  } catch (std::length_error& e) {
    std::string msg = e.what();
    CPPUNIT_ASSERT(msg.find("Field size exceeds limit") != std::string::npos);
  }
}

void LimitsTest::testRecordSizeLimit(void)
{
  // Test record size limit (3 fields, but limit is 2)
  std::stringstream stream("aaa,bbb,ccc\r\n");
  Config config;
  config.setMaxRecordSize(2);
  Reader reader(stream, config);
  std::vector<std::string> record;

  try {
    reader.read(record);
    CPPUNIT_FAIL("std::length_error must be thrown.");
  } catch (std::length_error& e) {
    std::string msg = e.what();
    CPPUNIT_ASSERT(msg.find("Record size exceeds limit") != std::string::npos);
  }
}

void LimitsTest::testMaxRecordsLimit(void)
{
  // Test max records limit (3 records, but limit is 2)
  std::stringstream stream("aaa,bbb\r\nccc,ddd\r\neee,fff\r\n");
  Config config;
  config.setMaxRecords(2);
  std::vector<std::vector<std::string> > csv;

  try {
    Util::load(stream, config, csv);
    CPPUNIT_FAIL("std::length_error must be thrown.");
  } catch (std::length_error& e) {
    std::string msg = e.what();
    CPPUNIT_ASSERT(msg.find("record count exceeds limit") != std::string::npos);
  }
}

} // namespace csv
} // namespace csl
