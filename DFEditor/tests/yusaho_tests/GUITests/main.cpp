#include "TestRunner.h"

#include "test_DFEAssetViewer.h"
#include "test_DFEExpandingWidget.h"
#include "test_DFEProjectExplorer.h"
#include "test_DFEContentManager.h"

int main(int argc, char *argv[])
{

    int status = 0;

    runTests<test_DFEAssetViewer>(argc, argv, &status);
    runTests<test_DFEExpandingWidget>(argc, argv, &status);
    runTests<test_DFEProjectExplorer>(argc, argv, &status);
    runTests<test_DFEContentManager>(argc, argv, &status);

    return status;

}
