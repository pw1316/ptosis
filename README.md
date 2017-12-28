# ptosis

Parse blink dynamics from a 240 FPS video

## 引用规则

### LBF 引用规则

按如下顺序引用

1. 同名头文件 `foo.h` (只针对源代码文件`foo.c foo.cpp`，头文件则不存在该项)
1. OpenCV `opencv2/opencv.hpp` (关闭4819警告)
1. 标准库 e.g. `iostream` (不使用`using namespace xxx;`，命名空间一律显示指定)
1. 项目中其它头文件 `bar.h`

对于上述每一类，按字典序排列

### QTLBF 引用规则

按如下顺序引用

1. 同名头文件 `foo.h` (只针对源代码文件`foo.c foo.cpp`，头文件则不存在该项)
1. lbf库 `lbf.h` (不在该项目中引用opencv与struct，需要的地方一律引用lbf)
1. Qt头文件 e.g. `QtCore/QObject` (不要直接引用`.h`)
1. 标准库 e.g. `iostream` (不使用`using namespace xxx;`，命名空间一律显示指定)
1. 项目中其它头文件 `bar.h`

对于上述每一类，按字典序排列

## 曲线处理规则

1. 从QTLBF程序中截取一个眨眼周期`[frameI, frameJ]`，归一化`X`从`0`开始，`Y`最小要到`0`
1. 这个曲线包含8个参数`(Pmax, Pmin, Pswitch, t1, t2, t3, t4, alpha)`
1. 分段拟合(Mathematica)
1. `y = Pmax , x < t1`
1. `y = -(Pmax - Pmin) / (t2 - t1) * (x - t2) + Pmin, t2 > x > t1`
1. `y = Pmin, t3 > x > t2`
1. `y = (Pswitch - Pmin) / (t4 - t3) * (x - t3) + Pmin, t4 > x > t3`
1. `y = Pswitch + (Pmax - Pswitch) * Tanh[alpha(x - t4)], x > t4`
1. 参数初始值要调，`P`和`alpha`可以硬编码，四个`t`要动态设定
1. `v1 = 1 / (t2 - t1)`
1. `v2 = (Pswitch - Pmin) / (Pmax - Pmin) / (t2 - t1)`
1. `alpha = alpha`
1. `delay = (Pmax + Pmin) * (t4 - t3) / 2 / (Pswitch - Pmin) + t3 - (t2 + t1) / 2`
1. `t4 - topen = t4 - (Pmax + Pmin) * (t4 - t3) / 2 / (Pswitch - Pmin) - t3`
1. 分类
