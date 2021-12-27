import math
import typing as tp

from .color_map import ColorMap
from .support import nanmin, nanmax

# HTML templates

PLOT = """
<div class="plot">
  <table>
    <tr>
      <td>{y_title}</td>
      <td>{y_labels}</td>
      <td>{heat_map}</td>
    </tr>
    <tr>
      <td></td>
      <td></td>
      <td>{x_labels}</td>
    </tr>
    <tr>
      <td></td>
      <td></td>
      <td>{x_title}</td>
    </tr>
  </table>
  <table class="color-bar">
    <tr>
      {color_bar_gradient}
      {color_bar_labels}
    </tr>
    <tr>
      {color_bar_title}
    </tr>
  </table>
</div>
"""

HEAT_MAP = """<table class="heat-map">{}</table>"""
HEAT_MAP_ROW = """<tr>{}</tr>"""
HEAT_MAP_CELL = """<td style="background: rgb({}, {}, {});"></td>"""
HEAT_MAP_EMPTY_CELL = """<td class="empty"></td>"""

Y_TITLE = """<div class="y-title">{}</div>"""
X_TITLE = """<div class="x-title">{}</div>"""

Y_LABELS = """<table class="y-labels">{}</table>"""
Y_LABEL = """<tr><td>{}</td></tr>"""

X_LABELS = """<table class="x-labels"><tr>{}</tr></table>"""
X_LABEL = """<td><div>{}</div></td>"""

COLOR_BAR_GRADIENT = """<td class="color-bar-gradient" style="background: linear-gradient({});"></td>"""
COLOR_BAR_GRADIENT_POINT = """rgb({}, {}, {}) {}%"""

COLOR_BAR_LABELS = """<td class="color-bar-labels">{}</td>"""
COLOR_BAR_LABEL = """<div class="dummy">{label}</div><div style="bottom: {percents}%">{label}</div>"""

COLOR_BAR_TITLE = """<td class="color-bar-title" colspan="2">{}</td>"""

CSS = """
.heat-map, .y-labels, .x-labels {
  border-spacing: 0;
}

.heat-map td {
  width: 25px;
  height: 25px;
}

.y-labels td {
  height: 25px;
  text-align: right;
}

.x-labels td {
  width: 25px;
  vertical-align: top;
}

.color-bar {
  margin-left: 10px
}

.color-bar-gradient {
  width: 20px;
  min-width: 10px;
  height: 300px;
}

.color-bar-labels {
  position: relative;
}

.y-title {
  writing-mode: vertical-rl;
  transform-origin: 50% 50%;
  transform: rotate(180deg);
  
  font-weight: bold;
}

.x-title {
  text-align: center;
  font-weight: bold;
}

.color-bar-title {
  font-weight: bold;
  padding-top: 5px;
}

.x-labels div {
  writing-mode: vertical-rl;
  text-align: right;

  margin: auto;

  transform-origin: 50% 50%;
  transform: rotate(180deg);
}

.color-bar-labels div[style] {
  position: absolute;
  transform: translateY(50%);
}

.dummy {
  visibility: hidden;
  height: 0;
}

.plot > table {
  border-spacing: 3px;
}

.empty {
  background: repeating-linear-gradient(
    45deg,
    #fff0,
    #fff0 12.5%,
    #fdd 12.5%,
    #fdd 25%
  );
}
"""

ColorBarLabels = tp.List[tp.Tuple[float, str]]


def _generate_heat_map(values: tp.List[float], width: int, height: int,
                       color_map: ColorMap,
                       min_value: tp.Optional[float] = None,
                       max_value: tp.Optional[float] = None) -> str:
    if len(values) != width * height:
        raise ValueError("invalid list size")

    min_value = nanmin(values) if min_value is None else min_value
    max_value = nanmax(values) if max_value is None else max_value

    rows = ""
    for row_index in range(height - 1, -1, -1):
        row = ""
        for col_index in range(width):
            value = (values[col_index + row_index * width] - min_value) / (max_value - min_value)
            if value < 0. or value > 1. or math.isnan(value):
                row += HEAT_MAP_EMPTY_CELL
            else:
                row += HEAT_MAP_CELL.format(*color_map(value))
        rows += HEAT_MAP_ROW.format(row)

    return HEAT_MAP.format(rows)


def _generate_x_labels(x_labels: tp.List[str]) -> str:
    return X_LABELS.format("".join(X_LABEL.format(label) for label in x_labels))


def _generate_y_labels(y_labels: tp.List[str]) -> str:
    return Y_LABELS.format("".join(Y_LABEL.format(label) for label in y_labels[::-1]))


def _generate_color_bar_gradient(color_map: ColorMap, point_count: int = 100) -> str:
    gradient_points = []
    for i in range(point_count):
        value = i / (point_count - 1)
        point = COLOR_BAR_GRADIENT_POINT.format(*color_map(1 - value), round(value * 100, 4))
        gradient_points.append(point)

    return COLOR_BAR_GRADIENT.format(",".join(gradient_points))


def _generate_color_bar_labels(labels: ColorBarLabels, min_value: float, max_value: float) -> str:
    result = []

    for label in labels:
        if min_value <= label[0] <= max_value:
            percents = 100 * (label[0] - min_value) / (max_value - min_value)
            result.append(COLOR_BAR_LABEL.format(percents=percents, label=label[1]))

    return COLOR_BAR_LABELS.format("".join(result))


def _find_closest_cover_range(min_value: float, max_value: float, color_bar_labels: ColorBarLabels,
                              min_color_bar_labels: int) \
        -> tp.Tuple[float, float]:
    if len(color_bar_labels) < min_color_bar_labels:
        raise ValueError("color_bar_labels contains less then min_color_bar_labels labels")

    left = []
    right = []
    labels_count = 0
    for i in range(len(color_bar_labels)):
        value = color_bar_labels[i][0]
        if min_value <= value <= max_value:
            labels_count += 1
        elif value < min_value:
            left.append(value)
        else:
            right.append(value)

    left, right = sorted(left), sorted(right, reverse=True)
    new_min = min_value
    new_max = max_value
    while labels_count < min_color_bar_labels:
        if len(left) == 0:
            new_max = right.pop()
        elif len(right) == 0:
            new_min = left.pop()
        elif min_value - left[-1] < right[-1] - min_value:
            new_min = left.pop()
        else:
            new_max = right.pop()
        labels_count += 1

    return new_min, new_max


def generate_heat_map_plot(values: tp.List[float],
                           x_labels: tp.List[str],
                           y_labels: tp.List[str],
                           x_title: str,
                           y_title: str,
                           color_bar_title: str,
                           color_bar_labels: ColorBarLabels,
                           color_map: ColorMap,
                           log_scale: bool = True,
                           middle_value: tp.Optional[float] = None,
                           min_value: tp.Optional[float] = None,
                           max_value: tp.Optional[float] = None,
                           min_color_bar_labels: int = 2) -> str:
    if len(values) != len(x_labels) * len(y_labels):
        raise ValueError("invalid list size")

    min_value = nanmin(values) if min_value is None else min_value
    max_value = nanmax(values) if max_value is None else max_value

    if log_scale:
        min_value = math.log(min_value)
        max_value = math.log(max_value)
        middle_value = math.log(middle_value) if middle_value is not None else None
        values = [math.log(value) for value in values]
        color_bar_labels = [(math.log(value), label) for value, label in color_bar_labels]

    min_value, max_value = _find_closest_cover_range(min_value, max_value, color_bar_labels, min_color_bar_labels)

    if middle_value is not None:
        delta = max(middle_value - min_value, max_value - middle_value)
        min_value = middle_value - delta
        max_value = middle_value + delta

    heat_map = _generate_heat_map(values, len(x_labels), len(y_labels), color_map, min_value, max_value)

    y_title = Y_TITLE.format(y_title)
    x_title = X_TITLE.format(x_title)

    y_labels = _generate_y_labels(y_labels)
    x_labels = _generate_x_labels(x_labels)

    color_bar_gradient = _generate_color_bar_gradient(color_map)
    color_bar_labels = _generate_color_bar_labels(color_bar_labels, min_value, max_value)
    color_bar_title = COLOR_BAR_TITLE.format(color_bar_title)

    return PLOT.format(heat_map=heat_map,
                       y_title=y_title,
                       x_title=x_title,
                       y_labels=y_labels,
                       x_labels=x_labels,
                       color_bar_gradient=color_bar_gradient,
                       color_bar_labels=color_bar_labels,
                       color_bar_title=color_bar_title)
