
#ifndef OPENAO_LOGIN_ACCOUNT_CONTROLLER_H
#define OPENAO_LOGIN_ACCOUNT_CONTROLLER_H

#include "transport/iclient.h"

#include "account/commands/authenticate.h"
#include "account/commands/entergame.h"

#include "account/events/announcement.h"
#include "account/events/autherror.h"
#include "account/events/characterlist.h"
#include "account/events/redirectserver.h"

#include "account/irepository.h"

#include "character/irepository.h"

#include "branches/branchesservice.h"

using openao::framework::transport::IClient;

using namespace openao::login::branches;
using namespace openao::login::account;

namespace openao::login::account {


class Controller {
public:
  static void authenticate(IClient &client,
                           const commands::Authenticate &command,
                           IRepository &account_repository,
                           character::IRepository &character_repository,
                           BranchesService &branches_service) {

    auto account = account_repository.get(command.username, command.password);

    if (!account) {
      // SEND INVALID USERNAME/PASSWORD MESSAGE.
      events::AuthError error;
      error.message_code = 152;
      client.send(error);
      client.disconnect();
      return;
    }

    // SEND CHARACTER LIST
    auto characters = character_repository.get(account->id);
    events::CharacterList character_list_event;
    for (int i = 0; i < character_list_event.characters.size(); i++) {
      auto &event = character_list_event.characters[i];
      event.account_id = account->id;
      event.account_name = account->username;
      if (i >= characters.size()) { continue; }
      auto &repo = characters[i];
      event.level = repo.level;
      event.faction = repo.faction;
      event.attributes.gender = 1;
      event.attributes.hair_style = 1;
      event.attributes.skin_color = 1;
      event.attributes.hair_color = 1;
      event.attributes.height = 1;
      event.stage = repo.stage;
      event.equipment.head = repo.equipment.head;
      event.equipment.body = repo.equipment.body;
      event.equipment.right_hand = repo.equipment.right_hand;
      event.equipment.left_hand = repo.equipment.left_hand;
      event.equipment.hand = repo.equipment.hand;
      event.equipment.feet = repo.equipment.feet;
      event.equipment.back = repo.equipment.back;
      event.equipment.ride = repo.equipment.ride;
      event.shape = repo.shape;
      event.character_id = repo.id;
      event.character_name = repo.name;
      event.stats.current_hp = 200;
      event.stats.current_mp = 200;
      event.title = repo.title;
      character_list_event.total_mps[i] = 200;
      character_list_event.total_hps[i] = 200;
      character_list_event.blood_types[i] = 1;
      character_list_event.active_skills[i] = {};
    }
    character_list_event.slots = account->slots;
    character_list_event.branches.statuses =
            branches_service.get_branch_statuses();
    client.send(character_list_event);
  }

  static void enter_game(IClient &client, const commands::EnterGame &command) {
    events::RedirectServer redirect_server;
    redirect_server.ip = "127.0.0.1";
    redirect_server.port = 30001;
    redirect_server.session = 1;

    client.send(redirect_server);
  }
};

}// namespace openao::login::account

#endif// OPENAO_LOGIN_ACCOUNT_CONTROLLER_H
