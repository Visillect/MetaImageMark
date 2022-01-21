# MetaImageMark reporter

A report generator for benchmarks.

## Usage Examples

### Generating a report for time

```sh
$ python3 -m report_builder minimg.json opencv.json --time
```

### Generating a report for bytes/s

```sh
$ python3 -m report_builder minimg.json opencv.json --bytes
```

### Grouping plots by key without comparison

```sh
$ python3 -m report_builder minimg.json opencv.json -g ch "" --time
```

In one group there will be benchmarks that differ only in the values of the keys `ch`, the rest will be the same.

### Grouping plots by multiple keys without comparison

```sh
$ python3 -m report_builder minimg.json opencv.json -g ch "" -g op "" --time
```

In one group there will be benchmarks that differ only in the values of the keys `ch` and `op`, the rest will be the
same.

### Grouping plots by key with comparison

```sh
$ python3 -m report_builder minimg.json opencv.json -g lib "MinImg" --time
```

In one group there will be benchmarks that differ only in the values of
the `lib` field, and if there is a graph with the value `lib == MinImg` in the group, then comparison plots will be
plotted relative to this graph.

### Grouping plots by multiple keys with comparison

```sh
$ python3 -m report_builder minimg.json opencv.json -g lib "MinImg" -g ch 1 --time
```

In one group there will be benchmarks that differ only in the values of the `lib`
and `ch` fields, and if there is a graph in the group with the values `lib == MinImg` and `ch == 1`, then comparison
plots will be plotted relative to this graph.

### Using the file name as a tag

```sh
$ python3 -m report_builder *.json --time --filename-as-tag
```

A tag of this file will be added for all benchmarks from the same file. This option allows you to compare operations
compiled in different ways without having to change the source code or `json` file (for example comparison of `Release` and
`Debug` builds).

### Using arbitrary names for tags.

```sh
$ python3 -m report_builder --time --tag-files _DEBUG data1.json --tag-files _RELEASE data2.json
```
