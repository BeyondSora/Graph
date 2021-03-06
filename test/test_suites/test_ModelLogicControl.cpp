#include "../_include/test_ModelLogicControl.h"

// Dependencies
#include "../_include/test_Log.h"

ModelLogicControl::ModelLogicControl ()
: stack_(),
  base_(stack_),
  logic_(base_)
{
}

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
    Identity g1 = logic_.newGraph();
    if (g1 != 1) {
        __log_print << "Graph_1 id != 1";
        __return_status(TestStatus::FAIL);
    }
    Identity g2 = logic_.newGraph();
    if (g2 != 2) {
        __log_print << "Graph_2 id != 2";
        __return_status(TestStatus::FAIL);
    }

    if (!logic_.hasGraph(g1) ||
        !logic_.hasGraph(g2)) {
        __log_print << "Graphs do not exist";
        __return_status(TestStatus::FAIL);
    }

    Graph::GraphList list = logic_.allGraphs();
    if (list.find(1) == list.end() ||
        list.find(2) == list.end()) {
        __log_print << "Cannot find graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexCreation ()
{
    __enter;
    __checkpoint("New Vertex Creation");

    Identity v1 = logic_.newVertex(1);
    if (v1 != 3) {
        __log_print << "Vertex_1 id != 3";
        __return_status(TestStatus::FAIL);
    }
    Identity v2 = logic_.newVertex(1);
    if (v2 != 4) {
        __log_print << "Vertex_2 id != 4";
        __return_status(TestStatus::FAIL);
    }
    Identity v3 = logic_.newVertex(2);
    if (v3 != 5) {
        __log_print << "Vertex_3 id != 5";
        __return_status(TestStatus::FAIL);
    }
    Identity v4 = logic_.newVertex(2);
    if (v4 != 6) {
        __log_print << "Vertex_4 id != 6";
        __return_status(TestStatus::FAIL);
    }
    Identity v5 = logic_.newVertex(2);
    if (v5 != 7) {
        __log_print << "Vertex_5 id != 7";
        __return_status(TestStatus::FAIL);
    }

    if (!logic_.hasVertex(v1) ||
        !logic_.hasVertex(v2) ||
        !logic_.hasVertex(v3) ||
        !logic_.hasVertex(v4) ||
        !logic_.hasVertex(v5)) {
        __log_print << "Vertices do not exist";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.graphOf(v1) != 1) {
        __log_print << "v1 is not in g1";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.graphOf(v2) != 1) {
        __log_print << "v2 is not in g1";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.graphOf(v3) != 2) {
        __log_print << "v3 is not in g2";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.graphOf(v4) != 2) {
        __log_print << "v4 is not in g2";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.graphOf(v5) != 2) {
        __log_print << "v5 is not in g2";
        __return_status(TestStatus::FAIL);
    }

    Graph::VertexList list = logic_.allVertices();
    if (list.find(3) == list.end() ||
        list.find(4) == list.end() ||
        list.find(5) == list.end() ||
        list.find(5) == list.end() ||
        list.find(7) == list.end()) {
        __log_print << "Cannot find graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexConnection ()
{
    __enter;
    __checkpoint("Join Vertices");

    if (logic_.join(3, 4) == false) {
        __log_print << "Cannot join 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(5, 6) == false) {
        __log_print << "Cannot join 5 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(5, 7) == false) {
        __log_print << "Cannot join 5 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(6, 7) == false) {
        __log_print << "Cannot join 6 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(5, 7) == true) {
        __log_print << "Joint 5 & 7 for a second time";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(3, 7) == true) {
        __log_print << "Joint 3 & 7, but they are from different graphs";
        __return_status(TestStatus::FAIL);
    }

    if (!logic_.isJointBetween(3, 4) ||
        !logic_.isJointBetween(5, 6)) {
        __log_print << "vertices are not joint";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.isJointBetween(3, 6)) {
        __log_print << "vertices not joint are said to be joint";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexDisconnection ()
{
    __enter;
    __checkpoint("Disjoin Vertices");

    if (logic_.disjoin(3, 4) == false) {
        __log_print << "Cannot disjoin 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.disjoin(5, 6) == false) {
        __log_print << "Cannot disjoin 5 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.disjoin(5, 7) == false) {
        __log_print << "Cannot disjoin 5 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.disjoin(5, 7) == true) {
        __log_print << "Disjoint 5 & 7 for a second time";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.disjoin(3, 7) == true) {
        __log_print << "disjoint 3 & 7, but they are from different graphs"
                       " and are not connected";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.isJointBetween(3, 7)) {
        __log_print << "vertices not joint are said to be joint";
        __return_status(TestStatus::FAIL);
    }
    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::VertexRemoval ()
{
    __enter;
    __checkpoint("Remove Vertex");

    if (!logic_.remVertex(3)) {
        __log_print << "Cannot remove Vertex_1";
        __return_status(TestStatus::FAIL);
    }
    if (!logic_.remVertex(6)) {
        __log_print << "Cannot remove Vertex_4";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.remVertex(3)) {
        __log_print << "Vertex_1 was removed twice";
        __return_status(TestStatus::FAIL);
    }
    __return_status(TestStatus::PASS);
}

TestStatus ModelLogicControl::GraphRemoval ()
{
    __enter;
    __checkpoint("Remove Graph");

    if (!logic_.remGraph(1)) {
        __log_print << "Cannot remove Graph_1";
        __return_status(TestStatus::FAIL);
    }
    if (!logic_.remGraph(2)) {
        __log_print << "Cannot remove Graph_2";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
