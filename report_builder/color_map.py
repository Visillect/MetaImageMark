import typing as tp

ColorMap = tp.Callable[[float], tp.Tuple[int, int, int]]


class LinearSegmentedColormap:
    def __init__(self, values: tp.List[tp.Tuple[int, int, int]]):
        self._values = values

    def __call__(self, value: float) -> tp.Tuple[int, int, int]:
        if value == 1.:
            return self._values[-1]

        index = int(value * (len(self._values) - 1))
        r_begin, g_begin, b_begin = self._values[index]
        r_end, g_end, b_end = self._values[index + 1]

        begin = index / (len(self._values) - 1)
        end = (index + 1) / (len(self._values) - 1)

        position = (value - begin) / (end - begin)

        return (round(r_begin + position * (r_end - r_begin)),
                round(g_begin + position * (g_end - g_begin)),
                round(b_begin + position * (b_end - b_begin)))


def read_float_color_map(file: str, inverse: bool = False) -> LinearSegmentedColormap:
    with open(file) as f:
        rgb = []
        for line in f.readlines():
            r, g, b = line.split(" ")
            r, g, b = round(255 * float(r)), round(255 * float(g)), round(255 * float(b))
            rgb.append((r, g, b))
        if inverse:
            rgb = rgb[::-1]
        return LinearSegmentedColormap(rgb)
