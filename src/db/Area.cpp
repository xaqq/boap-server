#include "Log.hpp"
#include "db/Area.hpp"
#include "db/GameObjectSpawn.hpp"
#include "odb_gen/GameObjectSpawn_odb.h"
#include <unistd.h>
using namespace DB;

Area::GameObjectSpawnVector Area::spawnData()
{
    GameObjectSpawnVector ret;
    for (auto &spawnInfoWeakPtr : goSpawnData_)
    {
        INFO("HERE");
        ret.push_back(spawnInfoWeakPtr.load());

        sleep(10);
    }
    return ret;
}
