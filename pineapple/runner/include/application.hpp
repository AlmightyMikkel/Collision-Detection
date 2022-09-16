// application.hpp

#pragma once

#include "batch.hpp"

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
      sf::Font         font;
      sf::Text         text;
      State            state;
   };
} // !runner
