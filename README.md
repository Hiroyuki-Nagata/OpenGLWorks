#  OpenGLWorks - some examples of OpenGL
OpenGLによる入門用のプログラムを個人的にautoconfでまとめたものです 
  
## AppVeyor  
[![Build status](https://ci.appveyor.com/api/projects/status/y0tox6cexrfp0kp4?svg=true)](https://ci.appveyor.com/project/Hiroyuki-Nagata/OpenGLWorks)  
  
## Travis CI  
[![Build Status](https://travis-ci.org/Hiroyuki-Nagata/OpenGLWorks.svg?branch=master)](https://travis-ci.org/Hiroyuki-Nagata/OpenGLWorks)  
  
## Reference:
  [OpenGLによる3次元CGプログラミング](http://www.res.kutc.kansai-u.ac.jp/~hayashi/cg3d/)  
  [CygwinでOpenGL/Glutを使う方法](http://www.pitecan.com/info/winglut.html)  
  [OpenGL Vertex Array](http://www.songho.ca/opengl/gl_vertexarray.html)  
  [メッシュを読み込む！！(2)　～Xファイル～](http://asura.iaigiri.com/OpenGL/gl44.html)  
  
### glBegin/glEndで実行される基本的なOpenGLプログラム
   * c1-1  
   * c1-2  
   * cube  
   * round  
   * oct  

### 頂点配列を使用したOpenGLプログラム
   * minimal  
   * vertex-array  
  
### .x形式のファイル読み込み  
   * xmesh  
  
```
  個人的にこれらはpmd形式ファイルの読み込みの学習につながると思っています  
```
  
## 環境
   * WindowsならばMinGW/CygwinのようなUNIX環境とautotoolsが必要です
   * Linux/Mac OS Xについても同様
   * 上記に加えてOpenGL/freeglutが必要です
  
## ビルド
  $ ./bootstrap  
  $ ./configure  
  $ make  
