/**
 * @file  Util.hpp
 * @brief Utilクラスヘッダーファイル
 */
#ifndef CSL_CSV_UTIL_HPP_
#define CSL_CSV_UTIL_HPP_

#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include "csl/csv/Config.hpp"

namespace csl {
namespace csv {

/**
 * @brief CSV形式ファイルの入出力ユーティリティーを提供します。
 */
class Util 
{
public:
  static void load(std::istream& stream,
		   std::vector<std::vector<std::string> >& csv);
  static void load(std::istream& stream,
		   const Config& config,
		   std::vector<std::vector<std::string> >& csv);
  static void load(const std::string& filepath,
		   std::vector<std::vector<std::string> >& csv);
  static void load(const std::string& filepath,
		   const Config& config,
		   std::vector<std::vector<std::string> >& csv);

  static void save(std::ostream& stream,
		   std::vector<std::vector<std::string> >& csv);
  static void save(std::ostream& stream,
		   const Config& config,
		   std::vector<std::vector<std::string> >& csv);
  static void save(const std::string& filepath,
		   std::vector<std::vector<std::string> >& csv);
  static void save(const std::string& filepath,
		   const Config& config,
		   std::vector<std::vector<std::string> >& csv);
  
private:
  Util(void);
  ~Util(void);
  Util(const Util& util);
  Util& operator=(const Util& util);
};

} // namespace csv
} // namespace csl

#endif // #ifndef CSL_CSV_UTIL_HPP_
