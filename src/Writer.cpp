/**
 * @file  Writer.cpp
 * @brief Writerクラス実装ファイル
 */
#include "csl/csv/Writer.hpp"

namespace csl {
namespace csv {

/**
 * @brief デフォルトのConfigオブジェクトを設定したWriterオブジェクトを構築します。
 * @param stream 出力ストリーム
 */
Writer::Writer(std::ostream& stream)
  : stream(stream)
  , config(DEFAULT_CONFIG)
{
}

/**
 * @brief 指定されたConfigオブジェクトを設定したWriterオブジェクトを構築します。
 * @param stream 出力ストリーム
 * @param config Configオブジェクト
 */
Writer::Writer(std::ostream& stream, const Config& config)
  : stream(stream)
  , config(config)
{
}

/**
 * @brief Writerオブジェクトを破棄します。
 */
Writer::~Writer(void)
{
}

/**
 * @brief 出力ストリームにCSVレコードを書き込みます。
 * @param record CSVレコード
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Writer::write(std::vector<std::string>& record)
{
  for (int i = 0; i < (int)record.size(); i++) {
    if (i > 0) {
      stream << config.getDelimitMark();
    }

    if (config.getQuoteEnabled()) {
      stream << config.getQuoteMark() << record[i] << config.getQuoteMark();
    } else {
      stream << record[i];
    }
  }

  stream << "\r\n";
  
  if (stream.fail() || stream.bad()) {
    throw std::ios_base::failure("Failed to write.");
  }
}

} // namespace csv
} // namespace csl
