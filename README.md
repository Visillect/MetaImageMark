# MetaImageMark

A framework to benchmark Image Processing Libraries.

Example of benchmark [report](reports).

## Application areas

The framework can be used for various tasks, including:

1. Image processing code optimization.
2. Performance comparison of various image processing libraries.
3. Investigation of the dependence of the speed of operations depending on the compilation parameters and/or hardware.

MetaImageMark has been successfully used to identify weaknesses of MinImg image processing library and in its further
optimization.

## Running benchmarks

### Building cmake project

To run benchmarks, you need to build a cmake project. The project depends on google/benchmark. There are two ways to get
a dependency: allow cmake to download it itself (option `-DDOWNLOAD_DEPENDENCIES=ON`), or specify the path to the
benchmark (`-Dbencharm_DIR=/path/to/benchmarkConfig.cmake` if benchmark is not installed in the system).

To run the benchmark of the selected library, you have to specify the path to this library.

#### OpenCV

If OpenCV is not installed in your system, specify

`-DOpenCV_DIR=/path/to/OpenCVConfig.cmake`

#### MinImg

To run MinImg benchmarks you have to specify the following varibales:

```
-DENABLE_MINIMG_BENCHMARK=ON
-DMINBASE_INCLUDE_DIR=/path/to/include
-DMINIMGAPI_INCLUDE_DIR=/path/to/include
-DMINIMGPRC_INCLUDE_DIR=/path/to/include
-DMINBASE_LIBRARY=/path/to/libminbase.so
-DMINIMGAPI_LIBRARY=/path/to/libminimgapi.so
-DMINIMGPRC_LIBRARY=/path/to/libminimgprc.so
```

### Running benchmarks

Before starting, read the [section](#noise-suppression) about noise suppression.

The executable files of the corresponding libraries will be located in the directory `library_benchmark`. Run the
desired benchmark using the command:

`./bench_library_operation --behnmark_out=out.json`.

### Building a report

A python program is used to build the report. Usage example:

```python3 -m report_builder build/minimg.json build/opencv.json --time -o transpose.html```

## Available benchmarks

| Operation           | Benchmark Name | MinImg | OpenCv | 
|---------------------|----------------|:------:|:------:|
| im = im1 + im2      | BinarySum      |   +    |    +   |
| im = im1 - im2      | BinaryDiff     |   +    |    +   |
| im = abs(im1 - im2) | BinaryADF      |   +    |    +   |
| im = im1 * im2      | BinaryMult     |   +    |    +   |
| im = im1 ^ im2      | BinaryPow      |   +    |    -   |

| Operation    | MinImg | OpenCv | 
|--------------|:------:|:------:|
| BoxFilter    |   +    |   +    |
| GaussFilter  |   +    |   +    |
| Transpose    |   +    |   +    |
| Downscale    |   +    |   +    |
| LinTransform |   +    |   +    |
| Convert      |   +    |   +    |

## Report builder

To analyze the benchmark data, a report builder is used. It allows you to visualize benchmarking data and conduct a
comparative analysis of operations.

See usage examples [here](report_builder/README.md).

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
