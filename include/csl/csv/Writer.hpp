/**
 * @file  Writer.hpp
 * @brief Writerクラスヘッダーファイル
 */
#ifndef CSL_CSV_WRITER_HPP_
#define CSL_CSV_WRITER_HPP_

#include <string>
#include <vector>
#include <ostream>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

/**
 * @brief CSV形式ファイルを書き込むための出力ストリームです。
 */
class Writer
{
public:
  Writer(std::ostream& stream);
  Writer(std::ostream& stream, const Config& config);

public:
  ~Writer(void);
  
public:
  void write(const std::vector<std::string>& record);

private:
  std::ostream& stream;
  const Config& config;

private:
  std::string escapeField(const std::string& field) const;

private:
  Writer(const Writer& writer);
  Writer& operator=(const Writer& writer);
};

} // namespace csv
} // namespace csl

#endif // #ifndef CSL_CSV_WRITER_HPP_
