#ifndef SERIALIZER_DESERIALIZER_HELPERS_H
#define SERIALIZER_DESERIALIZER_HELPERS_H
#include <txml/include/utils/fwd/utils.h>

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



#define TXML_DECLARE_SERIALIZER_CLASS(Class,BaseImpl,...)                                           \
struct Class : public BaseImpl < Class, __VA_ARGS__ >                                               \
{                                                                                                   \
    using base_t = BaseImpl < Class, __VA_ARGS__ >;                                                 \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class

#define TXML_SERIALIZER_OBJECT                                                                      \
        }; /* syntax_filler_##Class*/                                                               \
    public:                                                                                         \
    using base_t::serialize_impl;


#define TXML_DECLARE_SCHEMA_SERIALIZER_CLASS(Class,BaseImpl,...)                                    \
struct Class : public BaseImpl < Class, __VA_ARGS__ >                                               \
{                                                                                                   \
    using base_t = BaseImpl < Class, __VA_ARGS__ >;                                                 \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class

#define TXML_DECLARE_SCHEMA_SERIALIZER_TEMPLATED_CLASS(Class, Class_TEMPLATE_0, BaseImpl,...)       \
struct Class : public BaseImpl < Class<Class_TEMPLATE_0>, __VA_ARGS__ >                             \
{                                                                                                   \
    using base_t = BaseImpl < Class, __VA_ARGS__ >;                                                 \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class


#define TXML_DECLARE_SCHEMA_F_SERIALIZER_TEMPLATED_CLASS(Class, Class_TEMPLATE_0, BaseImpl,...)     \
struct Class : public BaseImpl < Class_TEMPLATE_0, __VA_ARGS__ >                                    \
{                                                                                                   \
    using base_t = BaseImpl < Class_TEMPLATE_0, __VA_ARGS__ >;                                      \
    using base_t::BaseImpl;                                                                         \
    private:                                                                                        \
        class syntax_filler_##Class

#define TXML_SCHEMA_SERIALIZER_OBJECT                                                               \
        }; /* syntax_filler_##Class*/                                                               \
    public:                                                                                         \
    using base_t::serialize_schema_impl;                                                            \
    using base_t::serialize_schema_tag_impl;                                                        \
    using base_t::is_registered_element;



#define TXML_PREPARE_SCHEMA_SERIALIZER_DISPATCHABLE_CLASS(DispatchableClass, Class_Aggregator, BaseImpl,...)     \
struct DispatchableClass : public BaseImpl < Class_Aggregator, __VA_ARGS__ >                        \
{                                                                                                   \
    using base_t = BaseImpl < Class_Aggregator, __VA_ARGS__ >;                                      \
    using base_t::BaseImpl;                                                                         \
    static constexpr const char *name() { return #DispatchableClass"<"#__VA_ARGS__">"; }             \
        static constexpr std::string_view enumerate() { return enumerate_impl<__VA_ARGS__>(); }           \
    template<class ...Elements>                                                                     \
    static constexpr std::string_view enumerate_impl() { return txml::utils::join_node_names_v<'[',',', ']', Elements...>; }           \
    private:                                                                                        \
        class syntax_filler_##DispatchableClass


#define TXML_SCHEMA_SERIALIZER_DISPATCHABLE_OBJECT                                                  \
        }; /* syntax_filler_##DispatchableClass*/                                                   \
    public:                                                                                         \
    using base_t::serialize_schema_impl;                                                            \
    using base_t::serialize_schema_tag_impl;                                                        \
    using base_t::is_registered_element;




#define TXML_DECLARE_SCHEMA_SERIALIZER_AGGREGATOR_CLASS(Class_Aggregator,...)                       \
struct Class_Aggregator : public txml::SerializerSchemaDispatcher< __VA_ARGS__ >                    \
{                                                                                                   \
    using base_t = txml::SerializerSchemaDispatcher < __VA_ARGS__ >;                                \
    static constexpr const char *name() { return #Class_Aggregator"<"#__VA_ARGS__">"; }             \
    private:                                                                                        \
        class syntax_filler_##AggregatorClass



#define TXML_SCHEMA_SERIALIZER_AGGREGATOR_OBJECT                                                    \
        }; /* syntax_filler_##CAggregatorClass*/                                                    \
    public:

////////////////////////////////////////////////////////////////////////////////////////////////////

#define TXML_PREPARE_DESERIALIZER_DISPATCHABLE_CLASS(DispatchableClass, Class_Aggregator, BaseImpl,...)     \
struct DispatchableClass : public BaseImpl < Class_Aggregator, __VA_ARGS__ >                        \
{                                                                                                   \
    using base_t = BaseImpl < Class_Aggregator, __VA_ARGS__ >;                                      \
    using base_t::BaseImpl;                                                                         \
    static constexpr const char *name() { return #DispatchableClass"<"#__VA_ARGS__">"; }            \
    static constexpr std::string_view enumerate() { return enumerate_impl<__VA_ARGS__>(); }           \
    template<class ...Elements>                                                                     \
    static constexpr std::string_view enumerate_impl() { return txml::utils::join_node_names_v<'[', ',', ']', Elements...>; }           \
    private:                                                                                        \
        class syntax_filler_##DispatchableClass


#define TXML_DESERIALIZER_DISPATCHABLE_OBJECT                                                       \
        }; /* syntax_filler_##DispatchableClas*/                                                    \
    public:                                                                                         \
    using base_t::deserialize_impl;                                                                 \
    using base_t::deserialize_tag_impl;                                                             \
    using base_t::is_registered_element;




#define TXML_DECLARE_DESERIALIZER_AGGREGATOR_CLASS(Class_Aggregator,...)                            \
struct Class_Aggregator : public txml::DeserializerDispatcher < __VA_ARGS__ >                       \
{                                                                                                   \
    using base_t = txml::DeserializerDispatcher < __VA_ARGS__ >;                                    \
    static constexpr const char *name() { return #Class_Aggregator"<"#__VA_ARGS__">"; }             \
    private:                                                                                        \
        class syntax_filler_##AggregatorClass



#define TXML_DESERIALIZER_AGGREGATOR_OBJECT                                                         \
        }; /* syntax_filler_##CAggregatorClass*/                                                    \
    public:


////////////////////////////////////////////////////////////////////////////////////////////////////

#define TXML_PREPARE_SERIALIZER_DISPATCHABLE_CLASS(DispatchableClass, Class_Aggregator, BaseImpl,...)     \
struct DispatchableClass : public BaseImpl < Class_Aggregator, __VA_ARGS__ >                        \
{                                                                                                   \
    using base_t = BaseImpl < Class_Aggregator, __VA_ARGS__ >;                                      \
    using base_t::BaseImpl;                                                                         \
    static constexpr const char *name() { return #DispatchableClass":"#Class_Aggregator"<"#__VA_ARGS__">"; }            \
    static constexpr std::string_view enumerate() { return enumerate_impl<__VA_ARGS__>(); }           \
    template<class ...Elements>                                                                     \
    static constexpr std::string_view enumerate_impl() { return txml::utils::join_node_names_v<'[',',', ']', Elements...>; }           \
    private:                                                                                        \
        class syntax_filler_##DispatchableClass


#define TXML_SERIALIZER_DISPATCHABLE_OBJECT                                                         \
        }; /* syntax_filler_##DispatchableClas*/                                                    \
    public:                                                                                         \
    using base_t::serialize_impl;                                                                   \
    using base_t::serialize_tag_impl;                                                               \
    using base_t::is_registered_element;




#define TXML_DECLARE_SERIALIZER_AGGREGATOR_CLASS(Class_Aggregator,...)                            \
struct Class_Aggregator : public txml::SerializerDispatcher < __VA_ARGS__ >                       \
{                                                                                                   \
    using base_t = txml::SerializerDispatcher < __VA_ARGS__ >;                                    \
    static constexpr const char *name() { return #Class_Aggregator"<"#__VA_ARGS__">"; }            \
    private:                                                                                        \
        class syntax_filler_##AggregatorClass



#define TXML_SERIALIZER_AGGREGATOR_OBJECT                                                         \
        }; /* syntax_filler_##CAggregatorClass*/                                                    \
    public:


////////////////////////////////////////////////////////////////////////////////////////////////////
#define TXML_PREPARE_VIRTUAL_SERIALIZER_DISPATCHABLE_CLASS(DispatchableClass, Class_Aggregator, BaseImpl,...)     \
struct DispatchableClass : public BaseImpl < Class_Aggregator, __VA_ARGS__ >                        \
{                                                                                                   \
    using base_t = BaseImpl < Class_Aggregator, __VA_ARGS__ >;                                      \
    using virtual_base_t = typename base_t::core_t;                                                 \
    using base_t::BaseImpl;                                                                         \
    static constexpr const char *name() { return #DispatchableClass":"#Class_Aggregator"<"#__VA_ARGS__">"; }            \
    static constexpr std::string_view enumerate() { return enumerate_impl<__VA_ARGS__>(); }           \
    template<class ...Elements>                                                                     \
    static constexpr std::string_view enumerate_impl() { return txml::utils::join_node_names_v<'[',',', ']', Elements...>; }           \
    private:                                                                                        \
        class syntax_filler_##DispatchableClass


#define TXML_VIRTUAL_SERIALIZER_DISPATCHABLE_OBJECT(...)                                                         \
        }; /* syntax_filler_##DispatchableClas*/                                                    \
    public:                                                                                         \
    using base_t::serialize_impl;                                                                   \
    using base_t::serialize_tag_impl;                                                               \
    using base_t::is_registered_element;                                                            \
     DispatchableClass(__VA_ARGS__) :                                                               \
            virtual_base_t(__VA_ARGS__),                                                            \
            base_t(__VA_ARGS__) {}

#define TXML_DECLARE_VIRTUAL_SERIALIZER_AGGREGATOR_CLASS(Class_Aggregator,Class_VirtualBase,...)                            \
struct Class_Aggregator : public txml::SerializerVirtualDispatcher <Class_VirtualBase, __VA_ARGS__ >                       \
{                                                                                                   \
    using base_t = txml::SerializerVirtualDispatcher <Class_VirtualBase, __VA_ARGS__ >;                                    \
    static constexpr const char *name() { return #Class_Aggregator"<"#__VA_ARGS__">"; }            \
    private:                                                                                        \
        class syntax_filler_##AggregatorClass##Class_VirtualBase



#define TXML_VIRTUAL_SERIALIZER_AGGREGATOR_OBJECT(...)                                                         \
        }; /* syntax_filler_##CAggregatorClass##Class_VirtualBase*/                                                    \
    public:                                                                                         \
        Class_Aggregator(__VA_ARGS__) :                                                             \
            Class_VirtualBase(__VA_ARGS__),                                                         \
            base_t(__VA_ARGS__) {}

#endif // SERIALIZER_DESERIALIZER_HELPERS_H
