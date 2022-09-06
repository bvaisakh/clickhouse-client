#include <iostream>
#include <clickhouse/client.h>

using namespace clickhouse;
using namespace std;

int main() {
/// Initialize client connection.
    Client client(ClientOptions().SetHost("localhost").SetPort(9100));

    ServerInfo serverInfo = client.GetServerInfo();
    cout << "Server Name: " << serverInfo.name << endl;
    cout << "Server TimeZone: " << serverInfo.timezone << endl;
    cout << "Display Name: " << serverInfo.display_name << endl;
    cout << "Version Major: " << serverInfo.version_major << endl;
    cout << "Version Minor: " << serverInfo.version_minor << endl;
    cout << "Version Patch: " << serverInfo.version_patch << endl;
    cout << "Revision: " << serverInfo.revision << endl;

/// Create a table.
    client.Execute("CREATE TABLE IF NOT EXISTS test.numbers (id UInt64, name String) ENGINE = Memory");

/// Insert some values.
    {
        Block block;

        auto id = std::make_shared<ColumnUInt64>();
        id->Append(1);
        id->Append(7);

        auto name = std::make_shared<ColumnString>();
        name->Append("one");
        name->Append("seven");

        block.AppendColumn("id", id);
        block.AppendColumn("name", name);

        client.Insert("test.numbers", block);
    }

/// Select values inserted in the previous step.
    client.Select("SELECT id, name FROM test.numbers", [](const Block &block) {
        for (size_t i = 0; i < block.GetRowCount(); ++i) {
            std::cout << block[0]->As<ColumnUInt64>()->At(i) << " " << block[1]->As<ColumnString>()->At(i) << "\n";
        }
    });

/// Delete table.
    client.Execute("DROP TABLE test.numbers");
}