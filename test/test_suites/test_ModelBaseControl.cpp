#include "../_include/test_ModelBaseControl.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/model/_include/BaseController.h"
#include "../../src/model/_include/Edge.h"
#include "../../src/model/_include/Resource.h"
#include "../../src/model/_include/Vertex.h"

TestStatus ModelBaseControl::run ()
{
    __enter;
    __checkpoint("New Vertex Creation");
    Vertex *v1 = BaseControl.newVertex(1);
    Vertex *v2 = BaseControl.newVertex(2);
    Vertex *v3 = BaseControl.newVertex(3);

    __checkpoint("Connect Vertices");
    Edge *e = BaseControl.join(4, 1, 2);
    if (e == NULL) {
        __log_print << "no edge";
        __return(TestStatus::FAIL);
    }

    Edge *e1 = BaseControl.join(5, 1, 3);
    if (e1 == NULL) {
        __log_print << "no edge";
        __return(TestStatus::FAIL);
    }

    Edge *e2 = BaseControl.join(6, 2, 3);
    if (e2 == NULL) {
        __log_print << "no edge";
        __return(TestStatus::FAIL);
    }

    __checkpoint("Remove Vertices");
    if (!BaseControl.removeVertex(1)) {
        __log_print << "remove fail";
        __return(TestStatus::FAIL);
    }
    if (!BaseControl.removeVertex(2)) {
        __log_print << "remove fail";
        __return(TestStatus::FAIL);
    }
    if (!BaseControl.removeVertex(3)) {
        __log_print << "remove fail";
        __return(TestStatus::FAIL);
    }

    __return(TestStatus::PASS);
}