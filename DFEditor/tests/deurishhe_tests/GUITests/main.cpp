#include "TestRunner.h"

#include "test_DFESceneInspectorTree.h"
#include "test_DFESceneInspector.h"

int main(int argc, char *argv[])
{

    int status = 0;

    runTests<test_DFESceneInspectorTree>(argc, argv, &status);
    runTests<test_DFESceneInspector>(argc, argv, &status);
    
    return status;

}
