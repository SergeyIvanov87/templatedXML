#ifndef SERIALIZER_DESERIALIZER_HELPERS_H
#define SERIALIZER_DESERIALIZER_HELPERS_H

#define TXML_DECLARE_DESERIALIZER_CLASS(Class,BaseImpl,...)                                         \
struct Class : public BaseImpl < Class, __VA_ARGS__ >                                               \
{                                                                                                   \
    using base_t = BaseImpl < Class, __VA_ARGS__ >;                                                 \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class

#define TXML_DESERIALIZER_OBJECT                                                                    \
        }; /* syntax_filler_##Class*/                                                               \
    public:                                                                                         \
    using base_t::deserialize_impl;



#define TXML_DECLARE_SERIALIZER_CLASS(Class,BaseImpl,...)                                         \
struct Class : public BaseImpl < Class, __VA_ARGS__ >                                               \
{                                                                                                   \
    using base_t = BaseImpl < Class, __VA_ARGS__ >;                                                 \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class

#define TXML_SERIALIZER_OBJECT                                                                    \
        }; /* syntax_filler_##Class*/                                                               \
    public:                                                                                         \
    using base_t::serialize_impl;

#endif // SERIALIZER_DESERIALIZER_HELPERS_H
