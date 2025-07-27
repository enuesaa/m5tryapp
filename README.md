# m5tryapp

M5Stack Cores3 で何か色々するリポジトリ

[![ci](https://github.com/enuesaa/m5tryapp/actions/workflows/ci.yml/badge.svg)](https://github.com/enuesaa/m5tryapp/actions/workflows/ci.yml)

## 開発方法
VS Code に [PlatformIO extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) を入れて開発する

### ステップ
1. VS Code に [PlatformIO extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) をインストールする
2. VS Code でこのリポジトリを開く  
  ---> PlatformIO が立ち上がるはず
3. M5Stack Cores3 を PC に USB 接続する
4. PlatformIO の「Upload」ボタンを押す  
  <img src="./docs/upload.png" width="500px" />  
  ---> ビルド & アップロードできるはず


## ライブラリ
### M5Unified

M5Stack の機種によってライブラリが異なっていたがそれを統一したもの、、と理解。

- https://speakerdeck.com/lovyan03/m5unifiednoshao-jie
- https://lang-ship.com/blog/work/m5unified-1/

## コマンド
### test
```bash
pio test -vvv
```

### format
```bash
clang-format -i src/**/*.{cpp,hpp}
```
