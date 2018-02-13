### libcalc

> A very basic math expressions(infix) evaluator

[![Build Status](https://travis-ci.org/b37t1td/libcalc.svg?branch=master)](https://travis-ci.org/b37t1td/libcalc)

This library built using basic `RPN` algorithm and intended to evaluate `infix` math expressions.
In simple words it evaluates expressions like this: 

```
( 5 - 3 ) * 2
```

into

```
4
```

### Installation

```
  git clone git@github.com:b37t1td/libcalc.git
  cd libcalc
  take build
  cmake ..
  cpack
  sudo dpkg -i libcalc_*.deb

```

### Usage

Example of `test.cxx`

```c++
#include <iostream>
#include <libcalc.hpp>

int main() {
  std::cout << libcalc::eval("2 * ( 5 - 3 )") << std::endl;
}
```

Which we build with:

```
g++ -std=c++11 -Wall test.cxx `pkg-config --libs --cflags libcalc`
```

So, run it `./a.out` and you will see `4`.

### License

MIT

