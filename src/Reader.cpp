/**
 * @file  Reader.cpp
 * @brief Readerクラス実装ファイル
 */
#include "csl/csv/Reader.hpp"
#include <sstream>
#include <stdexcept>

namespace csl {
namespace csv {

/**
 * @brief デフォルトのConfigオブジェクトを設定したReaderオブジェクトを構築します。
 * @param stream 入力ストリーム
 */
Reader::Reader(std::istream& stream)
  : stream(stream)
  , config(DEFAULT_CONFIG)
  , recordCount(0)
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
  , recordCount(0)
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
  if (stream.bad()) {
    throw std::ios_base::failure("Stream is in bad state");
  }
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
      std::ostringstream msg;
      msg << "Failed to read at record " << recordCount;
      if (stream.bad()) {
        msg << ": stream in bad state";
      } else if (stream.fail()) {
        msg << ": stream read failure";
      }
      throw std::ios_base::failure(msg.str());
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
	if (config.getMaxRecordSize() > 0 && record.size() >= config.getMaxRecordSize()) {
	  std::ostringstream msg;
	  msg << "Record size exceeds limit (" << config.getMaxRecordSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	state = STATE_AFTER_CR;
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	state = STATE_QUOTE;
      } else {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    } else if (state == STATE_AFTER_CR) {
      if (nextChar == config.getDelimitMark()) {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back('\r');
	if (config.getMaxRecordSize() > 0 && record.size() >= config.getMaxRecordSize()) {
	  std::ostringstream msg;
	  msg << "Record size exceeds limit (" << config.getMaxRecordSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back('\r');
	state = STATE_AFTER_CR;
      } else if (nextChar == '\n') {
	state = STATE_NORMAL;
	readNextChar();
	break; // end of record
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back('\r');
	state = STATE_QUOTE;
      } else {
	if (config.getMaxFieldSize() > 0 && field.size() + 1 >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back('\r');
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    } else if (state == STATE_QUOTE) {
      if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	state = STATE_ESCAPE;
      } else {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back(nextChar);
	state = STATE_QUOTE;
      }
    } else if (state == STATE_ESCAPE) {
      if (nextChar == config.getDelimitMark()) {
	if (config.getMaxRecordSize() > 0 && record.size() >= config.getMaxRecordSize()) {
	  std::ostringstream msg;
	  msg << "Record size exceeds limit (" << config.getMaxRecordSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	record.push_back(field);
	field.clear();
	state = STATE_NORMAL;
      } else if (nextChar == '\r') {
	state = STATE_AFTER_CR;
      } else if (config.getQuoteEnabled() && nextChar == config.getQuoteMark()) {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back(nextChar);
	state = STATE_QUOTE;
      } else {
	if (config.getMaxFieldSize() > 0 && field.size() >= config.getMaxFieldSize()) {
	  std::ostringstream msg;
	  msg << "Field size exceeds limit (" << config.getMaxFieldSize()
	      << ") at record " << recordCount;
	  throw std::length_error(msg.str());
	}
	field.push_back(nextChar);
	state = STATE_NORMAL;
      }
    }

    readNextChar();
  }

  // レコード終了時の状態チェック
  if (state == STATE_QUOTE) {
    std::ostringstream msg;
    msg << "Unmatched quote in record " << recordCount;
    throw std::runtime_error(msg.str());
  }

  if (state == STATE_AFTER_CR) {
    field.push_back('\r');
  }

  if (field.size() > 0) {
    if (config.getMaxRecordSize() > 0 && record.size() >= config.getMaxRecordSize()) {
      std::ostringstream msg;
      msg << "Record size exceeds limit (" << config.getMaxRecordSize()
          << ") at record " << recordCount;
      throw std::length_error(msg.str());
    }
    record.push_back(field);
  }

  recordCount++;
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
