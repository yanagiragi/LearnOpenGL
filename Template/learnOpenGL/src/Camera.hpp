#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

	public:
		const float M_PI = 3.14;

		float eyex = 0.0;
		float eyey = 0.0;
		float eyez = 6.0;
		float eyet = 0.0;	//theta in degree
		float eyep = 90.0;	//phi in degree

		float step = 0.1;

		Camera()
		{

		}

		~Camera()
		{

		}

		glm::mat4 getV()
		{
			glm::vec3 cameraPos = glm::vec3(eyex, eyey, eyez);
			glm::vec3 cameraFront = glm::vec3(cos(eyet*M_PI / 180)*cos(eyep*M_PI / 180), sin(eyet*M_PI / 180), -1.0 * cos(eyet*M_PI / 180)*sin(eyep*M_PI / 180));
			glm::vec3 cameraRight = glm::vec3(0.0, 1.0, 0.0);
			return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraRight);
		}

		glm::mat4 getP()
		{
			float fov = 45.0f;
			float aspect = 1.0 / 1.0f; // since window is (512, 512)
			float nearDistance = 0.1f;
			float farDistance = 1000.0f;
			return glm::perspective(glm::radians(fov), aspect, nearDistance, farDistance);
		}
};

#endif // !_CAMERA_HPP
