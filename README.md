# m5tryapp

M5Stack Cores3 で何か色々するリポジトリ

## 開発方法
VS Code に PlatformIO extension を入れて開発する。

### 開発ステップ
1. PlatformIO extension のインストール
2. VS Code でこのリポジトリを開いたら PlatformIO が立ち上がるはず
3. M5Stack Cores3 を PC に USB 接続する
4. ビルド & upload できるようになるはず

### M5Unified とは

M5Stack の機種によってライブラリが異なっていたがそれを統一したものと理解。

- https://speakerdeck.com/lovyan03/m5unifiednoshao-jie
- https://lang-ship.com/blog/work/m5unified-1/

### format
```bash
clang-format -i src/**/*.{cpp,hpp}
```
