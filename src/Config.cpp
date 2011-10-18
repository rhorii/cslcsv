/**
 * @file  Config.cpp
 * @brief Configクラス実装ファイル
 */
#include "csl/csv/Config.hpp"
#include <stdexcept>

namespace csl {
namespace csv {

/**
 * @brief デフォルトのConfigオブジェクトを構築します。
 */
Config::Config(void)
  : delimitMark(DEFAULT_DELIMIT_MARK)
  , quoteEnabled(DEFAULT_QUOTE_ENABLED)
  , quoteMark(DEFAULT_QUOTE_MARK)
  , commentEnabled(DEFAULT_COMMENT_ENABLED)
  , commentMark(DEFAULT_COMMENT_MARK)
{
}

/**
 * @brief 指定された区切り文字を設定したConfigオブジェクトを構築します。
 * @param delimitMark 区切り文字
 * @exception std::invalid_argument 指定された区切り文字が、デフォルトの囲み文字、デフォルトのコメント文字、改行コードと同一文字の場合
 */
Config::Config(const char delimitMark)
  : delimitMark(delimitMark)
  , quoteEnabled(DEFAULT_QUOTE_ENABLED)
  , quoteMark(DEFAULT_QUOTE_MARK)
  , commentEnabled(DEFAULT_COMMENT_ENABLED)
  , commentMark(DEFAULT_COMMENT_MARK)
{
  validate();
}

/**
 * @brief 指定された区切り文字、および、指定された囲み文字を有効にするかどうかと指定された囲み文字を設定したConfigオブジェクトを構築します。
 * @param delimitMark  区切り文字
 * @param quoteEnabled 囲み文字を有効にするかどうか
 * @param quoteMark    囲み文字
 * @exception std::invalid_argument 指定された区切り文字が、指定された囲み文字、デフォルトのコメント文字、改行コードと同一文字の場合、または、指定された囲み文字が、指定された区切り文字、デフォルトのコメント文字、改行コードと同一文字の場合
 */
Config::Config(const char delimitMark, const bool quoteEnabled, const char quoteMark)
  : delimitMark(delimitMark)
  , quoteEnabled(quoteEnabled)
  , quoteMark(quoteMark)
  , commentEnabled(DEFAULT_COMMENT_ENABLED)
  , commentMark(DEFAULT_COMMENT_MARK)
{
  validate();
}

/**
 * @brief 指定された区切り文字、および、指定された囲み文字を有効にするかどうかと指定された囲み文字、および、指定されたコメント文字を有効にするかどうかと指定されたコメント文字を設定したConfigオブジェクトを構築します。
 * @param delimitMark    区切り文字
 * @param quoteEnabled   囲み文字を有効にするかどうか
 * @param quoteMark      囲み文字
 * @param commentEnabled コメント文字を有効にするかどうか
 * @param commentMark    コメント文字
 * @exception std::invalid_argument 指定された区切り文字が、指定された囲み文字、指定されたコメント文字、改行コードと同一文字の場合、または、指定された囲み文字が、指定された区切り文字、指定されたコメント文字、改行コードと同一文字の場合、または、指定されたコメント文字が、指定された区切り文字、指定された囲み文字、改行コードと同一文字の場合
 */
Config::Config(const char delimitMark,
	       const bool quoteEnabled, const char quoteMark,
	       const bool commentEnabled, const char commentMark)
  : delimitMark(delimitMark)
  , quoteEnabled(quoteEnabled)
  , quoteMark(quoteMark)
  , commentEnabled(commentEnabled)
  , commentMark(commentMark)
{
  validate();
}

/**
 * @brief Configオブジェクトを破棄します。
 */
Config::~Config(void)
{
}

/**
 * @brief 区切り文字を返します。
 * @return 区切り文字
 */
char Config::getDelimitMark(void) const
{
  return delimitMark;
}

/**
 * @brief 区切り文字を設定します。
 * @param delimitMark 区切り文字
 * @exception std::invalid_argument 指定された区切り文字が、設定された囲み文字、設定されたコメント文字、改行コードと同一文字の場合
 */
void Config::setDelimitMark(const char delimitMark)
{
  this->delimitMark = delimitMark;
  validate();
}

/**
 * @brief 囲み文字が有効かをどうか返します。
 * @return 囲み文字が有効かどうか
 */
bool Config::getQuoteEnabled(void) const
{
  return quoteEnabled;
}

/**
 * @brief 囲み文字が有効かをどうか設定します。
 * @param quoteEnabled 囲み文字が有効かどうか
 */
void Config::setQuoteEnabled(const bool quoteEnabled)
{
  this->quoteEnabled = quoteEnabled;
}

/**
 * @brief 囲み文字を返します。
 * @return 囲み文字
 */
char Config::getQuoteMark(void) const
{
  return quoteMark;
}

/**
 * @brief 囲み文字を設定します。
 * @param quoteMark 囲み文字
 * @exception std::invalid_argument 指定された囲み文字が、設定された区切り文字、設定されたコメント文字、改行コードと同一文字の場合
 */
void Config::setQuoteMark(const char quoteMark)
{
  this->quoteMark = quoteMark;
  validate();
}

/**
 * @brief コメント文字が有効かどうかを返します。
 * @return コメント文字が有効かどうか
 */
bool Config::getCommentEnabled(void) const 
{
  return commentEnabled;
}

/**
 * @brief コメント文字が有効かどうかを設定します。
 * @param commentEnabled コメント文字が有効かどうか
 */
void Config::setCommentEnabled(const bool commentEnabled)
{
  this->commentEnabled = commentEnabled;
}

/**
 * @brief コメント文字を返します。
 * @return コメント文字
 */
char Config::getCommentMark(void) const
{
  return commentMark;
}

/**
 * @brief コメント文字を設定します。
 * @param commentMark コメント文字
 * @exception std::invalid_argument 指定されたコメント文字が、設定された区切り文字、設定された囲み文字、改行コードと同一文字の場合
 */
void Config::setCommentMark(const char commentMark)
{
  this->commentMark = commentMark;
  validate();
}

/**
 * @brief 設定された区切り文字、囲み文字、コメント文字が正当かどうか確認します。
 * @exception std::invalid_argument 設定された区切り文字が、設定された囲み文字、設定されたコメント文字、改行コードと同一文字の場合、または、設定された囲み文字が、設定された区切り文字、設定されたコメント文字、改行コードと同一文字の場合、または、設定されたコメント文字が、設定された区切り文字、設定された囲み文字、改行コードと同一文字の場合
 */
void Config::validate(void) const
{
  if (delimitMark == quoteMark || delimitMark == commentMark || delimitMark == '\r' || delimitMark == '\n') {
    throw std::invalid_argument("Invalid delimit mark.");
  }

  if (quoteMark == delimitMark || quoteMark == commentMark || quoteMark == '\r' || quoteMark == '\n') {
    throw std::invalid_argument("Invalid quote mark.");
  }

  if (commentMark == delimitMark || commentMark == quoteMark || commentMark == '\r' || commentMark == '\n') {
    throw std::invalid_argument("Invalid comment mark.");
  }
}

} // namespace csv
} // namespace csl
