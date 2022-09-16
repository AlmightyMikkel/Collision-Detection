// application.cpp

#include "application.hpp"

namespace runner
{
    void Application::run()
    {
        const sf::VideoMode mode{ 1000, 1000 };
        const sf::Uint32 flags = sf::Style::Titlebar | sf::Style::Close;
        m_window.create(mode, "pineapple", flags);

        if (!font.loadFromFile("assets/Arialn.ttf")) {
            return;
        }

        text.setFont(font);
        text.setString("TEST");
        text.setCharacterSize(500);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setPosition(200,200);
        if (!m_window.isOpen() || !enter()) {
            return;
        }

        m_window.setKeyRepeatEnabled(false);
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::MouseMoved) {
                    on_mouse_move({ float(event.mouseMove.x), float(event.mouseMove.y) });
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    on_button_pressed(event.mouseButton.button);
                }
                else if (event.type == sf::Event::MouseButtonReleased) {
                    on_button_released(event.mouseButton.button);
                }
                else if (event.type == sf::Event::KeyPressed) {
                    on_key_pressed(event.key.code);
                }
                else if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }

            if (!update()) {
                m_window.close();
            }

            render();
        }

        exit();
    }

    bool Application::enter()
    {
        return true;
    }

    void Application::exit()
    {
    }

    bool Application::update()
    {

        m_deltatime = m_clock.restart();

        return m_running;
    }


    bool check_collision(PrimitiveBatch& a, PrimitiveBatch& b) {
        return false;

    }


   void Application::render()
   {
      m_batch.clear();
      { 
          sf::Vector2f size = { 15,15 };
          sf::FloatRect rect{ m_mouse_position - sf::Vector2f(size.x / 2, size.y / 2), size};
          sf::Color rectColor{ 255,0,0,255 };
          switch (state)
          {
          case State::CirclevsCircle:
              text.setString("Circle vs Circle");
              m_batch.draw_circle(m_mouse_position, 15.0f, 12, 1.0f, sf::Color::Green);
              break;
          case State::CirclevsAABB:
              text.setString("Circle vs AABB");
              m_batch.draw_circle(m_mouse_position, 15.0f, 12, 1.0f, sf::Color::Blue);
              break;
          case State::CirclevsLine:
              text.setString("Circle vs Line Segment");
              m_batch.draw_circle(m_mouse_position, 15.0f, 12, 1.0f, sf::Color::Red);
              break;
          case State::AABBvsAABB:
              text.setString("AABB vs AABB");
              m_batch.draw_rectangle(rect, 1, rectColor);
              break;
          default:
              break;
          }

          m_window.draw(text); //Doesnt show up?

      }
      
      m_window.clear(sf::Color{ 0x44, 0x55, 0x66, 0xff });
      m_batch.present(m_window);
      m_window.display();
   }

   void Application::on_mouse_move(const sf::Vector2f &position) 
   {
      m_mouse_position = position;
   }

   void Application::on_key_pressed(const sf::Keyboard::Key key)
   {
       if (key == sf::Keyboard::Key::Escape) {
           m_running = false;
       }

       //Menu
       if (key == sf::Keyboard::Key::Num1) {
           //Circle vs circle
           state = State::CirclevsCircle;
       }
       else if (key == sf::Keyboard::Key::Num2) {
           //Circle vs Axis-aligned bounding box
           state = State::CirclevsAABB;
       }
       else if (key == sf::Keyboard::Key::Num3)
       {
           //Circle vs line segment
           state = State::CirclevsLine;
       }
       else if (key == sf::Keyboard::Key::Num4) {
           //Axis-aligned bounding box vs Axis-aligned bounding box
           state = State::AABBvsAABB;
       }

   }

   void Application::on_key_released(const sf::Keyboard::Key key)
   {
   }

   void Application::on_button_pressed(const  sf::Mouse::Button button)
   {
   }

   void Application::on_button_released(const sf::Mouse::Button button)
   {
   }
} // !runner
