/**
 * @file  Config.hpp
 * @brief Configクラスヘッダーファイル
 */
#ifndef CSL_CSV_CONFIG_HPP_
#define CSL_CSV_CONFIG_HPP_

#include <cstddef>

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
  size_t getMaxFieldSize(void) const;
  void setMaxFieldSize(size_t size);
  size_t getMaxRecordSize(void) const;
  void setMaxRecordSize(size_t size);
  size_t getMaxRecords(void) const;
  void setMaxRecords(size_t count);

private:
  void validate(void) const;
      
private:
  char delimitMark;
  bool quoteEnabled;
  char quoteMark;
  bool commentEnabled;
  char commentMark;
  size_t maxFieldSize;   // 0 = unlimited
  size_t maxRecordSize;  // 0 = unlimited
  size_t maxRecords;     // 0 = unlimited

private:
  Config(const Config& config);
  Config& operator=(const Config& config);
};

/**
 * @brief デフォルトのConfigオブジェクトです。
 */
extern const Config DEFAULT_CONFIG;

/**
 * @brief デフォルトの区切り文字です。
 */
constexpr char DEFAULT_DELIMIT_MARK = ',';

/**
 * @brief デフォルトの囲み文字を有効にするかどうかです。
 */
constexpr bool DEFAULT_QUOTE_ENABLED = true;

/**
 * @brief デフォルトの囲み文字です。
 */
constexpr char DEFAULT_QUOTE_MARK = '"';

/**
 * @brief デフォルトのコメント文字を有効にするかどうかです。
 */
constexpr bool DEFAULT_COMMENT_ENABLED = false;

/**
 * @brief デフォルトのコメント文字です。
 */
constexpr char DEFAULT_COMMENT_MARK = '#';

} // namespace csv
} // namespace csl

#endif // #ifndef CSL_CSV_CONFIG_HPP_
