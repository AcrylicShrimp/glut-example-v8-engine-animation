# Glut Example - V8 Engine Animation

This project is for a final test from my univ.

![result](result.gif)

## How to build

### macOS

Make `clang++` available first.

You need `freeglut` and `xquartz` to build. To install them through `homebrew`, issue below.

```bash
$ brew cask install xquartz
$ brew install freeglut

$ export DISPLAY=:0.0
```

Clone this repository and run `compile.sh`.

```bash
$ ./compile.sh
```

> **NOTE**: If the version of your `freeglut` is not `3.2.1`, edit the `compile.sh` correctly and try again.
