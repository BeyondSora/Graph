#include "../_include/test_ModelLogicControl.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"

TestStatus ModelLogicControl::run ()
{
    __enter;

    TestStatus testStatus = TestStatus::FAIL;
    if (!((testStatus = GraphCreation()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = VertexCreation()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = VertexConnection()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = VertexDisconnection()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = VertexRemoval()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = GraphRemoval()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::GraphCreation ()
{
    __enter;
    __checkpoint("New Graph Creation");
    Identity g1 = LogicControl.newGraph();
    if (g1 != 1) {
        __log_print << "Graph_1 id != 1";
        __return_status(TestStatus::FAIL);
    }
    Identity g2 = LogicControl.newGraph();
    if (g2 != 2) {
        __log_print << "Graph_2 id != 2";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexCreation ()
{
    __enter;
    __checkpoint("New Vertex Creation");

    Identity v1 = LogicControl.newVertex(1);
    if (v1 != 3) {
        __log_print << "Vertex_1 id != 3";
        __return_status(TestStatus::FAIL);
    }
    Identity v2 = LogicControl.newVertex(1);
    if (v2 != 4) {
        __log_print << "Vertex_2 id != 4";
        __return_status(TestStatus::FAIL);
    }
    Identity v3 = LogicControl.newVertex(2);
    if (v3 != 5) {
        __log_print << "Vertex_3 id != 5";
        __return_status(TestStatus::FAIL);
    }
    Identity v4 = LogicControl.newVertex(2);
    if (v4 != 6) {
        __log_print << "Vertex_4 id != 6";
        __return_status(TestStatus::FAIL);
    }
    Identity v5 = LogicControl.newVertex(2);
    if (v5 != 7) {
        __log_print << "Vertex_5 id != 7";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexConnection ()
{
    __enter;
    __checkpoint("Join Vertices");

    if (LogicControl.join(3, 4) == false) {
        __log_print << "Cannot join 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(5, 6) == false) {
        __log_print << "Cannot join 5 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(5, 7) == false) {
        __log_print << "Cannot join 5 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(5, 7) == true) {
        __log_print << "Joint 5 & 7 for a second time";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(3, 7) == true) {
        __log_print << "Joint 3 & 7, but they are from different graphs";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexDisconnection ()
{
    __enter;
    __checkpoint("Disjoin Vertices");

    if (LogicControl.disjoin(3, 4) == false) {
        __log_print << "Cannot disjoin 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.disjoin(5, 6) == false) {
        __log_print << "Cannot disjoin 5 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.disjoin(5, 7) == false) {
        __log_print << "Cannot disjoin 5 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.disjoin(5, 7) == true) {
        __log_print << "Disjoint 5 & 7 for a second time";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.disjoin(3, 7) == true) {
        __log_print << "disjoint 3 & 7, but they are from different graphs"
                       " and are not connected";
        __return_status(TestStatus::FAIL);
    }
    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexRemoval ()
{
    __enter;
    __checkpoint("Remove Vertex");

    if (!LogicControl.remVertex(3)) {
        __log_print << "Cannot remove Vertex_1";
        __return_status(TestStatus::FAIL);
    }
    if (!LogicControl.remVertex(6)) {
        __log_print << "Cannot remove Vertex_4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.remVertex(3)) {
        __log_print << "Vertex_1 was removed twice";
        __return_status(TestStatus::FAIL);
    }
    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::GraphRemoval ()
{
    __enter;
    __checkpoint("Remove Graph");

    if (!LogicControl.remGraph(1)) {
        __log_print << "Cannot remove Graph_1";
        __return_status(TestStatus::FAIL);
    }
    if (!LogicControl.remGraph(2)) {
        __log_print << "Cannot remove Graph_2";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}