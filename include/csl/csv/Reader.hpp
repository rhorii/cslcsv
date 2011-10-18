/**
 * @file  Reader.hpp
 * @brief Readerクラスヘッダーファイル
 */
#ifndef CSL_CSV_READER_HPP_
#define CSL_CSV_READER_HPP_

#include <string>
#include <vector>
#include <istream>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

/**
 * @brief CSV形式ファイルを読み込むための入力ストリームです。
 */
class Reader
{
public:
  Reader(std::istream& stream);
  Reader(std::istream& stream, const Config& config);

public:
  ~Reader(void);

public:
  bool hasNext(void);
  void read(std::vector<std::string>& record);

private:
  std::istream& stream;
  const Config& config;
  char nextChar;

private:
  void readNextChar(void);
  void readCommentLine(void);

private:
  Reader(const Reader& reader);
  Reader& operator=(const Reader& reader);
};

} // namespace csv
} // namespace csl

#endif // #ifndef CSL_CSV_READER_HPP_
