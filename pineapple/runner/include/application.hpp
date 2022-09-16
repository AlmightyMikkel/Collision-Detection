// application.hpp

#pragma once

#include "batch.hpp"
#include "object.h"
#include "collision_detection.h"

namespace runner
{
   class Application final
   {
       enum class State {
           CirclevsCircle,
           CirclevsAABB,
           CirclevsLine,
           AABBvsAABB
       };

   public:
      Application() = default;

      void run();

   private:
      bool enter();
      void exit();
      bool update();
      void render();

   private:
      void on_mouse_move(const sf::Vector2f &position);
      void on_key_pressed(const sf::Keyboard::Key key);
      void on_key_released(const sf::Keyboard::Key key);
      void on_button_pressed(const sf::Mouse::Button button);
      void on_button_released(const sf::Mouse::Button button);

   private:
      sf::RenderWindow m_window;
      PrimitiveBatch   m_batch;
      bool             m_running = true;
      sf::Clock        m_clock;
      sf::Time         m_deltatime;
      sf::Vector2f     m_mouse_position; 
      sf::Vector2u     center;
      object           circle;
      object           static_circle; //Spawn at random position for more fun
      object           aabb;
      object           static_aabb;//Spawn at random position for more fun
      object           static_line; //Draw the line at random positions for more fun
      collision_detection detector;
      sf::Font         font;
      sf::Text         text;
      State            state;
   };
} // !runner
