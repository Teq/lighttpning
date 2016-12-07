#pragma once

#include "../http/request.h"
#include "../http/response.h"
#include "middleware.h"

namespace lighttpning {

    class MiddlewareNode : public Middleware {

    public:

        class Next {
        public:
            virtual void operator() () const = 0;
        };

        using Function = void (*)(Request& req, Response& res, const Next& next);

        MiddlewareNode(const Function&);

    protected:

        void call(Request&, Response&) const override;

        const Function& func;

        class NextMiddlewareWrapper : public Next {
        public:
            NextMiddlewareWrapper (const Middleware& next, Request& request, Response& response) :
                nextMiddleware(next),
                request(request),
                response(response)
            { }

            inline void operator() () const override {
                nextMiddleware.call(request, response);
            }

        private:
            const Middleware& nextMiddleware;
            Request& request;
            Response& response;
        };

    };

}
