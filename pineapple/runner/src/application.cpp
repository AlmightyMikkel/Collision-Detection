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

        center = { m_window.getSize().x / 2, m_window.getSize().y / 2 };

        text.setFont(font);
        text.setString("TEST");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setPosition(400,50);

        circle.set_size(15, 0);
        circle.set_color(sf::Color::Red);
        circle.set_sections(12);
        circle.tag = tag::circle;

        aabb.set_size(20, 20);
        aabb.set_color(sf::Color::Red);
        aabb.tag = tag::aabb;

        static_circle.set_color(sf::Color::Red);
        static_circle.set_sections(30);
        static_circle.tag = tag::circle;

        static_aabb.set_color(sf::Color::Red);
        static_aabb.tag = tag::aabb;

        static_line.set_color(sf::Color::Red);
        static_line.tag = tag::line;


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

          switch (state)
          {
          case State::CirclevsCircle:
              text.setString("Circle vs Circle");

              circle.set_position(m_mouse_position);
              m_batch.draw_circle(circle.get_position(), circle.get_size().x, circle.get_sections(), circle.get_color());
              m_batch.draw_circle(static_circle.get_position(), static_circle.get_size().x, static_circle.get_sections(), static_circle.get_color());
              if (detector.collision(circle, static_circle)) {
                  circle.set_color(sf::Color::Green);
                  static_circle.set_color(sf::Color::Green);
              }
              else {
                  circle.set_color(sf::Color::Red);
                  static_circle.set_color(sf::Color::Red);
              }
              break;
          case State::CirclevsAABB:
              text.setString("Circle vs AABB");
 



              m_batch.draw_circle(m_mouse_position, circle.get_size().x, circle.get_sections(), circle.get_color());
              m_batch.draw_rectangle(static_aabb.get_rect(), static_aabb.get_color());
              if (detector.collision(circle, static_aabb)) {
                  circle.set_color(sf::Color::Green);
                  static_aabb.set_color(sf::Color::Green);
              }
              else {
                  circle.set_color(sf::Color::Red);
                  static_aabb.set_color(sf::Color::Red);
              }
              break;
          case State::CirclevsLine:
              text.setString("Circle vs Line Segment");


              m_batch.draw_circle(m_mouse_position, circle.get_size().x, circle.get_sections(), circle.get_color());
              m_batch.draw_line(static_line.get_points().from, static_line.get_points().to, 2, static_line.get_color());
              if (detector.collision(circle, static_line)) {
                  circle.set_color(sf::Color::Green);
                  static_line.set_color(sf::Color::Green);
              }
              else {
                  circle.set_color(sf::Color::Red);
                  static_line.set_color(sf::Color::Red);
              }
              break;
          case State::AABBvsAABB:
              text.setString("AABB vs AABB");

              aabb.set_rect(m_mouse_position, aabb.get_size()); //Have to do this here to update the rect


              m_batch.draw_rectangle(aabb.get_rect(), aabb.get_color());
              m_batch.draw_rectangle(static_aabb.get_rect(), static_aabb.get_color());
              if (detector.collision(aabb, static_aabb)) {
                  aabb.set_color(sf::Color::Green);
                  static_aabb.set_color(sf::Color::Green);
              }
              else {
                  aabb.set_color(sf::Color::Red);
                  static_aabb.set_color(sf::Color::Red);
              }
              break;
          default:
              break;
          }


      }
      
      m_window.clear(sf::Color{ 0x44, 0x55, 0x66, 0xff });
      m_window.draw(text);
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
           static_circle.set_size(rand() % 100 + 20.0f, 0);
           static_circle.set_position(sf::Vector2f(rand() % 1000 + static_circle.get_size().x, rand() % 1000 + static_circle.get_size().x));
           circle.set_color(sf::Color::Red);
           static_circle.set_color(sf::Color::Red);
       }
       else if (key == sf::Keyboard::Key::Num2) {
           //Circle vs Axis-aligned bounding box
           state = State::CirclevsAABB;
           static_aabb.set_rect(sf::Vector2f(rand() % 1000 + static_aabb.get_size().x, rand() % 1000 + static_aabb.get_size().y), static_aabb.get_size());
           static_aabb.set_size(rand() % 50 + 20.0f, 50);
           circle.set_color(sf::Color::Red);
           static_aabb.set_color(sf::Color::Red);
       }
       else if (key == sf::Keyboard::Key::Num3)
       {
           //Circle vs line segment
           state = State::CirclevsLine;
           static_line.set_points(sf::Vector2f(rand() % 1000 + 1.0f, rand() % 1000 + 1.0f), sf::Vector2f(rand() % 1000 + 1.0f, rand() % 1000 + 1.0f));
           circle.set_color(sf::Color::Red);
           static_line.set_color(sf::Color::Red);

       }
       else if (key == sf::Keyboard::Key::Num4) {
           //Axis-aligned bounding box vs Axis-aligned bounding box
           state = State::AABBvsAABB;
           static_aabb.set_rect(sf::Vector2f(rand() % 1000 + static_aabb.get_size().x, rand() % 1000 + static_aabb.get_size().y), static_aabb.get_size());
           static_aabb.set_size(rand() % 50 + 20.0f, 50);
           aabb.set_color(sf::Color::Red);
           static_aabb.set_color(sf::Color::Red);

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
