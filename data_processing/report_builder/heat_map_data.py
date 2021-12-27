import math
import typing as tp
from bisect import bisect_left
from warnings import warn

from .benchmark_data import make_groups
from .benchmark_parser import ParameterValues, Parameter, Benchmark
from .support import nan_filled


class HeatMapData(Benchmark):
    def __init__(self,
                 values: tp.List[float],
                 x_labels: tp.List[ParameterValues],
                 y_labels: tp.List[ParameterValues],
                 x_title: str,
                 y_title: str,
                 measure_title: str,
                 parameters: tp.List[Parameter],
                 errors: tp.Optional[tp.List[ParameterValues]] = None):
        Benchmark.__init__(self, parameters)
        self.values = values
        self.x_labels = x_labels
        self.y_labels = y_labels
        self.x_title = x_title
        self.y_title = y_title
        self.measure_title = measure_title
        self.errors = errors


def _get_benchmark_heat_map_point(benchmark: Benchmark, measure_key: str, width_key: str, height_key: str,
                                  error_key: tp.Optional[str] = None) \
        -> tp.Optional[tp.Tuple[float, ParameterValues, ParameterValues]]:
    measure_value = None
    x_label = None
    y_label = None
    for parameter in benchmark.parameters:
        if parameter.key == width_key:
            x_label = parameter.value
        elif parameter.key == height_key:
            y_label = parameter.value
        elif parameter.key == measure_key and measure_value is None:
            measure_value = parameter.value
        elif parameter.key == error_key:
            measure_value = math.nan

    if measure_value is None:
        measure_value = math.nan

    if x_label is None or y_label is None:
        warn("some values (width, height) are absent, benchmark is skipped")
        return None

    if not isinstance(measure_value, float) and not isinstance(measure_value, int):
        warn("only float or integer values are allowed as measures, benchmark is skipped")
        return None

    return float(measure_value), x_label, y_label


def _get_values_table(data: tp.List[tp.Tuple[float, ParameterValues, ParameterValues]],
                      widths: tp.List[ParameterValues],
                      heights: tp.List[ParameterValues],
                      aggregate_function: tp.Callable[[tp.List[float]], float]) \
        -> tp.List[float]:
    table: tp.List[tp.List[float]] = []
    for i in range(len(widths) * len(heights)):
        table.append([])

    for measure, width, height in data:
        width_index = bisect_left(widths, width)
        height_index = bisect_left(heights, height)
        table[width_index + height_index * len(widths)].append(measure)

    result = [math.nan] * (len(heights) * len(widths))
    for i in range(len(table)):
        if len(table[i]) > 0:
            result[i] = aggregate_function(table[i])

    return result


def _has_same_values(data: HeatMapData, keys_values: tp.List[Parameter]) -> bool:
    for parameter in keys_values:
        if parameter not in data.parameters:
            return False
    return True


def _is_comparable(first: HeatMapData, second: HeatMapData) -> bool:
    if first.x_labels != second.x_labels or \
            first.y_labels != second.y_labels or \
            first.x_title != second.x_title or \
            first.y_title != second.y_title or \
            first.measure_title != second.measure_title:
        return False
    return True


def generate_heat_map_data(benchmarks: tp.List[Benchmark],
                           measure_key: str,
                           width_key: str,
                           height_key: str,
                           aggregate_function: tp.Callable[[tp.List[float]], float] = min,
                           error_key: tp.Optional[str] = None) -> tp.List[HeatMapData]:
    groups = make_groups(benchmarks, [measure_key, width_key, height_key, error_key])

    result = []

    for group in groups:
        parameters = []
        errors = []
        data = []

        for parameter in group[0].parameters:
            if parameter.key not in {width_key, height_key, measure_key, error_key}:
                parameters.append(parameter)

        for benchmark in group:
            for parameter in benchmark.parameters:
                if parameter.key == error_key and parameter.value not in errors:
                    errors.append(parameter.value)

        for benchmark in group:
            point = _get_benchmark_heat_map_point(benchmark, measure_key, width_key, height_key, error_key)
            if point is not None:
                data.append(point)

        widths = sorted(list({w for m, w, h in data}))
        heights = sorted(list({h for m, w, h in data}))

        if not widths or not heights:
            continue

        table = _get_values_table(data, widths, heights, aggregate_function)
        result.append(HeatMapData(table, widths, heights, width_key, height_key, measure_key, parameters, errors))

    return result


def _find_compare_data(heat_map_data: tp.List[HeatMapData],
                       group_keys_values: tp.List[Parameter],
                       compare_first: bool = False) -> tp.Optional[HeatMapData]:
    compare_data = None
    for data in heat_map_data:
        if _has_same_values(data, group_keys_values):
            compare_data = data
            break
    if compare_data is None and not compare_first or not heat_map_data:
        return None
    return heat_map_data[0] if not compare_data else compare_data


def generate_comparison_heat_map_data(heat_map_data: tp.List[HeatMapData],
                                      group_keys_values: tp.List[Parameter],
                                      operation=lambda f, s: f / s,
                                      value_transform=lambda f, s: str(f) + "/" + str(s),
                                      force_compare: bool = False) -> tp.List[HeatMapData]:
    compare_data = _find_compare_data(heat_map_data, group_keys_values, force_compare)
    if not compare_data:
        return []

    keys = {parameter.key for parameter in group_keys_values}
    group_keys_values = {parameter.key: parameter.value for parameter in compare_data.parameters}

    result = []
    for data in heat_map_data:
        if data == compare_data:
            continue
        if not _is_comparable(data, compare_data):
            warn("some graphs are incompatible for comparison")
            continue

        values = [operation(data.values[i], compare_data.values[i]) for i in range(len(data.values))]

        if nan_filled(values):
            continue

        parameters = []
        for parameter in data.parameters:
            if parameter.key not in keys:
                parameters.append(parameter)
            else:
                transformed = value_transform(parameter.value, group_keys_values[parameter.key])
                parameters.append(Parameter(parameter.key, transformed))

        result.append(HeatMapData(values, data.x_labels, data.y_labels, data.x_title, data.y_title, "", parameters))

    return result
