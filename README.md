# m5tryapp

M5Stack Cores3 で何か色々するリポジトリ

## 開発方法
VS Code に PlatformIO extension を入れて開発する

### 開発ステップ
1. VS Code に PlatformIO extension をインストールする
2. VS Code でこのリポジトリを開く  
  ---> PlatformIO が立ち上がるはず
3. M5Stack Cores3 を PC に USB 接続する
4. PlatformIO のアップロードボタンを押す  
  ---> ビルド & アップロードできるはず


## ライブラリ
### M5Unified

M5Stack の機種によってライブラリが異なっていたがそれを統一したもの、、と理解。

- https://speakerdeck.com/lovyan03/m5unifiednoshao-jie
- https://lang-ship.com/blog/work/m5unified-1/

## コマンド
### format
```bash
clang-format -i src/**/*.{cpp,hpp}
```
