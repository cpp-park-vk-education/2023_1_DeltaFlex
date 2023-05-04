#include "TestRunner.h"

#include "test_DFESceneInspectorTree.h"

int main(int argc, char *argv[])
{

    int status = 0;

    runTests<test_DFESceneInspectorTree>(argc, argv, &status);
    
    return status;

}
