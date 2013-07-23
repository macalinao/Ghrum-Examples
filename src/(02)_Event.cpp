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
 * Handle when a player joins the server.
 *
 * @param event the event structure.
 */
void handleCheckPlayerLevel(Cube::PlayerLoginEvent & event) {
    // Check if the event was cancelled or if the player level
    // is lower than the requiement.
    if ( !event.isCancelled() && event.getPlayer().getLevel() < PLAYER_LEVEL_CAP )
        event.kick("Your level is too low to join this server.");
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
        plugin, handleCheckPlayerLevel, Ghrum::EventPriority::Monitor);
}

/**
 * Function called when the plugin has been disabled.
 *
 * @param plugin reference to this plugin
 */
EXPORT void onPluginDisable(Ghrum::IPlugin & plugin) {
    // We don't need to release the delegate here since the platform will
    // do it itself.
}
