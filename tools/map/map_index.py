from __future__ import annotations

import re
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path, PurePosixPath, PureWindowsPath
from typing import DefaultDict, Optional


SECTION_HEADER_RE = re.compile(r"^\s*(\.\w+|extab|extabindex)\s+section layout\s*$")
FOUND_IN_RE = re.compile(r"^\s*\d+\]\s*(.+?)\s*\(([^)]+)\)\s+found in\s+(.+?)\s*$")
OBJECT_LINE_RE = re.compile(r"\s+([^\s]+\.o)\s*$", re.IGNORECASE)
SOURCE_EXTENSIONS = (
    ".c",
    ".cc",
    ".cpp",
    ".cxx",
    ".cp",
    ".c++",
    ".s",
    ".asm",
    ".hpp",
    ".hh",
    ".hxx",
    ".h",
)


def _basename(path_str: str) -> str:
    if not isinstance(path_str, str) or not path_str:
        return ""
    path_obj = PureWindowsPath(path_str) if "\\" in path_str else PurePosixPath(path_str)
    return path_obj.name


def normalize_object_file(path_str: str) -> str:
    return _basename(path_str)


def normalize_source_file(path_str: str) -> str:
    return _basename(path_str)


def _looks_like_source_file(path_str: str) -> bool:
    return normalize_source_file(path_str).lower().endswith(SOURCE_EXTENSIONS)


def _parse_hex(text: str) -> Optional[int]:
    if text == "UNUSED" or text == "........":
        return None
    try:
        return int(text, 16)
    except ValueError:
        return None


@dataclass(frozen=True)
class FoundInRecord:
    symbol_name: str
    symbol_type: str
    container: str
    source_file: Optional[str]


@dataclass(frozen=True)
class LayoutRecord:
    section: str
    symbol_name: str
    object_file: str
    offset: Optional[int]
    size: int
    virtual_address: Optional[int]
    kind: Optional[str]
    is_unused: bool


@dataclass
class MapIndex:
    label: str
    found_in_by_symbol: DefaultDict[str, list[FoundInRecord]] = field(
        default_factory=lambda: defaultdict(list)
    )
    layout_by_symbol: DefaultDict[str, list[LayoutRecord]] = field(
        default_factory=lambda: defaultdict(list)
    )
    object_sections: DefaultDict[str, dict[str, int]] = field(
        default_factory=lambda: defaultdict(dict)
    )
    source_files_by_symbol: DefaultDict[str, set[str]] = field(
        default_factory=lambda: defaultdict(set)
    )

    def add_found_in(self, record: FoundInRecord) -> None:
        self.found_in_by_symbol[record.symbol_name].append(record)
        if record.source_file:
            self.source_files_by_symbol[record.symbol_name].add(record.source_file)

    def add_layout(self, record: LayoutRecord) -> None:
        self.layout_by_symbol[record.symbol_name].append(record)
        if record.symbol_name == record.section:
            self.object_sections[record.object_file][record.section] = record.size

    def object_section_size(self, object_file: str, section: str) -> Optional[int]:
        return self.object_sections.get(normalize_object_file(object_file), {}).get(section)

    def layout_records_for_symbol(self, symbol_name: str, section: Optional[str] = None) -> list[LayoutRecord]:
        records = self.layout_by_symbol.get(symbol_name, [])
        if section is None:
            return list(records)
        return [record for record in records if record.section == section]

    def source_files_for_symbol(self, symbol_name: str) -> set[str]:
        return set(self.source_files_by_symbol.get(symbol_name, set()))

    def found_in_records_for_symbol(self, symbol_name: str) -> list[FoundInRecord]:
        return list(self.found_in_by_symbol.get(symbol_name, []))


def _parse_found_in_line(line: str) -> Optional[FoundInRecord]:
    match = FOUND_IN_RE.match(line)
    if not match:
        return None

    found_in = match.group(3).strip()
    parts = found_in.split()
    if not parts:
        return None

    container = parts[0]
    source_file = None
    if len(parts) > 1 and _looks_like_source_file(parts[1]):
        source_file = normalize_source_file(parts[1])

    return FoundInRecord(
        symbol_name=match.group(1).strip(),
        symbol_type=match.group(2).strip(),
        container=container,
        source_file=source_file,
    )


def _parse_layout_line(line: str, current_section: str) -> Optional[LayoutRecord]:
    stripped = line.strip()
    if not stripped or stripped.startswith("Starting") or stripped.startswith("address") or stripped.startswith("-"):
        return None

    object_match = OBJECT_LINE_RE.search(line)
    if not object_match:
        return None

    object_file = normalize_object_file(object_match.group(1))
    prefix = line[: object_match.start()].strip()
    columns = prefix.split(maxsplit=3)
    if len(columns) < 4:
        return None

    offset_text, size_text, virtual_text, remainder = columns
    kind = None
    symbol_name = remainder.strip()
    kind_split = symbol_name.split(maxsplit=1)
    if len(kind_split) == 2 and re.fullmatch(r"[0-9A-Fa-f]+", kind_split[0]):
        kind = kind_split[0]
        symbol_name = kind_split[1].strip()

    size = _parse_hex(size_text)
    if size is None:
        return None

    return LayoutRecord(
        section=current_section,
        symbol_name=symbol_name,
        object_file=object_file,
        offset=_parse_hex(offset_text),
        size=size,
        virtual_address=_parse_hex(virtual_text),
        kind=kind,
        is_unused=offset_text == "UNUSED",
    )


def load_map_index(map_path: Path | str, label: Optional[str] = None) -> MapIndex:
    path = Path(map_path)
    index = MapIndex(label=label or path.stem)
    current_section: Optional[str] = None

    with path.open("r", encoding="utf-8", errors="ignore") as handle:
        for raw_line in handle:
            stripped = raw_line.strip()

            header_match = SECTION_HEADER_RE.match(stripped)
            if header_match:
                current_section = header_match.group(1)
                continue

            if current_section is not None:
                layout_record = _parse_layout_line(raw_line.rstrip("\n"), current_section)
                if layout_record is not None:
                    index.add_layout(layout_record)
                    continue

            found_in_record = _parse_found_in_line(raw_line.rstrip("\n"))
            if found_in_record is not None:
                index.add_found_in(found_in_record)

    return index
