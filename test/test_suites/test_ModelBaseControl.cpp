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

    TestStatus testStatus = TestStatus::FAIL;

    for (int i = 0; i < 10; ++i) {
        if (!((testStatus = BaseTest()) == TestStatus::PASS)) {
            __log_print << "Test failed at " << i << "th iteration";
            break;
        }
    }

    __return_status(testStatus);
}

TestStatus ModelBaseControl::BaseTest ()
{
    __enter;
    __checkpoint("New Vertex Creation");
    Vertex *v1 = BaseControl.newVertex(1);
    if (v1 == NULL) {
        __log_print << "vertex 1 was not created";
        __return_status(TestStatus::FAIL);
    }
    Vertex *v2 = BaseControl.newVertex(2);
    if (v2 == NULL) {
        __log_print << "vertex 2 was not created";
        __return_status(TestStatus::FAIL);
    }
    Vertex *v3 = BaseControl.newVertex(3);
    if (v3 == NULL) {
        __log_print << "vertex 3 was not created";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("Connect Vertices");
    Edge *e = BaseControl.join(4, 1, 2);
    if (e == NULL) {
        __log_print << "edge was not created";
        __return_status(TestStatus::FAIL);
    }

    Edge *e1 = BaseControl.join(5, 1, 3);
    if (e1 == NULL) {
        __log_print << "edge 1 was not created";
        __return_status(TestStatus::FAIL);
    }

    Edge *e2 = BaseControl.join(6, 2, 3);
    if (e2 == NULL) {
        __log_print << "edge 2 was not created";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("Check connectivity");
    if (!BaseControl.isJoint(1,2)) {
        __log_print << "1 & 2 not joint";
        __return_status(TestStatus::FAIL);
    }
    if (!BaseControl.isJoint(1,3)) {
        __log_print << "1 & 3 not joint";
        __return_status(TestStatus::FAIL);
    }
    if (!BaseControl.isJoint(2,3)) {
        __log_print << "2 & 3 not joint";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("Remove Vertices");
    if (!BaseControl.removeVertex(1)) {
        __log_print << "remove fail";
        __return_status(TestStatus::FAIL);
    }
    if (!BaseControl.removeVertex(2)) {
        __log_print << "remove fail";
        __return_status(TestStatus::FAIL);
    }
    if (!BaseControl.removeVertex(3)) {
        __log_print << "remove fail";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
