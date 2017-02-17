
//class Functor { // for tests

//    int val;

//    std::basic_ostream<std::string::value_type, std::string::traits_type>& log() const {
//        return std::cout << "<<" << (size_t)this << ">>, val = " << val << ", ";
//    }

//public:

//    //ctor
//    Functor(int n): val(n) {
//        log() << "CONSTRUCTOR" << std::endl;
//    }
//    Functor(const Functor& other) {
//        val = other.val;
//        log() << "COPY CONSTRUCTOR" << std::endl;
//    }
//    Functor(Functor&& other) {
//        val = other.val;
//        other.val = 0;
//        log() << "MOVE CONSTRUCTOR" << std::endl;
//    }

//    //dtor
//    ~Functor() {
//        log() << "DESTRUCTOR" << std::endl;
//        val = 0;
//    }

//    //assy
//    Functor& operator =(Functor other) {
//        val = other.val;
//        log() << "COPY ASSY (1)" << std::endl;
//        return *this;
//    }
//    Functor& operator =(const Functor& other) {
//        val = other.val;
//        log() << "COPY ASSY (2)" << std::endl;
//        return *this;
//    }

//    //methods
//    void operator ()(Request& req, Response& res, const Middleware::Next& next) const {
//        log() << "EXEC" << std::endl;
//        next();
//    }
//};

