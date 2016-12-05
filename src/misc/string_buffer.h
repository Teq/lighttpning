//    class StringBuffer {
//
//    public:
//
//        StringBuffer() {
//            buf = (char*)malloc(buf_len);
//        }
//
//        ~StringBuffer() {
//            free(buf);
//        }
//
//        void operator += (char c) {
//            buf[buf_cur++] = c;
//            if (buf_cur >= buf_len) {
//                buf_len *= 1.5;
//                void* newPtr = realloc(buf, buf_len);
//                if (newPtr == nullptr) {
//                    throw new std::runtime_error("Unable to allocate memory");
//                } else {
//                    buf = (char*)newPtr;
//                }
//            }
//        }
//
//        inline bool empty() {
//            return buf_cur == 0;
//        }
//
//        void clear() {
//            buf_len = DEFAULT_BUF_LEN;
//            buf = (char*)realloc(buf, buf_len); // realloc to lower size, should not fail
//            buf_cur = 0;
//        }
//
//    private:
//
//        constexpr unsigned short DEFAULT_BUF_LEN = 8;
//        char* buf = nullptr;
//        unsigned short buf_cur = 0;
//        unsigned short buf_len = DEFAULT_BUF_LEN;
//
//    };
