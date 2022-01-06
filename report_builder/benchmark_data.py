import typing as tp

ParameterValues = tp.Union[str, int, bool, float]
ContextValues = tp.Union[str, bool, float, int, tp.List, tp.Mapping]


class Parameter:
    def __init__(self, key: str, value: ParameterValues):
        self.key = key
        self.value = value

    def __eq__(self, other):
        return self.key == other.key and self.value == other.value

    def __ne__(self, other):
        return not self == other


class Benchmark:
    def __init__(self, parameters: tp.List[Parameter]):
        self.parameters = parameters


def append_tag_to_keys(benchmarks: tp.List[Benchmark], keys: tp.List[str], tag: str):
    for benchmark in benchmarks:
        for parameter in benchmark.parameters:
            if parameter.key in keys:
                parameter.value = str(parameter.value) + tag


def make_groups(benchmarks: tp.List[Benchmark], group_keys: tp.List[str]) -> tp.List[tp.List]:
    groups = dict()
    for benchmark in benchmarks:
        key = []
        for parameter in benchmark.parameters:
            if parameter.key not in group_keys:
                key.append((parameter.key, parameter.value))
        dict_key = tuple(key)
        if groups.get(dict_key) is None:
            groups[dict_key] = []

        groups[dict_key].append(benchmark)

    result = []

    for key, value in groups.items():
        result.append(value)

    return result


def collapse_contexts(contexts: tp.List[tp.Mapping[str, ContextValues]],
                      skip_keys: tp.Optional[tp.List[str]] = None) -> tp.Dict[str, ContextValues]:
    skip_keys = [] if skip_keys is None else skip_keys
    result = {}

    for context in contexts:
        for key, value in context.items():
            if key in skip_keys:
                continue
            if not result.get(key):
                result[key] = []
            if value not in result[key]:
                result[key].append(value)

    for key, value in result.items():
        if len(value) == 1:
            result[key] = result[key][0]

    return result
