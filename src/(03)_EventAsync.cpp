/*
 * Copyright (c) 2013 Ghrum Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <GhrumAPI/GhrumAPI.hpp>
#include <Cube_World/Events/PlayerLoginEvent.hpp>

/**
 * Define the player level cap.
 */
#define PLAYER_LEVEL_CAP 100


/**
 * Definition of a custom event.
 */
class CheckPlayerLevelEvent : public Ghrum::Event {
public:
    /**
     * Event custom ctor
     */
    CheckPlayerLevelEvent(Cube::Player & player) {
        player_ = player;
    }
    /**
     * Getter of the event.
     */
    Cube::Player & getPlayer() {
        return player_;
    }
protected:
    Cube::Player & player_;
};

/**
 * Handle when a player joins the server.
 *
 * @param event the event structure.
 */
void handlePlayerLogin(Cube::PlayerLoginEvent & event) {
    // Check if the event was cancelled or if the player level
    // is lower than the requiement.
    if ( event.isCancelled() ) {
        return;
    }

    // Send the custom event to all observers.
    CheckPlayerLevelEvent checkEvent(event.getPlayer());
    Ghrum::GhrumAPI::getEventManager().emitAsync(checkEvent);
}

/**
 * Handle when we need to check for the player level.
 *
 * @param event the event structure.
 */
void handleCheckPlayerLevel(CheckPlayerLevelEvent & event) {
    if ( event.getLevel() < PLAYER_LEVEL_CAP )
        event.getPlayer().kick("Your level is too low to join this server.");
}

/**
 * Function called when the plugin has been enabled.
 *
 * @param plugin reference to this plugin
 */
EXPORT void onPluginEnable(Ghrum::IPlugin & plugin) {
    // Add a new observer for the Cube::PlayerLoginEvent event, with a
    // monitor priority.
    Ghrum::GhrumAPI::getEventManager().addDelegate<Cube::PlayerLoginEvent>(
        plugin, handlePlayerLogin, Ghrum::EventPriority::Monitor);

    // Add a new observer for the CheckPlayerLevelEvent event, with a
    // lowest priority.
    Ghrum::GhrumAPI::getEventManager().addDelegate<CheckPlayerLevelEvent>(
        plugin, handleCheckPlayerLevel, Ghrum::EventPriority::Lowest);
}
