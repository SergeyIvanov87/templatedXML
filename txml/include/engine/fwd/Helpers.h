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
    private:                                                                                        \
        class syntax_filler_##DispatchableClass


#define TXML_SERIALIZER_DISPATCHABLE_OBJECT                                                       \
        }; /* syntax_filler_##DispatchableClas*/                                                    \
    public:                                                                                         \
    using base_t::serialize_impl;                                                                 \
    using base_t::serialize_tag_impl;                                                             \
    using base_t::is_registered_element;




#define TXML_DECLARE_SERIALIZER_AGGREGATOR_CLASS(Class_Aggregator,...)                            \
struct Class_Aggregator : public txml::SerializerDispatcher < __VA_ARGS__ >                       \
{                                                                                                   \
    using base_t = txml::SerializerDispatcher < __VA_ARGS__ >;                                    \
    private:                                                                                        \
        class syntax_filler_##AggregatorClass



#define TXML_SERIALIZER_AGGREGATOR_OBJECT                                                         \
        }; /* syntax_filler_##CAggregatorClass*/                                                    \
    public:

#endif // SERIALIZER_DESERIALIZER_HELPERS_H
