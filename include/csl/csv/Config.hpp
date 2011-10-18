/**
 * @file  Config.hpp
 * @brief Configクラスヘッダーファイル
 */
#ifndef CSL_CSV_CONFIG_HPP_
#define CSL_CSV_CONFIG_HPP_

namespace csl {
namespace csv {

/**
 * @brief 区切り文字、囲み文字、コメント文字などのCSV形式に関する設定の情報を管理します。
 */
class Config
{
public:
  Config(void);
  Config(const char delimitMark);
  Config(const char delimitMark,
	 const bool quoteEnabled, const char quoteMark);
  Config(const char delimitMark,
	 const bool quoteEnabled, const char quoteMark,
	 const bool commentEnabled, const char commentMark);
  
public:
  virtual ~Config(void);
      
public:
  char getDelimitMark(void) const;
  void setDelimitMark(const char delimiter);
  bool getQuoteEnabled(void) const;
  void setQuoteEnabled(const bool quoteEnabled);
  char getQuoteMark(void) const;
  void setQuoteMark(const char quoteMark);
  bool getCommentEnabled(void) const;
  void setCommentEnabled(const bool commentEnabled);
  char getCommentMark(void) const;
  void setCommentMark(const char commentMark);
      
private:
  void validate(void) const;
      
private:
  char delimitMark;
  bool quoteEnabled;
  char quoteMark;
  bool commentEnabled;
  char commentMark;
  
private:
  Config(const Config& config);
  Config& operator=(const Config& config);
};

/**
 * @brief デフォルトのConfigオブジェクトです。
 */
static const Config DEFAULT_CONFIG;

/**
 * @brief デフォルトの区切り文字です。
 */
static const char DEFAULT_DELIMIT_MARK = ',';

/**
 * @brief デフォルトの囲み文字を有効にするかどうかです。
 */
static const bool DEFAULT_QUOTE_ENABLED = true;

/**
 * @brief デフォルトの囲み文字です。
 */
static const char DEFAULT_QUOTE_MARK = '"';

/**
 * @brief デフォルトのコメント文字を有効にするかどうかです。
 */
static const bool DEFAULT_COMMENT_ENABLED = false;

/**
 * @brief デフォルトのコメント文字です。
 */
static const char DEFAULT_COMMENT_MARK = '#';

} // namespace csv
} // namespace csl

#endif // #ifndef CSL_CSV_CONFIG_HPP_
