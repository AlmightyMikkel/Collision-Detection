#include "collision_detection.h"
#include <cmath>



bool collision_detection::collision(object obj0, object obj1) {
	if (obj0.tag == tag::aabb && obj1.tag == tag::aabb) {
		if (obj0.get_rect().left < obj1.get_rect().left + obj1.get_rect().width &&
			obj0.get_rect().left + obj0.get_rect().width > obj1.get_rect().left &&
			obj0.get_rect().top < obj1.get_rect().top + obj1.get_rect().height &&
			obj0.get_rect().top + obj0.get_rect().height > obj1.get_rect().top) {
			return true;
		}
		else { return false; }

	}
	if (obj0.tag == tag::circle && obj1.tag == tag::circle) {
		float x_distance = obj0.get_position().x - obj1.get_position().x;
		float y_distance = obj0.get_position().y - obj1.get_position().y;
		float distance = sqrt((x_distance * x_distance) + (y_distance * y_distance));
		if (distance <= obj0.get_size().x + obj1.get_size().x) {
			return true;
		}
		else { return false; }
	}

	if (obj0.tag == tag::circle && obj1.tag == tag::line) { //This dont work

		float x_distance = obj1.get_points().from.x - obj1.get_points().to.x;
		float y_distance = obj1.get_points().from.y - obj1.get_points().to.y;
		float length = sqrt((x_distance * x_distance) + (y_distance * y_distance));

		float dot_product = (((obj0.get_position().x - obj1.get_points().from.x) * (obj1.get_points().to.x - obj1.get_points().from.x)) +
			((obj0.get_position().y - obj1.get_points().from.y) * (obj1.get_points().to.y - obj1.get_points().from.y))) / (float)pow(length, 2);

		float closest_xpoint = obj1.get_points().from.x + (dot_product * (obj1.get_points().to.x - obj1.get_points().from.x));
		float closest_ypoint = obj1.get_points().from.y + (dot_product * (obj1.get_points().to.y - obj1.get_points().from.y));


		x_distance = closest_xpoint - obj0.get_position().x;
		y_distance = closest_ypoint - obj0.get_position().y;

		float distance = sqrt((x_distance * x_distance) + (y_distance * y_distance));

		if (distance <= obj0.get_size().x) {
			return true;
		}
		else { return false; }

	}


	if (obj0.tag == tag::circle && obj1.tag == tag::aabb) { //This dont work
		float closest_xedge = obj0.get_position().x;
		float closest_yedge = obj0.get_position().y;
		if (obj0.get_position().x < obj1.get_rect().left) {
			closest_xedge = obj1.get_rect().left;
		}
		else if (obj0.get_position().x > obj1.get_rect().left + obj1.get_rect().width) {
			closest_xedge = obj1.get_rect().left + obj1.get_rect().width;
		}
		if (obj0.get_position().y < obj1.get_rect().top) {
			closest_yedge = obj1.get_rect().top;
		}
		else if (obj0.get_position().y > obj1.get_rect().top + obj1.get_rect().height) {
			closest_yedge = obj1.get_rect().top + obj1.get_rect().height;
		}

		float x_distance = obj0.get_position().x - closest_xedge;
		float y_distance = obj0.get_position().y - closest_yedge;
		float distance = sqrt((x_distance * x_distance) + (y_distance * y_distance));

		if (distance <= obj0.get_size().x) {
			return true;
		}
		else { return false; }

	}
	else {
		return false;
	}
}