import typing as tp

Values = tp.Union[str, bool, float, int, tp.List, tp.Mapping]

TABLE = """<table {}>{}</table>"""

LINE = """<tr>{}</tr>"""
HEADER_ITEM = """<th>{}</th>"""
ITEM = """<td>{}</td>"""

LIST = """<ul>{}</ul>"""
LIST_ITEM = """<li>{}</li>"""


def _get_column_headers(json_list: tp.List[Values]) -> tp.Optional[tp.List[str]]:
    if not json_list or not hasattr(json_list[0], "keys"):
        return None
    headers = json_list[0].keys()
    for value in json_list:
        if not hasattr(value, "keys") or len(value.keys()) != len(headers):
            return None
        for header in headers:
            if header not in value:
                return None
    return list(headers)


def _convert_and_collapse_list(json_list: tp.List[Values], table_attributes: str) -> tp.Optional[str]:
    headers = _get_column_headers(json_list)
    if not headers:
        return None

    result = LINE.format("".join(HEADER_ITEM.format(header) for header in headers))

    for item in json_list:
        line = ""
        for key in headers:
            line += ITEM.format(_convert_json_value(item[key], table_attributes))
        result += LINE.format(line)

    return TABLE.format(table_attributes, result)


def _convert_list(json_list: tp.List[Values], table_attributes: str) -> str:
    result = _convert_and_collapse_list(json_list, table_attributes)
    if result:
        return result
    result = ""

    for value in json_list:
        result += LIST_ITEM.format(_convert_json_value(value, table_attributes))

    if not result:
        return ""
    return LIST.format(result)


def _convert_object(json_object: tp.Mapping[str, Values], table_attributes: str) -> str:
    result = ""

    for key, value in json_object.items():
        result += LINE.format(HEADER_ITEM.format(key) + ITEM.format(_convert_json_value(value, table_attributes)))

    if not result:
        return ""
    return TABLE.format(table_attributes, result)


def _convert_json_value(value: Values, table_attributes: str) -> str:
    if type(value) is str:
        return value
    if hasattr(value, "items"):
        return _convert_object(value, table_attributes)
    if hasattr(value, "__iter__") and hasattr(value, "__getitem__"):
        return _convert_list(value, table_attributes)
    return str(value)


def convert_json(json_object: tp.Mapping[str, Values], table_attributes: str = "") -> str:
    return _convert_json_value(json_object, table_attributes)
