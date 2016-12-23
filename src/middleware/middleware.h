#pragma once

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {
        
    public:

        virtual ~Middleware() { };

        virtual void call(Request&, Response&) const = 0;

        void setNext(const Middleware&);

        class Next {
        public:
            virtual void operator ()() const = 0;
        };

    protected:

        const Middleware* next = nullptr;

    };

}
