#include "runtime_error.h"

namespace lighttpning {

    RuntimeError::RuntimeError(Cause c): cause(c) { }

    RuntimeError::Cause RuntimeError::what() {
        return cause;
    }

}
