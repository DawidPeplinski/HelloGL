/*
 * robotPPP.h
 *
 *  Created on: 27 Nov 2018
 *      Author: davca
 */

#ifndef ROBOTPPP_H_
#define ROBOTPPP_H_

#include "cuboid.h"

#define EPS 0.0001

class RobotPPP {
public:
	RobotPPP(float len, float width) :
	cuboid_x { glm::vec3(width, width, len) },
	cuboid_y { glm::vec3(len, width, width) },
	cuboid_z { glm::vec3(width, len/2.0, width) },
	min_xy(-len/2.0 + width/2.0),
	min_z(len/4.0 - width/2.0),
	max_xy(-min_xy),
	max_z(-min_z),
	curr_pos(glm::vec3(0, 0, 0)),
	curr_target(curr_pos) {
		SetPos(curr_pos);
	}

	void Draw(Shader& shader, Camera& camera) {
		glm::vec3 dist(glm::vec3(curr_pos.x - curr_target.x, curr_pos.y - curr_target.y, curr_pos.z - curr_target.z));
		if(abs(dist.x) > EPS) {
			float mult = EPS*50.0;
//			if(abs(dist.x) < 0.1) {
//				mult = (1.0 - cosf(10.0*dist.x*M_PI/2.0))*mult;
//			}
			curr_pos.x += (dist.x > 0) ? -1.0*mult : mult;
		}
		if(abs(dist.y) > EPS) {
			float mult = EPS*50.0;
//			if(abs(dist.y) < 0.1) {
//				mult = (1.0 - cosf(10.0*dist.y*M_PI/2.0))*mult;
//			}
			curr_pos.y += (dist.y > 0) ? -1.0*mult : mult;
		}
		if(abs(dist.z) > EPS) {
			float mult = EPS*50.0;
//			if(abs(dist.z) < 0.1) {
//				mult = (1.0 - cosf(10.0*dist.z*M_PI/2.0))*mult;
//			}
			curr_pos.z += (dist.z > 0) ? -1.0*mult : mult;
		}
		SetPos(curr_pos);

		cuboid_x.Draw(shader, camera);
		cuboid_y.Draw(shader, camera);
		cuboid_z.Draw(shader, camera);
	}

	void SetTarget(glm::vec3 target) {
		curr_target = target;
	}

protected:
private:
	Cuboid cuboid_x;
	Cuboid cuboid_y;
	Cuboid cuboid_z;
	const float min_xy;
	const float min_z;
	const float max_xy;
	const float max_z;
	glm::vec3 curr_pos;
	glm::vec3 curr_target;

	void SetPos(glm::vec3 pos) {
		float x = min_xy + pos.x*2.0*max_xy;
		float y = min_xy + pos.y*2.0*max_xy;
		float z = min_z + pos.z*4.0*max_z;
		cuboid_x.SetPos(glm::vec3(x, 0, 0));
		cuboid_y.SetPos(glm::vec3(0, 0, y));
		cuboid_z.SetPos(glm::vec3(x, z, y));
	}
};



#endif /* ROBOTPPP_H_ */
