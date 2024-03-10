#include "Main.h"


int main(int argc, char *argv[])
{
        DnsController DC;
        json Diff = DC.GetDiffrence();

        //DC.Sync();
        //json diff = DC.GetDiffrence();
        cout << Diff.dump(3) <<endl;

    return 0;
}
