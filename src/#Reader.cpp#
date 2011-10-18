/**
 * @file  Reader.cpp
 * @brief Readerクラス実装ファイル
 */
#include "csl/csv/Reader.hpp"

namespace csl {
namespace csv {

/**
 * @brief デフォルトのConfigオブジェクトを設定したReaderオブジェクトを構築します。
 * @param stream 入力ストリーム
 */
Reader::Reader(std::istream& stream)
  : stream(stream)
  , config(DEFAULT_CONFIG)
{
  readNextChar();
}

/**
 * @brief 指定されたConfigオブジェクトを設定したReaderオブジェクトを構築します。
 * @param stream 入力ストリーム
 * @param config Configオブジェクト
 */
Reader::Reader(std::istream& stream, const Config& config)
  : stream(stream)
  , config(config)
{
  readNextChar();
}

/**
 * @brief Readerオブジェクトを破棄します。
 */
Reader::~Reader(void)
{
}

/**
 * @brief 次のCSVレコードがあるかどうかを返します。
 * @return 次のCSVレコードがあるかどうか
 */
bool Reader::hasNext(void)
{
  return !stream.eof();
}

/**
 * @brief 入力ストリームからCSVレコードを読み込んで返します。
 * @param record CSVレコード
 * @exception std::ios_base::failure 入力ストリームにエラーが発生した場合
 */
void Reader::read(std::vector<std::string>& record)
{
  typedef enum {
    STATE_NORMAL,
    STATE_QUOTE,
    STATE_ESCAPE,
    STATE_AFTER_CR,
  } STATE;

  record.clear();

  std::string field;
  STATE state = STATE_NORMAL;
  bool firstCharFlag = true;
  
  while (hasNext()) {
    if (stream.fail() || stream.bad()) {
      throw std::ios_base::failure("Failed to read.");
    }

    if (firstCharFlag) {
      firstCharFlag = false;
      if (config.getCommentEnabled() && nextChar == config.getCommentMark()) {
	readCommentLine();
	if (!hasNext()) {
	  break; // end of file
	}
      }
    }

    if (state == STATE_NORMAL) {
      if (nextChar == config.getDelimitMark()) {
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	state = STATE_AFTER_CR;
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	state = STATE_QUOTE;
      } else {
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    } else if (state == STATE_AFTER_CR) {
      if (nextChar == config.getDelimitMark()) {
	field.push_back('\r');
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	field.push_back('\r');
	state = STATE_AFTER_CR;
      } else if (nextChar == '\n') {
	state = STATE_NORMAL;
	readNextChar();
	break; // end of record
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	field.push_back('\r');
	state = STATE_QUOTE;
      } else {
	field.push_back('\r');
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    } else if (state == STATE_QUOTE) {
      if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	state = STATE_ESCAPE;
      } else {
	field.push_back(nextChar);
	state = STATE_QUOTE;
      }
    } else if (state == STATE_ESCAPE) {
      if (nextChar == config.getDelimitMark()) {
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	state = STATE_AFTER_CR;
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	field.push_back(nextChar);
	state = STATE_QUOTE;
      } else {
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    }

    readNextChar();
  }

  if (state == STATE_AFTER_CR) {
    field.push_back('\r');
  }

  if (field.size() > 0) {
    record.push_back(field);
  }
}

/**
 * @brief 入力ストリームから次の１文字を読み込みます。
 */
void Reader::readNextChar(void)
{
  nextChar = stream.get();
}

/**
 * @brief コメント行を読み飛ばします。
 */
void Reader::readCommentLine(void)
{
  bool carriageReturnFlag = false;
  
  while (hasNext()) {
    if (carriageReturnFlag && nextChar == '\n') {
      readNextChar();
      break;
    }

    if (nextChar == '\r') {
      carriageReturnFlag = true;
    } else {
      carriageReturnFlag = false;
    }

    readNextChar();
  }
}

} // namespace csv
} // namespace csl
