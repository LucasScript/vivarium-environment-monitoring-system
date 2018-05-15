#include "Arduino.h"

class Option
{
  public:
    Option(String name, int itemsSize, void fn);
    String name();
    Item item(int index);
    void function();
    void add(Item item);

  private:
    String _name;
    void _fn;
    int _count;
    Item _items[]
};

Option::Option(String name, int itemsSize, void fn)
{
    _name = name;
    _fn = fn;
    _items = _items[itemsSize];
}

String Option::name()
{
    return _name;
}

String Option::add(Item item)
{
    _items[_count] = item;
    _count++;
}

void Option::function()
{
    _fn();
}

Item Option::item(int index)
{
    return _items[index];
}
