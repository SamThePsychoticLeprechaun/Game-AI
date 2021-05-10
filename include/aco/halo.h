#ifndef __aco_halo_h
#define __aco_halo_h

#pragma once

#include <array>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <random>

namespace aco {
    namespace halo {
        std::default_random_engine generator;

        constexpr size_t dim_to_padded_dim(size_t map_dim);
        constexpr size_t dim_to_size(size_t map_dim);

        template <size_t MapSize>
        constexpr std::array<float, MapSize> initialise_pheromone_map();

        template <size_t MapSize>
        constexpr std::array<uint16_t, MapSize> initialise_ant_count_map();

        template <size_t MapSize>
        struct AntColony {
            std::array<float,    MapSize> pheromone_map = initialise_pheromone_map<MapSize>();
            std::array<char,     MapSize> actual_map;
            std::array<uint16_t, MapSize> ant_count_map = initialise_ant_count_map<MapSize>();

            size_t start_idx;
            size_t end_idx;
        };

        template <size_t MapSize, size_t MaxSteps>
        struct Ant {
            AntColony<MapSize>* colony;

            bool has_food = false;

            // TODO: This shouldn't really be a fixed amount, needs to be somehow
            //       set dynamically. If we want to keep it non-dynamic, then we
            //       would either have to have a pool that ants share and the ant
            //       count be made dynamic, or subdivide the space being searched.
            std::array<size_t, MaxSteps> previous_node_indices;
            size_t current_node_idx;
            size_t steps_taken = 0;
            size_t path_length = 0;
        };

        template <size_t MapDim>
        constexpr void zero_halo_of_pheromone_map(AntColony<dim_to_size(MapDim)>* ant_colony);

        template <size_t MapDim, size_t MaxSteps>
        size_t choose_next_node(Ant<dim_to_size(MapDim), MaxSteps>* ant);

        template <size_t MapDim, size_t MaxSteps>
        void do_simulation(std::string tag, size_t iterations, const char* actual_map_ptr, size_t ant_count, float pheromone_increment, float pheromone_evaporation);
    };
};

#include "halo.inl"

#endif // __aco_halo_h
