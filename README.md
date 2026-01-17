# cslcsv

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

**cslcsv** は、C++でCSVファイルの読み書きを行うためのシンプルなライブラリです。

## 📚 このライブラリについて

このライブラリは**学習目的**で作成されています。C++初心者の方が、以下のようなことを学ぶのに適しています：

- CSVパーサーの仕組み
- C++のストリーム入出力
- クラス設計の基礎
- テスト駆動開発（TDD）
- ライブラリの使い方

プロダクション環境での使用も可能ですが、より高機能なライブラリが必要な場合は他の選択肢も検討してください。

## ✨ 特徴

- **シンプルなAPI** - わかりやすいインターフェース
- **カスタマイズ可能** - 区切り文字、囲み文字、コメント文字を設定可能
- **ヘッダーオンリーではない** - ソースコードを読んで学習しやすい
- **テスト付き** - CppUnitによる単体テストが含まれています
- **ドキュメント付き** - Doxygenによるドキュメントが生成できます

## 🔧 必要な環境

### コンパイラ
- **g++** 4.8以降
- **clang++** 3.4以降
- または互換性のあるC++コンパイラ

### ビルドツール
- **make** (GNU Make)
- **ar** (アーカイバ)
- **ranlib**

### テスト実行（オプション）
- **CppUnit** 1.12以降

### ドキュメント生成（オプション）
- **Doxygen** 1.7以降

## 📦 インストール/ビルド方法

### 1. リポジトリのクローン

```bash
git clone https://github.com/yourusername/cslcsv.git
cd cslcsv
```

### 2. ライブラリのビルド

```bash
# ビルドに必要なディレクトリを作成
mkdir -p lib bin obj

# ライブラリをビルド
make all
```

これにより、以下のファイルが生成されます：
- `lib/libcslcsv.a` - 静的ライブラリ
- `lib/libcslcsv.so` - 共有ライブラリ

### 3. テストの実行（オプション）

CppUnitがインストールされている場合：

```bash
make test
```

### 4. クリーンアップ

```bash
make clean
```

## 🚀 使い方

### 基本的な使用例

#### CSVファイルの読み込み

```cpp
#include "csl/csv/Util.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    // CSVデータを格納する2次元配列
    std::vector<std::vector<std::string>> csv;

    try {
        // CSVファイルを読み込む
        csl::csv::Util::load("data.csv", csv);

        // データを表示
        for (size_t i = 0; i < csv.size(); i++) {
            for (size_t j = 0; j < csv[i].size(); j++) {
                std::cout << csv[i][j];
                if (j < csv[i].size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "エラー: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

#### CSVファイルの書き込み

```cpp
#include "csl/csv/Util.hpp"
#include <vector>
#include <string>

int main() {
    // CSVデータを準備
    std::vector<std::vector<std::string>> csv;

    // 1行目
    std::vector<std::string> row1;
    row1.push_back("名前");
    row1.push_back("年齢");
    row1.push_back("職業");
    csv.push_back(row1);

    // 2行目
    std::vector<std::string> row2;
    row2.push_back("山田太郎");
    row2.push_back("30");
    row2.push_back("エンジニア");
    csv.push_back(row2);

    try {
        // CSVファイルに書き込む
        csl::csv::Util::save("output.csv", csv);
        std::cout << "CSVファイルを保存しました" << std::endl;
    } catch (std::exception& e) {
        std::cerr << "エラー: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

### 詳細な制御（Readerクラスを使用）

```cpp
#include "csl/csv/Reader.hpp"
#include "csl/csv/Config.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ファイルを開く
    std::ifstream file("data.csv", std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "ファイルを開けません" << std::endl;
        return 1;
    }

    // 設定をカスタマイズ（タブ区切り）
    csl::csv::Config config('\t');  // タブを区切り文字に

    // Readerを作成
    csl::csv::Reader reader(file, config);

    // 1行ずつ読み込む
    std::vector<std::string> record;
    while (reader.hasNext()) {
        reader.read(record);

        // レコードを処理
        for (size_t i = 0; i < record.size(); i++) {
            std::cout << "[" << record[i] << "] ";
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}
```

### 詳細な制御（Writerクラスを使用）

```cpp
#include "csl/csv/Writer.hpp"
#include "csl/csv/Config.hpp"
#include <fstream>
#include <vector>
#include <string>

int main() {
    // ファイルを開く
    std::ofstream file("output.csv", std::ofstream::binary);
    if (!file.is_open()) {
        std::cerr << "ファイルを開けません" << std::endl;
        return 1;
    }

    // 設定をカスタマイズ（クォートを無効化）
    csl::csv::Config config;
    config.setQuoteEnabled(false);

    // Writerを作成
    csl::csv::Writer writer(file, config);

    // データを書き込む
    std::vector<std::string> record;
    record.push_back("データ1");
    record.push_back("データ2");
    record.push_back("データ3");

    writer.write(record);

    file.close();
    return 0;
}
```

### コンパイル方法

```bash
# 静的ライブラリを使用
g++ -O2 -Wall -Iinclude -o myprogram myprogram.cpp -Llib -lcslcsv

# 共有ライブラリを使用
g++ -O2 -Wall -Iinclude -o myprogram myprogram.cpp -Llib -lcslcsv
```

## 📖 API概要

### Utilクラス（簡単に使える）

静的メソッドでCSVファイルの読み書きができます。

```cpp
// ファイルから読み込み
void load(const std::string& filepath,
          std::vector<std::vector<std::string>>& csv);

void load(const std::string& filepath,
          const Config& config,
          std::vector<std::vector<std::string>>& csv);

// ファイルへ書き込み
void save(const std::string& filepath,
          std::vector<std::vector<std::string>>& csv);

void save(const std::string& filepath,
          const Config& config,
          std::vector<std::vector<std::string>>& csv);
```

### Readerクラス（詳細な制御）

ストリームから1行ずつCSVを読み込みます。

```cpp
Reader(std::istream& stream);
Reader(std::istream& stream, const Config& config);

bool hasNext();  // 次の行があるか
void read(std::vector<std::string>& record);  // 1行読み込む
```

### Writerクラス（詳細な制御）

ストリームへCSVを1行ずつ書き込みます。

```cpp
Writer(std::ostream& stream);
Writer(std::ostream& stream, const Config& config);

void write(std::vector<std::string>& record);  // 1行書き込む
```

### Configクラス（設定）

CSV形式の設定を管理します。

```cpp
Config();  // デフォルト設定
Config(char delimitMark);  // 区切り文字を指定
Config(char delimitMark, bool quoteEnabled, char quoteMark);
Config(char delimitMark, bool quoteEnabled, char quoteMark,
       bool commentEnabled, char commentMark);

// ゲッター/セッター
char getDelimitMark() const;
void setDelimitMark(char delimitMark);

bool getQuoteEnabled() const;
void setQuoteEnabled(bool quoteEnabled);

char getQuoteMark() const;
void setQuoteMark(char quoteMark);

bool getCommentEnabled() const;
void setCommentEnabled(bool commentEnabled);

char getCommentMark() const;
void setCommentMark(char commentMark);
```

### デフォルト設定

```cpp
区切り文字:     ','  (カンマ)
囲み文字:       '"'  (ダブルクォート)
囲み文字有効:   true
コメント文字:   '#'  (シャープ)
コメント有効:   false
```

## 🧪 テスト

このライブラリには、以下のテストが含まれています：

- `ConfigTest` - 設定クラスのテスト
- `ReaderTest` - 読み込み機能のテスト
- `WriterTest` - 書き込み機能のテスト
- `UtilTest` - ユーティリティクラスのテスト

テストを実行するには：

```bash
make test
```

## ❓ よくある質問

### Q: UTF-8のファイルを読み込めますか？

A: 基本的に読み込めますが、文字エンコーディングの検証は行っていません。バイナリモードでファイルを開くため、マルチバイト文字もそのまま扱えます。

### Q: 大きなCSVファイルを処理できますか？

A: ReaderクラスとWriterクラスを使用すれば、1行ずつ処理できるため、メモリに全体を読み込む必要はありません。ただし、非常に大きなファイルの場合はパフォーマンスに注意が必要です。

### Q: Excelで作成したCSVファイルを読み込めますか？

A: はい、Excelで作成した標準的なCSVファイル（カンマ区切り、ダブルクォート囲み）に対応しています。

### Q: 改行を含むフィールドは扱えますか？

A: はい、ダブルクォートで囲まれたフィールド内の改行は正しく処理されます。

### Q: エラーハンドリングはどうすればいいですか？

A: ファイル操作やパースエラーが発生すると `std::ios_base::failure` または `std::invalid_argument` 例外がスローされます。try-catchで捕捉してください。

## 🤝 コントリビューション

このプロジェクトへの貢献を歓迎します！

### 貢献方法

1. このリポジトリをフォーク
2. 機能ブランチを作成 (`git checkout -b feature/amazing-feature`)
3. 変更をコミット (`git commit -m 'Add some amazing feature'`)
4. ブランチにプッシュ (`git push origin feature/amazing-feature`)
5. プルリクエストを作成

### バグ報告や機能リクエスト

GitHubのIssuesでお気軽に報告してください。以下の情報があると助かります：

- 使用しているOS
- コンパイラのバージョン
- エラーメッセージ（該当する場合）
- 再現手順

## 📄 ライセンス

このプロジェクトはMITライセンスの下で公開されています。詳細は [LICENSE](LICENSE) ファイルをご覧ください。

## 💬 サポート

質問や問題がある場合は、以下の方法でお問い合わせください：

- **GitHub Issues**: バグ報告や機能リクエストはこちら
- **Discussions**: 一般的な質問や議論はこちら（有効にしている場合）

初心者の方からの質問も大歓迎です！わからないことがあれば、遠慮なくIssueを立ててください。

## 🔗 参考リンク

- [RFC 4180 - CSV形式の仕様](https://tools.ietf.org/html/rfc4180)
- [Doxygen公式サイト](https://www.doxygen.nl/)
- [CppUnit公式サイト](https://freedesktop.org/wiki/Software/cppunit/)

---

**Happy Coding! 🎉**
