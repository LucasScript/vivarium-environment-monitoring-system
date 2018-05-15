#include "Arduino.h"

class Item
{
  public:
    Item(String name, void fn);
    String name();
    void function();

  private:
    String _name;
    void _fn;
};

Item::Item(String name, void fn)
{
    _name = name;
    _fn = fn;
}

String Item::name()
{
    return _name;
}

void Item::function()
{
    _fn();
}