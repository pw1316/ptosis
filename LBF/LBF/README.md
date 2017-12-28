# Align

```C++
#include "align.h"
#include <string>

void foo()
{
    std::string fn; // path to model.bin
    Mat img; // uchar8 image
    Vec4d bb; // [center_x, center_y, half_width, half_height]

    Align align(fn);

    Mat shape = align.predict(img, bb);
}
```
