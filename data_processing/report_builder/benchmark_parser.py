import typing as tp

from .support import isfloat
from .benchmark_data import Parameter, ParameterValues, Benchmark


def parse_value(value: str) -> ParameterValues:
    if value.isnumeric():
        value = int(value)
    elif isfloat(value):  # Remove isfloat
        value = float(value)
    return value


def _parse_field(parameter: Parameter,
                 parse_keys: tp.List[str]) -> tp.List[Parameter]:
    if not isinstance(parameter.value, str) or parameter.key not in parse_keys:
        return [parameter]

    result = []
    for pair in parameter.value.split("/"):
        pair = pair.split(":")
        if len(pair) == 1:
            continue
        elif len(pair) > 2:
            raise ValueError("invalid key/value pairs")

        result.append(Parameter(pair[0], parse_value(pair[1])))

    return result


def parse_benchmark(benchmark: tp.Mapping[str, ParameterValues],
                    required_key_values: tp.Dict[str, tp.List[ParameterValues]],
                    skip_keys: tp.List[str],
                    parse_keys: tp.List[str]) -> tp.Optional[Benchmark]:
    parameters = []
    for key, value in benchmark.items():
        if not isinstance(value, str) and not isinstance(value, int) and \
                not isinstance(value, bool) and not isinstance(value, float):
            raise ValueError("benchmark values have to be str, int, bool or float")
        parameters += _parse_field(Parameter(key, value), parse_keys)

    for parameter in parameters:
        if parameter.key in required_key_values and parameter.value not in required_key_values[parameter.key]:
            return None

    return Benchmark(list(filter(lambda p: p.key not in skip_keys, parameters)))


def parse_benchmarks(benchmarks: tp.List[tp.Mapping[str, ParameterValues]],
                     required_key_values: tp.Dict[str, tp.List[ParameterValues]],
                     skip_keys: tp.List[str],
                     parse_keys: tp.List[str]) -> tp.List[Benchmark]:
    parsed_benchmarks = []
    for benchmark in benchmarks:
        parsed_benchmark = parse_benchmark(benchmark, required_key_values, skip_keys, parse_keys)
        if parsed_benchmark is not None:
            parsed_benchmarks.append(parsed_benchmark)

    return parsed_benchmarks
