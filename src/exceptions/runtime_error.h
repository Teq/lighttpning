#pragma once

namespace Lighttpning {

    class RuntimeError {

    public:

        enum Cause {
            UNKNOWN,
            OUT_OF_MEMORY,
            BAD_ARGUMENT
        };

        RuntimeError(Cause);

        Cause what();

        static inline RuntimeError OutOfMemory() {
            return RuntimeError(Cause::OUT_OF_MEMORY);
        }

        static inline RuntimeError BadArgument() {
            return RuntimeError(Cause::BAD_ARGUMENT);
        }

    private:
        Cause cause;
    };

}
