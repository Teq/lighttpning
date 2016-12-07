#include "middleware.h"

namespace lighttpning {

    static class : public Middleware {
    protected:
        void call(Request&, Response&) const override {  }
    } FINAL_OBJ;

    Middleware * const Middleware::FINAL = &FINAL_OBJ;

    Middleware::Middleware():
        next(FINAL)
    { }

}
