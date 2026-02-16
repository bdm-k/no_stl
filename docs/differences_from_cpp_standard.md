This document summarizes how `no_stl` differs from the C++ standard. `no_stl` doesn't conform to the
standard because it avoids exceptions and runtime type information (RTTI). Note that we are limiting
the scope to C++20 for now.

## optional

| Feature | std | no_stl |
| ------- | --- | ------ |
| `optional::value()` | Throws `std::bad_optional_access` if *this* optional does not contain a value. | The behavior is undefined if *this* optional does not contain a value (as with `operator*`). |
