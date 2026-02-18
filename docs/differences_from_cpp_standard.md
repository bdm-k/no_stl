This document summarizes how `no_stl` differs from the C++ standard. `no_stl` doesn't conform to the
standard because it avoids exceptions and runtime type information (RTTI). Note that we are limiting
the scope to C++20 for now.

## \<optional>

### optional

| Feature | std | no_stl |
| ------- | --- | ------ |
| `value()` | Throws `std::bad_optional_access` if *this* optional does not contain a value. | The behavior is undefined if *this* optional does not contain a value (as with `operator*`). |

## \<memory>

### allocator

| Feature | std | no_stl |
| ------- | --- | ------ |
| `allocate()` | Throws `std::bad_alloc` if allocation fails. | Returns `std::nullptr` if allocation fails. |

Currently, the `no_stl::allocator` implementation relies on the following external functions:

- `void * operator new(std::size_t count, std::align_val_t al, const std::nothrow_t & tag) noexcept;`
- `void operator delete(void * ptr, std::size_t sz) noexcept;`

To achieve `no_stl`'s goal of being truly header-only, we plan to introduce an alternative that uses a static memory region defined by `no_stl` for all allocations. Moreover, this no-dependency approach will be made the default option.

## \<expected>

### expected

| Feature | std | no_stl |
| ------- | --- | ------ |
| `operator=`<br/>`swap()` | Strong exception guarantee is provided. | No exception guarantee is provided. |
| `value()` | Throws `std::bad_expected_access` if *this* contains an unexpected value. | The behavior is undefined if *this* contains an unexpected value(as with `operator*`). |

No exception guarantee is provided for `operator=` and `swap()`, because offering one would require using try-catch blocks.
