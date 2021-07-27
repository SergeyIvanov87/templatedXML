# templatedXML
Simple high-configurable XML parser which uses compile-time customizable model-based approach to parse XML documents due to predefiend schema.
TemplatedXML depends on well-known `libXml2`(https://github.com/GNOME/libxml2), but provide high-level C++ wrappers which allow to construct user-defined model in a short time and provides a simple methods to parse this model into C++ classes from a raw XML file.
Additionally, templatedXML provides FB2 and XDXF completely constructed models, which would be used out-of-the-box

If you want to parse XML document just...
If you want to do not learn about XML very much...
If you like C++ very much....
If you like simple code...
You are welcome!

# Installing templatedXML

  1) Get a package
  2) Make sure libxml2 is ready and installed on your system (templatedXML is built on top of that at now)
  3) Go to the package directory for configure and install #templatedXML by using the following command:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<your installation prefix> ..
make install
```

  4) Append your project `CMakeLists.txt` with the following rows

```
set (CMAKE_CXX_STANDARD 17)                               # yes, it uses c++17
find_package(TemplatedXML REQUIRED)                       # use CMake package
...
target_link_libraries(<YOUR_PROJECT_NAME_TARGET> txml)    # link with `txml`
```

  5) go to the next section

# Build user-define model by templatedXML

Let's consider XDXF format. It uses the following structure:

```
  Article
      |
      |__Key
      |__Transcription
      |__Comment
```
Please see https://github.com/soshial/xdxf_makedict/blob/master/format_standard/xdxf_description.md for details

So `templatedXML` model is:

```
class KeyPhrase;
class Comment;
class Transcription;
class TextElement;
class XDXFArticle : public XMLNode<KeyPhrase, Comment, Transcription, TextElement>
{
};
```

Then add required-methods `class_name()` and `class_node_type()`

```
class XDXFArticle : public XMLNode<KeyPhrase, Comment, Transcription, TextElement>
{
    static constexpr const char *class_name()
    {
        return "ar";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }
};
```

As you can see XML element `XDXFArticle` is a node-container for other XML elements: `KeyPhrase`, `Comment` etc. And `XMLNode` is a container mix-in class for other relate XML nodes (which can be containers itself). To extract container elements from `XMLNode` you can you

```
 std::shared_ptr<XDXFArticle> art;
 ....
 auto key_phrase = art->get<KeyPhrase>();
 auto comment = art->get<Comment>();
 auto transcr = art->get<Transcription>();
```

Lets's implement others XML nodes too.
In current XDXF schema `TextElement` is a termination XML elements in XML tree, so use `XMLNodeLeaf` as base mix-in class for it:

```
class TextElement : public XMLNodeLeaf<std::string>
{
};
```

After that fill required-methods `class_name()` and `class_node_type()`:

```
class TextElement : public XMLNodeLeaf<std::string>
{
public:
    static constexpr const char* class_name()
    {
        return "#text";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Text;
    };
};
```

`XMLNodeLeaf` as a XML leaf element will contains the data from RAW xml document for appropriate type: `std::string`, some sort of `integer` and etc.
It's because we use typed `XMLNodeLeaf` for `std::string` here: `class TextElement : public XMLNodeLeaf<std::string>`
Let's add constructor for `TextElement`:

```
class TextElement : public XMLNodeLeaf<std::string>
{
public:
    static constexpr const char* class_name()
    {
        return "#text";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Text;
    };

    // Ctor from `string`
    TextElement(std::string&& str);
    ~TextElement() = default;
};
```
Now you can access to the `TextElement` by using the base `XMLNodeLeaf` method `getValue()`:

```
 auto transcr = art->get<Transcription>();
...
if (transcr)
{
  const std::string& name = transcr->getValue();

  //use `name`
  ...
 }
 ```

 Please find the completed XDXF model in `templatedXML/txml/applications/xdxf/` and usage examples in `templatedXML/examples/xdxf/main.cpp`
