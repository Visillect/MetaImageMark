#!/usr/bin/env python3

import json
import argparse
import os
import typing as tp

from .benchmark_parser import parse_benchmarks, parse_value
from .benchmark_data import append_tag_to_keys, collapse_contexts
from .benchmark_data import Parameter, ParameterValues, ContextValues, Benchmark
from .color_map import read_float_color_map
from .heat_map_reporter import generate_heat_map_report

BAR_LABELS = {
    "bytes": [(1, '1 B/s'), (4, '4 B/s'), (16, '16 B/s'), (64, '64 B/s'), (256, '256 B/s'), (1024, '1 KiB/s'),
              (4096, '4 KiB/s'), (16384, '16 KiB/s'), (65536, '64 KiB/s'), (262144, '256 KiB/s'),
              (1048576, '1 MiB/s'), (4194304, '4 MiB/s'), (16777216, '16 MiB/s'), (67108864, '64 MiB/s'),
              (268435456, '256 MiB/s'), (1073741824, '1 GiB/s'), (4294967296, '4 GiB/s'),
              (17179869184, '16 GiB/s'), (68719476736, '64 GiB/s'), (274877906944, '256 GiB/s')],

    "time": [(1, '1ns'), (10, '10ns'), (100, '100ns'), (1000, '1us'), (10000, '10us'), (100000, '100us'),
             (1000000, '1ms'), (10000000, '10ms'), (100000000, '100ms'), (1000000000, '1s')],

    "coeff": [(0.0078125, '1/128'), (0.015625, '1/64'), (0.03125, '1/32'), (0.0625, '1/16'), (0.125, '1/8'),
              (0.25, '1/4'), (0.5, '1/2'), (1, '1'), (2, '2'), (4, '4'), (8, '8'), (16, '16'), (32, '32'),
              (64, '64'), (128, '128')]
}

REQUIRED_KEY_VALUES = {"run_type": ["iteration"]}
SKIP_KEYS = ["run_name", "run_type", "repetitions", "repetition_index", "threads", "iterations", "time_unit", "repeats",
             "min_time", "real_time", "error_occurred", "per_family_instance_index", "family_index"]
PARSE_KEYS = ["name"]

CONTEXT_SKIP_KEYS = ["date", "load_avg"]


def read_benchmark(filepath: str) \
        -> tp.Tuple[tp.Mapping[str, ContextValues], tp.List[tp.Mapping[str, ParameterValues]]]:
    with open(filepath, "r") as f:
        json_data = json.load(f)
        return json_data["context"], json_data["benchmarks"]


def prepare_benchmarks(paths: tp.List[str],
                       tags: tp.List[str],
                       required_key_values: tp.Dict[str, tp.List[ParameterValues]],
                       skip_keys: tp.List[str],
                       parse_keys: tp.List[str],
                       context_skip_keys: tp.List[str],
                       group_keys: tp.List[str]) -> tp.Tuple[tp.Dict[str, ContextValues], tp.List[Benchmark]]:
    contexts = []
    benchmarks = []
    for path, tag in zip(paths, tags):
        context, current_benchmarks = read_benchmark(path)
        contexts.append(context)
        current_benchmarks = parse_benchmarks(current_benchmarks,
                                              required_key_values,
                                              skip_keys,
                                              parse_keys)
        append_tag_to_keys(current_benchmarks, group_keys, tag)
        benchmarks += current_benchmarks

    return collapse_contexts(contexts, context_skip_keys), benchmarks


def get_group_keys_values(values: tp.Optional[tp.List[tp.List[str]]], tag: str = "") -> tp.List[Parameter]:
    if values is None:
        return [Parameter("lib", "MinImg" + tag)]
    result = []
    for key, value in values:
        result.append(Parameter(key, parse_value(value)))
    return result


def make_tag_from_filepath(filepath: str) -> str:
    return "_" + os.path.splitext(os.path.basename(filepath))[0]


def parse_args():
    arg_parser = argparse.ArgumentParser(description="ImgPrcBenchmark report generator")
    arg_parser.add_argument("json", nargs="*", type=str, help="input json files")
    arg_parser.add_argument("--filename-as-tag", type=str, nargs="+", help="add filename tag to group keys", default=[])
    arg_parser.add_argument("--tag-files", type=str, metavar=("TAG", "FILES"), nargs="+", action="append",
                            help="parse json files and add tag to group keys", default=[])
    arg_parser.add_argument("--width", type=str, help="set width key", default="img_w")
    arg_parser.add_argument("--height", type=str, help="set height key", default="img_h")
    arg_parser.add_argument("--not-equalize", action="store_true",
                            help="disable normalization of the color bar range for the entire group",
                            default=False)
    arg_parser.add_argument("-g", "--group", type=str, metavar=("KEY", "VALUE"), nargs=2, action="append",
                            help="set the group creation parameter "
                                 "(only the values of KEY will differ in the group, "
                                 "the VALUE will be used to search for benchmarks against which to compare)")
    arg_parser.add_argument("-s", "--skip", type=str, nargs="+", help="ignore specified keys",
                            default=[])
    arg_parser.add_argument("-c", "--context", type=str, metavar=("KEY", "VALUE"), nargs=2, action="append",
                            help="add key-value pair to context info", default=[])
    arg_parser.add_argument("-p", "--precision", type=int, help="set rate precision", default=2)
    arg_parser.add_argument("-o", "--output", type=str, help="output html filepath", required=True)
    arg_parser.add_argument("--disable-force-comparison", action="store_true", default=False,
                            help="disable forced comparison (comparison will be only with specified group keys values)")

    measure = arg_parser.add_mutually_exclusive_group(required=True)
    measure.add_argument("--bytes", action="store_true", default=False, help="make report for bytes/second")
    measure.add_argument("--time", action="store_true", default=False, help="make report for time")

    return arg_parser.parse_args()


def generate_report(args) -> str:
    measure_key = "cpu_time" if args.time else "bytes_per_second"

    dir_path = os.path.dirname(os.path.abspath(__file__))
    color_map = read_float_color_map(os.path.join(dir_path, "color_maps/cividis.rgb"))
    color_map_compare = read_float_color_map(os.path.join(dir_path, "./color_maps/RdYlGr.rgb"), args.bytes)

    skip_keys = SKIP_KEYS + ["bytes_per_second" if args.time else "cpu_time"] + args.skip

    paths = args.json + args.filename_as_tag
    tags = [""] * len(args.json) + [make_tag_from_filepath(path) for path in args.filename_as_tag]

    for tagged in args.tag_files:
        tags += tagged[:1] * (len(tagged) - 1)
        paths += tagged[1:]

    group_parameters = get_group_keys_values(args.group, tags[0] if tags else "")
    group_keys = [parameter.key for parameter in group_parameters]

    contexts, benchmarks = prepare_benchmarks(paths,
                                              tags,
                                              REQUIRED_KEY_VALUES,
                                              skip_keys,
                                              PARSE_KEYS,
                                              CONTEXT_SKIP_KEYS,
                                              group_keys)

    for key, value in args.context:
        contexts[key] = value

    report = generate_heat_map_report(benchmarks,
                                      measure_key, args.width, args.height,
                                      color_bar_labels=BAR_LABELS["bytes" if args.bytes else "time"],
                                      color_map=color_map,
                                      log_scale=True,
                                      equalize_group_bars=not args.not_equalize,
                                      aggregate_function=min if args.time else max,
                                      group_keys_values=group_parameters,
                                      comparison_color_bar_labels=BAR_LABELS["coeff"],
                                      comparison_color_map=color_map_compare,
                                      comparison_operation=lambda f, s: f / s,
                                      comparison_value_transform=lambda f, s: str(f) + "/" + str(s),
                                      comparison_log_scale=True,
                                      comparison_middle_value=1.,
                                      force_compare=not args.disable_force_comparison,
                                      error_key="error_message",
                                      rate_min_value=1 / 4,
                                      rate_max_value=4.,
                                      rate_precision=args.precision,
                                      context=contexts)

    return report


def main():
    args = parse_args()
    with open(args.output, "w") as f:
        f.write(generate_report(args))


if __name__ == "__main__":
    main()
