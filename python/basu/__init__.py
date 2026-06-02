"""Locator for the bundled basu (standalone sd-bus) C library.

basu is distributed as a wheel so that projects building C/C++ extensions
against sd-bus can find its headers and shared library without a system
install or pkg-config. The headers and ``libbasu`` ship inside this package
(``include/`` and ``lib/``), so the paths below are stable relative to the
installed package regardless of the environment layout.
"""

from __future__ import annotations

import os

__all__ = ["get_include", "get_library_dir", "get_prefix", "__version__"]

__version__ = "0.2.1"

_HERE = os.path.dirname(os.path.abspath(__file__))


def get_prefix() -> str:
    """Root of the bundled basu install (contains ``include/`` and ``lib/``)."""
    return _HERE


def get_include() -> str:
    """Directory to pass with ``-I`` so that ``<basu/sd-bus.h>`` resolves."""
    return os.path.join(_HERE, "include")


def get_library_dir() -> str:
    """Directory containing ``libbasu`` — pass with ``-L`` and as an rpath."""
    return os.path.join(_HERE, "lib")
