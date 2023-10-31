#include "gamedata.h"

#include "../../util/csv/csv.h"

void GameData::load() {
  this->loadExperience();
  this->loadMoves();
  this->loadStats();
  this->loadTypeNames();
  this->loadPokemonMoves();
  this->loadPokemonSpecies();
  this->loadPokemonStats();
  this->loadPokemonTypes();
  this->loadPokemon();
}

void GameData::loadMoves() {
  CSV* movesCSV = new CSV(this->sourceDirectory + "moves.csv");

  for (int i = 0; i < movesCSV->data.size(); i++) {
    Move move;
    move.fromCSV(movesCSV->data[i]);
    this->moves.insert(std::pair<int, Move>(move.id, move));
  }

  debug("Loaded " + std::to_string(movesCSV->data.size()) + " moves.");

  delete movesCSV;
}

void GameData::loadStats() {
  CSV* statsCSV = new CSV(this->sourceDirectory + "stats.csv");

  for (int i = 0; i < statsCSV->data.size(); i++) {
    Stat stat;
    stat.fromCSV(statsCSV->data[i]);
    this->stats.insert(std::pair<int, Stat>(stat.id, stat));
  }

  debug("Loaded " + std::to_string(statsCSV->data.size()) + " stats.");

  delete statsCSV;
}

void GameData::loadExperience() {
  CSV* experienceCSV = new CSV(this->sourceDirectory + "experience.csv");

  for (int i = 0; i < experienceCSV->data.size(); i++) {
    Experience experience;
    experience.fromCSV(experienceCSV->data[i]);
    this->experience.insert(
        std::pair<int, Experience>(experience.growth_rate_id, experience));
  }

  debug("Loaded " + std::to_string(experienceCSV->data.size()) +
        " experience entries.");

  delete experienceCSV;
}

void GameData::loadTypeNames() {
  CSV* typeNamesCSV = new CSV(this->sourceDirectory + "type_names.csv");

  for (int i = 0; i < typeNamesCSV->data.size(); i++) {
    TypeName typeName;
    typeName.fromCSV(typeNamesCSV->data[i]);

    if (typeName.local_language_id != 9) {
      continue;
    }

    this->typeNames.insert(
        std::pair<int, TypeName>(typeName.type_id, typeName));
  }

  debug("Loaded " + std::to_string(typeNamesCSV->data.size()) + " type names.");

  delete typeNamesCSV;
}

void GameData::loadPokemonMoves() {
  CSV* pokemonMovesCSV = new CSV(this->sourceDirectory + "pokemon_moves.csv");

  for (int i = 0; i < pokemonMovesCSV->data.size(); i++) {
    PokemonMove pokemonMove;
    pokemonMove.fromCSV(pokemonMovesCSV->data[i]);
    this->pokemonMoves.push_back(pokemonMove);
  }

  debug("Loaded " + std::to_string(pokemonMovesCSV->data.size()) +
        " pokemon moves.");

  delete pokemonMovesCSV;
}

void GameData::loadPokemonSpecies() {
  CSV* pokemonSpeciesCSV =
      new CSV(this->sourceDirectory + "pokemon_species.csv");

  for (int i = 0; i < pokemonSpeciesCSV->data.size(); i++) {
    PokemonSpecies pokemonSpecies;
    pokemonSpecies.fromCSV(pokemonSpeciesCSV->data[i]);
    this->pokemonSpecies.insert(
        std::pair<int, PokemonSpecies>(pokemonSpecies.id, pokemonSpecies));
  }

  debug("Loaded " + std::to_string(pokemonSpeciesCSV->data.size()) +
        " pokemon species.");

  delete pokemonSpeciesCSV;
}

void GameData::loadPokemonStats() {
  CSV* pokemonStatsCSV = new CSV(this->sourceDirectory + "pokemon_stats.csv");

  for (int i = 0; i < pokemonStatsCSV->data.size(); i++) {
    PokemonStat pokemonStat;
    pokemonStat.fromCSV(pokemonStatsCSV->data[i]);
    this->pokemonStats.push_back(pokemonStat);
  }

  debug("Loaded " + std::to_string(pokemonStatsCSV->data.size()) +
        " pokemon stats.");

  delete pokemonStatsCSV;
}

void GameData::loadPokemonTypes() {
  CSV* pokemonTypesCSV = new CSV(this->sourceDirectory + "pokemon_types.csv");

  for (int i = 0; i < pokemonTypesCSV->data.size(); i++) {
    PokemonType pokemonType;
    pokemonType.fromCSV(pokemonTypesCSV->data[i]);
    this->pokemonTypes.push_back(pokemonType);
  }

  debug("Loaded " + std::to_string(pokemonTypesCSV->data.size()) +
        " pokemon types.");

  delete pokemonTypesCSV;
}

void GameData::loadPokemon() {
  CSV* pokemonCSV = new CSV(this->sourceDirectory + "pokemon.csv");

  for (int i = 0; i < pokemonCSV->data.size(); i++) {
    Pokemon pokemon;
    pokemon.fromCSV(pokemonCSV->data[i]);
    this->pokemon.insert(std::pair<int, Pokemon>(pokemon.id, pokemon));
  }

  debug("Loaded " + std::to_string(pokemonCSV->data.size()) + " pokemon.");

  delete pokemonCSV;
}

void GameData::printPokemon() {
  for (int i = 0; i < this->pokemon.size(); i++) {
    Pokemon pokemon = this->pokemon[i];

    std::cout << pokemon.id << " " << pokemon.identifier << " "
              << pokemon.species_id << " " << pokemon.height << " "
              << pokemon.weight << " " << pokemon.base_experience << " "
              << pokemon.order << " " << pokemon.is_default << std::endl;
  }
}

void GameData::printMoves() {
  for (int i = 0; i < this->moves.size(); i++) {
    Move move = this->moves[i];

    std::cout << move.id << " " << move.identifier << " " << move.generation_id
              << " " << move.type_id << " " << move.power << " " << move.pp
              << " " << move.accuracy << " " << move.priority << " "
              << move.target_id << " " << move.damage_class_id << " "
              << move.effect_id << " " << move.effect_chance << " "
              << move.contest_type_id << " " << move.contest_effect_id << " "
              << move.super_contest_effect_id << std::endl;
  }
}

void GameData::printStats() {
  for (int i = 0; i < this->stats.size(); i++) {
    Stat stat = this->stats[i];

    std::cout << stat.id << " " << stat.damage_class_id << " "
              << stat.identifier << " " << stat.is_battle_only << " "
              << stat.game_index << std::endl;
  }
}

void GameData::printExperience() {
  for (int i = 0; i < this->experience.size(); i++) {
    Experience experience = this->experience[i];

    std::cout << experience.growth_rate_id << " " << experience.level << " "
              << experience.experience << std::endl;
  }
}

void GameData::printTypeNames() {
  for (int i = 0; i < this->typeNames.size(); i++) {
    TypeName typeName = this->typeNames[i];

    std::cout << typeName.type_id << " " << typeName.local_language_id << " "
              << typeName.name << std::endl;
  }
}

void GameData::printPokemonMoves() {
  for (int i = 0; i < this->pokemonMoves.size(); i++) {
    PokemonMove pokemonMove = this->pokemonMoves[i];

    std::cout << pokemonMove.pokemon_id << " " << pokemonMove.version_group_id
              << " " << pokemonMove.move_id << " "
              << pokemonMove.pokemon_move_method_id << " " << pokemonMove.level
              << " " << pokemonMove.order << std::endl;
  }
}

void GameData::printPokemonSpecies() {
  /*
    int id;
  std::string identifier;
  int generation_id;
  int evolves_from_species_id;
  int evolution_chain_id;
  int color_id;
  int shape_id;
  int habitat_id;
  int gender_rate;
  int capture_rate;
  int base_happiness;
  bool is_baby;
  int hatch_counter;
  bool has_gender_differences;
  int growth_rate_id;
  bool forms_switchable;
  bool is_legendary;
  bool is_mythical;
  int order;
  int conquest_order;*/

  for (int i = 0; i < this->pokemonSpecies.size(); i++) {
    PokemonSpecies pokemonSpecies = this->pokemonSpecies[i];

    std::cout << pokemonSpecies.id << " " << pokemonSpecies.identifier << " "
              << pokemonSpecies.generation_id << " "
              << pokemonSpecies.evolves_from_species_id << " "
              << pokemonSpecies.evolution_chain_id << " "
              << pokemonSpecies.color_id << " " << pokemonSpecies.shape_id
              << " " << pokemonSpecies.habitat_id << " "
              << pokemonSpecies.gender_rate << " "
              << pokemonSpecies.capture_rate << " "
              << pokemonSpecies.base_happiness << " " << pokemonSpecies.is_baby
              << " " << pokemonSpecies.hatch_counter << " "
              << pokemonSpecies.has_gender_differences << " "
              << pokemonSpecies.growth_rate_id << " "
              << pokemonSpecies.forms_switchable << " "
              << pokemonSpecies.is_legendary << " "
              << pokemonSpecies.is_mythical << " " << pokemonSpecies.order
              << " " << pokemonSpecies.conquest_order << std::endl;
  }
}

void GameData::printPokemonStats() {
  for (int i = 0; i < this->pokemonStats.size(); i++) {
    PokemonStat pokemonStat = this->pokemonStats[i];

    std::cout << pokemonStat.pokemon_id << " " << pokemonStat.stat_id << " "
              << pokemonStat.base_stat << " " << pokemonStat.effort
              << std::endl;
  }
}

void GameData::printPokemonTypes() {
  for (int i = 0; i < this->pokemonTypes.size(); i++) {
    PokemonType pokemonType = this->pokemonTypes[i];

    std::cout << pokemonType.pokemon_id << " " << pokemonType.type_id << " "
              << pokemonType.slot << std::endl;
  }
}