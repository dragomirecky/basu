# SPDX-License-Identifier: LGPL-2.1+

_systemd_headers = '''
        sd-bus.h
        sd-bus-protocol.h
        sd-bus-vtable.h
        sd-id128.h
'''.split()

# https://github.com/mesonbuild/meson/issues/1633
systemd_headers = files(_systemd_headers)

# install_data (not install_headers) so meson-python maps these under the
# Python package dir rather than the "headers" wheel scheme.
install_data(
        systemd_headers,
        '_sd-common.h',
        install_dir : basu_install_includedir)

