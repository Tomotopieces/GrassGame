# 拔草游戏

## 游戏方法
点击鼠标左键，开始拔草。

拔不掉的话请多点几次，因为模拟鼠标点击的地方写的不是很好，正在寻找改进的方法。

![拔草游戏](https://raw.githubusercontent.com/Tomotopieces/GrassGame/master/GrassGame.gif "拔草游戏")

## 更新

#### 2019.10.02

1. 0.2相比0.1添加了GrassGame类，把原来的GrassCursor类合并了；
2. 增加了胜利时的提示画面；
3. 现在鼠标的位置会出现灰色，具体效果看图；

#### 2019.10.03

1. 类名改变：GrassGame->GrassGameFunction；

#### 2019.10.04

1. 接着3号的，把代码逻辑整理了一遍；

#### 2019.10.09

1. 尝试了多线程；

	1. 将CursorStyle这个功能单独分了一个线程；

	2. 去掉了一些数据成员，改成了线程里的临时变量；