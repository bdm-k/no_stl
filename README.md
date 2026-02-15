# no_stl

This project aims to provide a STL-like, header-only library for bare-metal development.

## Features

- **No standard library.** `no_stl` does not require C/C++ standard libraries. It it header-only and
  works out of the box without linking against anything.
- **Customizable.** If you can provide certain functions, you can customize the behavior of `no_stl`
  via a well-defined set of preprocessor feature macros.
- **No RTTI or exceptions.** `no_stl` does not rely on exceptions or runtime type information. You
  can safely build your project with `-fno-exceptions` and `-fno-rtti`.

## Limitations

Components from the system headers that already meet `no_stl`'s requirements are reused and exposed
in the `no_stl` namespace rather than being implemented from scratch.

Although this implementation strategy greatly improves compatibility, it can accidentally expose
components that depend on the standard library. As far as I know, the only reliable way to determine
whether a component requires the standard library is to compile that component with `-nostdlib`.

> [!important]
> It would be great if you could report any linkage errors that suggest `no_stl` requires the
> standard library.
