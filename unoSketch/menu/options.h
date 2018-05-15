#include "Arduino.h"

class Options
{
  public:
    Options(int size);
    void add(Option opt);
    Option option(int index);

  private:
    int _count = 0;
    Option _options[];

}

Options::Options(int size)
{
    _options = _options[size];
}

void Options::add(Option opt)
{
    _options[_count] = opt;
    _count++;
}

Option Options::option(int index)
{
    return _options[index];
}