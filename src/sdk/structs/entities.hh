//
//  ruvi base
//

// includes
#include "../memory/memory.hh"
#include "../netvars/netvars.hh"
#include "../valve/iclientnetworkable.hh"
#include "../valve/iclientrenderable.hh"
#include "../vector/matrix3x4.hh"
#include "../vector/vector.hh"

enum cs_team_id_t {
  NONE = 0,
  SPECTATOR = 1,
  TERRORIST = 2,
  COUNTER_TERRORIST = 3
};

enum entity_flags_t {
  ON_GROUND = (1 << 0),
  DUCKING = (1 << 1),
  PARTIAL_GROUND = (1 << 17),
  STEP_MOVEMENT = (1 << 21),
  UNBLOCKABLE_BY_PLAYER = (1 << 30)
};

enum item_definition_index_t : int {
  INVALID = -1,
  WEAPON_NONE = 0,
  WEAPON_DEAGLE,
  WEAPON_ELITE,
  WEAPON_FIVESEVEN,
  WEAPON_GLOCK,
  WEAPON_AK47 = 7,
  WEAPON_AUG,
  WEAPON_AWP,
  WEAPON_FAMAS,
  WEAPON_G3SG1,
  WEAPON_GALILAR = 13,
  WEAPON_M249,
  WEAPON_M4A1 = 16,
  WEAPON_MAC10,
  WEAPON_P90 = 19,
  WEAPON_MP5 = 23,
  WEAPON_UMP45,
  WEAPON_XM1014,
  WEAPON_BIZON,
  WEAPON_MAG7,
  WEAPON_NEGEV,
  WEAPON_SAWEDOFF,
  WEAPON_TEC9,
  WEAPON_TASER,
  WEAPON_HKP2000,
  WEAPON_MP7,
  WEAPON_MP9,
  WEAPON_NOVA,
  WEAPON_P250,
  WEAPON_SHIELD,
  WEAPON_SCAR20,
  WEAPON_SG556,
  WEAPON_SSG08,
  KNIFE_GG,
  KNIFE_CT,
  WEAPON_FLASHBANG,
  WEAPON_HEGRENADE,
  WEAPON_SMOKEGRENADE,
  WEAPON_MOLOTOV,
  WEAPON_DECOY,
  WEAPON_INCGRENADE,
  WEAPON_C4,
  WEAPON_HEALTHSHOT = 57,
  KNIFE_T = 59,
  WEAPON_M4A1_SILENCER,
  WEAPON_USP_SILENCER,
  WEAPON_CZ75A = 63,
  WEAPON_REVOLVER,
  WEAPON_TAGRENADE = 68,
  WEAPON_FISTS,
  WEAPON_BREACHCHARGE,
  WEAPON_TABLET = 72,
  WEAPON_MELEE = 74,
  WEAPON_AXE,
  WEAPON_HAMMER,
  WEAPON_SPANNER = 78,
  KNIFE_GHOST = 80,
  WEAPON_FIREBOMB,
  WEAPON_DIVERSION,
  WEAPON_FRAG_GRENADE,
  WEAPON_SNOWBALL,
  WEAPON_BUMPMINE,
  KNIFE_BAYONET = 500,
  KNIFE_FLIP = 505,
  KNIFE_GUT,
  KNIFE_KARAMBIT,
  KNIFE_M9_BAYONET,
  KNIFE_TACTICAL,
  KNIFE_FALCHION = 512,
  KNIFE_BOWIE = 514,
  KNIFE_BUTTERFLY,
  KNIFE_PUSH,
  KNIFE_URSUS = 519,
  KNIFE_NAVAJA,
  KNIFE_STILETTO = 522,
  KNIFE_TALON,
  GLOVE_STUDDED_BLOODHOUND = 5027,
  GLOVE_T_SIDE = 5028,
  GLOVE_CT_SIDE = 5029,
  GLOVE_SPORTY = 5030,
  GLOVE_SLICK = 5031,
  GLOVE_LEATHER_WRAP = 5032,
  GLOVE_MOTORCYCLE = 5033,
  GLOVE_SPECIALIST = 5034,
  GLOVE_HYDRA = 5035,
  WEAPON_MAX
};

struct entity_t : public i_client_networkable, public i_client_renderable {

  inline bool is_valid() {

    entity_t *local_player =
        reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
            csgo::engine_client->get_local_player()));

    if (!this)
      return false;

    if (IClientNetworkable()->is_dormant())
      return false;

    if (m_iHealth() == 0)
      return false;

    if (this == local_player)
      return false;

    return true;
  }

  inline vector3d get_bone_position(int i) {

    matrix3x4_t matrix[128];

    if (setup_bones(matrix, 128, 0x100, 0))
      return vector3d(matrix[i][0][3], matrix[i][1][3], matrix[i][2][3]);

    return {};
  }

  inline vector3d get_head_position() { return get_bone_position(8); }

  inline vector3d get_eye_position() {
    return m_vecOrigin() + m_vecViewOffset();
  }

  inline vector3d get_abs_origin() {
    return memory::vfunc<12, const vector3d &>(this);
  }

  void set_model_index(int index) {
    return memory::vfunc<111, void>(this, index);
  }

  //
  // offsets goes here
  //
  OFFSET_PTR(i_client_networkable, IClientNetworkable, 0x10);
  OFFSET(qangle, m_angEyeAngles, 0x8 + 0x4);

  //
  // netvars goes here
  //
  NETVAR(int, m_iHealth, "DT_CSPlayer", "m_iHealth");
  NETVAR(int, m_iTeamNum, "DT_CSPlayer", "m_iTeamNum");
  NETVAR(vector3d, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin");
  NETVAR(vector3d, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
};

struct weapon_t {

  //
  // netvars goes here
  //
};