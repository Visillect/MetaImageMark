# MetaImageMark

A framework to benchmark Image Processing Libraries.

## Application areas

The framework can be used for various tasks, including:

1. Image processing code optimization.
2. Performance comparison of various image processing libraries.
3. Investigation of the dependence of the speed of operations depending on the compilation parameters and/or hardware.

MetaImageMark has been successfully used to identify weaknesses of MinImg image processing library and in its further
optimization.

## Running benchmarks



## Supported Libraries

### OpenCV

### MinImg

## Report builder

## Noise suppression

Detailed information about the factors affecting noise is
described [here](https://github.com/JuliaCI/BenchmarkTools.jl/blob/master/docs/src/linuxtips.md).

### Processor shielding

```bash
$ sudo apt-get install cpuset
$ sudo cset shield --cpu=0,1 --kthread=on
$ sudo cset shield --exec -- mybench --params
$ sudo cset shield --reset
```

### CPU frequency scaling

```bash
$ sudo cpupower frequency-set --governor performance
$ ./mybench
$ sudo cpupower frequency-set --governor powersave
```

## Project design

### Levels of abstractions
