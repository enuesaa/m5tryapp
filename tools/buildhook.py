import os
import shutil

"""
ビルドフック

定数の宣言ファイルを gitignore しており、そのままだとビルドできないため、ビルド前にコピーする
"""
src = 'src/env/vars.example.hpp'
dst = 'src/env/vars.hpp'

if not os.path.exists(dst):
    print(f"Copying {src} to {dst}")
    shutil.copy(src, dst)
