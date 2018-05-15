#include "Arduino.h"


class Menu
{
  public:
    Menu(String name, void fn);
    String name();
    void function();

  private:
    String _name;
    void _fn;
};


bool menuMode = false;

void backOptionFunction()
{
}

void temperatureOptionFunction()
{
}

void humidityOptionFunction()
{
}

void timeOptionFunction()
{
}

void dateOptionFunction()
{
}

void lightOptionFunction()
{
}

void fogOptionFunction()
{
}

void waterfallOptionFunction()
{
}

void errorsOptionFunction()
{
}

Option backOption("Back", 0, backOptionFunction);
Option temperatureOption("Temperature", 4, temperatureOptionFunction);
Option humidityOption("Humidity", 4, humidityOptionFunction);
Option timeOption("Time", 3, timeOptionFunction);
Option dateOption("Date", 3, dateOptionFunction);
Option lightOption("Light", 2, lightOptionFunction);
Option fogOption("Fog", 3, fogOptionFunction);
Option waterfallOption("Waterfall", 3, waterfallOptionFunction);
Option errorsOption("Errors", 0, errorsOptionFunction);

Item maxDay("maxDay", )

    temperatureOption.add();
temperatureOption.add();
humidityOption.add();
timeOption.add();
dateOption.add();
lightOption.add();
fogOption.add();
waterfallOption.add();
errorsOption.add();

Options options(10);

options.add(backOption);
options.add(temperatureOption);
options.add(humidityOption);
options.add(timeOption);
options.add(dateOption);
options.add(lightOption);
options.add(fogOption);
options.add(waterfallOption);
options.add(errorsOption);