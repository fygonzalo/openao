
#ifndef OPENAO_EXPERIMENTAL_GAME_ITEMMALL_CONTROLLER_H
#define OPENAO_EXPERIMENTAL_GAME_ITEMMALL_CONTROLLER_H

#include "experimental/transport/iclient.h"

#include "experimental/game/account/accountmanager.h"
#include "experimental/game/itemmall/loadangelgoldevent.h"
#include "experimental/game/itemmall/opencommand.h"
#include "experimental/game/itemmall/service.h"

using namespace openao::experimental::game::account;

namespace openao::experimental::game::itemmall {

class ItemMallController {
public:
  static void open_mall(IClient &client, const OpenCommand &command,
                        AccountManager& account_manager,
                        MallService mall_service) {
    auto account_id = account_manager.get_account_by_client(client);

    LoadAngelGoldEvent load_event{};
    load_event.amount = mall_service.get_ag_by_account(account_id);

    client.send(load_event);
  }
};

}// namespace openao::experimental::game::itemmall

#endif// OPENAO_EXPERIMENTAL_GAME_ITEMMALL_CONTROLLER_H
