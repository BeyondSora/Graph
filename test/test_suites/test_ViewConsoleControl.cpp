#include "../_include/test_ViewConsoleControl.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/controller/_include/Controller.h"
#include "../../src/model/_include/AlgorithmController.h"
#include "../../src/model/_include/LogicController.h"
#include "../../src/view/console/_include/ConsoleMain.h"

TestStatus ViewConsoleControl::run ()
{
    __enter;

    __checkpoint("Console Unit Test");
    Storage stack;
    BaseController base(stack);
    LogicController logic(base);
    AlgorithmController alg(logic);
    Controller control(&logic, &alg);
    ConsoleMain console(&control);

    control.subscribe(&console);

    console.start();

    __return(TestStatus::PASS);
}
