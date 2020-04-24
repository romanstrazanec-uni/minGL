# MinGL

Simple minimalistic C++ graphics library for Windows.

Compile with:

`g++ source_file.cpp -lminGL -lgdiplus`

## Examples

### Creating "Hello world" window

```C++
#include <mingl>

int main() {
    Window window("Hello world", 100, 100, 300, 300);

    window.addLabel("Hello world", 10, 10, 100, 30);

    return window.show();
}
```

## Compiler versions

- MSVC 19.16.27035.0
- GNU 9.3.0
