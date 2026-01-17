/**
 * @file  Util.cpp
 * @brief Utilクラス実装ファイル
 */
#include "csl/csv/Util.hpp"
#include <fstream>
#include "csl/csv/Reader.hpp"
#include "csl/csv/Writer.hpp"

namespace csl {
namespace csv {

/**
 * @brief デフォルトのConfigオブジェクトの設定に従って、指定された入力ストリームからCSVデータを読み込んで返します。
 * @param stream 入力ストリーム
 * @param csv CSVデータ
 * @exception std::ios_base::failure 入力ストリームにエラーが発生した場合
 */
void Util::load(std::istream& stream,
		std::vector<std::vector<std::string> >& csv)
{
  load(stream, DEFAULT_CONFIG, csv);
}

/**
 * @brief 指定されたConfigオブジェクトの設定に従って、指定された入力ストリームからCSVデータを読み込んで返します。
 * @param stream 入力ストリーム
 * @param config Configオブジェクト
 * @param csv CSVデータ
 * @exception std::ios_base::failure 入力ストリームにエラーが発生した場合
 */
void Util::load(std::istream& stream,
		const Config& config,
		std::vector<std::vector<std::string> >& csv)
{
  csv.clear();

  Reader reader(stream, config);
  std::vector<std::string> record;

  while (reader.hasNext()) {
    reader.read(record);
    csv.push_back(record);
    record.clear();
  }
}

/**
 * @brief デフォルトのConfigオブジェクトの設定に従って、指定されたファイルからCSVデータを読み込んで返します。
 * @param filepath ファイルパス
 * @param csv CSVデータ
 * @exception std::ios_base::failure 入力ストリームにエラーが発生した場合
 */
void Util::load(const std::string& filepath,
		std::vector<std::vector<std::string> >& csv)
{
  load(filepath, DEFAULT_CONFIG, csv);
}

/**
 * @brief 指定されたConfigオブジェクトの設定に従って、指定されたファイルからCSVデータを読み込んで返します。
 * @param filepath ファイルパス
 * @param config Configオブジェクト
 * @param csv CSVデータ
 * @exception std::ios_base::failure 入力ストリームにエラーが発生した場合
 */
void Util::load(const std::string& filepath,
		const Config& config,
		std::vector<std::vector<std::string> >& csv)
{
  std::ifstream stream(filepath.c_str(), std::ifstream::binary);

  if (!stream.is_open()) {
    throw std::ios_base::failure("Failed to open file for reading: " + filepath);
  }

  try {
    load(stream, config, csv);
  } catch (...) {
    stream.close();
    throw;
  }

  stream.close();
}

/**
 * @brief デフォルトのConfigオブジェクトの設定に従って、指定された出力ストリームにCSVデータを書き込みます。
 * @param stream 出力ストリーム
 * @param csv CSVデータ
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Util::save(std::ostream& stream,
		std::vector<std::vector<std::string> >& csv)
{
  save(stream, DEFAULT_CONFIG, csv);
}

/**
 * @brief 指定されたConfigオブジェクトの設定に従って、指定された出力ストリームにCSVデータを書き込みます。
 * @param stream 出力ストリーム
 * @param config Configオブジェクト
 * @param csv CSVデータ
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Util::save(std::ostream& stream,
		const Config& config,
		std::vector<std::vector<std::string> >& csv)
{
  Writer writer(stream, config);

  typedef std::vector<std::vector<std::string> >::iterator iterator;
  for (iterator i = csv.begin(); i != csv.end(); i++) {
    writer.write(*i);
  }
}

/**
 * @brief デフォルトのConfigオブジェクトの設定に従って、指定されたファイルにCSVデータを書き込みます。
 * @param filepath ファイルパス
 * @param csv CSVデータ
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Util::save(const std::string& filepath,
		std::vector<std::vector<std::string> >& csv)
{
  save(filepath, DEFAULT_CONFIG, csv);
}

/**
 * @brief 指定されたConfigオブジェクトの設定に従って、指定されたファイルにCSVデータを書き込みます。
 * @param filepath ファイルパス
 * @param config Configオブジェクト
 * @param csv CSVデータ
 * @exception std::ios_base::failure 出力ストリームにエラーが発生した場合
 */
void Util::save(const std::string& filepath,
		const Config& config,
		std::vector<std::vector<std::string> >& csv)
{
  std::ofstream stream(filepath.c_str(), std::ofstream::binary);

  if (!stream.is_open()) {
    throw std::ios_base::failure("Failed to open file for writing: " + filepath);
  }

  try {
    save(stream, config, csv);
  } catch (...) {
    stream.close();
    throw;
  }

  stream.close();
}

} // namespace csv
} // namespace csl
