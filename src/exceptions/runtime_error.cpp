#include "runtime_error.h"

namespace Lighttpning {

    RuntimeError::RuntimeError(Cause c): cause(c) { }

    RuntimeError::Cause RuntimeError::what() {
        return cause;
    }

}
