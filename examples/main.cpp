#include <iostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <stdio.h>

struct indent {
  int depth_;
  explicit indent(int depth): depth_(depth) {};
};

std::ostream & operator<<(std::ostream & o, indent const & in)
{
  for(int i = 0; i != in.depth_; ++i)
  {
    o << "  ";
  }
  return o;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("need file name");
        return -1;
    }

    auto xml_reader = std::make_unique<xmlpp::TextReader>(argv[1]);
    std::string name;
    std::locale::global(std::locale(""));
    while(xml_reader->read())
    {
      int depth = xml_reader->get_depth();
      std::cout << indent(depth) << "--- node ---" << std::endl;
      std::cout << indent(depth) << "name: " << xml_reader->get_name() << std::endl;
      std::cout << indent(depth) << "depth: " << xml_reader->get_depth() << std::endl;
      auto v = xml_reader->get_value() ;
      std::cout << indent(depth) << "value: " << v << std::endl;
    }
    return 0;
}
