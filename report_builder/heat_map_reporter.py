import math
import typing as tp

from .benchmark_data import make_groups
from .benchmark_data import Parameter, Benchmark, ParameterValues, ContextValues
from .support import nanmin, nanmax, contains_nan
from .heat_map_html import generate_heat_map_plot, ColorBarLabels, ColorMap, CSS as PLOT_CSS
from .heat_map_data import generate_heat_map_data, generate_comparison_heat_map_data, HeatMapData
from .json2html import convert_json

HTML = """<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>MetaImageMark report</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Fira+Mono&display=swap" rel="stylesheet">
  <style>{css}</style>
</head>
<body>
  <div class="container">
    <header>
      <h1>MetaImageMark report</h1>
    </header>
  </div>
  {context}
  {toc}
  {groups}
</body>
</html>
"""

CELL = """
<div class="cell" id="{id}">
{plot}
{description}
{errors}
</div>
"""

DESCRIPTION = """<table class="description">{}</table>"""
DESCRIPTION_ROW = """<tr>{}</tr>"""
DESCRIPTION_ITEM = """<td><b>{key}:&nbsp;</b>{value}</td>"""

ERRORS = """<div class="errors">{}</div>"""
ERROR = """<div>{}</div>"""

GROUP = """<div class="container">{}</div>"""
GROUP_BASIC_CELLS = """<div class="basic-cells">{}</div>"""
GROUP_COMPARE_CELLS = """<div class="compare-cells">{}</div>"""

TOC = """<div class="container">{}</div>"""
TOC_BLOCK = """<div class="toc"><div>{}</div></div>"""
TOC_ITEM = """<a href="#{id}">{name}{info}</a>"""
TOC_ITEM_NAME = """<div class="toc-name">{}</div>"""
TOC_ITEM_NAME_PARAMETER = """<span><b>{key}:&nbsp;</b>{value}</span>"""
TOC_ITEM_INFO = """<div class="toc-info">{}</div>"""
TOC_ITEM_INFO_RATE = """<div>{}</div><div class="toc-mark" style="background-color: rgb({}, {}, {})"></div>"""
TOC_ITEM_INFO_ERROR = """<div class="toc-error toc-mark"></div>"""

CONTEXT = """<div class="container context"><div>{}</div></div>"""

CSS = """
* {
  margin: 0;
  padding: 0;

  box-sizing: border-box;

  font-family: 'Fira Mono', monospace;
}

header {
  text-align: center;
  margin: 15px;
}

.container {
  background-color: #f8f9fa;
  border-bottom: 1px solid #ddd;
  border-top: 1px solid #ddd;

  width: 100%;
  margin: 0 0 30px;
  min-width: 650px;
}

.plot {
  display: flex;
  margin: auto;
}

.cell {
  display: flex;
  flex-direction: column;

  border-radius: 5px;
  box-shadow: 0 0 3px gray; 

  background-color: white;

  padding: 15px;
  margin: 15px;
}

.description {
  margin-top: 15px;

  border: 1px solid #ccc;
  border-radius: 5px;
}

.description td {
  padding: 5px;
  border-radius: 5px;
  text-align: center;
}

.description td:hover {
  background-color: #f5f5f5;
  cursor: default;
}

.errors {
  margin: 15px auto 0;
  
  border: 1px dashed #fbb;
  border-radius: 5px; 
  
  word-break: break-all;
  width: 500px;
}

.errors div {
  padding: 5px;
  border-radius: 5px;
  font-size: 70%;
  margin: 5px;
}

.basic-cells, .compare-cells {
  display: flex;
  justify-content: center;
  flex-wrap: wrap;
  align-items: center;
}

.compare-cells {
  border-top: 1px dashed #aaa;
}

.toc {
  text-align: center;
  margin: 15px;
}

.toc > div {
  display: inline-flex;
  flex-direction: column;
  border-radius: 5px;
  box-shadow: 0 0 3px gray;
  background-color: white;
  padding: 5px;
}

.toc a {
  display: inline-flex;
  text-decoration: none;
  color: black;
  border-bottom: 1px solid #eee;
  border-radius: 5px;
  padding: 5px 0;
}

.toc a:hover {
  background-color: #f0f0f0;
}

.toc a span {
  margin: 0 1em;
}

.toc-info {
  display: inline-flex;
  align-items: center;
  padding: 0 1em;
  border-left: 1px solid #ddd;
}

.toc-mark {
  width: 2em;
  border-radius: 3px;
  margin: 0 5px;
}

.toc-mark::after {
  content: "\\00a0";
}

.toc-error {
  background: repeating-linear-gradient(
    45deg,
    #fff0,
    #fff0 12.5%,
    #faa 12.5%,
    #faa 25%
  );
}

.toc-name {
  display: inline-flex;
  flex-wrap: wrap;
}

.context {
  text-align: center;
}

.context > div {
  display: inline-flex;
  margin: 15px;
  padding: 5px;
  background-color: white;
  border-radius: 5px;
  box-shadow: 0 0 3px gray;
}

.context table {
  border-spacing: 0;
  border-collapse: collapse;
}

.context th, .context td {
  padding: 5px;
  border-bottom: 1px solid #ddd;
  text-align: left;
}

.context ul {
  padding: 0 2em;
}

.context li {
  padding: 5px 0;
}
"""


# TOC generation

def _generate_heat_map_id(data: HeatMapData) -> int:
    result = ""
    for parameter in data.parameters:
        result += parameter.key + str(parameter.value)
    return abs(hash(result))


def _generate_toc_name(data: HeatMapData) -> str:
    result = ""
    for parameter in data.parameters:
        result += TOC_ITEM_NAME_PARAMETER.format(key=parameter.key, value=parameter.value)
    return TOC_ITEM_NAME.format(result) if result else ""


def _generate_toc_rate(data: HeatMapData,
                       color_map: ColorMap,
                       min_value: float,
                       max_value: float,
                       log_scale: bool,
                       precision: int = 1) -> str:
    filtered_values = [value for value in data.values if not math.isnan(value)]
    if len(filtered_values) == 0:
        return ""

    if log_scale:
        mean = math.exp(sum(math.log(value) for value in filtered_values) / len(filtered_values))
        value = math.log(mean / min_value) / math.log(max_value / min_value)
    else:
        mean = sum(filtered_values) / len(filtered_values)
        value = (mean - min_value) / (max_value - min_value)

    if math.isnan(value):
        return ""

    value = max(0., min(value, 1.))
    return TOC_ITEM_INFO_RATE.format(round(mean, precision), *color_map(value))


def _generate_toc_error(data: HeatMapData) -> str:
    return TOC_ITEM_INFO_ERROR if data.errors or contains_nan(data.values) else ""


def _generate_toc_info(data: HeatMapData,
                       color_map: tp.Optional[ColorMap] = None,
                       min_value: tp.Optional[float] = None,
                       max_value: tp.Optional[float] = None,
                       log_scale: tp.Optional[bool] = None,
                       rate_precision: int = 1) -> str:
    result = ""

    if color_map:
        result += _generate_toc_rate(data, color_map, min_value, max_value, log_scale, rate_precision)

    result += _generate_toc_error(data)

    return TOC_ITEM_INFO.format(result) if result else ""


def _generate_toc_item(data: HeatMapData,
                       color_map: tp.Optional[ColorMap] = None,
                       min_value: tp.Optional[float] = None,
                       max_value: tp.Optional[float] = None,
                       log_scale: tp.Optional[bool] = None,
                       rate_precision: int = 1) -> str:
    name = _generate_toc_name(data)
    if not name:
        return ""

    info = _generate_toc_info(data, color_map, min_value, max_value, log_scale, rate_precision)

    return TOC_ITEM.format(id=_generate_heat_map_id(data), name=name, info=info)


# Cell generation

def _find_measure_range(data: tp.List[HeatMapData]) -> tp.Tuple[float, float]:
    min_value = math.nan
    max_value = math.nan

    for item in data:
        if math.isnan(min_value):
            min_value = nanmin(item.values)
        if math.isnan(max_value):
            max_value = nanmax(item.values)

        min_value = nanmin((min_value, nanmin(item.values)))
        max_value = nanmax((max_value, nanmax(item.values)))

    return min_value, max_value


def _generate_description(data: tp.List[Parameter]) -> str:
    result = ""
    to = len(data) if len(data) % 2 == 0 else len(data) - 1
    for i in range(0, to, 2):
        first = DESCRIPTION_ITEM.format(key=data[i].key, value=data[i].value)
        second = DESCRIPTION_ITEM.format(key=data[i + 1].key, value=data[i + 1].value)
        result += DESCRIPTION_ROW.format(first + second)

    if len(data) != to:
        result += DESCRIPTION_ROW.format(DESCRIPTION_ITEM.format(key=data[-1].key, value=data[-1].value))

    if not result:
        return ""
    return DESCRIPTION.format(result)


def _generate_errors(data: tp.Optional[tp.List[ParameterValues]]) -> str:
    if not data:
        return ""

    result = ""
    for error in data:
        result += ERROR.format(str(error))

    return ERRORS.format(result)


def _generate_html_cells(cells_data: tp.List[HeatMapData],
                         color_bar_labels: ColorBarLabels,
                         color_map: ColorMap,
                         log_scale: bool,
                         equalize_group_bars: bool,
                         middle_value: tp.Optional[float] = None) -> str:
    cells = ""

    min_value = None
    max_value = None

    if equalize_group_bars:
        min_value, max_value = _find_measure_range(cells_data)

    for data in cells_data:
        plot = generate_heat_map_plot(data.values, data.x_labels, data.y_labels,
                                      data.x_title, data.y_title, data.measure_title,
                                      color_bar_labels, color_map,
                                      log_scale=log_scale,
                                      min_value=min_value,
                                      max_value=max_value,
                                      middle_value=middle_value)

        cells += CELL.format(plot=plot,
                             description=_generate_description(data.parameters),
                             errors=_generate_errors(data.errors),
                             id=_generate_heat_map_id(data))

    return cells


def _generate_html_context(contexts: tp.Mapping[str, ContextValues]) -> str:
    return CONTEXT.format(convert_json(contexts))


def generate_heat_map_report(benchmarks: tp.List[Benchmark],
                             measure_key: str,
                             width_key: str,
                             height_key: str,
                             color_bar_labels: ColorBarLabels,
                             color_map: ColorMap,
                             log_scale: bool = True,
                             equalize_group_bars: bool = True,
                             aggregate_function: tp.Callable[[tp.List[float]], float] = min,
                             group_keys_values: tp.Optional[tp.List[Parameter]] = None,
                             comparison_color_bar_labels: tp.Optional[ColorBarLabels] = None,
                             comparison_color_map: tp.Optional[ColorMap] = None,
                             comparison_operation=lambda f, s: f / s,
                             comparison_value_transform=lambda f, s: str(f) + "/" + str(s),
                             comparison_log_scale: bool = True,
                             comparison_middle_value: float = 1.,
                             force_compare: bool = False,
                             error_key: tp.Optional[str] = None,
                             rate_min_value: float = 1 / 4,
                             rate_max_value: float = 4.,
                             rate_precision: int = 1,
                             context: tp.Optional[tp.Mapping[str, ContextValues]] = None) -> str:
    if group_keys_values is None:
        group_keys_values = []

    heat_map_data = generate_heat_map_data(benchmarks, measure_key, width_key, height_key, aggregate_function,
                                           error_key)
    groups: tp.List[tp.List[HeatMapData]] = make_groups(heat_map_data,
                                                        [parameter.key for parameter in group_keys_values])

    basic_toc = ""
    compare_toc = ""

    html_groups = ""
    for group in groups:
        basic_cells = _generate_html_cells(group, color_bar_labels, color_map, log_scale, equalize_group_bars)
        html_group = GROUP_BASIC_CELLS.format(basic_cells)
        basic_toc += "".join(_generate_toc_item(heat_map) for heat_map in group)

        comparison_data = generate_comparison_heat_map_data(group, group_keys_values,
                                                            comparison_operation,
                                                            comparison_value_transform,
                                                            force_compare)
        compare_cells = _generate_html_cells(comparison_data,
                                             comparison_color_bar_labels, comparison_color_map,
                                             log_scale=comparison_log_scale, equalize_group_bars=False,
                                             middle_value=comparison_middle_value)

        compare_toc += "".join(_generate_toc_item(heat_map, comparison_color_map,
                                                  rate_min_value, rate_max_value,
                                                  comparison_log_scale, rate_precision)
                               for heat_map in comparison_data)
        if compare_cells:
            html_group += GROUP_COMPARE_CELLS.format(compare_cells)

        html_groups += GROUP.format(html_group)

    toc = ""
    toc += TOC_BLOCK.format(basic_toc) if basic_toc else ""
    toc += TOC_BLOCK.format(compare_toc) if compare_toc else ""
    toc = TOC.format(toc) if toc else ""

    html_context = _generate_html_context(context) if context else ""

    return HTML.format(groups=html_groups,
                       toc=toc,
                       css=PLOT_CSS + CSS,
                       context=html_context)
