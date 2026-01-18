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
 * @brief フィールド内の引用符をエスケープします。
 * @param field エスケープ対象のフィールド
 * @return エスケープされたフィールド
 */
std::string Writer::escapeField(const std::string& field) const
{
  if (!config.getQuoteEnabled()) {
    return field;
  }

  const char quoteMark = config.getQuoteMark();
  std::string escaped;
  escaped.reserve(field.size() + 10); // 余裕を持ってreserve

  for (size_t i = 0; i < field.size(); i++) {
    if (field[i] == quoteMark) {
      escaped.push_back(quoteMark); // エスケープ用の追加引用符
    }
    escaped.push_back(field[i]);
  }

  return escaped;
}

/**
 * @brief 出力ストリームにCSVレコードを書き込みます。
 * @param record CSVレコード
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Writer::write(const std::vector<std::string>& record)
{
  for (int i = 0; i < (int)record.size(); i++) {
    if (i > 0) {
      stream << config.getDelimitMark();
    }

    if (config.getQuoteEnabled()) {
      std::string escapedField = escapeField(record[i]);
      stream << config.getQuoteMark() << escapedField << config.getQuoteMark();
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
