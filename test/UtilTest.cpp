#include <cppunit/extensions/HelperMacros.h>
#include "csl/csv/Util.hpp"
#include <string>
#include <vector>

namespace csl {
namespace csv {

class UtilTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(UtilTest);
  CPPUNIT_TEST(testLoadIstreamVectorVectorString);
  CPPUNIT_TEST(testLoadIstreamVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testLoadIstreamConfigVectorVectorString);
  CPPUNIT_TEST(testLoadIstreamConfigVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testLoadStringVectorVectorString);
  CPPUNIT_TEST(testLoadStringVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testLoadStringConfigVectorVectorString);
  CPPUNIT_TEST(testLoadStringConfigVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testSaveOstreamVectorVectorString);
  CPPUNIT_TEST(testSaveOstreamVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testSaveOstreamConfigVectorVectorString);
  CPPUNIT_TEST(testSaveOstreamConfigVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testSaveStringVectorVectorString);
  CPPUNIT_TEST(testSaveStringVectorVectorStringThrowFailure);
  CPPUNIT_TEST(testSaveStringConfigVectorVectorString);
  CPPUNIT_TEST(testSaveStringConfigVectorVectorStringThrowFailure);
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp(void);
  virtual void tearDown(void);

private:
  void testLoadIstreamVectorVectorString(void);
  void testLoadIstreamVectorVectorStringThrowFailure(void);
  void testLoadIstreamConfigVectorVectorString(void);
  void testLoadIstreamConfigVectorVectorStringThrowFailure(void);
  void testLoadStringVectorVectorString(void);
  void testLoadStringVectorVectorStringThrowFailure(void);
  void testLoadStringConfigVectorVectorString(void);
  void testLoadStringConfigVectorVectorStringThrowFailure(void);
  void testSaveOstreamVectorVectorString(void);
  void testSaveOstreamVectorVectorStringThrowFailure(void);
  void testSaveOstreamConfigVectorVectorString(void);
  void testSaveOstreamConfigVectorVectorStringThrowFailure(void);
  void testSaveStringVectorVectorString(void);
  void testSaveStringVectorVectorStringThrowFailure(void);
  void testSaveStringConfigVectorVectorString(void);
  void testSaveStringConfigVectorVectorStringThrowFailure(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);

void UtilTest::setUp(void)
{
}

void UtilTest::tearDown(void)
{
}

void UtilTest::testLoadIstreamVectorVectorString(void)
{
  std::stringstream stream("\"aaa\",\"bbb\",\"ccc\"\r\n"
			   "\"ddd\",\"eee\",\"fff\"\r\n");
  std::vector<std::vector<std::string> > csv;

  Util::load(stream, csv);

  CPPUNIT_ASSERT(csv.size() == 2);

  CPPUNIT_ASSERT(csv[0].size() == 3);
  CPPUNIT_ASSERT(csv[0][0] == "aaa");
  CPPUNIT_ASSERT(csv[0][1] == "bbb");
  CPPUNIT_ASSERT(csv[0][2] == "ccc");

  CPPUNIT_ASSERT(csv[1].size() == 3);
  CPPUNIT_ASSERT(csv[1][0] == "ddd");
  CPPUNIT_ASSERT(csv[1][1] == "eee");
  CPPUNIT_ASSERT(csv[1][2] == "fff");
}

void UtilTest::testLoadIstreamVectorVectorStringThrowFailure(void)
{ 
  std::stringstream stream("aaa");
  std::vector<std::vector<std::string> > csv;
  stream.setstate(std::ios_base::badbit);

  try {
    Util::load(stream, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testLoadIstreamConfigVectorVectorString(void)
{
  std::stringstream stream("\"aaa\",\"bbb\",\"ccc\"\r\n"
			   "\"ddd\",\"eee\",\"fff\"\r\n");
  std::vector<std::vector<std::string> > csv;

  Config config;
  config.setQuoteEnabled(false);
  Util::load(stream, config, csv);

  CPPUNIT_ASSERT(csv.size() == 2);

  CPPUNIT_ASSERT(csv[0].size() == 3);
  CPPUNIT_ASSERT(csv[0][0] == "\"aaa\"");
  CPPUNIT_ASSERT(csv[0][1] == "\"bbb\"");
  CPPUNIT_ASSERT(csv[0][2] == "\"ccc\"");

  CPPUNIT_ASSERT(csv[1].size() == 3);
  CPPUNIT_ASSERT(csv[1][0] == "\"ddd\"");
  CPPUNIT_ASSERT(csv[1][1] == "\"eee\"");
  CPPUNIT_ASSERT(csv[1][2] == "\"fff\"");
}

void UtilTest::testLoadIstreamConfigVectorVectorStringThrowFailure(void)
{
  std::stringstream stream("aaa");
  std::vector<std::vector<std::string> > csv;
  stream.setstate(std::ios_base::badbit);

  Config config;
  config.setQuoteEnabled(false);

  try {
    Util::load(stream, config, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testLoadStringVectorVectorString(void)
{
  std::string filepath = "./test/test.csv";
  std::vector<std::vector<std::string> > csv;

  Util::load(filepath, csv);

  CPPUNIT_ASSERT(csv.size() == 4);

  CPPUNIT_ASSERT(csv[0].size() == 5);
  CPPUNIT_ASSERT(csv[0][0] == "aaa");
  CPPUNIT_ASSERT(csv[0][1] == "bbb");
  CPPUNIT_ASSERT(csv[0][2] == "ccc");
  CPPUNIT_ASSERT(csv[0][3] == "ddd");
  CPPUNIT_ASSERT(csv[0][4] == "eee");

  CPPUNIT_ASSERT(csv[1].size() == 5);
  CPPUNIT_ASSERT(csv[1][0] == "aaa");
  CPPUNIT_ASSERT(csv[1][1] == "bbb");
  CPPUNIT_ASSERT(csv[1][2] == "ccc");
  CPPUNIT_ASSERT(csv[1][3] == "ddd");
  CPPUNIT_ASSERT(csv[1][4] == "e\"e\"e");
    
  CPPUNIT_ASSERT(csv[2].size() == 5);
  CPPUNIT_ASSERT(csv[2][0] == "aaa");
  CPPUNIT_ASSERT(csv[2][1] == "bbb");
  CPPUNIT_ASSERT(csv[2][2] == "ccc");
  CPPUNIT_ASSERT(csv[2][3] == "ddd");
  CPPUNIT_ASSERT(csv[2][4] == "e,e");

  CPPUNIT_ASSERT(csv[3].size() == 5);
  CPPUNIT_ASSERT(csv[3][0] == "aaa");
  CPPUNIT_ASSERT(csv[3][1] == "bbb");
  CPPUNIT_ASSERT(csv[3][2] == "ccc");
  CPPUNIT_ASSERT(csv[3][3] == "ddd");
  CPPUNIT_ASSERT(csv[3][4] == "e\ne");
}

void UtilTest::testLoadStringVectorVectorStringThrowFailure(void)
{
  std::string filepath = "./";
  std::vector<std::vector<std::string> > csv;

  try {
    Util::load(filepath, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testLoadStringConfigVectorVectorString(void)
{
  std::string filepath = "./test/test.csv";
  std::vector<std::vector<std::string> > csv;

  Config config;
  config.setQuoteEnabled(false);
  Util::load(filepath, config, csv);

  CPPUNIT_ASSERT(csv.size() == 4);

  CPPUNIT_ASSERT(csv[0].size() == 5);
  CPPUNIT_ASSERT(csv[0][0] == "aaa");
  CPPUNIT_ASSERT(csv[0][1] == "bbb");
  CPPUNIT_ASSERT(csv[0][2] == "ccc");
  CPPUNIT_ASSERT(csv[0][3] == "ddd");
  CPPUNIT_ASSERT(csv[0][4] == "eee");

  CPPUNIT_ASSERT(csv[1].size() == 5);
  CPPUNIT_ASSERT(csv[1][0] == "aaa");
  CPPUNIT_ASSERT(csv[1][1] == "bbb");
  CPPUNIT_ASSERT(csv[1][2] == "ccc");
  CPPUNIT_ASSERT(csv[1][3] == "ddd");
  CPPUNIT_ASSERT(csv[1][4] == "\"e\"\"e\"\"e\"");
    
  CPPUNIT_ASSERT(csv[2].size() == 6);
  CPPUNIT_ASSERT(csv[2][0] == "aaa");
  CPPUNIT_ASSERT(csv[2][1] == "bbb");
  CPPUNIT_ASSERT(csv[2][2] == "ccc");
  CPPUNIT_ASSERT(csv[2][3] == "ddd");
  CPPUNIT_ASSERT(csv[2][4] == "\"e");
  CPPUNIT_ASSERT(csv[2][5] == "e\"");

  CPPUNIT_ASSERT(csv[3].size() == 5);
  CPPUNIT_ASSERT(csv[3][0] == "aaa");
  CPPUNIT_ASSERT(csv[3][1] == "bbb");
  CPPUNIT_ASSERT(csv[3][2] == "ccc");
  CPPUNIT_ASSERT(csv[3][3] == "ddd");
  CPPUNIT_ASSERT(csv[3][4] == "\"e\ne\"");
}

void UtilTest::testLoadStringConfigVectorVectorStringThrowFailure(void)
{
  std::string filepath = "./";
  std::vector<std::vector<std::string> > csv;
  
  Config config;
  config.setQuoteEnabled(false);
  
  try {
    Util::load(filepath, config, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testSaveOstreamVectorVectorString(void)
{
  std::stringstream stream("");
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");
  csv.push_back(record);
  record.clear();
  record.push_back("ddd");
  record.push_back("eee");
  record.push_back("fff");
  csv.push_back(record);
  record.clear();

  Util::save(stream, csv);

  CPPUNIT_ASSERT(stream.str() ==
		 "\"aaa\",\"bbb\",\"ccc\"\r\n"
		 "\"ddd\",\"eee\",\"fff\"\r\n");
}

void UtilTest::testSaveOstreamVectorVectorStringThrowFailure(void)
{
  std::stringstream stream("");
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  csv.push_back(record);
  record.clear();
  stream.setstate(std::ios_base::badbit);

  try {
    Util::save(stream, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testSaveOstreamConfigVectorVectorString(void)
{
  std::stringstream stream("");
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");
  csv.push_back(record);
  record.clear();
  record.push_back("ddd");
  record.push_back("eee");
  record.push_back("fff");
  csv.push_back(record);
  record.clear();

  Config config;
  config.setQuoteEnabled(false);

  Util::save(stream, config, csv);
  
  CPPUNIT_ASSERT(stream.str() ==
		 "aaa,bbb,ccc\r\n"
		 "ddd,eee,fff\r\n");
}

void UtilTest::testSaveOstreamConfigVectorVectorStringThrowFailure(void)
{
  std::stringstream stream("");
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  csv.push_back(record);
  record.clear();
  stream.setstate(std::ios_base::badbit);

  Config config;
  config.setQuoteEnabled(false);

  try {
    Util::save(stream, config, csv);
    CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testSaveStringVectorVectorString(void)
{
  std::string filepath = "./test/out.csv";
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");
  csv.push_back(record);
  record.clear();
  record.push_back("ddd");
  record.push_back("eee");
  record.push_back("fff");
  csv.push_back(record);
  record.clear();

  Util::save(filepath, csv);

  Config config;
  config.setQuoteEnabled(false);
  csv.clear();
  Util::load(filepath, config, csv);

  CPPUNIT_ASSERT(csv.size() == 2);

  CPPUNIT_ASSERT(csv[0].size() == 3);
  CPPUNIT_ASSERT(csv[0][0] == "\"aaa\"");
  CPPUNIT_ASSERT(csv[0][1] == "\"bbb\"");
  CPPUNIT_ASSERT(csv[0][2] == "\"ccc\"");
  
  CPPUNIT_ASSERT(csv[1].size() == 3);
  CPPUNIT_ASSERT(csv[1][0] == "\"ddd\"");
  CPPUNIT_ASSERT(csv[1][1] == "\"eee\"");
  CPPUNIT_ASSERT(csv[1][2] == "\"fff\"");
}

void UtilTest::testSaveStringVectorVectorStringThrowFailure(void)
{
  std::string filepath = "./";
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  csv.push_back(record);
  record.clear();

  try {
    Util::save(filepath, csv);
        CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

void UtilTest::testSaveStringConfigVectorVectorString(void)
{
  std::string filepath = "./test/out.csv";
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  record.push_back("bbb");
  record.push_back("ccc");
  csv.push_back(record);
  record.clear();
  record.push_back("ddd");
  record.push_back("eee");
  record.push_back("fff");
  csv.push_back(record);
  record.clear();

  Config config;
  config.setQuoteEnabled(false);
  Util::save(filepath, config, csv);

  csv.clear();
  Util::load(filepath, config, csv);

  CPPUNIT_ASSERT(csv.size() == 2);

  CPPUNIT_ASSERT(csv[0].size() == 3);
  CPPUNIT_ASSERT(csv[0][0] == "aaa");
  CPPUNIT_ASSERT(csv[0][1] == "bbb");
  CPPUNIT_ASSERT(csv[0][2] == "ccc");
  
  CPPUNIT_ASSERT(csv[1].size() == 3);
  CPPUNIT_ASSERT(csv[1][0] == "ddd");
  CPPUNIT_ASSERT(csv[1][1] == "eee");
  CPPUNIT_ASSERT(csv[1][2] == "fff");
}

void UtilTest::testSaveStringConfigVectorVectorStringThrowFailure(void)
{
  std::string filepath = "./";
  std::vector<std::vector<std::string> > csv;
  std::vector<std::string> record;
  record.push_back("aaa");
  csv.push_back(record);
  record.clear();

  Config config;
  config.setQuoteEnabled(false);

  try {
    Util::save(filepath, csv);
        CPPUNIT_FAIL("std::ios_base::failure must be throw.");
  } catch (std::ios_base::failure&) {
    CPPUNIT_ASSERT(true);
  }
}

} // namespace csv
} // namespace csl
