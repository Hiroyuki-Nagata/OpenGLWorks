#  OpenGLWorks - some examples of OpenGL
OpenGLによる入門用のプログラムを個人的にaucoconfでまとめたものです 
  
## Reference:
  [OpenGLによる3次元CGプログラミング](http://www.res.kutc.kansai-u.ac.jp/~hayashi/cg3d/)  
  [CygwinでOpenGL/Glutを使う方法](http://www.pitecan.com/info/winglut.html)  
  [OpenGL Vertex Array](http://www.songho.ca/opengl/gl_vertexarray.html)  

### glBegin/glEndで実行される基本的なOpenGLプログラム
   c1-1  
   c1-2  
   cube  
   round  
   oct  

### 頂点配列を使用したOpenGLプログラム
   vertex-array  
  
## 環境
* WindowsならばMinGW/CygwinのようなUNIX環境とautotoolsが必要です
* Linux/Mac OS Xについても同様
* 上記に加えてOpenGL/GLUTが必要です
  
## ビルド
  $ ./bootstrap  
  $ ./configure  
  $ make  
