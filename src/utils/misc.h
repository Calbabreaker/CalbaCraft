#define CC_BIND_FUNC(func)                                                                         \
    [this](auto&&... args) -> decltype(auto) {                                                     \
        return this->func(std::forward<decltype(args)>(args)...);                                  \
    }
