import math
import typing as tp
from collections.abc import Iterable


def _nanaggr(values: Iterable, aggregation: tp.Callable[[float, float], float]) -> float:
    result = math.nan
    for value in values:
        if math.isnan(value):
            continue
        if math.isnan(result):
            result = value
        result = aggregation(result, value)
    return result


def nanmin(values: Iterable) -> float:
    return _nanaggr(values, min)


def nanmax(values: Iterable) -> float:
    return _nanaggr(values, max)


def contains_nan(values: tp.List[float]) -> bool:
    for val in values:
        if math.isnan(val):
            return True
    return False


def nan_filled(data: tp.List[float]) -> bool:
    for val in data:
        if not math.isnan(val):
            return False
    return True


def isfloat(value: str) -> bool:
    try:
        float(value)
        return True
    except ValueError:
        return False
